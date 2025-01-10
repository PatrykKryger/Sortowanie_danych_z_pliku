#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/sysinfo.h>
#endif

// Funkcja do obliczania sumy
long long some_function() {
    long long total = 0;
    for (int i = 1; i < 1000000; ++i) {
        total += i;
    }
    return total;
}

// Funkcja do uzyskania informacji o CPU w systemie Linux
void get_cpu_info(std::ofstream &file) {
#ifdef _WIN32
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    file << "Liczba rdzeni CPU (fizycznych): " << sysInfo.dwNumberOfProcessors << std::endl;
#else
    file << "Liczba rdzeni CPU (fizycznych): " << std::thread::hardware_concurrency() << std::endl;
#endif
}

// Funkcja do uzyskania informacji o pamięci w systemie Linux
void get_memory_info(std::ofstream &file) {
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    file << "Całkowita pamięć RAM: " << statex.ullTotalPhys << " bytes\n";
    file << "Wykorzystana pamięć RAM: " << statex.ullTotalPhys - statex.ullAvailPhys << " bytes\n";
    file << "Wolna pamięć RAM: " << statex.ullAvailPhys << " bytes\n";
#else
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    file << "Całkowita pamięć RAM: " << memInfo.totalram << " bytes\n";
    file << "Wykorzystana pamięć RAM: " << (memInfo.totalram - memInfo.freeram) << " bytes\n";
    file << "Wolna pamięć RAM: " << memInfo.freeram << " bytes\n";
#endif
}

int main() {
    std::string filepath = "dane.txt";
    std::ifstream file(filepath);
    std::vector<double> lines;
    double x;
    
    while (file >> x) {
        lines.push_back(x);
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    std::sort(lines.begin(), lines.end());

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> execution_time = end_time - start_time;

    std::string sorted_filepath = "posortowane_dane.txt";
    std::ofstream sorted_file(sorted_filepath);
    for (auto &value : lines) {
        sorted_file << value << "\n";
    }

    std::string wynik_filepath = "wynik.txt";
    std::ofstream wynik_file(wynik_filepath);
    wynik_file << "Czas sortowania: " << execution_time.count() << " sekundy\n";
    wynik_file << "Program wykonujący sortowanie: C++\n";

    get_cpu_info(wynik_file);
    get_memory_info(wynik_file);

    // Dodatkowe informacje o systemie
    wynik_file << "System operacyjny: ";
#ifdef _WIN32
    wynik_file << "Windows\n";
#else
    wynik_file << "Linux\n";
#endif

    std::cout << "Informacje zostały zapisane do pliku " << wynik_filepath << "." << std::endl;

    return 0;
}
