<!--
SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
SPDX-License-Identifier: MIT
-->

# WheezeMesh
This is a demonstration programme about CVT (Centroidal Voronoi Tesellations) and ODT (Optimal Delaunay Triangulation) mesh optimization. Also enables conversion from *.node and *.ele format, used in [Triangle](http://www.cs.cmu.edu/~quake/triangle.html), into *.mphtxt suitable for COMSOL Multiphysics 3.5a

## About
Initially written as a final project for an advanced C++ course, it has been extended for my [master thesis](https://dspace.cuni.cz/handle/20.500.11956/40184) defended in 2012. It reflects my skill level back then and is not actively developed anymore.

## Prerequisities
Requires [Triangle](http://www.cs.cmu.edu/~quake/triangle.html) installed and also [Showme](http://www.cs.cmu.edu/~quake/showme.html) if you want to visualise the results. On Ubuntu both can be installed with
```
$ sudo apt install triangle-bin
```
Reference:
> Jonathan Richard Shewchuk, Triangle: Engineering a 2D Quality Mesh Generator and Delaunay Triangulator, in ``Applied Computational Geometry: Towards Geometric Engineering'' (Ming C. Lin and Dinesh Manocha, editors), volume 1148 of Lecture Notes in Computer Science, pages 203-222, Springer-Verlag, Berlin, May 1996. (From the First ACM Workshop on Applied Computational Geometry.)

## Installation
Executing
```
$ g++ *.cpp
```
should do the trick. Tested on Ubuntu on 2024-04-13.

## Usage
Start with
```
$ ./a.out
```
A menu in the console should appear and let you chose what to do. Note that with more points inside the programme is likely to crash,
while (probably) there appear situations of three colinear points, causing problems with computation of the centroid.

## Improvements that it would deserve
The program reflects my skills and knowledge back in 2012. There are a few improvements that it would deserve. For instance:

- Triangle should be dynamically linked instead of invoking it with the ```system``` command.
- A well-written ```CMakeLists.txt``` script would ensure more reliable and out-of-source build on any major platform.
- It should be separated into a library and an executable on top of it.
- Instead of the textual menus, the executable should work with command line parameters.
- In-source documentation should be made Doxygen-compatible.
