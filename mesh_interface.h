// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef MESH_INTERFACE_H_GUARD
#define MESH_INTERFACE_H_GUARD

#include <string>
#include <sstream>
#include "exceptions.h"
#include "mesh.h"

class mesh_interface
{
  private:
    mesh* mesh_pt;
    mesh_interface(){};
    
    void newline();
    void comsol_export();
    void balancing_menu( char method );
    
    void CVT_balance( int nr_iter, int visualisation_frequency );
    void ODT_balance( int nr_iter, int visualisation_frequency );
    
    void ODT_automatic( char domain_option, int nr_iter, int nr_boundary_vertices, int nr_inside_vertices, int visualisation_frequency );
    void CVT_automatic( char domain_option, int nr_iter, int nr_boundary_vertices, int nr_inside_vertices, int visualisation_frequency );
  public:
    mesh_interface( mesh* new_mesh_pt ) : mesh_pt( new_mesh_pt ){};
    
    void main_menu();
};
#endif//MESH_INTERFACE_H_GUARD
