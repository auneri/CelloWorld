#include <cstdio>
#include <cstdlib>

const int N = 16;
const int blocksize = 16;


__global__
void hello(char *a, int *b) {
	a[threadIdx.x] += b[threadIdx.x];
}


int main(int, char *[]) {
	char a[N] = "Hello \0\0\0\0\0\0";
	int b[N] = {15, 10, 6, 0, -11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	printf("%s", a);

	char *da;
	int *db;
	const int csize = N * sizeof(char);
	const int isize = N * sizeof(int);

	cudaMalloc((void**)&da, csize);
	cudaMalloc((void**)&db, isize);
	cudaMemcpy(da, a, csize, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, isize, cudaMemcpyHostToDevice);

	dim3 dimBlock(blocksize, 1);
	dim3 dimGrid(1, 1);
	hello<<<dimGrid, dimBlock>>>(da, db);

	cudaMemcpy(a, da, csize, cudaMemcpyDeviceToHost);
	cudaFree(da);
	cudaFree(db);

	printf("%s\n", a);

	return EXIT_SUCCESS;
}
