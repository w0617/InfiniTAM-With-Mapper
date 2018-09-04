/*
Copyright 2011. All rights reserved.
Institute of Measurement and Control Systems
Karlsruhe Institute of Technology, Germany

This file is part of libviso2.
Authors: Andreas Geiger

libviso2 is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or any later version.

libviso2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
libviso2; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/

#ifndef Matrix_H
#define Matrix_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#ifndef _MSC_VER
  #include <stdint.h>
#else
  typedef __int8            int8_t;
  typedef __int16           int16_t;
  typedef __int32           int32_t;
  typedef __int64           int64_t;
  typedef unsigned __int8   uint8_t;
  typedef unsigned __int16  uint16_t;
  typedef unsigned __int32  uint32_t;
  typedef unsigned __int64  uint64_t;
#endif

#define endll endl << endl // double end line definition

typedef double FLOAT;      // double precision
//typedef float  FLOAT;    // single precision

class libviso2_Matrix {

public:

  // constructor / deconstructor
  libviso2_Matrix ();                                                  // init empty 0x0 libviso2_Matrix
  libviso2_Matrix (const int32_t m,const int32_t n);                   // init empty mxn libviso2_Matrix
  libviso2_Matrix (const int32_t m,const int32_t n,const FLOAT* val_); // init mxn libviso2_Matrix with values from array 'val'
  libviso2_Matrix (const libviso2_Matrix &M);                                   // creates deepcopy of M
  ~libviso2_Matrix ();

  // assignment operator, copies contents of M
  libviso2_Matrix& operator= (const libviso2_Matrix &M);

  // copies sublibviso2_Matrix of M into array 'val', default values copy whole row/column/libviso2_Matrix
  void getData(FLOAT* val_,int32_t i1=0,int32_t j1=0,int32_t i2=-1,int32_t j2=-1);

  // set or get submatrices of current libviso2_Matrix
  libviso2_Matrix getMat(int32_t i1,int32_t j1,int32_t i2=-1,int32_t j2=-1);
  void   setMat(const libviso2_Matrix &M,const int32_t i,const int32_t j);

  // set sub-libviso2_Matrix to scalar (default 0), -1 as end replaces whole row/column/libviso2_Matrix
  void setVal(FLOAT s,int32_t i1=0,int32_t j1=0,int32_t i2=-1,int32_t j2=-1);

  // set (part of) diagonal to scalar, -1 as end replaces whole diagonal
  void setDiag(FLOAT s,int32_t i1=0,int32_t i2=-1);

  // clear libviso2_Matrix
  void zero();
  
  // extract columns with given index
  libviso2_Matrix extractCols (std::vector<int> idx);

  // create identity libviso2_Matrix
  static libviso2_Matrix eye (const int32_t m);
  void          eye ();

  // create diagonal libviso2_Matrix with nx1 or 1xn libviso2_Matrix M as elements
  static libviso2_Matrix diag(const libviso2_Matrix &M);
  
  // returns the m-by-n libviso2_Matrix whose elements are taken column-wise from M
  static libviso2_Matrix reshape(const libviso2_Matrix &M,int32_t m,int32_t n);

  // create 3x3 rotation matrices (convention: http://en.wikipedia.org/wiki/Rotation_libviso2_Matrix)
  static libviso2_Matrix rotMatX(const FLOAT &angle);
  static libviso2_Matrix rotMatY(const FLOAT &angle);
  static libviso2_Matrix rotMatZ(const FLOAT &angle);

  // simple arithmetic operations
  libviso2_Matrix  operator+ (const libviso2_Matrix &M); // add libviso2_Matrix
  libviso2_Matrix  operator- (const libviso2_Matrix &M); // subtract libviso2_Matrix
  libviso2_Matrix  operator* (const libviso2_Matrix &M); // multiply with libviso2_Matrix
  libviso2_Matrix  operator* (const FLOAT &s);  // multiply with scalar
  libviso2_Matrix  operator/ (const libviso2_Matrix &M); // divide elementwise by libviso2_Matrix (or vector)
  libviso2_Matrix  operator/ (const FLOAT &s);  // divide by scalar
  libviso2_Matrix  operator- ();                // negative libviso2_Matrix
  libviso2_Matrix  operator~ ();                // transpose
  FLOAT   l2norm ();                   // euclidean norm (vectors) / frobenius norm (matrices)
  FLOAT   mean ();                     // mean of all elements in libviso2_Matrix

  // complex arithmetic operations
  static libviso2_Matrix cross (const libviso2_Matrix &a, const libviso2_Matrix &b);    // cross product of two vectors
  static libviso2_Matrix inv (const libviso2_Matrix &M);                       // invert libviso2_Matrix M
  bool   inv ();                                             // invert this libviso2_Matrix
  FLOAT  det ();                                             // returns determinant of libviso2_Matrix
  bool   solve (const libviso2_Matrix &M,FLOAT eps=1e-20);            // solve linear system M*x=B, replaces *this and M
  bool   lu(int32_t *idx, FLOAT &d, FLOAT eps=1e-20);        // replace *this by lower upper decomposition
  void   svd(libviso2_Matrix &U,libviso2_Matrix &W,libviso2_Matrix &V);                 // singular value decomposition *this = U*diag(W)*V^T

  // print libviso2_Matrix to stream
  friend std::ostream& operator<< (std::ostream& out,const libviso2_Matrix& M);

  // direct data access
  FLOAT   **val;
  int32_t   m,n;

private:

  void allocateMemory (const int32_t m_,const int32_t n_);
  void releaseMemory ();
  inline FLOAT pythag(FLOAT a,FLOAT b);

};

#endif // libviso2_Matrix_H
