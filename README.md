<!--
SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
SPDX-License-Identifier: MIT
-->

WheezeMesh, a demonstration programme on CVT and ODT mesh optimization. Also enables conversion from *.node and *.ele format, used in Triangle, into *.mphtxt suitable for COMSOL Multiphysics 3.5a

=================================
==Installation:==
=================================
Requires Triangle installed and also Showme, if you want to visualise the results. Available at
http://www.cs.cmu.edu/~quake/triangle.html

Jonathan Richard Shewchuk, Triangle: Engineering a 2D Quality Mesh Generator and Delaunay Triangulator, in ``Applied Computational Geometry: Towards Geometric Engineering'' (Ming C. Lin and Dinesh Manocha, editors), volume 1148 of Lecture Notes in Computer Science, pages 203-222, Springer-Verlag, Berlin, May 1996. (From the First ACM Workshop on Applied Computational Geometry.)

Then g++ *.cpp shall do the rest (I use the uptodate version on 13.04.2012).

=================================
==Usage:==
=================================
A menu in the console should appear and let you chose, what to do. Note that with more points inside the programme is likely to crash,
while (probably) there appear situations of three colinear points, causing problems with computation of the centroid.