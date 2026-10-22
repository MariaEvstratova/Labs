#ifndef READER_H
#define READER_H
#include <fstream>
#include <string>

class Reader {
public:
    explicit Reader(const std::string& fileName);

    bool isOpen() const;
    bool readLine(std::string& line);

private:
    std::ifstream in_;
};
#endif