// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef TRIANGLE_WM_CPP_GUARD
#define TRIANGLE_WM_CPP_GUARD

#include "triangle_wm.h"

triangle_wm::triangle_wm( int v_1, int v_2, int v_3, mesh* mesh_address ) : vertex_1( v_1 ), vertex_2( v_2 ), vertex_3( v_3 )
{
  /* Just a constructor. */
  mesh_pt = mesh_address;
}


double triangle_wm::get_centroid_x()
{
  /* Computes the x coordinate of triangle's centroid. */
  double return_value;
  return_value 	= (mesh_pt -> get_point_from_vector( vertex_1 ) ).get_x();
  return_value += (mesh_pt -> get_point_from_vector( vertex_2 ) ).get_x();
  return_value += (mesh_pt -> get_point_from_vector( vertex_3 ) ).get_x();
  return return_value / 3;
}

double triangle_wm::get_centroid_y()
{
  /* Computes the y coordinate of triangle's centroid. */
  double return_value;
  return_value 	= (mesh_pt -> get_point_from_vector( vertex_1 ) ).get_y();
  return_value += (mesh_pt -> get_point_from_vector( vertex_2 ) ).get_y();
  return_value += (mesh_pt -> get_point_from_vector( vertex_3 ) ).get_y();
  return return_value / 3;
}


point triangle_wm::get_whole_centroid()
{
  /* Returns a point, which is a centroid of the triangle. */
  point point_to_return( 0, 0, 1, 0 );
  
  double new_x = get_centroid_x();
  double new_y = get_centroid_y();
  
  point_to_return.change_coordinates( new_x, new_y );
  return point_to_return;
}

point triangle_wm::compute_circumcenter()
{
  /* Computes circumcenter of a triangle by choosing two sides and finding an intersection of their perpendicular bisectors. */
  point& p1 = mesh_pt -> get_point_from_vector( vertex_1 );
  point& p2 = mesh_pt -> get_point_from_vector( vertex_2 );
  point& p3 = mesh_pt -> get_point_from_vector( vertex_3 );
  
  // 2
  direction dir_1( p2, p1 );
  dir_1.turn_90();
  direction dir_2( p3, p2 );
  dir_2.turn_90();
  
  // 1
  point mid_1 = p1.halfway_to( p2 );
  point mid_2 = p2.halfway_to( p3 );
  
  // 3
  try
  {
    matrix LHS( dir_1.get_x(), dir_2.get_x(), - dir_1.get_y(), - dir_2.get_y() );
    
    if( ! LHS.regular() )
    {
      singular_matrix_exception e;
      throw e;
    }
    
    matrix Cramer_1( mid_2.get_x() - mid_1.get_x(), - dir_2.get_x(), mid_2.get_y() - mid_1.get_y(), - dir_2.get_y() );
    
    double line_parameter = Cramer_1.det() / LHS.det();
    
    // 4
    double circumcenter_x = mid_1.get_x() + line_parameter * dir_1.get_x();
    // 5
    double circumcenter_y = mid_1.get_y() + line_parameter * dir_1.get_y();
    
    // 6
    point circumcenter( circumcenter_x, circumcenter_y, 1, 0 );
    return circumcenter;
  }
  catch( std::exception& e )
  {
    std::cerr << "in compute_circumcenter() : " << e.what() << std::endl;
    throw e;
  }
}




void triangle_wm::write( std::ostream& fout )
{
  /* Used during testing to write point's coordinates. */
  fout << vertex_1 << " " << vertex_2 << " " << vertex_3 << std::endl;
}

/* Functions get_* show the private parts. */

int triangle_wm::get_vertex_1()
{
  return vertex_1;
}

int triangle_wm::get_vertex_2()
{
  return vertex_2;
}

int triangle_wm::get_vertex_3()
{
  return vertex_3;
}

