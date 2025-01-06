<div align="center">
<h2>
  ByteTrackLib
</h2>
</div>

This repository provides a C++ implementation of the [ByteTrack](https://github.com/ifzhang/ByteTrack) algorithm with Python bindings and easy cross-compilation.

### Compilation
To compile the project, follow these steps:
```bash
mkdir build && cmake ../
make -j4 install
```
Use `-DWITH_PYTHON=true` if you need to build the Python library.

### Cross Compile
For rv1106 compilation, use:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain/rv1106.toolchain.cmake ..
```

### Dependencies
No need to download separately; dependencies are embedded within the project:
- Eigen 3.3.9
- pybind11-2.10.4 (optional)

### Example Usage
```cpp
#include "ByteTracker.h"
#include <iostream>
int main(int argc, char* argv[]) 
{
    bytetrack::ByteTracker tracker;
    for (int i = 0; i < 20; i++) 
    {
        std::vector<bytetrack::Object> objects;
        objects.push_back({0.9, 0, {100+i*10, 100, 50, 50}});
        std::vector<bytetrack::Track> tracks = tracker.update(objects);
    }
    return 0;
}
```

### References:
- [ByteTrack](https://github.com/ifzhang/ByteTrack)
- [ByteTrack-cpp](https://github.com/Vertical-Beach/ByteTrack-cpp)

### Citation
```bibtex
@article{zhang2022bytetrack,
  title={ByteTrack: Multi-Object Tracking by Associating Every Detection Box},
  author={Zhang, Yifu and Sun, Peize and Jiang, Yi and Yu, Dongdong and Weng, Fucheng and Yuan, Zehuan and Luo, Ping and Liu, Wenyu and Wang, Xinggang},
  booktitle={Proceedings of the European Conference on Computer Vision (ECCV)},
  year={2022}
}
```