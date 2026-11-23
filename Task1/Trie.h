#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <string>

struct Node {
    std::map<char, Node*> children;
    bool isEnd;
};

class Trie {
    Node* root;
    int count;
public:
    using size_type = std::size_t;

    Trie();
    ~Trie();

    Trie(const Trie& other);
    Trie(Trie&& other) noexcept;

    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other) noexcept;

    // --- базовые методы ---
    void insert(std::string_view s);
    bool contains(std::string_view s) const;
    bool erase(std::string_view s);
    size_type prefix_count(std::string_view pref) const;

    std::vector<std::string> words_with_prefix(std::string pref, size_type limit = 0) const;

    void clear();
    bool empty() const;
    size_type size() const;

    bool operator==(const Trie& other) const;
    bool operator!=(const Trie& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Trie& trie);
};

#endif //TRIE_H