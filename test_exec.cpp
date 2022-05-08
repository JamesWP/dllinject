#include <iostream>

extern "C" {
__declspec(dllimport) int blah();
}

int main(int argc, const char* argv[]) {
    blah();
    std::cout << "Main running" << std::endl;
    return 0;
}