## **Counter-Strike: Source SDK [x64]**

### Description:
This project is meant to serve as a "do-anything" SDK for Counter-Strike: Source.

### Features:
- 

**Create Build Folder**

```
cmake . -B build -DCMAKE_BUILD_TYPE=Debug/Release -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl
```
## !!! Where it says Debug/Release above, choose one of the two !!!

**Build DLL**

```
ninja -C build
```