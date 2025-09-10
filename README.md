## **Counter-Strike: Source SDK [x64]**

[![Build Status](https://github.com/nikmcphail/css-sdk/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/nikmcphail/css-sdk/actions/workflows/cmake-single-platform.yml)

## Description:
### This project is meant to serve as a "do-anything" SDK for Counter-Strike: Source. Currently this is only client-side, but in the future I may add another build version to include server features.

## **Create Build Folder**

```
cmake . -B build -DCMAKE_BUILD_TYPE=Debug/Release -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl
```
## **!!! Where it says Debug/Release above, choose one of the two !!!**

## **Build DLL**

```
ninja -C build
```

## Credits/References:
### - [emily](https://github.com/emilyinure), [rumour](https://github.com/rumourA), [batman](https://github.com/bamtna) (Answering All My Questions)
### - [Source SDK 2013](https://github.com/ValveSoftware/source-sdk-2013) (Valve's Official SDK)
### - [Amalgam](https://github.com/rei-2/Amalgam) (Updated Structures/NetVars)
