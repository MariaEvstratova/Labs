#include "writer.h"

Writer::Writer(const std::string& fileName): out_(fileName) {}

bool Writer::isOpen() const {
    return out_.is_open();
}

void Writer::write(const std::string& header, const std::vector<WordStat>& stats) {
    out_ << header << "\n";

    for (const auto& s : stats) {
        out_ << s.word << "," << s.count << "," << s.percent << "\n";
    }
}