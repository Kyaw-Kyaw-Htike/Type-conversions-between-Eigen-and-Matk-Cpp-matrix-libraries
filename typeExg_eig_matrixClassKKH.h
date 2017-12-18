#ifndef TYPEEXG_EIG_MATRIXCLASSKKH_H
#define TYPEEXG_EIG_MATRIXCLASSKKH_H

// Copyright (C) 2017 Kyaw Kyaw Htike @ Ali Abdul Ghafur. All rights reserved.

#include "matrix_class_KKH.h"
#include "Eigen/Dense"
#include <vector>
#include <cstring> // for memcpy

#define EigenMatrix Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
#define EIGEN_NO_DEBUG // to remove bound checking to get faster element access


// works for 2D matrices (real numbers, not complex)
// assumes that underlying matrix data is stored in column major order.
template <typename T>
void eigen2matKKH(const EigenMatrix& matIn, Matk<T> &matOut)
{	
	int nrows = matIn.rows();
	int ncols = matIn.cols();
	
	matOut.create(nrows, ncols);
	
	T * ptr = matOut.get_ptr();
	unsigned long count = 0;
	
	for (int j = 0; j < ncols; j++)
		for (int i = 0; i < nrows; i++)
			ptr[count++] = matIn(i,j);		
}

// works for 3D matrices (real numbers, not complex)
// a 3D matrix can be thought of as a 2D matrix with any number of channels
// assumes that underlying matrix data is stored in column major order.
template <typename T>
void eigen2matKKH(const std::vector<EigenMatrix> &matIn, Matk<T> &matOut)
{
	int nrows = matIn[0].rows();
	int ncols = matIn[0].cols();
	int nchannels = matIn.size();
	
	matOut.create(nrows, ncols, nchannels);
	
	T * ptr = matOut.get_ptr();
	unsigned int count = 0;
	
	EigenMatrix temp;
	
	for (int k = 0; k < nchannels; k++)
	{
		temp = matIn[k];
		for (int j = 0; j < ncols; j++)
		{
			for (int i = 0; i < nrows; i++)
			{
				ptr[count++] = temp(i,j);				
			}				
		}	
	}
}


// works for 2D matrices (real numbers, not complex)
// assumes that underlying matrix data is stored in column major order.
template <typename T>
void matKKH2eigen(const Matk<T> &matIn, EigenMatrix &matOut)
{		
	int nrows = matIn.nrows();
	int ncols = matIn.ncols();
	
	matOut.setZero(nrows, ncols);
	
	T *src_pointer = (T*)matIn.get_ptr();
	T *dst_pointer = (T*)matOut.data();
	
	std::memcpy(dst_pointer, scr_pointer, sizeof(T)*nrows*ncols);
}

// works for 3D matrices (real numbers, not complex)
// a 3D matrix can be thought of as a 2D matrix with any number of channels
// assumes that underlying matrix data is stored in column major order.
template <typename T>
void matKKH2eigen(const Matk<T> matIn, std::vector<EigenMatrix> &matOut)
{
	
	int nrows = matIn.n_rows;
	int ncols = matIn.n_cols;
	int nchannels = matIn.n_slices;

	matOut.resize(nchannels);	
	T* src_pointer = matIn.get_ptr();
	
	for (int k = 0; k < nchannels; k++)
	{
		matOut[k].setZero(nrows, ncols);
		T *dst_pointer = (T*)matOut[k].data();
		std::memcpy(dst_pointer, src_pointer+k*nrows*ncols, sizeof(T)*nrows*ncols);
	}		

}

/*
By default, Eigen currently supports standard floating-point types 
(float, double, std::complex<float>, std::complex<double>, long double), 
as well as all native integer types (e.g., int, unsigned int, short, etc.), and bool.
*/


#undef EigenMatrix
#undef EIGEN_NO_DEBUG

#endif
