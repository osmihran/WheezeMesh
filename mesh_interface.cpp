// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef MESH_INTERFACE_CPP_GUARD
#define MESH_INTERFACE_CPP_GUARD

#include "mesh_interface.h"

void mesh_interface::newline()
{
  /* Small technicality making programming comfortable. */
  std::cout << "=======================================================" << std::endl;
}


void mesh_interface::main_menu()
{
  char task;
  
  std::cout << "Welcome to WheezeMesh, CVT and ODT sample mesh optimizator." << std::endl;
  std::cout << "Select option, please" << std::endl;
  std::cout << "m ... convert mesh from *.node and *.ele to *.mphtxt" << std::endl;
  std::cout << "c ... Centroidal Voronoi Tessellations meshing" << std::endl;
  std::cout << "o ... Optimal Delaunay Triangulations meshing" << std::endl;
  std::cin >> task;
  if( task == 'm' )
    comsol_export();
  else if( task == 'c' || task == 'o' )
    balancing_menu( task );
  else
  {
    unknown_argument_exception e;
    throw e;
  }
}

void mesh_interface::comsol_export()
{
  /* Menu for exporting into COMSOL--legible files. */
  std::string filename;
  newline();
  newline();
  std::cout << "This enables you to write your mesh into a *.mphtxt format." << std::endl;
  std::cout << "You may use and test it in the COMSOL Multiphysics program." << std::endl;
  newline();
  std::cout << "Specify the name common to your *.node and *.ele file, please:" << std::endl;
  std::cout << "If you don't have them in this directory, press 'q' to return to main menu, please." << std::endl;
  newline();
  std::cin >> filename ;
  
  if( filename == "q" )
    return;
  
  mesh_pt -> read_whole_mesh_from_node_and_ele( filename );
  mesh_pt -> write_to_file( filename, "mph" );
  
  newline();
  newline();
  std::cout << "Your file " << filename << ".mphtxt should be ready now." << std::endl;
  std::cout << "You may give it to the COMSOL Multiphysics 3.5a" << std::endl;
  std::cout << "via \"File > import > mesh from the file\" option there." << std::endl;
  //wait_for_enter();
  return;
}

void mesh_interface::balancing_menu( char method_option )
{
  /* Submenu */
  char domain_option;
  int nr_boundary_vertices;
  int nr_interior_vertices;
  int nr_iterations;
  char visualisations_char;
  int visualisation_frequency;
  
  std::cout << "Select the domain, please" << std::endl;
  std::cout << "c ... unit circle" << std::endl;
  std::cout << "s ... square [0,1]^2" << std::endl;
  std::cout << "e ... upper half of the unit circle" << std::endl;
  std::cin >> domain_option;
  std::cout << "Specify number of boundary vertices, please." << std::endl;
  std::cin >> nr_boundary_vertices;
  std::cout << "Specify number of interior vertices, please." << std::endl;
  std::cin >> nr_interior_vertices;
  std::cout << "Specify number of iterations, please." << std::endl;
  std::cin >> nr_iterations;
  std::cout << "Would you like visualisations? Requires installed program Showme (y/n)" << std::endl;
  std::cin >> visualisations_char;
  
  if( visualisations_char == 'y' )
  {
    std::cout << "Specify visualisation frequency, please." << std::endl;
    std::cin >> visualisation_frequency;
  }
  else if( visualisations_char == 'n' )
  {
    visualisation_frequency = nr_iterations + 2;
    // Assures not to be asked for visualisations.
  }
  else
  {
    unknown_argument_exception e;
    throw e;
  }
  
  if( method_option == 'c' )
    CVT_automatic( domain_option, nr_iterations, nr_boundary_vertices, nr_interior_vertices, visualisation_frequency );
  else if( method_option == 'o' )
    ODT_automatic( domain_option, nr_iterations, nr_boundary_vertices, nr_interior_vertices, visualisation_frequency );
  else
  {
    unknown_argument_exception e;
    throw e;
  }
}


