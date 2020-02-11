#include <iostream>
#include <fstream>


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::ofstream fout("output01.txt");
    fout << "Hello world!" << std::endl;
    fout.close();
    return 0;
}
