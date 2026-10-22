#include "wordStat.h"

std::vector<WordStat> toWordStats(
    const std::vector<std::pair<std::string, int>>& sortedWords,
    int totalCount) {

    std::vector<WordStat> stats;
    stats.reserve(sortedWords.size());

    for (const auto& w : sortedWords) {
        double percent = 100.0 * w.second / totalCount;
        stats.push_back({w.first, w.second, percent});
    }

    return stats;
}