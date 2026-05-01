#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    std::ifstream f1(argv[1], std::ios::binary);
    std::ifstream f2(argv[2], std::ios::binary);
    
    std::vector<char> b1((std::istreambuf_iterator<char>(f1)), std::istreambuf_iterator<char>());
    std::vector<char> b2((std::istreambuf_iterator<char>(f2)), std::istreambuf_iterator<char>());
    
    if (b1.size() != b2.size()) {
        std::cout << "Size mismatch: " << b1.size() << " vs " << b2.size() << std::endl;
    }
    
    size_t limit = b1.size() < b2.size() ? b1.size() : b2.size();
    for (size_t i = 0; i < limit; ++i) {
        if (b1[i] != b2[i]) {
            std::cout << "Mismatch at offset " << i << ": 0x" << std::hex << (int)(unsigned char)b1[i] << " vs 0x" << (int)(unsigned char)b2[i] << std::endl;
            if (i > 0) std::cout << "Previous byte at " << i-1 << ": 0x" << (int)(unsigned char)b1[i-1] << " vs 0x" << (int)(unsigned char)b2[i-1] << std::endl;
            return 0;
        }
    }
    std::cout << "No mismatch found in first " << limit << " bytes." << std::endl;
    return 0;
}
