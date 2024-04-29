// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef POINT_CPP_GUARD
#define POINT_CPP_GUARD

#include <vector>
#include <iostream>
/* TODO archivovat:
Kdyz se zapomene vlozit iostream, tak radek se std::cerr << (...) vyhazuje
point.cpp: In member function ‘void point::move_to_voronoi_cell_centroid()’:
point.cpp:100: error: ‘cerr’ is not a member of ‘std’
*/

#include "exceptions.h"
#include "point.h"

point::point( double x, double y, double new_mass, int new_boundary_marker ) : x_coord( x ), y_coord( y ), mass( new_mass ), boundary_marker( new_boundary_marker )
{
}

bool point::outside( double x, double y )
{
  /* Returns true, if x and y are outside the domain. */
  /* Uncomment the one, you'd like: */
  
  // Circle:
  // return ( x * x + y * y >= 1 );
  
  // Square:
  return ( x <= -10 || x >= 10 || y <= -1 || y >= 1 );
}

void point::write_monitor( std::ostream& os ) const
{
  os << "(" << x_coord << ", " << y_coord << "; " << boundary_marker << ")";
}
/* TODO archivovat: zmatek s const v argumentech a const za tim dava dost slozite chybkky =). */

void point::write_mph( std::ostream& fout)
{
  fout << x_coord << " " << y_coord << std::endl;
}

void point::write_stl( std::ostream& fout)
{
  fout << x_coord << " " << y_coord << " 0" << std::endl;
}

void point::write_node( std::ostream& fout )
{
  fout << x_coord << " " << y_coord << " " << boundary_marker << std::endl;
}

double point::get_x() const
{
  return x_coord;
}

double point::get_y() const
{
  return y_coord;
}

double point::get_mass() const
{
  return mass;
}

int point::get_boundary_marker()
{
  return boundary_marker;
}

void point::change_boundary_marker( int new_boundary_marker )
{
  boundary_marker = new_boundary_marker;
}

void point::change_coordinates( double new_x, double new_y )
{
  x_coord = new_x;
  y_coord = new_y;
}

void point::divide_coordinates( double denominator )
{
  x_coord = x_coord / denominator;
  y_coord = y_coord / denominator;
}

bool point::turns_left( point* start_point, point* middle_point, point* end_point )
{
  /* Tells, whether we are turning left or right in the middle_point when started in start_point and headed to end_point. */
  /* Method comes from Algorithm and data structures. */
  /* If no turning, (i.e. direct way), we consider it to be turning left. It shall be more convenient for the further treatment in Voronoi(...). */
  
  double lhs = ( middle_point -> get_y() - start_point -> get_y() ) * ( end_point -> get_x() - middle_point -> get_x() );
  double rhs = ( middle_point -> get_x() - start_point -> get_x() ) * ( end_point -> get_y() - middle_point -> get_y() );
  
  if( lhs <= rhs )
    return true;
  else
    return false;
}

void point::write_voronoi_corners( std::ostream& os )
{
  for( std::vector< point* >::iterator it = sorrounding_voronoi_cell_corners.begin(); it != sorrounding_voronoi_cell_corners.end(); ++it )
    (*it) -> write_monitor( os );
}

void point::add_voronoi_corner( point* new_corner )
{
  /* Adds another point to sorrounding_voronoi_cell_corners. Keep in mind, the pointers inside shall be stored anticlockwise. */
  
  // We shall not move with the points on the boundary.
  if( boundary_marker != 0 )
    return;
  
  if( sorrounding_voronoi_cell_corners.size() < 2 )
  {
    sorrounding_voronoi_cell_corners.push_back( new_corner );
    return;
  }
  
  if( turns_left( sorrounding_voronoi_cell_corners.back(), new_corner, sorrounding_voronoi_cell_corners.front() ) )
  {
    sorrounding_voronoi_cell_corners.push_back( new_corner );
    return;
  }
  
  for( std::vector< point* >::iterator it = sorrounding_voronoi_cell_corners.begin(); it + 1 != sorrounding_voronoi_cell_corners.end(); ++it )
  {
    if( turns_left( *it, new_corner, *( it + 1 ) ) )
    {
      sorrounding_voronoi_cell_corners.insert( it + 1, new_corner );
      return;
    }
  }
  
//   std::cerr << "The program shouldn't get to this point; something is wrong." << std::endl;
  std::cerr << "point::in add_voronoi_corner( ... );" << std::endl;
  wrong_program_behavior_exception e;
  throw e;
}

