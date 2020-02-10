//
// Created by Fran on 03.10.19.
//

#include "data/csvreader.h"
namespace AIX{namespace Data{

        boost::regex CsvReader::linesregx("\\r\\n|\\n\\r|\\n|\\r");
        boost::regex CsvReader::fieldsregx(",(?=(?:[^\"]*\"[^\"]*\")*(?![^\"]*\"))");

    std::string CsvReader::readfile(const std::string& filepath){
            std::ifstream in(filepath);
            std::string contents((std::istreambuf_iterator<char>(in)),
                                 std::istreambuf_iterator<char>());

            return contents;
        }

        std::vector<CsvReader::Row> CsvReader::parse(const char* data, unsigned int length)
        {
            std::vector<Row> result;

            // iterator splits data to lines
            boost::cregex_token_iterator li(data, data + length, linesregx, -1);
            boost::cregex_token_iterator end;

            while (li != end) {
                std::string line = li->str();
                ++li;

                // Split line to tokens
                boost::sregex_token_iterator ti(line.begin(), line.end(), fieldsregx, -1);
                boost::sregex_token_iterator end2;

                std::vector<std::string> row;
                while (ti != end2) {
                    std::string token = ti->str();
                    ++ti;
                    row.push_back(token);
                }
                if (line.back() == ',') {
                    // last character was a separator
                    row.push_back("");
                }
                result.push_back(row);
            }
            return result;
        }

    }}