double triangle_wm::compute_area()
{
  // Computing the area of the triangle according to
  // http://en.wikipedia.org/wiki/Triangle_%28geometry%29#Using_coordinates
  
  double x_1 = (mesh_pt -> get_point_from_vector( vertex_1 ) ).get_x();
  double y_1 = (mesh_pt -> get_point_from_vector( vertex_1 ) ).get_y();
  
  double x_2 = (mesh_pt -> get_point_from_vector( vertex_2 ) ).get_x();
  double y_2 = (mesh_pt -> get_point_from_vector( vertex_2 ) ).get_y();
  
  double x_3 = (mesh_pt -> get_point_from_vector( vertex_3 ) ).get_x();
  double y_3 = (mesh_pt -> get_point_from_vector( vertex_3 ) ).get_y();
  
  double area = 0;
  area += x_1 * y_2 - x_1 * y_3;
  area += x_2 * y_3 - x_2 * y_1;
  area += x_3 * y_1 - x_3 * y_2;
  
  area = area * 0.5;
  return area;
  
}

void triangle_wm::check_side( point& point_on_the_boundary_1, point& point_on_the_boundary_2, point& point_inside )
{
  /* If point_on_the_boundary_1 and point_on_the_boundary_2 are really on the boundary, find intersection of their axis in the other
  halfplane, than point_inside and add this intersection into voronoi_cells_corners of point_on_the_boundary_1 and point_on_the_boundary_2.*/
  
  if( point_on_the_boundary_1.get_boundary_marker() == 0 || point_on_the_boundary_2.get_boundary_marker() == 0 )
    return;
  // So if not returned, those two points are really on the boundary.
  
  // Find the axis now.
  // Axis = (x_s, y_s) + t ( x_v, y_v );
  double x_s = 0.5 * ( point_on_the_boundary_1.get_x() + point_on_the_boundary_2.get_x() );
  double y_s = 0.5 * ( point_on_the_boundary_1.get_y() + point_on_the_boundary_2.get_y() );
  
  double x_v = point_on_the_boundary_2.get_y() - point_on_the_boundary_1.get_y();
  double y_v = point_on_the_boundary_1.get_x() - point_on_the_boundary_2.get_x();
  
  // Intersection of a parametric line and implicit unit circle leads us to solving a quadratic equation
  // (x_s + t * x_v)^2 + (y_s + t * y_v)^2 = 1^2.
  double sqrt_diskriminant = 2 * x_s * x_v * y_s * y_v;
  sqrt_diskriminant -= x_v * x_v * y_s * y_s;
  sqrt_diskriminant -= y_v * y_v * x_s * x_s;
  sqrt_diskriminant += x_v * x_v; // * r * r but r = 1;
  sqrt_diskriminant += y_v * y_v; // again * r * r;
  sqrt_diskriminant = sqrt( sqrt_diskriminant );
  
  // t1 and t2 are values of the parameter of the intersection point.
  double t1 = - x_s * x_v - y_s * y_v;
  t1 += sqrt_diskriminant;
  t1 = t1 / (x_v * x_v + y_v * y_v );
  
  double t2 = - x_s * x_v - y_s * y_v;
  t2 -= sqrt_diskriminant;
  t2 = t2 / (x_v * x_v + y_v * y_v );
  
  // We need to choose one of them. We divide the plane into two halfplanes by the line (point_on_the_boundary_1, point_on_the_boundary_2).
  // Then we choose the one in the other halfplane than the point_inside.
  // The line shall be sought in the form y + slope * x + intercept = 0.
  
  double slope = ( point_on_the_boundary_1.get_y() - point_on_the_boundary_2.get_y() ) / ( point_on_the_boundary_2.get_x() - point_on_the_boundary_1.get_x() );
  double intercept = - point_on_the_boundary_1.get_y() - slope * point_on_the_boundary_1.get_x();
  
  
  point* candidate_1 = new point( x_s + t1 * x_v, y_s + t1 * y_v, 1, 1 );
  point* candidate_2 = new point( x_s + t2 * x_v, y_s + t2 * y_v, 1, 1 );
  
  if( ( candidate_1 -> get_y() + slope * candidate_1 -> get_x() + intercept ) * (point_inside.get_y() + slope * point_inside.get_x() + intercept ) < 0 )
  {
    // Their product is negative, so they're on two different sides.
    point_on_the_boundary_1.add_voronoi_corner( candidate_1 );
    point_on_the_boundary_2.add_voronoi_corner( candidate_1 );
  }
  
  else
  {
    // They are on the same side, so choose the candidate_2.
    point_on_the_boundary_1.add_voronoi_corner( candidate_2 );
    point_on_the_boundary_2.add_voronoi_corner( candidate_2 );
  }
}

