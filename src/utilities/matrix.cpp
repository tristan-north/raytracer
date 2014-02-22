#include <math.h>
#include <cstring>
#include "utilities/matrix.h"

// a default matrix is an identity matrix
Matrix::Matrix(void) {
    set_identity();
}


Matrix Matrix::operator* (const Matrix& mat) const {
	Matrix 	product;

	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			double sum = 0.0;

			for (int j = 0; j < 4; j++)
				sum += m[x][j] * mat.m[j][y];

			product.m[x][y] = sum;
		}

    return (product);
}


// division by a scalar
Matrix Matrix::operator/ (const double d) {
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			m[x][y] = m[x][y] / d;

	return (*this);
}


void Matrix::set_identity(void) {
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
        }
}


void Matrix::scale(float sx, float sy, float sz)
{
    Matrix scaleMatrix;

    scaleMatrix.m[0][0] = sx;
    scaleMatrix.m[1][1] = sy;
    scaleMatrix.m[2][2] = sz;

    Matrix result = *this * scaleMatrix;
    memcpy(m, result.m, sizeof(m[0][0])*16);
}


void Matrix::rotateByDeg(float rx, float ry, float rz)
{
    const float degToRad = 0.017453293;
	rx *= degToRad;
    ry *= degToRad;
    rz *= degToRad;

    Matrix rotXMatrix, rotYMatrix, rotZMatrix;

	rotXMatrix.m[1][1] = cos(rx);
	rotXMatrix.m[1][2] = sin(rx);
	rotXMatrix.m[2][1] = -sin(rx);
	rotXMatrix.m[2][2] = cos(rx);

    rotYMatrix.m[0][0] = cos(ry);
    rotYMatrix.m[0][2] = sin(ry);
    rotYMatrix.m[2][0] = -sin(ry);
    rotYMatrix.m[2][2] = cos(ry);

    rotZMatrix.m[0][0] = cos(rz);
    rotZMatrix.m[0][1] = -sin(rz);
    rotZMatrix.m[1][0] = sin(rz);
    rotZMatrix.m[1][1] = cos(rz);


    Matrix result = *this * rotXMatrix * rotYMatrix * rotZMatrix;
    memcpy(m, result.m, sizeof(m[0][0])*16);
}

void Matrix::translate(float tx, float ty, float tz)
{
    Matrix translateMatrix;
    translateMatrix.m[0][3] = tx;
    translateMatrix.m[1][3] = ty;
    translateMatrix.m[2][3] = tz;

    Matrix result = *this * translateMatrix;
    memcpy(m, result.m, sizeof(m[0][0])*16);
}
