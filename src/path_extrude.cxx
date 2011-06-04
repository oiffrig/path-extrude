/*
 * path_extrude.cxx - Path extrusion algorithm
 *
 * Copyright (C) 2011 Olivier Iffrig
 * Authors: Olivier Iffrig <olivier@iffrig.eu>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "geometry.h"
#include "matrix.h"
#include "path_extrude.h"

#include <iostream>

Object path_extrude(Polygon poly, Path path, Path guide, bool close_ends) {
    Object obj;
    Polygon refpoly, oldp;
    Point path_fst, guide_fst;
    Vector refX, refY, refZ;
    Matrix refP, refPI;

    path_fst = path.front().first;
    guide_fst = guide.front().first;
    refZ = path.front().second;
    refZ *= 1. / refZ.norm();

    refX = guide_fst - path_fst;
    refY = Vector::cross(refZ, refX);

    //std::cout << "refX = (" << refX.dump() << "), refY = (" << refY.dump() << "), refZ = (" << refZ.dump() << ")" << std::endl;
    refP.AssignColumns(refX, refY, refZ);
    refPI = refP.Invert();
    //std::string *srefP = refP.dump();
    //std::string *srefPI = refPI.dump();
    //std::cout << "       ⎛" << srefP[0] << "⎞          ⎛" << srefPI[0] << "⎞" << std::endl
    //          << "refP = ⎜" << srefP[1] << "⎟, refPI = ⎜" << srefPI[1] << "⎟" << std::endl
    //          << "       ⎝" << srefP[2] << "⎠          ⎝" << srefPI[2] << "⎠" << std::endl;
    //delete[] srefP;
    //delete[] srefPI;

    for(Polygon::iterator poly_it = poly.begin(); poly_it != poly.end(); poly_it++) {
        refpoly.push_back((Point)(refPI * (*poly_it - path_fst)));
    }

    for(Path::iterator path_it = path.begin(), guide_it = guide.begin(); path_it != path.end(); path_it++, guide_it++) {
        Polygon newp;
        Point path_cur, guide_cur;
        Vector X, Y, Z;
        Matrix P;
        Point oldp_prev, newp_prev;

        path_cur = (*path_it).first;
        guide_cur = (*guide_it).first;
        Z = (*path_it).second;
        Z *= 1. / Z.norm();

        X = guide_cur - path_cur;
        Y = Vector::cross(Z, X);

        //std::cout << "X = (" << X.dump() << "), Y = (" << Y.dump() << "), Z = (" << Z.dump() << ")" << std::endl;

        P.AssignColumns(X, Y, Z);

        for(Polygon::iterator refpoly_it = refpoly.begin(); refpoly_it != refpoly.end(); refpoly_it++) {
            Point PP = path_cur + P * (*refpoly_it);
            //std::cout << "(" << (*refpoly_it).dump() << ") -> (" << PP.dump() << ")" << std::endl;
            newp.push_back(PP);
        }
        
        oldp_prev = oldp.back();
        newp_prev = newp.back();
        for(Polygon::iterator oldp_it = oldp.begin(), newp_it = newp.begin(); oldp_it != oldp.end() && newp_it != newp.end(); oldp_it++, newp_it++) {
            Triangle T1(oldp_prev, newp_prev, *newp_it);
            Triangle T2(oldp_prev, *oldp_it, *newp_it);

            obj.push_back(T1);
            obj.push_back(T2);

            oldp_prev = *oldp_it;
            newp_prev = *newp_it;
        }

        oldp = newp;
    }

    return obj;
}

