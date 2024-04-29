// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef DIRECTION_CPP_GUARD
#define DIRECTION_CPP_GUARD

#include "direction.h"

direction::direction( point& begin, point& end )
{
  x_dir = end.get_x() - begin.get_x();
  y_dir = end.get_y() - begin.get_y();
}

double direction::get_x()
{
  return x_dir;
}

double direction::get_y()
{
  return y_dir;
}

void direction::turn_90()
{
  /* Turns this direction into perpendicular one by rotating 90 degrees. */
  double temp = x_dir;
  x_dir = y_dir;
  y_dir = -temp;
}

double direction::scalar_product( direction* with )
{
  return x_dir * y_dir + with->get_x() * with->get_y();
}

double direction::norm()
{
  return sqrt( x_dir * x_dir + y_dir * y_dir );
}

#endif//DIRECTION_CPP_GUARD
