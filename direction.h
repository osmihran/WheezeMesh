// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef DIRECTION_H_GUARD
#define DIRECTION_H_GUARD

#include <math.h>
#include "point.h"
class direction;
class direction
{
  private:
    double x_dir;
    double y_dir;
    direction(){};
  public:
    direction( point& begin, point& end );
    double get_x();
    double get_y();
    void turn_90();
    double scalar_product( direction* with );
    double norm();
};

#endif//DIRECTION_H_GUARD
