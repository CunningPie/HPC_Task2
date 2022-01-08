#include "BasicFunctions.h"

double* c_get_data_buff(double* matrix_data, double vector_data, size_t col)
{
	double* data = (double*)malloc((N + 1) * sizeof(double));

	for (size_t i = 0; i < N; i++)
	{
		data[i] = matrix_data[i * N + col];
	}

	data[N] = vector_data;

	return data;
}

void main(int* argc, char** argv)
{
	double* vec = get_vector(N);
	double* matr = get_matrix(N, N);
	double* res = (double*)malloc(N * sizeof(double));
	
	clock_t begin = clock();
	res = mult_matrix_vector(matr, vec, N);
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("TIME: %f\n", time);
	/*
	int process_cnt;
	int process_rank;
	MPI_Status status;

	MPI_Init(argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_cnt);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	if (process_rank == 0)
	{
		double* vec = get_vector(N);
		double* matr = get_matrix(N, N);
		double* res = (double*)malloc(N * sizeof(double));

		for (int i = 0; i < N; i++)
			res[i] = 0;


		clock_t begin = clock();

		for (size_t col = 0; col < N; col++)
		{
			process_rank = col % (process_cnt - 1) + 1;
			double* send_data = c_get_data_buff(matr, vec[col], col);

			MPI_Send(send_data, N + 1, MPI_DOUBLE, process_rank, 0, MPI_COMM_WORLD);
		}

		for (int col = 0; col < N; col++)
		{
			double * resElement = (double *)malloc(N * sizeof(double));
			process_rank = col % (process_cnt - 1) + 1;
			MPI_Recv(resElement, N, MPI_DOUBLE, process_rank, col, MPI_COMM_WORLD, &status);

			for (int j = 0; j < N; j++)
				res[j] += resElement[j];
		}

		clock_t end = clock();
		double time = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("TIME: %f\n", time);
	}
	else
	{
		int compute_processes = process_cnt - 1;
		int cnt = process_rank <= (N % compute_processes) ? (N / compute_processes) + 1 : (N / compute_processes);

		for (int i = 0; i < cnt; i++)
		{
			int col = (compute_processes * i + process_rank) - 1;
			double* res = (double*)malloc(N * sizeof(double));
			double* buf = (double*)malloc((N + 1) * sizeof(double));

			MPI_Recv(buf, N + 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

			for (size_t i = 0; i < N; i++)
			{
				res[i] = buf[i] * buf[N];
			}
			MPI_Send(res, N, MPI_DOUBLE, 0, col, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();*/
}