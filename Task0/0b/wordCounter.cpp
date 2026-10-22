#include "wordCounter.h"
#include <algorithm>

void WordCounter::addLine(const std::string& line) {
    std::string word;
    for (unsigned char symbol : line) {
        if (std::isalnum(symbol)) {
            word += static_cast<char>(std::tolower(symbol));
        } else if (!word.empty()) {
            words_[word] += 1;
            totalCount_ += 1;
            word.clear();
        }
    }
    if (!word.empty()) {
        words_[word] += 1;
        totalCount_ += 1;
    }
}

void WordCounter::readAll(Reader& reader) {
    std::string line;
    while (reader.readLine(line)) {
        addLine(line);
    }
}

std::vector<std::pair<std::string, int>> WordCounter::sortWords() const {
    std::vector<std::pair<std::string, int>> result(words_.begin(), words_.end());

    std::sort(result.begin(), result.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
                  if (a.second != b.second) return a.second > b.second;
                  return a.first < b.first;
              });

    return result;
}

int WordCounter::getTotalCount() const {
    return totalCount_;
}