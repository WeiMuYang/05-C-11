#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>

#include <stdlib.h>
#include <string.h>
#include <memory.h>


class Matrix
{
public:
	Matrix();
	Matrix(const Matrix & mat);  // 拷贝构造的形参只能这么写
	Matrix(Matrix&& mat);
	~Matrix();
	void display();

	//Matrix operator+(const Matrix& mat) {
	//	if (col != mat.col || row != mat.row) {
	//		exit(1);
	//	}
	//	Matrix result = std::move(mat); // 将亡值优先匹配右值引用的重载
	//	result.col = col;
	//	result.row = row;
	//	for (size_t i = 0; i < row; i++)
	//	{
	//		for (size_t j = 0; j < col; ++j) {
	//			result.base[i][j] = base[i][j] + mat.base[i][j];
	//		}
	//	}
	//	return result;
	//}

	friend Matrix operator+(const Matrix& mat1, const Matrix & mat) {
		if (mat1.col != mat.col || mat1.row != mat.row) {
			exit(1);
		}
		Matrix result; // 将亡值优先匹配右值引用的重载
		result.col = mat1.col;
		result.row = mat1.row;
		for (size_t i = 0; i < mat1.row; i++)
		{
			for (size_t j = 0; j < mat1.col; ++j) {
				result.base[i][j] = mat1.base[i][j] + mat.base[i][j];
			}
		}
		return result;
	}
	friend Matrix operator+(Matrix&& mat1, const Matrix& mat) {
		if (mat1.col != mat.col || mat1.row != mat.row) {
			exit(1);
		}
		 //Matrix result = mat1; // 右值引用是一个左值，因此如果这样写的话，会调用拷贝构造，不是移动构造
		Matrix result = std::move(mat1); // 将亡值优先匹配右值引用的重载
	/*	result.col = col;
		result.row = row;*/
		for (size_t i = 0; i < result.row; i++)
		{
			for (size_t j = 0; j < result.col; ++j) {
				result.base[i][j] = result.base[i][j] + mat.base[i][j];
			}
		}
		return result;
	}


	Matrix& operator= (const Matrix& mat) {
		row = mat.row;
		col = mat.col;
		base = new int* [row];
		for (int i = 0; i < row; ++i) {
			base[i] = new int[col];
		}
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; ++j) {
				base[i][j] = mat.base[i][j];
			}
		}
		return *this;
	}


	int col;
	int row;
	int** base;

};

// 移动构造函数的作用是：将原来的参数值，进行浅拷贝，原来的指针成员置空
Matrix::Matrix(Matrix&& mat) {
	std::cout << "Matrix::Matrix(const Matrix&& mat)" << std::endl;
	row = mat.row;
	col = mat.col;
	base = mat.base;
	mat.base = nullptr;
	mat.row = 0;
	mat.col = 0;
}

Matrix::Matrix()
{
	std::cout << "Matrix::Matrix()" << std::endl;
	row = 3;
	col = 4;
	
	base = new int* [row];
	for (int i = 0; i < row; ++i) {
		base[i] = new int[col];
	}
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; ++j) {
			base[i][j] = 1;
		}
	}
}

Matrix::Matrix(const Matrix& mat) {
	std::cout << "Matrix::Matrix(const Matrix& mat)" << std::endl;
	row = mat.row;
	col = mat.col;
	base = new int* [row];
	for (int i = 0; i < row; ++i) {
		base[i] = new int[col];
	}
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; ++j) {
			base[i][j] = mat.base[i][j];
		}
	}
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < row; i++)
	{
		if(base[i])
			delete[]base[i];
		base[i] = nullptr;
	}
	if (base)
		delete []base;
	col = 0;
	row = 0;
	base = nullptr;
}

void Matrix::display() {

	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; j++)
		{
			std::cout << base[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main() {


	Matrix mat1;
	//mat1.display();

	Matrix mat2;
	Matrix mat3;  // 调用的是拷贝构造
	
	Matrix mat4;
	Matrix m = mat1 + mat2 + mat3 + mat4;  // 调用的是赋值运算符的重载
    // 上面运算会出现临时变量，也就是将亡值
	m.display();
	


	return 0;
}