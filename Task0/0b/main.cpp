#include <iostream>
#include "reader.h"
#include "wordCounter.h"
#include "writer.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Недостаточно аргументов\n";
        return 1;
    }

    Reader reader(argv[1]);
    if (!reader.isOpen()) {
        std::cerr << "Не удалось открыть входной файл\n";
        return 1;
    }

    WordCounter counter;
    for (const std::string& line: reader.readLines()) {
        counter.addLines(line);
    }

    Writer writer(argv[2]);
    if (!writer.isOpen()) {
        std::cerr << "Не удалось открыть выходной файл\n";
        return 1;
    }
    writer.write(counter.sortWords(), counter.getTotalCount());

    return 0;
}