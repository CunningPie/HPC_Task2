#include "BasicFunctions.h"

int get_index(int i, int j, int size)
{
	return i * size + j;
}

double get_random_number(double mod, int digits)
{
	return round((rand() * 1.0 / RAND_MAX) * mod * pow(10, digits)) / pow(10, digits);
}

double* get_matrix(size_t rows, size_t cols)
{
	double* matrix = (double*)malloc(rows * cols * sizeof(double));
	size_t size = rows * cols;

	for (int i = 0; i < size; i++)
		matrix[i] = get_random_number(10.0, 2);

	return matrix;
}

double* get_vector(size_t length)
{
	double* vector = (double*)malloc(length * sizeof(double));

	for (int i = 0; i < length; i++)
		vector[i] = get_random_number(10.0, 2);

	return vector;
}

void display_matrix(double* matrix, int rows, int cols)
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			printf("%f ", matrix[i * rows + j]);
		}

		printf("\n");
	}
}

void display_vector(double* vector, int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("%f ", vector[i]);
	}

	printf("\n");
}

/// <summary>
/// ���������������� ��������� ���������� ������� �� ������.
/// </summary>
/// <param name="matrix"> ���������� �������. </param>
/// <param name="vector"> ������. </param>
/// <param name="N"> ������ �������. </param>
/// <returns></returns>
double* mult_matrix_vector(double* matrix, double* vector, int size)
{
	double* res = (double*)malloc(size * sizeof(double));

	for (int i = 0; i < size; i++)
	{
		res[i] = 0;

		for (int j = 0; j < size; j++)
		{
			res[i] += matrix[get_index(i, j, size)] * vector[j];
		}
	}

	return res;
}