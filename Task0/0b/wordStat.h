#ifndef WORD_STAT_H
#define WORD_STAT_H
#include <string>
#include <vector>
#include <utility>

struct WordStat {
    std::string word;
    int count;
    double percent;
};

std::vector<WordStat> toWordStats(
    const std::vector<std::pair<std::string, int>>& sortedWords,
    int totalCount);

#endif
