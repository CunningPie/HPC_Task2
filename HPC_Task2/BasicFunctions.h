#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

static const size_t N = 3000;

int get_index(int i, int j, int size);
double get_random_number(double mod, int digits);
double* get_matrix(size_t rows, size_t cols);
double* get_vector(size_t length);
void display_matrix(double* matrix, int rows, int cols);
void display_vector(double* vector, int length);
double* mult_matrix_vector(double* matrix, double* vector, int size);