void mesh_interface::CVT_balance( int nr_iter, int visualisation_frequency )
{
  try
  {
    /* Each point is assigned corners of its Voronoi tessell and then is moved to its centroid. Iterated several times. */
    std::string filename;
    mesh_pt -> write_to_file( "CVT_initial", "node" );
    system( "triangle -Q CVT_initial" );
    if( visualisation_frequency < nr_iter )
      system( "showme CVT_initial.1" );
    mesh_pt -> read_whole_mesh_from_node_and_ele( "CVT_initial.1" );
    for( int i = 1; i <= nr_iter; i++ )
    {
      std::cout << "iteration : " << i << std::endl;
      mesh_pt -> CVT_balance();
      mesh_pt -> write_to_file( "CVT_automatic", "node" );
      system( "triangle -Q CVT_automatic" );
      mesh_pt -> read_whole_mesh_from_node_and_ele( "CVT_automatic.1" );
      if( i % visualisation_frequency == 0 )
      {
	// According to http://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string/
	system( "showme CVT_automatic.1" );
	std::stringstream out;
	out <<  i;
	filename = "CVT" + out.str();
	mesh_pt -> write_to_file( filename, "mph" );
      }
    }
    
    mesh_pt -> write_to_file( "CVT_optimized", "node" );
    if( visualisation_frequency < nr_iter )
      system( "showme CVT_optimized" );
  }
  catch( std::exception& e )
  {
    std::cerr << "in mesh_interface::CVT_balance( " << nr_iter << " ) : " << e.what() << std::endl;
    throw e;
  }
}

void mesh_interface::ODT_balance( int nr_iter, int visualisation_frequency )
{
  /* Compute a star, move the point to the centroid, reconstruct the Delaunay triangulation and iterate, if not satisfied. */
  try
  {
    std::string filename;
    mesh_pt -> write_to_file( "ODT_initial", "node" );
    system( "triangle -Q ODT_initial" );
    if( visualisation_frequency < nr_iter )
      system( "showme ODT_initial.1" );
    mesh_pt -> read_whole_mesh_from_node_and_ele( "ODT_initial.1" );
    for( int i = 1; i <= nr_iter; i++ )
    {
      std::cout << "iteration : " << i << std::endl;
      mesh_pt -> ODT_balance();
      mesh_pt -> write_to_file( "ODT_automatic", "node" );
      system( "triangle -Q ODT_automatic" );
      mesh_pt -> read_whole_mesh_from_node_and_ele( "ODT_automatic.1" );
      if( i % visualisation_frequency == 0 )
      {
	// According to http://notfaq.wordpress.com/2006/08/30/c-convert-int-to-string/
	system( "showme ODT_automatic.1" );
	std::stringstream out;
	out <<  i;
	filename = "ODT" + out.str();
	mesh_pt -> write_to_file( filename, "mph" );
      }
    }
    
    mesh_pt -> write_to_file( "ODT_optimized", "node" );
    if( visualisation_frequency < nr_iter )
      system( "showme ODT_optimized" );
  }
  catch( std::exception &e )
  {
    std::cerr << "in mesh_interface::ODT_balance( " << nr_iter << " ) : " << e.what() << std::endl;
    throw e;
  }
}

void mesh_interface::ODT_automatic( char domain_option, int nr_iter, int nr_boundary_vertices, int nr_inside_vertices, int
visualisation_frequency )
{
  /* Initial attempts before going to the heart of the matter of ODT optimization. */
  try
  {
    mesh_pt -> create_domain( domain_option, nr_boundary_vertices );
    std::cout << "boundary created" << std::endl;
    mesh_pt -> refine( nr_inside_vertices );
    std::cout << "points given inside" << std::endl;
    std::cout << "starting mesh optimization" << std::endl;
    ODT_balance( nr_iter, visualisation_frequency );
  }
  catch( std::exception& e )
  {
    std::cerr << "in mesh_interface::ODT_automatic( " << nr_iter << " ) : " << e.what() << std::endl;
  }
}

void mesh_interface::CVT_automatic( char domain_option, int nr_iter, int nr_boundary_vertices, int nr_inside_vertices, int
visualisation_frequency )
{
  /* Preliminaries for CVT optimization. */
  try
  {
    mesh_pt -> create_domain( domain_option, nr_boundary_vertices );
    std::cout << "boundary created" << std::endl;
    mesh_pt -> refine( nr_inside_vertices );
    std::cout << "points given inside" << std::endl;
    std::cout << "starting mesh optimization" << std::endl;
    CVT_balance( nr_iter, visualisation_frequency );
  }
  catch( std::exception& e )
  {
    std::cerr << "in mesh_interface::CVT_automatic( " << nr_iter << " ) : " << e.what() << std::endl;
  }
}

#endif//MESH_INTERFACE_CPP_GUARD
