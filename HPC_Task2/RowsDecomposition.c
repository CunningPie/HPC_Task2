#include "BasicFunctions.h"

double* r_get_data_buff(double* matrix_data, double* vector_data, int matrix_data_length, int vector_data_length)
{
	double* data = (double*)malloc((matrix_data_length + vector_data_length) * sizeof(double));

	for (size_t i = 0; i < matrix_data_length; i++)
	{
		data[i] = matrix_data[i];
	}

	for (size_t i = 0; i < vector_data_length; i++)
	{
		data[matrix_data_length + i] = vector_data[i];
	}

	return data;
}


void main2(int* argc, char** argv)
{
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
		double* res = (double*)malloc(N * N * sizeof(double));

		/*
		display_vector(vec, N);
		printf("####\n");
		display_matrix(matr, N, N);
		printf("####\n");*/

		clock_t begin = clock();

		for (size_t row = 0; row < N; row++)
		{
			process_rank = row % (process_cnt - 1) + 1;
			double* send_data = r_get_data_buff(matr + row * N, vec, N, N);

			MPI_Send(send_data, 2 * N, MPI_DOUBLE, process_rank, 0, MPI_COMM_WORLD);
		}

		for (int row = 0; row < N; row++)
		{
			double resElement = 0;
			process_rank = row % (process_cnt - 1) + 1;
			MPI_Recv(&resElement, 1, MPI_DOUBLE, process_rank, row, MPI_COMM_WORLD, &status);
			res[row] = resElement;
		}

		clock_t end = clock();
		double time = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("TIME: %f\n", time);
		//display_vector(res, N);
	}
	else
	{
		int compute_processes = process_cnt - 1;
		int cnt = process_rank <= (N % compute_processes) ? (N / compute_processes) + 1 : (N / compute_processes);

		for (int i = 0; i < cnt; i++)
		{
			int row = (compute_processes * i + process_rank) - 1;
			double res = 0;
			double* buf = (double*)malloc(2 * N * sizeof(double));

			MPI_Recv(buf, 2 * N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

			for (size_t i = 0; i < N; i++)
			{
				res += buf[i] * buf[i + N];
			}
			MPI_Send(&res, 1, MPI_DOUBLE, 0, row, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
}