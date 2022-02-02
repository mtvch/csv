#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <fstream>
#include "csv_helper/csv_helper.h"
#include <tuple>
#include <string.h>
#include <iostream>

template <typename... Args>
class CSVParser {
    private:
        std::ifstream &m_file;
        size_t m_offset;
        char m_row_delim;
        char m_col_delim;
        char m_escape_symbol;

        class CSVPIterator {
            private:
                std::string m_buffer;
                CSVParser &m_parser;
                size_t m_index;
            public:
                explicit CSVPIterator(CSVParser &parser, const size_t &offset) : m_parser(parser), m_index(offset) {
                    m_buffer = get_nth_line(m_parser.m_file, m_index, m_parser.m_escape_symbol, m_parser.m_row_delim);
                }

                ~CSVPIterator() {

                }

                CSVPIterator& operator++() {
                    this->m_index++;
                    m_buffer = get_nth_line(m_parser.m_file, m_index, m_parser.m_escape_symbol, m_parser.m_row_delim);
                    return *this;
                }

                bool operator==(const CSVPIterator &iterator) {
                    return this->m_index == iterator.m_index && strcmp(this->m_buffer.c_str(), iterator.m_buffer.c_str()) == 0;
                }

                bool operator!=(const CSVPIterator &iterator) {
                    return !(*this == iterator);
                }

                std::tuple<Args...> operator*() {
                    if (m_index > get_number_of_rows(m_parser.m_file, m_parser.m_escape_symbol, m_parser.m_row_delim)) {
                        throw(std::string("operator*: out of range"));
                    }
                    return m_parser.parse_line(m_buffer);
                }
        };

    public:
        explicit CSVParser(std::ifstream &file, const size_t &offset, char row_delim = '\n', char col_delim = ',', char escape_symbol = '"') :
        m_file(file), m_offset(offset), m_row_delim(row_delim), m_col_delim(col_delim), m_escape_symbol(escape_symbol) {

        }

        ~CSVParser() {

        }

        CSVPIterator begin() {
            return CSVPIterator(*this, m_offset);
        }
        CSVPIterator end() {
            return CSVPIterator(*this, get_number_of_rows(m_file, m_escape_symbol, m_row_delim));
        }

        std::tuple<Args...> parse_line(std::string& line) {
            std::vector<std::string> items = split(line, m_escape_symbol, m_col_delim);
            std::tuple<Args...> t;
            if (sizeof...(Args) != items.size()) {
                throw("Line '" + line + "' has wrong number of columns");
            }
            try {
                add_each_to_tuple(t, items);
            }
            catch (const std::string &error) {
                throw("Line '" + line + "': " + error);
            }
            return t;
        }
};

#endif