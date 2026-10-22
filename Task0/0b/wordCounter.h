#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H
#include <map>
#include <string>
#include <vector>
#include <utility>
#include "reader.h"

class WordCounter {
public:
    void addLine(const std::string& line);
    void readAll(Reader& reader);

    std::vector<std::pair<std::string, int>> sortWords() const;
    int getTotalCount() const;

private:
    std::map<std::string, int> words_;
    int totalCount_ = 0;
};
#endif