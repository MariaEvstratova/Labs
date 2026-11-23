#include "Trie.h"
#include <string>
#include <ostream>

void delete_node(Node* node) {
    if (!node) {
        return;
    }
    for (auto& p: node->children) {
        delete_node(p.second);
    }
    delete node;
}

Node* clone(const Node* node) {
    if (!node) {
        return nullptr;
    }
    Node* copy = new Node();
    copy->isEnd = node->isEnd;
    for (const auto& p: node->children) {
        copy->children[p.first] = clone(p.second);
    }
    return copy;
}

int count_words_from_that_node(const Node* node) {
    if (!node) {
        return 0;
    }
    int count = node->isEnd;
    for (const auto& p: node->children) {
        count += count_words_from_that_node(p.second);
    }
    return count;
}

void add_words_from_that_node(std::vector<std::string>& words, Node* node, std::string& buffer, Trie::size_type limit) {
    if (node->isEnd) {
        words.push_back(buffer);
    }
    Node* cur_node = node;
    for (const auto& p: cur_node->children) {
        if (limit != 0 && (words.size() >= limit)) {
            return;
        }
        buffer.push_back(p.first);
        add_words_from_that_node(words, p.second, buffer, limit);
        buffer.pop_back();
    }
}

bool is_equal(Node* a, Node* b) {
    if (!a && !b) {
        return true;
    }

    if (!a || !b) {
        return false;
    }

    if (a->isEnd != b->isEnd) {
        return false;
    }

    if (a->children.size() != b->children.size()) {
        return false;
    }

    for (const auto& p: a->children) {
        auto comp = b->children.find(p.first);
        if (comp == b->children.end()) {
            return false;
        }
        if (!is_equal(p.second, comp->second)) {
            return false;
        }
    }
    return true;
}

std::ostream& print_trie(std::ostream& os, Node* root, std::string& buffer) {
    Node* cur_node = root;

    if (cur_node->isEnd) {
        os << buffer << "\n";
    }
    for (const auto& p: cur_node->children) {
        buffer.push_back(p.first);
        print_trie(os, p.second, buffer);
        buffer.pop_back();
    }
    return os;
}

Trie::Trie() {
    root = new Node();
    count = 0;
};

Trie::~Trie() {
    delete_node(root);
};

Trie::Trie(const Trie& other) {
    root = clone(other.root);
    count = other.count;
};

Trie::Trie(Trie&& other) noexcept {
    root = std::move(other.root);
    count = std::move(other.count);
    other.root = nullptr;
    other.count = 0;
}

Trie& Trie::operator=(const Trie& other) {
    if (this == &other) {
        return *this;
    }
    delete_node(root);
    root = clone(other.root);
    count = other.count;
    return *this;
}

Trie& Trie::operator=(Trie&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete_node(root);
    root = std::move(other.root);
    count = std::move(other.count);
    other.root = nullptr;
    other.count = 0;
    return *this;
}

void Trie::insert(std::string_view s) {
    Node* cur_node = root;
    for (unsigned char c : s) {
        if (cur_node->children.find(c) == cur_node->children.end()) {
            cur_node->children[c] = new Node();
        }
        cur_node = cur_node->children[c];
    }
    if (!cur_node->isEnd) {
        cur_node->isEnd = true;
        count++;
    }
}

bool Trie::contains(std::string_view s) const {
    if (count == 0) {
        return false;
    }
    Node* cur_node = root;
    for (unsigned char c : s) {
        if (cur_node->children.find(c) == cur_node->children.end()) {
            return false;
        }
        cur_node = cur_node->children[c];
    }
    if (!cur_node->isEnd) {
        return false;
    }
    return true;
}

bool Trie::erase(std::string_view s) {
    if (!contains(s)) {
        return false;
    }
    Node* cur_node = root;
    std::vector<std::pair<unsigned char, Node*>> path;
    for (unsigned char c : s) {
        cur_node = cur_node->children[c];
        path.push_back({c, cur_node});
    }
    if (cur_node->isEnd) {
        cur_node->isEnd = false;
        count--;
    }
    if (cur_node->children.empty()) {
        for (int i = path.size() - 1; i >= 0; i--) {
            if (!path[i].second->isEnd && path[i].second->children.empty()) {
                Node* parent;
                if (i == 0) {
                    parent = root;
                } else {
                    parent = path[i - 1].second;
                }
                parent->children.erase(path[i].first);
                delete path[i].second;
            } else {
                break;
            }
        }
    }
    return true;
}

Trie::size_type Trie::prefix_count(std::string_view pref) const {
    Node* cur_node = root;
    for (const auto& c : pref) {
        if (cur_node->children.find(c) == cur_node->children.end()) {
            return false;
        }
        cur_node = cur_node->children[c];
    }

    return static_cast<size_type>(count_words_from_that_node(cur_node));
}

std::vector<std::string> Trie::words_with_prefix(std::string pref, size_type limit) const {
    std::vector<std::string> words;
    Node* cur_node = root;
    for (const auto& c: pref) {
        if (cur_node->children.find(c) == cur_node->children.end()) {
            return words;
        }
        cur_node = cur_node->children[c];
    }
    add_words_from_that_node(words, cur_node, pref, limit);
    return words;
}

void Trie::clear() {
    delete_node(root);
    root = new Node();
    count = 0;
}

bool Trie::empty() const {
    return count == 0;
}

Trie::size_type Trie::size() const {
    return static_cast<size_type>(count);
};

bool Trie::operator==(const Trie& other) const {
    if (this->count != other.count) {
        return false;
    }
    return is_equal(root, other.root);
}

bool Trie::operator!=(const Trie& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Trie& trie) {
    std::string buffer;
    return print_trie(os, trie.root, buffer);
}
