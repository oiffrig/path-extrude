/*
 * geometry.h - Basic 3D geometry
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

#ifndef _I_GEOMETRY_H_
#define _I_GEOMETRY_H_

#include <cstdio>
#include <list>
#include <string>
#include <utility>

class Vector {
public:
    double x, y, z;

    Vector();
    Vector(double x, double y, double z);
    Vector(const Vector &V);

    Vector operator +();
    Vector operator -();

    Vector operator +(const Vector V);
    Vector operator -(const Vector V);

    Vector operator +=(const Vector V);
    Vector operator -=(const Vector V);
    Vector operator *=(double k);

    Vector operator =(const Vector V);

    static double dot(Vector X, Vector Y);
    static Vector cross(Vector X, Vector Y);

    double norm();

    std::string dump();
};

Vector operator *(double k, Vector V);

class Point: public Vector {
public:
    
    Point(): Vector() {}
    Point(double x, double y, double z): Vector(x, y, z) {}
    Point(const Vector &V): Vector(V) {}
    Point(const Point &P): Vector((const Vector&)P) {}
};

class Triangle {
public:
    Point points[3];

    Triangle();
    Triangle(Point A, Point B, Point C);
    Triangle(const Triangle &T);

    Triangle operator =(const Triangle &T);

    Vector normal();
    void WriteSTL(FILE *s);
};

typedef std::list<Point> Polygon;

typedef std::list<Triangle> Object;

typedef std::list<std::pair<Point, Vector> > Path;

#endif

