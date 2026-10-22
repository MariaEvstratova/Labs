#ifndef WRITER_H
#define WRITER_H
#include <fstream>
#include <string>
#include <vector>
#include "wordStat.h"

class Writer {
public:
    explicit Writer(const std::string& fileName);

    bool isOpen() const;
    void write(const std::string& header, const std::vector<WordStat>& stats);

private:
    std::ofstream out_;
};
#endif
