#include "wordCounter.h"

void WordCounter::addLines(const std::string& line) {
    std::string word;
    for (unsigned char symbol: line) {
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
        word.clear();
    }
}

std::list<std::pair<std::string, int>> WordCounter::sortWords() const {
    std::list<std::pair<std::string, int>> result(words_.begin(), words_.end());
    result.sort([](const std::pair<std::string, int>& a,
                   const std::pair<std::string, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    return result;
}

int WordCounter::getTotalCount() const {
    return totalCount_;
}