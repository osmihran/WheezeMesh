// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef MATRIX_CPP_GUARD
#define MATRIX_CPP_GUARD

#include "matrix.h"

bool matrix::regular()
{
  if( a_11 * a_22 - a_12 * a_21 == 0 )
    return false;
  
  return true;
}

double matrix::det()
{
  return( a_11 * a_22 - a_12 * a_21 );
}

#endif//MATRIX_CPP_GUARD
