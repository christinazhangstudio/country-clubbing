#include <stdio.h>
#include <wchar.h>

// compiled using:
// clang++ -shared -o output.dll dllmake.cpp

// tells compiler that
// function names should be preserved.
// that is, not to "mangle" names.
// https://en.wikipedia.org/wiki/Name_mangling#Simple_example
extern "C" {

__declspec(dllexport) void print_hello(const wchar_t *u) {
  wprintf(L"hello: %s\n", u);
}

} // extern "C"
