#include <cuda_runtime.h>
#include <vector>
#include<string>
#include <iostream>
#include <ostream>
#include "tensor.h'
namespace pydemo
{
	template <typename T>
	void add_impl(void* stream, T* a, T* b, T* out, int cnt);	
}