void triangle_wm::check_the_boundary()
{
  /* If the triangle_wm is not on the boundary, do nothing.
  If it is, find the intersection of the boundary side axis and the boundary of the whole region.
  Then add it to Voronoi cells corners of the boundary vertices. */
  
  
  // [1] Find, if there are two vertices on the boundary. If yes, store pointers for them.
  //   Well and what if there are three of them? More work should be done there then.
  point& v1 = mesh_pt -> get_point_from_vector( vertex_1 );
  point& v2 = mesh_pt -> get_point_from_vector( vertex_2 ); 
  point& v3 = mesh_pt -> get_point_from_vector( vertex_3 );
  
  check_side( v1, v2, v3 );
  check_side( v2, v3, v1 );
  check_side( v3, v1, v2 );
  
  /*
  point* boundary_vertex_0;
  point* boundary_vertex_1;
  point* inside_vertex;
  
  if( v1.get_boundary_marker() != 0 && v2.get_boundary_marker() != 0 )
  {
    boundary_vertex_0 = &v1;
    boundary_vertex_1 = &v2;
    inside_vertex = &v3;
  }
  else if( v2.get_boundary_marker() != 0  && v3.get_boundary_marker() != 0 )
  {
    inside_vertex = &v1;
    boundary_vertex_0 = &v2;
    boundary_vertex_1 = &v3;
  }
  else if( v3.get_boundary_marker() != 0 && v1.get_boundary_marker() != 0 )
  {
    boundary_vertex_1 = &v1;
    inside_vertex = &v2;
    boundary_vertex_0 = &v3;
  }
  else
    return; // Less, than two boundary vertices.
    
  
  // [2] Find axis of the boundary side.
  //direction dir_perpendicular_to_boundary_side( *boundary_vertex_1, *boundary_vertex_0 ); // vector( bv_1 - bv_0 ), i.e. vector in the direction of the boundary side
  //dir_perpendicular_to_boundary_side.turn_90(); // vector perpendicular to the boundary side
  point middle = boundary_vertex_0 -> halfway_to( *boundary_vertex_1 );
  
  
  // [3] Find intersections of the axis and the implicit formula defining the domain.
    // intersections shall be denoted
    // p1 = middle + t1 * dir_perpendicular_to_boundary_side
    // p2 = middle + t2 * dir_perpendicular_to_boundary_side
  
  double x_s = middle.get_x();
  double y_s = middle.get_y();
  double x_v = boundary_vertex_1 -> get_y () - boundary_vertex_0 -> get_y();
  //dir_perpendicular_to_boundary_side.get_x();
  double y_v =  boundary_vertex_0 -> get_x() - boundary_vertex_1 -> get_x();
  //dir_perpendicular_to_boundary_side.get_y();
  
  double sqrt_diskriminant = 2 * x_s * x_v * y_s * y_v;
  sqrt_diskriminant -= x_v * x_v * y_s * y_s;
  sqrt_diskriminant -= y_v * y_v * x_s * x_s;
  sqrt_diskriminant += x_v * x_v; // * r * r but r = 1;
  sqrt_diskriminant += y_v * y_v; // again * r * r;
  sqrt_diskriminant = sqrt( sqrt_diskriminant );
  
  double t1 = - x_s * x_v - y_s * y_v;
  t1 += sqrt_diskriminant;
  t1 = t1 / (x_v * x_v + y_v * y_v );
  
  double t2 = - x_s * x_v - y_s * y_v;
  t2 -= sqrt_diskriminant;
  t2 = t2 / (x_v * x_v + y_v * y_v );
  
  
  // [4] Check in which halfplane lies the third vertex of the triangle.
    // [4.1] Find the equation of the boundary line.
    // [4.2] Check the sign of the halfplane with the third vertex.
    // [4.3] Remember it.
    
  double slope = ( boundary_vertex_0 -> get_y() - boundary_vertex_1 -> get_y() ) / ( boundary_vertex_0 -> get_x() - boundary_vertex_1 -> get_x() );
  double intercept = - boundary_vertex_0 -> get_x() * slope - boundary_vertex_0 -> get_y();
  
  double third_vertex_height = inside_vertex -> get_y() + slope * ( inside_vertex -> get_x() ) + intercept;
  
  point* point_on_the_boundary_1 = new point( middle.get_x() + t1 * x_v, middle.get_y() + t1 * y_v, 1, 1 );
  point* point_on_the_boundary_2 = new point( middle.get_x() + t2 * x_v, middle.get_y() + t2 * y_v, 1, 1 );
  
  double pb_1_height = point_on_the_boundary_1 -> get_y() + slope * ( point_on_the_boundary_1 -> get_x() ) + intercept;
  // [5] Choose the intersection in the other halfplane.
  
  if( third_vertex_height * pb_1_height < 0 ) // Their signs are opposite =).
  {
    boundary_vertex_0 -> add_voronoi_corner( point_on_the_boundary_1 );
    boundary_vertex_1 -> add_voronoi_corner( point_on_the_boundary_1 );
    delete point_on_the_boundary_2;
  }
    
  else
  {
    boundary_vertex_0 -> add_voronoi_corner( point_on_the_boundary_2 );
    boundary_vertex_1 -> add_voronoi_corner( point_on_the_boundary_2 );
    delete point_on_the_boundary_1;
  }
  */
  // Let's see, if it works =).
}

