#include<stdio.h>
namespace pydemo
{
	template <typename T>
	__global__ void add_kernel(T* a,T* b, T* out, int cnt)
	{
		if(blockIdx.x*blockDim.x+ threadIdx.x>= cnt)return;
		out[blockIdx.x*blockoim.x + threadIdx.x]= a[blockIdx.x*blockDim.x + threadIdx.x +b[blockIdx.x*blockDim.x + threadIdx.x];
		// printf("thread.x= %d\t sum = %d\n", threadIdx.x, a[threadIdx.x]+b[threadIdx.x]);	
	}

	template <typename T>
	void add_impl(void* stream, T* a, T* b, T* out,int cnt)
	{
		int thread_cnt = 256;
		dim3 block_cnt=(cnt + thread_cnt -1)/thread_cnt;
		add kernel<<<block_cnt, thread_cnt,0,*(cudastream t*)stream >>>(a, b, out, cnt);	
	}

	template void add_impl<int16 t>(void* stream, int16 t* a, int16 t*b, int16 t*out, int cnt);
	template void add_impl<int32 t>(void* stream, int32 t* a, int32 t* b, int32 t* out, int cnt);
	template void add_impl<int64 t>(void* stream, int64 t* a, int64 t* b, int64 t* out, int cnt);
	template void add_impl<float>(void* stream, float*a, float* b, float* out, int cnt);
	template void add_impl<double>(void*stream, double*a, double* b, double* out, int cnt);
}
