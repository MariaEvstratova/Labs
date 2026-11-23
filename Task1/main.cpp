#include "Trie.h"
#include <iostream>


int main() {
    Trie trie;
    const std::string keys[] = {"the", "a", "there",
                    "answer", "any", "by",
                    "bye", "their", "русский", "рус", "слово"};
    for (const auto& k : keys) {
        trie.insert(k);
    }
    std::cout << trie;
    return 0;
}