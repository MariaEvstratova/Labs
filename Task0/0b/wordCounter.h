#include <list>
#include <map>
#include <string>
#include <utility>

class WordCounter {
private:
    std::map<std::string, int> words_;
    int totalCount_ = 0;
public:
    void addLines(const std::string& line);
    std::list<std::pair<std::string, int>> sortWords() const;
    int getTotalCount() const;
};