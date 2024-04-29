// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef POINT_H_GUARD
#define POINT_H_GUARD

#include <fstream>
#include <vector>

#include "problem.h"
/* TODO archivovat: kdyz jsem tu zapomnel vector, vyprudilo me to, ze
point.h:16: error: ISO C++ forbids declaration of ‘vector’ with no type
point.h:16: error: invalid use of ‘::’
point.h:16: error: expected ‘;’ before ‘<’ token
*/

class point;
class problem;

class point {
private:
  double x_coord;
  double y_coord;
  int boundary_marker; // 0, if inside, number of the side, if on boundary
  double mass;
  
  std::vector< point* > sorrounding_voronoi_cell_corners;
  // Supporting data structure to see, in which Voronoi cell this point belongs. The cells shall be stored anticlockwise for further treatment.
  
  std::vector< point* > star_corners;
  // Supporting data structure for ODT
  
  bool turns_left( point* start_point, point* middle_point, point* end_point );
  bool outside( double x, double y );
public:
  point(){};
  /* TODO archivovat: kdyz zapomenu ty prazdne slozene zavorky za tim konstruktorem, vyhodi to
  /tmp/ccpR7ezq.o: In function `mesh::compute_voronoi_cells_corners()':
mesh.cpp:(.text+0xf51): undefined reference to `point::point()'
collect2: ld returned 1 exit status
*/
  
  point( double x, double y, double new_mass, int new_boundary_marker );
  void write_monitor( std::ostream& os ) const;
  void write_mph( std::ostream& fout );
  void write_stl( std::ostream& fout );
  void write_node( std::ostream& fout );
  double get_x() const;
  double get_y() const;
  double get_mass() const;
  int get_boundary_marker();
  void change_boundary_marker( int new_boundary_marker );
  void change_coordinates( double new_x, double new_y );
  void divide_coordinates( double denominator );
  
  void write_voronoi_corners( std::ostream& os );
  /* TODO archivovat: Kdyz se nakonec prida const, vyhodi to dost podivnou hlasku
  point.cpp: In member function ‘void point::write_voronoi_corners(std::ostream&) const’:
  point.cpp:90: error: conversion from ‘__gnu_cxx::__normal_iterator<point* const*, std::vector<point*, std::allocator<point*> > >’ to non-scalar type ‘__gnu_cxx::__normal_iterator<point**, std::vector<point*, std::allocator<point*> > >’ requested
  a to teda na radku, kde se to snazime prochazet iteratorem =).*/

  void add_voronoi_corner( point* new_corner );
  void move_to_voronoi_cell_centroid( problem* problem_pt );
  
  void add_star_corner( point* new_corner );
  void move_to_star_centroid( problem* problem_pt );

  point halfway_to( point& the_other_point );
  bool operator!=( const point& point_to_compare_with );
};

std::ostream& operator<<( std::ostream& os, const point& point_to_write );

#endif//POINT_H_GUARD
