#include "reader.h"

Reader::Reader(const std::string& fileName) : in_(fileName) {}

bool Reader::isOpen() const {
    return in_.is_open();
}

bool Reader::readLine(std::string& line) {
    return static_cast<bool>(std::getline(in_, line));
}
