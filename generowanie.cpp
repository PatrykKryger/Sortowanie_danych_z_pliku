#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::string filepath = "dane.txt";
    std::ofstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku!" << std::endl;
        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < 100000; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX * 100.0;
        file << x << std::endl;
    }

    file.close();

    std::cout << "Dane zostały zapisane do pliku." << std::endl;

    return 0;
}
