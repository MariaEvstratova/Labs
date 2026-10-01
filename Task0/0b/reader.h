#include <fstream>
#include <list>
#include <string>

class Reader {
private:
    std::ifstream in_;
public:
    explicit Reader(const std::string& fileName);
    bool isOpen() const;
    std::list<std::string> readLines();
};