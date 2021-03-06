/*
 * main.cxx - Main entry point for examples
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

#include "../src/geometry.h"
#include "examples.h"

#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    std::vector<Example_script> examples = get_examples();
    size_t i;

    std::cout << "Path extrusion examples" << std::endl;
    std::cout << "Choose which example you want to run:" << std::endl;

    for(i = 0; i < examples.size(); i++)
        std::cout << "    " << i+1 << "\t" << examples[i].name << "\t" << examples[i].description << std::endl;

    while(true) {
        std::cin >> i;
        if(i < 1 || i > examples.size())
            std::cout << "Invalid choice, retry" << std::endl;
        else
            break;
    }

    Example_script script = examples[i-1];

    std::string sline("solid "), fname(script.name);
    fname += ".stl";
    sline += script.name;
    sline += "\n";

    FILE *fd = fopen(fname.c_str(), "w");

    if(fd == NULL) {
        std::cout << "Cannot open " << fname << std::endl;
        return 1;
    }

    fprintf(fd, sline.c_str());

    Object obj = script.callback();

    for(Object::iterator it = obj.begin(); it != obj.end(); it++)
        (*it).WriteSTL(fd);

    fprintf(fd, "endsolid\n");
    fclose(fd);

    std::cout << "Result wrote to " << fname << std::endl;

    return 0;
}

