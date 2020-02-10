//
// Created by Fran on 03.10.19.
//

#ifndef GLOBAL_CSVREADER_H
#define GLOBAL_CSVREADER_H

#include<boost/regex.hpp>
#include <string>
#include <fstream>
#include <iterator>

namespace AIX{namespace Data{
        class CsvReader {
        private:
            static  boost::regex linesregx;
            static  boost::regex fieldsregx;

        public:
            typedef std::vector<std::string> Row;

            static std::string readfile(const std::string& filepath);

            static std::vector<Row> parse(const char* data, unsigned int length);

        };

    }}


#endif //GLOBAL_CSVREADER_H
