#!/bin/bash
##
## Copyright (c) 2019 alpha group, CS department, University of Torino.
## 
## This file is part of pico 
## (see https://github.com/alpha-unito/pico).
## 
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
## 
## You should have received a copy of the GNU Lesser General Public License
## along with this program. If not, see <http://www.gnu.org/licenses/>.
##


# generate input files
echo "> generating input data"
cd testdata
make
if [ ! -f lines.txt ]; then
./generate_lines dictionary.txt 1k > lines.txt
fi
if [ ! -f pairs.txt ]; then
./generate_pairs 1k > pairs.txt
fi
if [ ! -f pairs_64.txt ]; then
./generate_pairs 64 > pairs_64.txt
fi
cd ..
