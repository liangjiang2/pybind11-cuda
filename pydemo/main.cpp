#include"iostream'
#include"hello.h'
#include:<vector>
int main()
{
	cudastream t stream;
	cudasetDevice(1);
	cudastreamCreate(&stream);
	int N= 10;
	std::vector<int>a(N,2);
	std::vector<int>b(N, 3);
	std::vector<int>out(N，0);//在GPU上分配内存: GPU上分配的内存大小是N
	void *dev_a, *dev_b,*dev_o;
	cudaMalloc((void **)&dev_a,N* sizeof(int));
	cudaMalloc((void **)&dev_b,N* sizeof(int));
	cudaMalloc((void **)&dev_o,N* sizeof(int));
	cudaMemcpyAsync(dev_a, a.data(),N*sizeof(int),cudaMemcpyHostToDevice, stream);
	cudaMemcpyAsync(dev_b, b.data(),N*sizeof(int),cudaMemcpyHostToDevice, stream);
	pydemo::add_impl(&stream,(int32_t*)dev_a,(int32_t*)dev_b,(int32_t*)dev_o, N);
	cudaMemcpyAsync(out.data(),dev_o,N* sizeof(int),cudaMemcpyDeviceToHost, stream);
	cudastreamsynchronize(stream);
	std::cout<<"host_result="<<std::endl;
	for(auto i : out)
	{
		std::cout<<i<<","		
	}
	std::cout<<std::endl;

	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_o);
	cudastreamDestroy(stream);
	return 0;
}
