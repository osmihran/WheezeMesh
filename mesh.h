// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef MESH_H_GUARD
#define MESH_H_GUARD

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "point.h"
#include "triangle_wm.h"
#include "exceptions.h"
#include "direction.h"
#include "matrix.h"
#include "problem.h"

class test;
class triangle_wm;
class problem;

class mesh {
private:
  std::vector< point > point_vector;
  std::vector< point > voronoi_corners_vector;
  std::vector< triangle_wm > triangle_vector;
  
  problem* problem_pt;
  
  void insert_point( point new_point );
  void insert_triangle( int index_1, int index_2, int index_3 );
  
  void get_points_from_node( std::string node_file_name );
  void get_triangles_from_ele( std::string ele_file_name );
  
  void compute_voronoi_cells_corners();
  void compute_star_triangles_centroids();
  
  void write_to_file_mph( std::string filename );
  void write_to_file_stl( std::string filename );
  void write_to_file_node( std::string filename );
  
  double write_point_coordinates( int vertex_index );
public:
  mesh();
  void clear_mesh();
  void insert_point( double x_coordinate, double y_coordinate, int new_boundary_marker );
  
  void angle_statistics();
  int get_smallest_angle();
  
  void CVT_balance();
  void ODT_balance();
  
  void read_whole_mesh_from_node_and_ele( std::string file_name );
  void write_to_file( std::string filename, std::string extension );
  point& get_point_from_vector( int point_index );
  
  void create_domain( char option, int boundary_vertices );
  void refine( int nr_new_vertices );
};
#endif//MESH_H_GUARD
