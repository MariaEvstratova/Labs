#include <iostream>
#include <string>

#include "reader.h"
#include "wordCounter.h"
#include "wordStat.h"
#include "writer.h"

#define arguments_number 3
#define header "Слово,Частота,Частота (в %)"

int main(int argc, char** argv) {
    if (argc != arguments_number) {
        std::cout << "Недостаточно аргументов\n";
        return 1;
    }

    std::string input = argv[1];
    std::string output = argv[2];

    Reader reader(input);
    if (!reader.isOpen()) {
        std::cerr << "Файл не найден\n";
        return 1;
    }

    WordCounter counter;
    counter.readAll(reader);

    auto sortedWords = counter.sortWords();
    auto stats = toWordStats(sortedWords, counter.getTotalCount());

    Writer writer(output);
    if (!writer.isOpen()) {
        std::cerr << "Не удалось открыть выходной файл\n";
        return 1;
    }

    writer.write(header, stats);

    return 0;
}