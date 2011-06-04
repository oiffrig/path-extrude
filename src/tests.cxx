/*
 * tests.cxx - Test models
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

#include "path_extrude.h"
#include "paths.h"
#include "tests.h"

Polygon gen_circle_xz(Point center, double radius) {
    Polygon poly;
    double t = 0, dt = 2. * M_PI / 100.;

    for(int i = 0; i < 100; i++) {
        t = i*dt;
        Vector V(radius * std::cos(t), 0., radius * std::sin(t));
        poly.push_back(center + V);
    }

    return poly;
}

Polygon gen_rectangle_xz(Point center, double width, double height) {
    Polygon poly;
    double a = width / 2.;
    double b = height / 2.;

    poly.push_back(center + Vector(a, 0, b));
    poly.push_back(center + Vector(-a, 0, b));
    poly.push_back(center + Vector(-a, 0, -b));
    poly.push_back(center + Vector(a, 0, -b));
    poly.push_back(center + Vector(a, 0, b));

    return poly;
}

Object pipe() {
    Polygon poly = gen_circle_xz(Point(0, 0, 0), 1);
    Path l1 = path_line(Point(0, 0, 0), Point(0, 5, 0), 100);
    Path c1 = path_arc(0., 0.5 * M_PI, 2., Point(-2, 5, 0), 100);
    Path p1 = path_concat(l1, c1);

    Path l2 = path_line(Point(1, 0, 0), Point(1, 5, 0), 100);
    Path c2 = path_arc(0., 0.5 * M_PI, 3., Point(-2, 5, 0), 100);
    Path p2 = path_concat(l2, c2);

    return path_extrude(poly, p1, p2, true);
}

Object ell_torus() {
    Polygon poly = gen_circle_xz(Point(3, 0, 0), 1);
    Path e1 = path_ell_arc(0., 1.5 * M_PI, 3., 2., Point(0, 0, 0), 100);
    Path e2 = path_ell_arc(0., 1.5 * M_PI, 3., 2., Point(0, 0, 1), 100);

    return path_extrude(poly, e1, e2, true);
}

Object funnel() {
    Polygon poly = gen_circle_xz(Point(0, 0, 0), 3);

    Path l1 = path_line(Point(0, 0, 0), Point(0, 6, 0), 200);

    Path l2 = path_line(Point(3, 0, 0), Point(0.5, 3, 0), 100);
    Path l3 = path_line(Point(0.5, 3, 0), Point(0.25, 6, 0), 100);
    Path p2 = path_concat(l2, l3);

    return path_extrude(poly, l1, p2, true);
}

Object spring() {
    Polygon poly = gen_rectangle_xz(Point(2, 0, 0), 0.5, 0.25);

    Path h1 = path_helix(0., 10. * 2. * M_PI, 2., 10., Point(0, 0, 0), 1000);
    Path h2 = path_helix(0., 10. * 2. * M_PI, 2., 10., Point(0, 0, 1), 1000);

    return path_extrude(poly, h1, h2, true);
}

std::vector<Test_script> get_tests() {
    std::vector<Test_script> tests;
    Test_script test;

    test.name = "pipe";
    test.description = "A pipe";
    test.callback = pipe;
    tests.push_back(test);

    test.name = "ell_torus";
    test.description = "An (open) elliptic torus";
    test.callback = ell_torus;
    tests.push_back(test);

    test.name = "funnel";
    test.description = "A funnel";
    test.callback = funnel;
    tests.push_back(test);

    test.name = "spring";
    test.description = "A spring";
    test.callback = spring;
    tests.push_back(test);

    return tests;
};

