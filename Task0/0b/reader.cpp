#include "reader.h"

Reader::Reader(const std::string& fileName): in_(fileName) {}

bool Reader::isOpen() const {
    return in_.is_open();
}

std::list<std::string> Reader::readLines() {
    std::list<std::string> lines;
    std::string line;
    while (std::getline(in_, line)) {
        lines.push_back(line);
    }
    return lines;
}