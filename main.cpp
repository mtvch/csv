#include <iostream>
#include "tuple_helper.h"
#include "csv_parser.h"
#include <vector>

int main() {
    std::ifstream file("test.csv");

    try {
        CSVParser<std::size_t, std::string> parser(file, 0);
        for (std::tuple<std::size_t, std::string> rs : parser) {
            std::cout << rs << std::endl;
        }
    }
    catch (const std::string &error) {
        std::cout << "ERROR: " << error << std::endl;
    }

    return 0;
}