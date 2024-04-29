// SPDX-FileCopyrightText: 2024 Dr. Dominik Mokris <dominik.mokris42@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef EXCEPTIONS_H_GUARD
#define EXCEPTIONS_H_GUARD

// http://www.cplusplus.com/forum/general/33758/
// TODO archivovat: Zapomnel jsem includovat <exception>, vyhodilo to 
// exceptions.h:7: error: expected class-name before ‘{’ token,
// coz vypadalo na problem podle linku vyse a pritom to bylo tohle ;].
#include <exception>

class file_not_open_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "File not open exception happened.";
 }
};


class wrong_dimension_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "Wrong dimension exception encountered.";
 }
};


class wrong_argument_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "wrong argument";
 }
};


class wrong_line_number_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "wrong line number";
 }
};

class non_complete_voronoi_cell_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "noncomplete Voronoi cell";
 }
};

class singular_matrix_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "singular matrix";
 }
};

class triangle_with_no_interior_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "triangle with no interior";
 }
};

class wrong_program_behavior_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "The program behaves wrongly, check the code.";
 }
};

class wrong_nr_of_arguments_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "Wrong number of arguments.";
 }
};

class unknown_argument_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "Unknown argument.";
 }
};


class unknown_file_format_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "Unknown file format.";
 }
};

class unknown_exception: public std::exception
{
 virtual const char* what() const throw()
 {
   return "Unknown exception.";
 }
};

#endif//EXCEPTIONS_H_GUARD
