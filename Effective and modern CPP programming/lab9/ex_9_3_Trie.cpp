#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>

using namespace std;

/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code. 
 */
class Trie {
//    map<string, std::unique_ptr<Trie>> trie{};
    map<string, std::shared_ptr<Trie>> trie{};
public:
    static void printSentence(const std::vector<std::string> &sentence) {
        for (const auto &w: sentence)
            cout << w << " ";
    }

    void add(const std::vector<std::string> &sentence) {
        cout << "Adding : ";
        printSentence(sentence);
        cout << "\n";

        auto currTrie = this;
//        std::shared_ptr<Trie> currTrie{this};
        for (auto const &word: sentence) {
            auto ins = currTrie->trie.emplace(word, std::make_shared<Trie>());
            currTrie = ins.first->second.get();
//            currTrie = ins.first->second;
//            currTrie.reset(ins.first->second.get());
        }
    }

    void printPossibleEndings(const std::vector<std::string> &beginningOfSentence) {
        cout << "Endings for \"";
        printSentence(beginningOfSentence);
        cout << "\" are :\n";

        auto currTrie = this;
        for (auto const &word: beginningOfSentence) {
            currTrie = currTrie->trie.at(word).get();
        }

        std::vector<string> vec{};
        vec.emplace_back(" >");

        currTrie->printRecursively(vec, 1);
    }

    void load(const std::string &fileName) {
        ifstream file(fileName);
        if (!file) {
            cerr << "Error when opening file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while (file >> word) {
            sentence.push_back(word);
            // is it end of the sentence?
            if (word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }

private:

    void printRecursively(std::vector<string> &vec, int length) {
        if (this->trie.empty()) {
            std::for_each_n(vec.begin(), length, [](const auto &str) { std::cout << str << " "; });
            std::cout << std::endl;
            return;
        }

        if (vec.size() <= length) {
            vec.resize(vec.size() * 2);
        }

        for (auto const &[word, trieRecursive]: this->trie) {
            vec[length] = word;
            trieRecursive->printRecursively(vec, length + 1);
        }
    }
};


int main() {
//    Trie dictionary;
    auto dictionary = std::make_shared<Trie>();
    dictionary->load("../sample.txt");
    //dictionary.load("hamletEN.txt");

    dictionary->printPossibleEndings({"Curiosity"});
    dictionary->printPossibleEndings({"Curiosity", "killed"});
    dictionary->printPossibleEndings({"The", "mouse", "was", "killed"});

    /* cout << "Beginning of sentence (ended with single .): ";
    string word;
    vector<string> sentence;
    while(true){
        cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
    }*/
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */