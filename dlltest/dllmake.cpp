#include <stdio.h>

// compiled using:
// clang++ -shared -o output.dll dllmake.cpp

// well actually this one on my machine;
// gcc -c dllmake.cpp
// gcc -shared -o mydll.dll dllmake.o //add -shared to create a dll, will output "mydll.dll"

// tells compiler that
// function names should be preserved.
// that is, not to "mangle" names.
// https://en.wikipedia.org/wiki/Name_mangling#Simple_example
extern "C" {

__declspec(dllexport) void print_hello() {
  printf("hello!!\n");
}

} // extern "C"
