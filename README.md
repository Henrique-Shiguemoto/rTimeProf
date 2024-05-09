# rTimeProf

This is a simple C/C++ profiler to time code sections. It just profiles time, not memory usage. Tested with gcc, clang, g++ and clang++.

See <code>main.c</code> (or the c++ version) for a simple example of how to use the library.

## Features

- Create code section statistics (start time and end time)
- Code sections naming
- Multiplatform (Windows and Linux)

## How to Use

Just copy and paste <code>rTimeProf.c</code> and <code>rTimeProf.h</code> (or the c++ version) into your project and it should be good to go, then you can include the header file in your source files. Make sure you update your build system if it doesn't update automatically.

## Run Example

- C version: <code>make</code> then <code>make run</code>

- C++ version: <code>make cpp</code> then <code>make run</code>

## Technologies used

- C11
- Makefiles
- Sublime Text 3
