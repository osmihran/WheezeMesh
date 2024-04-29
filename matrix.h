// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef MATRIX_H_GUARD
#define MATRIX_H_GUARD

class matrix
{
  private:
    // entries
    double a_11;
    double a_12;
    double a_21;
    double a_22;
    
    matrix(){};
  public:
    matrix( double new_a_11, double new_a_12, double new_a_21, double new_a_22 ) : a_11( new_a_11 ), a_12( new_a_12 ), a_21( new_a_21 ), a_22( new_a_22 ){};
    bool regular();
    double det();
};
#endif//MATRIX_H_GUARD
