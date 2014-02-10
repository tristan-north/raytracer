#ifndef MATRIX_H
#define MATRIX_H

// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix.

class Matrix
{

public:
	double	m[4][4];								// elements

	Matrix(void);									// default constructor
	Matrix operator* (const Matrix& mat) const; 	// multiplication of two matrices
	Matrix operator/ (const double d); 				// divsion by a double
	void set_identity(void);						// set to the identity matrix

    void scale(float sx, float sy, float sz);
    void rotateByDeg(float rx, float ry, float rz);
    void translate(float tx, float ty, float tz);

};

#endif // MATRIX_H
