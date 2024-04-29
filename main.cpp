// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef MAIN_CPP_GUARD
#define MAIN_CPP_GUARD

#include <iostream>
#include "exceptions.h"
#include "mesh.h"
#include "mesh_interface.h"

int main( int argc, char *argv[] )
{
  mesh Mesh;
  mesh_interface Mesh_interface( &Mesh );
  
  try
  {
    Mesh_interface.main_menu();
  }
  catch( std::exception& e )
  {
    std::cerr << "Error : " << e.what() << std::endl;
    throw e;
  }
  std::cout << "Thanks for using WheezeMesh." << std::endl;  
  return 0;
}
#endif//MAIN_CPP_GUARD