void point::move_to_voronoi_cell_centroid( problem* problem_pt )
{
  try
  {
    // We shall not move with the boundary points.
    if( boundary_marker != 0 )
      return;
    
    if( sorrounding_voronoi_cell_corners.empty() || sorrounding_voronoi_cell_corners.size() <= 2 )
    {
      non_complete_voronoi_cell_exception e;
      throw e;
    }
    
    // The pattern, we're using requires the polygon to be closed, i.e. the last point to coincide with the first one.
    // If isn't, copy the initial one to the back:
    if( sorrounding_voronoi_cell_corners.front() != sorrounding_voronoi_cell_corners.back() )
      sorrounding_voronoi_cell_corners.push_back( sorrounding_voronoi_cell_corners.front() );
    
    // Computing centroid according to http://en.wikipedia.org/wiki/Centroid,
    // the same as http://local.wasp.uwa.edu.au/~pbourke/geometry/polyarea/
    
    double centroid_x = 0;
    double centroid_y = 0;
    double common_product;
    double area = 0;
    std::vector< point* >::iterator i;
    std::vector< point* >::iterator iplus;
    
    // Working on all the sums at the same time.
    for( std::vector< point* >::iterator it = sorrounding_voronoi_cell_corners.begin(); it + 1!= sorrounding_voronoi_cell_corners.end(); ++ it )
    {
//      std::cerr << area << std::endl;
      i = it;
      iplus = it + 1;
      
      common_product = ( (*i) -> get_x() ) * ( (*iplus) -> get_y() ) - ( (*i) -> get_y() ) * ( (*iplus ) -> get_x() );
      centroid_x += ( (*i) -> get_x() + (*iplus) -> get_x() ) * common_product;
      centroid_y += ( (*i) -> get_y() + (*iplus) -> get_y() ) * common_product;
      area += common_product;
    }
    
    area = 0.5 * area;
    if( area == 0 )
    {
      triangle_with_no_interior_exception e;
//       std::cerr << "triangle_with_no_interior_exception" << std::endl;
      throw e;
    }
    centroid_x = centroid_x / ( 6 * area );
    centroid_y = centroid_y / ( 6 * area );
    
    
    // Finally, change the coordinates accordingly.
    // If the point is outside, put it somewhere inside and give it one more try.
    // A different attitude may be just forgetting about this point and putting it away.
    if( problem_pt -> outside( centroid_x, centroid_y ) )
    {
      srand((unsigned)time(0));
      centroid_x = (float)rand()/(float)RAND_MAX; // Nahodny float z [0,1] dle http://stackoverflow.com/questions/686353/c-random-float.
      centroid_y = (float)rand()/(float)RAND_MAX;
      change_coordinates( centroid_x, centroid_y );
    }
    else
      change_coordinates( centroid_x, centroid_y );
    
    // Once computed, the point will be moving, that can cause changes in the cell corners.
    sorrounding_voronoi_cell_corners.clear();
    
    /* TODO archivuj: kdyz se tam udelalo it.get_x();,
    vyhazovalo to 
    point.cpp: In member function ‘void point::move_to_voronoi_cell_centroid()’:
    point.cpp:77: error: ‘class __gnu_cxx::__normal_iterator<point**, std::vector<point*, std::allocator<point*> > >’ has no member named ‘get_x’
    .
    Kdyz se naopak udelalo jenom it -> get_x();
    nebo (*it).get_x();,
    tak to vyhazovalo
    point.cpp:78: error: request for member ‘get_y’ in ‘* it.__gnu_cxx::__normal_iterator<_Iterator, _Container>::operator-> [with _Iterator = point**, _Container = std::vector<point*, std::allocator<point*> >]()’, which is of non-class type ‘point*’
    
    http://www.cplusplus.com/forum/general/2566/
    Diky ;).
    */

  }
  catch( std::exception& e )
  {
    std::cerr << "in move_to_voronoi_cell_centroid() : " << e.what() << std::endl;
    throw e;
  }
}

void point::add_star_corner( point* new_corner )
{
  star_corners.push_back( new_corner );
}

void point::move_to_star_centroid( problem* problem_pt )
{
  try
  {
    double backup_x = x_coord;
    double backup_y = y_coord;
    if( star_corners.empty() || star_corners.size() <= 2 )
    {
      non_complete_voronoi_cell_exception e;
      //std::cerr << "non_complete_voronoi_cell_exception" << std::endl;
//       throw e;
      
    }
    
    double result_x = 0;
    double result_y = 0;
    double whole_area = 0;
    
    for( std::vector< point* >::iterator it = star_corners.begin(); it != star_corners.end(); ++ it )
    {
      result_x += (*it) -> get_x() * (*it) -> get_mass();
      result_y += (*it) -> get_y() * (*it) -> get_mass();
      whole_area += (*it) -> get_mass();
    }
    
    result_x = result_x / whole_area;
    result_y = result_y / whole_area;
    
    if( problem_pt -> outside( result_x, result_y ) )
    {
      // change_coordinates( 0, 0 );
      change_coordinates( backup_x, backup_y );
    }
    else
      change_coordinates( result_x, result_y );
    
    // Once computed, the point will be moving, that can cause changes in the cell corners.
    star_corners.clear();

  }
  catch( std::exception& e )
  {
    std::cerr << "in point::move_to_star_centroid() : " << e.what() << std::endl;
    throw e;
  }
}

point point::halfway_to( point& the_other_point )
{
  double new_x = 0.5 * ( x_coord + the_other_point.get_x() );
  double new_y = 0.5 * ( y_coord + the_other_point.get_y() );
  
  point to_return( new_x, new_y, 1, 0 );
  return to_return;
}

bool point::operator!=( const point& point_to_compare_with )
{
  if( x_coord != point_to_compare_with.get_x() )
    return false;
  
  if( y_coord != point_to_compare_with.get_y() )
    return false;
  
  return true;
}

std::ostream& operator<<( std::ostream& os, const point& point_to_write )
{
  point_to_write.write_monitor( os );
  
  return os;
}

#endif//POINT_CPP_GUARD
