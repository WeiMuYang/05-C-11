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
	Matrix(const Matrix & mat);  // ����������β�ֻ����ôд
	Matrix(Matrix&& mat);
	~Matrix();
	void display();

	//Matrix operator+(const Matrix& mat) {
	//	if (col != mat.col || row != mat.row) {
	//		exit(1);
	//	}
	//	Matrix result = std::move(mat); // ����ֵ����ƥ����ֵ���õ�����
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
		Matrix result; // ����ֵ����ƥ����ֵ���õ�����
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
		 //Matrix result = mat1; // ��ֵ������һ����ֵ������������д�Ļ�������ÿ������죬�����ƶ�����
		Matrix result = std::move(mat1); // ����ֵ����ƥ����ֵ���õ�����
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

// �ƶ����캯���������ǣ���ԭ���Ĳ���ֵ������ǳ������ԭ����ָ���Ա�ÿ�
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
	Matrix mat3;  // ���õ��ǿ�������
	
	Matrix mat4;
	Matrix m = mat1 + mat2 + mat3 + mat4;  // ���õ��Ǹ�ֵ�����������
    // ��������������ʱ������Ҳ���ǽ���ֵ
	m.display();
	


	return 0;
}