#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream f(argv[1], std::ios::binary);
    unsigned char b;
    int count = 0;
    std::cout << std::hex << std::setfill('0');
    while (f.read((char*)&b, 1) && count < 128) {
        std::cout << std::setw(2) << (int)b << " ";
        if (++count % 16 == 0) std::cout << std::endl;
    }
    return 0;
}
