#include <fstream>
#include <list>
#include <string>
#include <utility>

class Writer {
private:
    std::ofstream out_;
public:
    explicit Writer(const std::string& fileName);
    bool isOpen() const;
    void write(const std::list<std::pair<std::string, int>>& words, int totalCount);
};