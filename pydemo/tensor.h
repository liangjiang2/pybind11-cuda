#include<vector>
#include<string>
#include<iostream>
#include <ostream>
namespace pydemo
{
	enum TensorType
	{
		UNKNOWN = -1,
		UINT8   = 0,	//内置
		UINT16	= 1,	//内置
		UINT32	= 2,	//内置
		UINT64	= 3,	//内置
		INT8	= 4,	//内置
		INT16	= 5,	//内置
		INT32	= 6,	//内置
		INT64	= 7,	//内置
		FP8		= 8,	//不支持
		FP16	= 9,	//不支持
		FP32	= 10,	//内置
		FP64	= 11,	//内置
	};
	
	int getElemsize(TensorType type)
	{
		switch(type)
		{
			case TensorType::UINT8:
			case TensorType::INT8:
			case TensorType::FP8:
				return 1;
			case TensorType::UINT16:
			case TensorType::INT16:
			case TensorType::FP16:
				return 2;
			case TensorType::UINT32:
			case TensorType::INT32:
			case TensorType::FP32:
				return 4;
			case TensorType::UINT64:
			case TensorType::INT64:
			case TensorType::FP64:
				return 8;
			default :
				return -1
		}
	}
	
	struct TensorShape
	{
		Tensorshape(std::vector<int64 t> shape):shape_(shape)
		{};
		int32_t getElemcnt()
		{
		
		}
		if(elem_cnt !=-1)return elem_cnt; 
		int32_t cnt = 1;
		for(auto i:shape_)
		{
			cnt *= i;
		}
		
		elem_cnt =cnt;
		return cnt;
		};
		
		friend std::ostream& operator<<(std::ostream& os, const TensorShape& shape)
		{
			os<<"(”;
			for(auto i: shape.shape_)
				os<< i <<",";
			os<<")";
			return os;		
		};

	
		int32_t elem_cnt =-1;
		std::vector<int64_t>shape_;
	}

	struct Tensor
	{
		Tensor(void* ptr, std::vector<int64 t> shape, TensorType tensor type,std::string name ="default")
		: data_(ptr),shape_(shape),tensor_type_(tensor_type), name_(name)	
		{
			elem_size_ = getElemsize(tensor_type_);
		};
		int32 t ByteLen()
		{
			return shape_.getElemcnt()* elem_size_ ;
		}

		void* data = nullptr;
		Tensorshape shape_;
		TensorType tensor_type_;
		int32_t elem_size_ = -1;
		std::string name_;
	}


}