int triangle_wm::get_angle( point& point_1, point& point_2, point& point_3 )
{
  /* Returns the size of the angle point_1, point_2, point_3 rounded to int.
  In degrees. */
  direction dir_1( point_1, point_2 );
  direction dir_2( point_2, point_3 );
  
  double result = dir_1.scalar_product( &dir_2 );
  result = result / dir_1.norm();
  result = result / dir_2.norm();
  
  result = acos( result ); // In radians!
  result = result * 90 / 3.1415926535;
  
  return (int)(result);
  /* TODO: archivovat arccos vrati
  /* triangle_wm.cpp:318: error: ‘arccos’ was not declared in this scope
  spravne je samozrejme acos, akorat to az tak samozrejme neni =). */
}
  
void triangle_wm::add_angles_to_vector( std::vector< int > &angle_vector )
{
  /* Computation of statistics on mesh angles is ready, however not linked from the menu. */
  point& v1 = mesh_pt -> get_point_from_vector( vertex_1 );
  point& v2 = mesh_pt -> get_point_from_vector( vertex_2 );
  point& v3 = mesh_pt -> get_point_from_vector( vertex_3 );
  
  angle_vector[ get_angle( v1, v2, v3 ) ] ++;
  angle_vector[ get_angle( v2, v3, v1 ) ] ++;
  angle_vector[ get_angle( v3, v1, v2 ) ] ++;
}

void triangle_wm::add_point_inside( float& new_x, float& new_y )
{
  /* Enables adding one point on a random place inside the triangle by returning random coordinates inside this triangle_wm.
  The technique comes from the idea of barycentric coordinates. */
  srand((unsigned)time(0));
  float rand_1 = (float)rand()/(float)RAND_MAX;
  float rand_2 = (float)rand()/(float)RAND_MAX;
  float rand_3 = 1 - rand_1 - rand_2;
  
  point& point_1 = mesh_pt -> get_point_from_vector( vertex_1 );
  point& point_2 = mesh_pt -> get_point_from_vector( vertex_2 );
  point& point_3 = mesh_pt -> get_point_from_vector( vertex_3 );
  
  new_x = point_1.get_x() * rand_1 + point_2.get_x() * rand_2 + point_3.get_x() * rand_3;
  new_y = point_1.get_y() * rand_1 + point_2.get_y() * rand_2 + point_3.get_y() * rand_3;
}
 
#endif//TRIANGLE_WM_CPP_GUARD
