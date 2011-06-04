/*
 * paths.h - Basic paths
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

#ifndef _I_PATHS_H_
#define _I_PATHS_H_

#include "geometry.h"

Path path_line(Point start, Point end, int npoints);
Path path_arc(double start_angle, double end_angle, double radius, Point center, int npoints);
Path path_helix(double start_angle, double end_angle, double radius, double height, Point center, int npoints);
Path path_ell_arc(double start_angle, double end_angle, double a, double b, Point center, int npoints);

Path path_concat(Path p1, Path p2);

#endif

