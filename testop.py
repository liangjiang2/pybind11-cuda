import pydemo
import numpy as np
## 创建一个CUDA流
# stream = torch.cuda.stream()
pydemo.test("nihao" )
a = np.array([2,2,2,2,2,2,2,2,2,2]).astype(np.float64).reshape(2,5)
print(a.shape)
b= np.array([3,3,3,3,3,5,5,5,5,5).astype(np.float64).reshape(2,5)
out = np.zeros like(a)
pydemo.add(1,a, b, out, pydemo.TensorType.FP64)
print(out)
# npout = a+b
# print(npout)
