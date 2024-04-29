// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef TRIANGLE_WM_H_GUARD
#define TRIANGLE_WM_H_GUARD

#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "mesh.h"
#include "point.h"

class mesh;
class point;

class triangle_wm {
private:
  int vertex_1;
  int vertex_2;
  int vertex_3; //Vertex indices, not coordinates.
  mesh* mesh_pt;
  void check_side( point& point_on_the_boundary_1, point& point_on_the_boundary_2, point& point_inside );
  int get_angle( point& point_1, point& point_2, point& point_3 );
public:
  double get_centroid_x();
  double get_centroid_y();
  triangle_wm( mesh* mesh_address ){ mesh_pt = mesh_address; };
  triangle_wm(int v_1, int v_2, int v_3, mesh* mesh_address );
  point get_whole_centroid();
  void write( std::ostream& fout );
  int get_vertex_1();
  int get_vertex_2();
  int get_vertex_3();
  point compute_circumcenter();
  double compute_area();
  void check_the_boundary();
  void add_angles_to_vector( std::vector< int > &angle_vector );
  void add_point_inside( float& new_x, float& new_y );
  //double get_centroid_x();
  //double get_centroid_y();
};
#endif//TRIANGLE_WM_H_GUARD
