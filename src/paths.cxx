/*
 * paths.cxx - Basic paths
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
#include "paths.h"

#include <cmath>

Path path_line(Point start, Point end, int npoints) {
    Path path;
    Vector dir(end - start);
    Vector dv = 1. / (npoints-1.) * dir;

    for(int i = 0; i < npoints; i++) {
        Point P(start + i*dv);
        path.push_back(std::make_pair(P, dir));
    }

    return path;
}

Path path_arc(double start_angle, double end_angle, double radius, Point center, int npoints) {
    Path path;
    double t = 0, dt = (end_angle - start_angle) / (npoints-1.);

    for(int i = 0; i < npoints; i++) {
        t = start_angle + i*dt;
        Vector V(radius * std::cos(t), radius * std::sin(t), 0.);
        Vector T(-radius * std::sin(t), radius * std::cos(t), 0.);

        path.push_back(std::make_pair(center + V, T));
    }

    return path;
}

Path path_helix(double start_angle, double end_angle, double radius, double height, Point center, int npoints) {
    Path path;
    double t = 0, dt = (end_angle - start_angle) / (npoints-1.);
    double z = 0, dz = height / (npoints-1.);

    for(int i = 0; i < npoints; i++) {
        t = start_angle + i*dt;
        z = i*dz;
        Vector V(radius * std::cos(t), radius * std::sin(t), z);
        Vector T(-radius * std::sin(t), radius * std::cos(t), dz/dt);

        path.push_back(std::make_pair(center + V, T));
    }

    return path;
}

Path path_ell_arc(double start_angle, double end_angle, double a, double b, Point center, int npoints) {
    Path path;
    double c = std::cos(start_angle), s = -std::sin(start_angle);
    double t = 0, dt = (end_angle - start_angle) / (npoints - 1.);
    double phi = std::atan(a/b * std::tan(start_angle));

    Matrix R(Vector(c, s, 0.), Vector(-s, c, 0.), Vector(0., 0., 1.));
    
    for(int i = 0; i < npoints; i++) {
        t = phi + i*dt;
        Vector V(a * std::cos(t), b * std::sin(t), 0.);
        Vector T(-a * std::sin(t), b * std::cos(t), 0.);

        path.push_back(std::make_pair(center + R*V, R*T));
    }

    return path;
}

Path path_concat(Path p1, Path p2) {
    Path res(p1);

    for(Path::iterator p2_it = p2.begin(); p2_it != p2.end(); p2_it++)
        res.push_back(*p2_it);
    
    return res;
}

Path path_translate(Path p, Vector v) {
    Path res;

    for(Path::iterator p_it = p.begin(); p_it != p.end(); p_it++)
        res.push_back(std::make_pair(p_it->first + v, p_it->second));

    return res;
}

Path path_transform(Path p, Matrix M) {
    Path res;

    for(Path::iterator p_it = p.begin(); p_it != p.end(); p_it++)
        res.push_back(std::make_pair(M * p_it->first, M * p_it->second));

    return res;
}

Path path_scale(Path p, Vector k) {
    Matrix M = Matrix::Diag(k);
    return path_transform(p, M);
}

Path path_scale(Path p, double k) {
    return path_scale(p, Vector(k, k, k));
}

Path path_rotate(Path p, Vector angles) {
    Matrix M = Matrix::RotationYPR(angles);
    return path_transform(p, M);
}

Path path_rotate(Path p, double angle, Vector n) {
    Vector k = (1. / n.norm()) * n;
    double c = std::cos(angle), s = std::sin(angle);
    Path res;

    for(Path::iterator p_it = p.begin(); p_it != p.end(); p_it++) {
        Vector a = p_it->first;
        Vector b = p_it->second;
        Vector cr_a = Vector::cross(k, a);
        double d_a = Vector::dot(k, a);
        Vector cr_b = Vector::cross(k, b);
        double d_b = Vector::dot(k, b);
        a = c * a + s * cr_a + d_a * (1 - c) * k;
        b = c * b + s * cr_b + d_b * (1 - c) * k;
        res.push_back(std::make_pair(a, b));
    }

    return res;
}

