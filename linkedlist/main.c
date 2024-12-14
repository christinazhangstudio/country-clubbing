#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    return 0;
}

// Error #1: UNADDRESSABLE ACCESS beyond top of stack: reading 0x00000099c17ff550-0x00000099c17ff558 8 byte(s)
// # 0 .text   
// # 1 _pei386_runtime_relocator
// # 2 __tmainCRTStartup
// # 3 .l_start
// # 4 ntdll.dll!RtlUserThreadStart
// Note: @0:00:00.097 in thread 26012
// Note: 0x00000099c17ff550 refers to 776 byte(s) beyond the top of the stack 0x00000099c17ff858
// Note: instruction: or     $0x0000000000000000 (%rcx) -> (%rcx)

// Error #2: POSSIBLE LEAK 54 direct bytes 0x00000226010801c0-0x00000226010801f6 + 0 indirect bytes
// # 0 replace_malloc                   [D:\a\drmemory\drmemory\common\alloc_replace.c:2580]
// # 1 msvcrt.dll!malloc_crt
// # 2 msvcrt.dll!_setargv  
// # 3 msvcrt.dll!_getmainargs
// # 4 pre_cpp_init
// # 5 msvcrt.dll!initterm  
// # 6 __tmainCRTStartup
// # 7 .l_start
// # 8 ntdll.dll!RtlUserThreadStart