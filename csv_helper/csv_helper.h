#ifndef CSV_HELPER_H
#define CSV_HELPER_H

#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

size_t get_number_of_rows(std::ifstream &file, char escape_symbol = '"', char delim = '\n');
std::string get_nth_line(std::ifstream &file, size_t n, char escape_symbol = '"', char delim = '\n'); // "" - end, error otherwise; do not forget to trim
std::vector<std::string> split(const std::string &string, char escape_symbol = '"', char delim = ',');

#endif