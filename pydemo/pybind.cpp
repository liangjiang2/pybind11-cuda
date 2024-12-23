#include <pybind11/stl.h>
#include<pybind11/pybind11.h>
#include<pybind11/numpy.h>
// #ifdef USE CUDA
#include <cuda runtime.h>
// #endif
#ifdef USE ATLAS
#include "acl/acl.h"
#include"acl/acl base.h"
#include"acl/acl mdl.h"
#endif

#include <iostream>
#include <string>
#include "hello.h'

namespace py= pybind11;
using namespace pydemo;

void test(std::string str)
{
	std::cout<<"hahaha"+str<<std::endl;
}

template<typename T>
static Tensor fromNumpy(const py::array_t<T>& buf, TensorType tensor_type)
{
	py::buffer_info p_info = buf.request();
	// int64_t p_size = p_info.size*p_info.itemsize;
	std::vector<int64_t>shapes;
	shapes.reserve(p_info.ndim);
	for(size_t i=0;i<p_info.shape.size();i++ )
	{
		shapes.push_back(p_info.shape[i]);	
	}

	return Tensor(p_info.ptr, shapes, tensor_type);
}

template<typename T>
static void add(int deviceId, const py::array_t<T>& bufA, const py::array_t<T>& bufB, py:array_t<T>& bufo, TensorType tensor_type)
{
	cudaStream_t stream;
	cudasetDevice(1);
	cudaStreamCreate(&stream);
	
	Tensor a=fromNumpy(bufA, tensor_type);
	Tensor b=fromNumpy(bufB, tensor_type);
	Tensor out =fromNumpy(bufO,tensor_type);
	
	std::cout<<"a shape ="<<a.shape_<<std::endl;
	std::cout<<"a elem_size="<<a.elem_size_<<std::endl;
	std::cout<<"a ByteLen = "<<a.ByteLen()<<std::endl;
	
	//在GPU上分配内存: GPU上分配的内存大小是N
	void *dev_a,*dev_b,*dev_o;
	cudaMalloc((void **)&dev_a, a.ByteLen());
	cudaMalloc((void **)&dev_b, b.ByteLen());
	cudaMalloc((void **)&dev_o, out.ByteLen());
	cudaMemcpyAsync(dev_a, a.data, a.ByteLen(),cudaMemcpyHostToDevice, stream);
	cudaMemcpyAsync(dev_b, b.data, b.ByteLen(),cudaMemcpyHostToDevice, stream);

	pydemo::add impl(&stream,(T*)dev_a,(T*)dev_b,(T*)dev_o, out.shape .getElemcnt());
	cudaMemcpyAsync(out.data ,dev_o,out.ByteLen(),cudaMemcpyDeviceToHost, stream);
	cudastreamsynchronize(stream)

	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_o);
	cudastreamDestroy(stream);
}

PYBIND11_MODULE(PYDEMO,m)
{
	py::enum_<TensorType>(m,"TensorType",py::arithmetic())
	.value("UNKNOWN", TensorType::UNKNOWN)
	.value("UINT8”,TensorType::UINT8)
	.value("UINT16”,TensorType::UINT16)
	.value("UINT32",TensorType::UINT32)
	.value("UINT64", TensorType::UINT64)
	.value("INT8",TensorType::INT8)
	.value("INT16",TensorType::INT16)
	.value("INT32",TensorType::INT32)
	.value("INT64", TensorType::INT64)
	.value("FP8",TensorType::FP8)
	.value("FP16",TensorType::FP16)
	.value("FP32",TensorType::FP32)
	.value("FP64",TensorType::FP64)
	.export_values();
	m.def("add", [](int deviceId, py::array_t<int16_t>& bufA, py::array_t<int16_t>& bufB, py::array_t<int16_t>& bufo, TensorType tensorType){
		add(deviceId, bufA, bufB, bufo, tensorType);
	});
	m.def("add", [](int deviceld, py::array_t<int32_t>& bufA, py::array_t<int32_t>& bufB, py::array_t<int32_t>& bufo, TensorType tensorType){
		add(deviceId, bufA, bufB, bufo, tensorType);
	});
	m.def("add", &add<float>, "A function that addstwo arrays of floats using CUDA");
	m.def("add",&add<double>);

	m.def("test", &test);
}


