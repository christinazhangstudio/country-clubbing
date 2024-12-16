#include <windows.h>
#include <stdio.h>

typedef void (*pfn)(const wchar_t *);

int main(int argc, char *argv[]) {
    // kernel32.dll is a known DLL,
    // this is for debugging that "LoadLibrary" works.
    HMODULE hDll = LoadLibrary("kernel32.dll");
    if (hDll) {
        printf("Kernel32.dll loaded successfully\n");
    } else {
        printf("Failed to load Kernel32.dll: %d\n", GetLastError());
    }  
   
    pfn fn;
    printf("loading DLL\n");
    HMODULE h = LoadLibrary("output.dll");
    if (h) {
        printf("DLL loaded succesfully\n");
        printf(h);
    } else {
        printf("Error loading DLL: %d\n", GetLastError());
        return 1;
    }

    fn = (pfn)GetProcAddress(h, "print_hello");
    if (fn) {
        // Call the function
        const wchar_t *message = L"world";
        fn(message);
    } else {
        printf("Error: Could not get function address: %d\n", GetLastError());
    }

    printf("loaded..");
    return 0;
}
