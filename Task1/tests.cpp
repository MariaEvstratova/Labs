#include <gtest/gtest.h>
#include <sstream>
#include "Trie.h"

Trie makeExample() {
    Trie t;
    for (const char* k : {"the", "a", "there", "answer", "any", "by", "bye", "their", "русский", "рус", "слово"})
        t.insert(k);
    return t;
}

TEST(TrieTest, EmptyTrie) {
    Trie t;
    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.size(), 0);
    EXPECT_FALSE(t.contains("a"));
}

TEST(TrieTest, ContainsWholeWordsOnly) {
    Trie t = makeExample();
    EXPECT_TRUE(t.contains("a"));
    EXPECT_TRUE(t.contains("any"));
    EXPECT_TRUE(t.contains("their"));
    EXPECT_FALSE(t.contains("th"));
    EXPECT_FALSE(t.contains("b"));
    EXPECT_FALSE(t.contains("sobaka"));
}

TEST(TrieTest, InsertDuplicateDontIncrease) {
    Trie t;
    t.insert("cat");
    t.insert("cat");
    EXPECT_EQ(t.size(), 1);
}

TEST(TrieTest, EraseExisting) {
    Trie t = makeExample();
    EXPECT_TRUE(t.erase("there"));
    EXPECT_FALSE(t.contains("there"));
    EXPECT_TRUE(t.contains("the"));
    EXPECT_TRUE(t.contains("their"));
    EXPECT_EQ(t.size(), 10);
}

TEST(TrieTest, EraseMissing) {
    Trie t = makeExample();
    EXPECT_FALSE(t.erase("th"));
    EXPECT_FALSE(t.erase("zzz"));
    EXPECT_EQ(t.size(), 11);
}

TEST(TrieTest, PrefixCount) {
    Trie t = makeExample();
    EXPECT_EQ(t.prefix_count("th"), 3);
    EXPECT_EQ(t.prefix_count("a"), 3);
    EXPECT_EQ(t.prefix_count("x"), 0);
    EXPECT_EQ(t.prefix_count(""), 11);
}

TEST(TrieTest, WordsWithPrefix) {
    Trie t = makeExample();
    std::vector<std::string> expected = {"the", "their", "there"};
    EXPECT_EQ(t.words_with_prefix("th"), expected);
    EXPECT_EQ(t.words_with_prefix("th", 2).size(), 2);
    EXPECT_TRUE(t.words_with_prefix("q").empty());
}

TEST(TrieTest, Clear) {
    Trie t = makeExample();
    t.clear();
    EXPECT_TRUE(t.empty());
    EXPECT_FALSE(t.contains("a"));
}

TEST(TrieTest, Copy) {
    Trie a = makeExample();
    Trie b;
    b = a;
    EXPECT_EQ(a, b);
    b = b;
    EXPECT_EQ(b.size(), 11);
    b.insert("new");
    EXPECT_FALSE(a.contains("new"));
    EXPECT_NE(a, b);
}

TEST(TrieTest, Move) {
    Trie a = makeExample();
    Trie b = std::move(a);
    EXPECT_EQ(b.size(), 11);
    Trie c;
    c = std::move(b);
    EXPECT_TRUE(c.contains("bye"));
}

TEST(TrieTest, OutputOperator) {
    Trie t;
    t.insert("b");
    t.insert("a");
    std::ostringstream out;
    out << t;
    EXPECT_NE(out.str().find("a"), std::string::npos);
    EXPECT_LT(out.str().find("a"), out.str().find("b"));
}