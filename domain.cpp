// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef DOMAIN_CPP_GUARD
#define DOMAIN_CPP_GUARD

#include "domain.h"

bool circle::outside( point* possibly_out )
{
  const float x = possibly_out -> get_x();
  const float y = possibly_out -> get_y();
  
  if( x * x + y * y >= 1 )
    return true;
  
  return false;
}


void circle::create_boundary( int nr_vertices )
{
  double piece = 6.2830 / nr_vertices;
  
  for( int i = 0; i < nr_vertices; i++)
  {
     mesh_pt -> insert_point( cos( i * piece ), sin( i * piece ), 1 );
     //std::cerr << '*' << std::endl;
  }
}

void circle::refine( int nr_new_vertices )
{
  srand((unsigned)time(0));
  int sign; // To bude resit znamenko nahodnych cisel.
  
  for( int i = 0; i < nr_new_vertices; i++ )
  {    
    float new_x = (float)rand()/(float)RAND_MAX; // Nahodny float z [0,1] dle http://stackoverflow.com/questions/686353/c-random-float.
    float new_y = sqrt( 1 - new_x * new_x ) * (float)rand()/(float)RAND_MAX; // Tohle by moho zajistit, ze bude uvnitr kruhu.
    
    new_x = 0.9 * new_x;
    new_y = 0.9 * new_y;
    
    //Nasleduje pripadna zmena znaminek.
    sign = rand();
    if( sign % 4 == 0 || sign % 4 == 2 )
      new_x *= -1;
    
    if( sign % 4 == 0 || sign % 4 == 1 )
      new_y *= -1;
    
    mesh_pt -> insert_point( new_x, new_y, 0);
  }
}



bool square::outside( point* possibly_out )
{
  const float x = possibly_out -> get_x();
  const float y = possibly_out -> get_y();
  
  if( x <= 0 || x >= 1 || y <= 0 || y >= 1 )
    return true;
  
  return false;
}


void square::create_boundary( int nr_vertices )
{
  //mesh_pt -> clear_mesh();
  //std::cerr << "creating boundary" << std::endl;
  //std::cin.get();
  //std::cin.get();
  
  int pieces_per_side = (int)(nr_vertices / 4 );
  
  if( pieces_per_side <= 1 )
    pieces_per_side = 2;
  
  float left_x = 0;
  float bottom_y = 0;
  float right_x = 1;
  float top_y = 1;
  
  float horizontal_piece = 1 / ( (float)(pieces_per_side - 1) );
  float vertical_piece = 1 / ( (float)(pieces_per_side - 1) );
  
  for( int i = 0; i < pieces_per_side - 1; i++ )
  {
    mesh_pt -> insert_point( left_x + i * horizontal_piece, bottom_y, 1 );
    mesh_pt -> insert_point( right_x - i * horizontal_piece, top_y, 3 );
    
    mesh_pt -> insert_point( right_x, bottom_y + i * vertical_piece, 2 );
    mesh_pt -> insert_point( left_x, top_y - i * vertical_piece, 4 );
  }
  //std::cerr << "square ready";
  //std::cin.get();
  //std::cin.get();
}

void square::refine( int nr_new_vertices )
{
  srand((unsigned)time(0));
  int sign; // To bude resit znamenko nahodnych cisel.
  
  for( int i = 0; i < nr_new_vertices - 4; i++ )
  {    
    float new_x = (float)rand()/(float)RAND_MAX; // Nahodny float z [0,1] dle http://stackoverflow.com/questions/686353/c-random-float.
    float new_y = (float)rand()/(float)RAND_MAX; // Tohle by moho zajistit, ze bude uvnitr kruhu.
    
    // We want the points to be further from the boundary.
    
    if( new_x < 0.1 )
      new_x += 0.1;
    else if( new_x > 0.9 )
      new_x -= 0.1;
    
    if( new_y < 0.1 )
      new_y += 0.1;
    else if( new_y > 0.9 )
      new_y -= 0.1;
    
    
    mesh_pt -> insert_point( new_x, new_y, 0);
  }
  
//   mesh_pt -> insert_point( 0.01, 0.01, 0 );
//   mesh_pt -> insert_point( 0.99, 0.01, 0 );
//   mesh_pt -> insert_point( 0.01, 0.99, 0 );
//   mesh_pt -> insert_point( 0.99, 0.99, 0 );
}




bool semicircle::outside( point* possibly_out )
{
  const float x = possibly_out -> get_x();
  const float y = possibly_out -> get_y();
  
  if( y <= 0 )
    return true;
  
  if( x * x >= 1 - y * y )
    return true;
  
  return false;
}


void semicircle::create_boundary( int nr_vertices )
{
  int line_vertices = (int)(0.3890 * nr_vertices ); //Estimated to have similar distances between points both on arc and line.
  int arc_vertices = nr_vertices - line_vertices;
  
  double arc_piece = 3.1415 / arc_vertices;
   
  int total_vertices = 0;
  for( int i = 0; i < arc_vertices; i++)
  {
     mesh_pt -> insert_point( cos( i * arc_piece ), sin( i * arc_piece ), 1 );
     //std::cerr << '*' << std::endl;
     total_vertices++;
  }
  
  float horizontal_piece = 2 / ( (float)( line_vertices ));
  // TODO: archivovat: Kdyz se tam neudela konverze do floatu, tak to pocita jako s integery a horizontal_piece vyjde 0. Zaludne =)=).
  
  for( int i = 0; i < line_vertices; i++ )
  {
    mesh_pt -> insert_point( -1 + i * horizontal_piece, 0, 1 );
    total_vertices++;
  }
  std::cout << "Total: " << total_vertices << std::endl;
}

void semicircle::refine( int nr_new_vertices )
{
  srand((unsigned)time(0));
  int sign; // To bude resit znamenko nahodnych cisel.
  
  
  for( int i = 0; i < nr_new_vertices; i++ )
  {    
    float new_x = (float)rand()/(float)RAND_MAX; // Nahodny float z [0,1] dle http://stackoverflow.com/questions/686353/c-random-float.
    float new_y = sqrt( 1 - new_x * new_x ) * (float)rand()/(float)RAND_MAX; // Tohle by moho zajistit, ze bude uvnitr kruhu.
    
    new_x = 0.9 * new_x;
    new_y = 0.9 * new_y;
    
    if( new_y <= 0.1 )
    {
      new_y += 0.1;
      new_x *= 0.87;
    }
    
    //Nasleduje pripadna zmena znaminek.
    sign = rand();
    if( sign % 4 == 0 || sign % 4 == 2 )
      new_x *= -1;
  
    
    mesh_pt -> insert_point( new_x, new_y, 0 );
  }
}
#endif//DOMAIN_CPP_GUARD
