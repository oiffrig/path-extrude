/*
 * geometry.cxx - Basic 3D geometry
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

#include <cmath>
#include <cstdio>

#include "geometry.h"

Vector::Vector() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vector::Vector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const Vector &V) {
    this->x = V.x;
    this->y = V.y;
    this->z = V.z;
}

Vector Vector::operator +() {
    return Vector(*this);
}

Vector Vector::operator -() {
    return Vector(-this->x, -this->y, -this->z);
}

Vector Vector::operator +(const Vector V) {
    return Vector(this->x + V.x, this->y + V.y, this->z + V.z);
}

Vector Vector::operator -(const Vector V) {
    return Vector(this->x - V.x, this->y - V.y, this->z - V.z);
}

Vector operator *(double k, Vector V) {
    return Vector(k * V.x, k * V.y, k * V.z);
}

Vector Vector::operator +=(const Vector V) {
    this->x += V.x;
    this->y += V.y;
    this->z += V.z;
    return *this;
}

Vector Vector::operator -=(const Vector V) {
    this->x -= V.x;
    this->y -= V.y;
    this->z -= V.z;
    return *this;
}

Vector Vector::operator *=(double k) {
    this->x *= k;
    this->y *= k;
    this->z *= k;
    return *this;
}

Vector Vector::operator =(const Vector V) {
    this->x = V.x;
    this->y = V.y;
    this->z = V.z;
    return *this;
}

double Vector::dot(Vector X, Vector Y) {
    return X.x * Y.x + X.y * Y.y + X.z * Y.z;
}

Vector Vector::cross(Vector X, Vector Y) {
    Vector V;
    V.x = X.y * Y.z - X.z * Y.y;
    V.y = X.z * Y.x - X.x * Y.z;
    V.z = X.x * Y.y - X.y * Y.x;
    return V;
}

double Vector::norm() {
    return std::sqrt(Vector::dot(*this, *this));
}

std::string Vector::dump() {
    char buf[16];
    std::string s;

    sprintf(buf, "%g", this->x);
    s += buf;
    s += ", ";
    sprintf(buf, "%g", this->y);
    s += buf;
    s += ", ";
    sprintf(buf, "%g", this->z);
    s += buf;

    return s;
}

Triangle::Triangle() {
}

Triangle::Triangle(Point A, Point B, Point C) {
    this->points[0] = A;
    this->points[1] = B;
    this->points[2] = C;
}

Triangle::Triangle(const Triangle &T) {
    for(size_t i = 0; i < 3; i++)
        this->points[i] = T.points[i];
}

Triangle Triangle::operator=(const Triangle &T) {
    for(size_t i = 0; i < 3; i++)
        this->points[i] = T.points[i];
    return *this;
}

Vector Triangle::normal() {
    Vector v1(this->points[1] - this->points[0]);
    Vector v2(this->points[2] - this->points[0]);
    Vector V = Vector::cross(v1, v2);
    double n = 1. / V.norm();
    return n * V;
}

void Triangle::WriteSTL(FILE *fd) {
    Vector N = this->normal();
    fprintf(fd, "  facet normal %e %e %e\n", N.x, N.y, N.z);
    fprintf(fd, "    outer loop\n");

    for(int i = 0; i < 3; i++)
        fprintf(fd, "      vertex %e %e %e\n", this->points[i].x, this->points[i].y, this->points[i].z);
    
    fprintf(fd, "    endloop\n");
    fprintf(fd, "  endfacet\n");
}

