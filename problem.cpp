// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef PROBLEM_CPP_GUARD
#define PROBLEM_CPP_GUARD

#include "problem.h"

problem::problem( mesh* new_mesh_pt, char new_domain_option )
{
  mesh_pt = new_mesh_pt;
  try
  {
    circle_pt = new circle( mesh_pt );
    square_pt = new square( mesh_pt );
    semicircle_pt = new semicircle( mesh_pt );
    
    update_domain_option( new_domain_option );
  }
  catch( std::exception& e )
  {
    std::cerr << "in problem() " << e.what() << std::endl;
    throw e;
  }
}

void problem::update_domain_option( char new_domain_option )
{
  switch( new_domain_option )
  {
    case 'c':
      //circle_pt = new circle( mesh_pt );
      domain_pt = circle_pt;
      break;
    case 's':
      domain_pt = square_pt;
      break;
    case 'e':
      domain_pt = semicircle_pt;
      break;
    default :
      unknown_argument_exception e;
      throw e;
      break;
  }
}

bool problem::outside( float x, float y )
{
  point* Point = new point( x, y, 1, 0 );
  return domain_pt -> outside( Point );
  delete Point;
}

void problem::create_domain_boundary( int nr_vertices )
{
  domain_pt -> create_boundary( nr_vertices );
}

void problem::refine( int nr_new_vertices )
{
  domain_pt -> refine( nr_new_vertices );
}


#endif//PROBLEM_CPP_GUARD
