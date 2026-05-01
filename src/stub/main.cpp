#include <zhvm.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

// This is the obfuscated ZHVM image we generated
unsigned char zhi_data[] = {
#include "zhi_bytes.inc"
};

void AntiDebugCheck() {
    if (IsDebuggerPresent()) {
        exit(1);
    }
}

int main() {
    // AntiDebugCheck();
    zhvm::memory mem(65536, 1024000); 
    std::string data((char*)zhi_data, sizeof(zhi_data));
    std::istringstream iss(data);
    
    try {
        mem.Load(iss);
        mem.Set(15, 0); 
        zhvm::Execute(&mem, false);
    } catch (...) {
        return -1;
    }
    return 0;
}
