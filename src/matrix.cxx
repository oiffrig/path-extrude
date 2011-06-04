/*
 * matrix.cxx - Operations on 3D matrices
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

#include <cstdio>

#include "matrix.h"

Matrix::Matrix() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            this->coeffs[i][j] = 0.;
}

Matrix::Matrix(const Vector c1, const Vector c2, const Vector c3) {
    this->AssignColumns(c1, c2, c3);
}

Matrix::Matrix(const Matrix &M) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            this->coeffs[i][j] = M.coeffs[i][j];
}

Matrix Matrix::operator +() {
    return Matrix(*this);
}

Matrix Matrix::operator -() {
    Matrix M;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            M.coeffs[i][j] = -this->coeffs[i][j];
    return M;
}

Matrix Matrix::operator +(Matrix B) {
    Matrix M;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            M.coeffs[i][j] = this->coeffs[i][j] + B.coeffs[i][j];
    return M;
}

Matrix Matrix::operator -(Matrix B) {
    Matrix M;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            M.coeffs[i][j] = this->coeffs[i][j] - B.coeffs[i][j];
    return M;
}

Matrix Matrix::operator *(Matrix B) {
    Matrix M;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                M.coeffs[i][j] += this->coeffs[i][k] * B.coeffs[k][j];
    return M;
}

Vector Matrix::operator *(Vector X) {
    Vector Y;
    double xc[3] = {X.x, X.y, X.z};
    double yc[3] = {0., 0., 0.};

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            yc[i] += this->coeffs[i][j] * xc[j];
    Y.x = yc[0];
    Y.y = yc[1];
    Y.z = yc[2];
    return Y;
}

double Matrix::Det() {
    return this->coeffs[0][0] * (this->coeffs[1][1] * this->coeffs[2][2] - this->coeffs[1][2] * this->coeffs[2][1])
         + this->coeffs[0][1] * (this->coeffs[2][0] * this->coeffs[1][2] - this->coeffs[1][0] * this->coeffs[2][2])
         + this->coeffs[0][2] * (this->coeffs[1][0] * this->coeffs[2][1] - this->coeffs[2][0] * this->coeffs[1][1]);
}

Matrix Matrix::Invert() {
    Matrix M;
    double D = this->Det();
    M.coeffs[0][0] = 1. / D * (this->coeffs[1][1] * this->coeffs[2][2] - this->coeffs[2][1] * this->coeffs[1][2]);
    M.coeffs[0][1] = 1. / D * (this->coeffs[2][1] * this->coeffs[0][2] - this->coeffs[0][1] * this->coeffs[2][2]);
    M.coeffs[0][2] = 1. / D * (this->coeffs[0][1] * this->coeffs[1][2] - this->coeffs[1][1] * this->coeffs[0][2]);
    M.coeffs[1][0] = 1. / D * (this->coeffs[2][0] * this->coeffs[1][2] - this->coeffs[1][0] * this->coeffs[2][2]);
    M.coeffs[1][1] = 1. / D * (this->coeffs[0][0] * this->coeffs[2][2] - this->coeffs[2][0] * this->coeffs[0][2]);
    M.coeffs[1][2] = 1. / D * (this->coeffs[1][0] * this->coeffs[0][2] - this->coeffs[0][0] * this->coeffs[1][2]);
    M.coeffs[2][0] = 1. / D * (this->coeffs[1][0] * this->coeffs[2][1] - this->coeffs[2][0] * this->coeffs[1][1]);
    M.coeffs[2][1] = 1. / D * (this->coeffs[2][0] * this->coeffs[0][1] - this->coeffs[0][0] * this->coeffs[2][1]);
    M.coeffs[2][2] = 1. / D * (this->coeffs[0][0] * this->coeffs[1][1] - this->coeffs[1][0] * this->coeffs[0][1]);
    return M;
}

void Matrix::AssignColumns(const Vector c1, const Vector c2, const Vector c3) {
    this->coeffs[0][0] = c1.x;
    this->coeffs[0][1] = c2.x;
    this->coeffs[0][2] = c3.x;
    this->coeffs[1][0] = c1.y;
    this->coeffs[1][1] = c2.y;
    this->coeffs[1][2] = c3.y;
    this->coeffs[2][0] = c1.z;
    this->coeffs[2][1] = c2.z;
    this->coeffs[2][2] = c3.z;
}

std::string *Matrix::dump() {
    std::string *S = new std::string[3];
    char buf[25];

    for(int i = 0; i < 3; i++) {
        std::sprintf(buf, "%7g %7g %7g", this->coeffs[i][0], this->coeffs[i][1], this->coeffs[i][2]);
        S[i] = buf;
    }

    return S;
}

Matrix operator *(double k, Matrix M) {
    Matrix R;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            R.coeffs[i][j] = k * M.coeffs[i][j];
    return R;
}

