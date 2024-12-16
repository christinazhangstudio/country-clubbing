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

    // WHEN LOADING FROM ANOTHER LOCATION...
    // THIS DOESN'T WORK:
    //HMODULE h = LoadLibrary("C:\\Program Files\\some_party\\B30\\win_b64\\code\\bin\\some_party.dll");
    
    // THIS WORKS!
    //SetDllDirectory("C:\\Program Files\\some_party\\B30\\win_b64\\code\\bin");
    //HMODULE h = LoadLibrary("some_party.dll");
    // https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-security?redirectedfrom=MSDN maybe?
    // putting this in PATH env *should* work

    
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
