// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef PROBLEM_H_GUARD
#define PROBLEM_H_GUARD

#include "mesh.h"
#include "point.h"
#include "domain.h"

//#include "circle.h"
//#include "square.h"
//#include "semicircle.h"

class mesh;
class point;
class domain;
class circle;
class square;
class semicircle;

class problem
{
  private:
    mesh* mesh_pt;
    domain* domain_pt;
    circle* circle_pt;
    square* square_pt;
    semicircle* semicircle_pt;
    problem();
  public:
    problem( mesh* new_mesh_pt, char new_domain_option = 'c' );
    bool outside( float x, float y );
    void update_domain_option( char new_domain_option);
    void create_domain_boundary( int nr_vertices );
    void refine( int nr_new_vertices );
};

#endif//PROBLEM_H_GUARD
