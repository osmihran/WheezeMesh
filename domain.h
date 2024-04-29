// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef DOMAIN_H_GUARD
#define DOMAIN_H_GUARD

#include "point.h"
#include "mesh.h"

/* Contains also definitions of classes circle, square and semicircle, while placing them in different files was causing
circular inclusion and errors which I wasn't able to prevent any different way. This seems to be working and sorry for any
possible confusion. */

class mesh;
class point;

class domain
{
  protected:
    mesh* mesh_pt;
    domain(){};
  public:
    domain( mesh* new_mesh_pt )
    {
      mesh_pt = new_mesh_pt;
    };
    virtual bool outside( point* possibly_out ){};
    virtual void create_boundary( int nr_vertices ){};
    virtual void refine( int nr_new_vertices ){};
    /* TODO archivovat: nesmi se zapomenout na nulova tela tech funkci, jinak to vyhazuje moc divne errory. Jako
/tmp/ccjWmLof.o:(.rodata._ZTI6circle[typeinfo for circle]+0x8): undefined reference to `typeinfo for domain'
/tmp/ccTylD9c.o: In function `domain::domain()':
problem.cpp:(.text._ZN6domainC2Ev[domain::domain()]+0x8): undefined reference to `vtable for domain'
collect2: ld returned 1 exit status

http://www.wellho.net/mouth/802_undefined-reference-to-typeinfo-C-error-message.html
Diky, diky, diky=).
*/
};

class circle : public domain
{
  private:
    mesh* mesh_pt;
    circle();
  public:
    circle( mesh* new_mesh_pt )
    {
      mesh_pt = new_mesh_pt;
    };
    bool outside( point* possibly_out );
    void create_boundary( int nr_vertices );
    void refine( int nr_new_vertices );
};


class square : public domain
{
  private:
    mesh* mesh_pt;
    square();
  public:
    square( mesh* new_mesh_pt )
    {
      mesh_pt = new_mesh_pt;
    };
    bool outside( point* possibly_out );
    void create_boundary( int nr_vertices );
    void refine( int nr_new_vertices );
};

class semicircle : public domain
{
  private:
    mesh* mesh_pt;
    semicircle();
  public:
    semicircle( mesh* new_mesh_pt )
    {
      mesh_pt = new_mesh_pt;
    };
    bool outside( point* possibly_out );
    void create_boundary( int nr_vertices );
    void refine( int nr_new_vertices );
};

#endif//DOMAIN_H_GUARD
