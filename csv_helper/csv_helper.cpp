#include "csv_helper.h"
#include <iostream>

size_t get_number_of_rows(std::ifstream &file, char escape_symbol, char delim) {
    size_t length = 0;
    std::string buffer;
    while (std::getline(file, buffer, delim)) {
        if (!(buffer.length() >= 2 && buffer.back() == escape_symbol && buffer[buffer.length() - 2] != escape_symbol)) {
            length++;
        }
    }
    file.clear();
    file.seekg(0);
    return length;
}

std::string get_nth_line(std::ifstream &file, size_t n, char escape_symbol, char delim) {
    std::string buffer;
    for (size_t i = 0; i <= n; i++) {
        if (!std::getline(file, buffer, delim)) {
            file.clear();
            file.seekg(0);
            return "";
        }
        std::string cont = buffer;
        while (cont.length() >= 2 && cont.back() == escape_symbol && cont[cont.length() - 2] != escape_symbol && std::getline(file, cont, delim)) {
            buffer.back() = delim;
            buffer += cont;
        }
    }
    file.clear();
    file.seekg(0);
    return buffer;
}

std::vector<std::string> split(const std::string &string, char escape_symbol, char delim) {
    std::stringstream ss(string);
    std::string item;
    std::vector<std::string> items;
    while (std::getline(ss, item, delim)) {
        items.push_back(item);
    }
    for (size_t i = 0; i < items.size() - 1; i++) {
        if (items[i].length() >= 2 && items[i].back() == escape_symbol && items[i][items[i].length() - 2] != escape_symbol) {
            items[i].back() = delim;
            items[i] += items[i + 1];
            items.erase(items.begin() + i + 1);
        }
    }
    return items;
}