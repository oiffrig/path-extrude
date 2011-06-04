/*
 * matrix.h - Operations on 3D matrices
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

#ifndef _I_MATRIX_H_
#define _I_MATRIX_H_

#include <string>

#include "geometry.h"

class Matrix {
public:
    double coeffs[3][3];

    Matrix();
    Matrix(const Vector c1, const Vector c2, const Vector c3);
    Matrix(const Matrix &M);

    Matrix operator +();
    Matrix operator -();

    Matrix operator +(Matrix B);
    Matrix operator -(Matrix B);
    Matrix operator *(Matrix B);

    Vector operator *(Vector X);

    double Det();
    Matrix Invert();

    void AssignColumns(const Vector c1, const Vector c2, const Vector c3);

    std::string *dump();
};

Matrix operator *(double k, Matrix M);

#endif

