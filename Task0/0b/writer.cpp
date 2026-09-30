#include "writer.h"

Writer::Writer(const std::string& fileName): out_(fileName) {}

bool Writer::isOpen() const {
    return out_.is_open();
}

void Writer::write(const std::list<std::pair<std::string, int>>& words, int totalCount) {
    out_ << "Слово,Частота,Частота(в %)\n";
    for (const auto& w: words) {
        double percent = 100.0 * w.second / totalCount;
        out_ << w.first << "," << w.second << "," << percent << "\n";
    }
}