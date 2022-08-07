#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string &s1) {
    s1.erase(std::remove_if(s1.begin(),
                            s1.end(),
                            [](unsigned char ch) { return !std::isalnum(ch); }),
             s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    int count = 0;
    std::string word;
    map<string, int> wordsCountMap;
    unordered_map<string, int> wordsCountUnorderedMap;

    while (cin >> word) {
        toLowerAlpha(word);

        if (!word.empty()) {
            wordsCountMap[word]++;
//            wordsCountUnorderedMap[word]++;
            count++;
        }

    }

    cout << "Number of distinct words : " << count << endl;
    cout << "\nThe top 20 most popular words: \n";

    multimap<int, string> wordsCountOrdered;

    std::for_each(wordsCountMap.cbegin(),
                  wordsCountMap.cend(),
                  [&wordsCountOrdered](auto const &pair) {
                      wordsCountOrdered.emplace(pair.second, pair.first);
                  });

//    std::for_each(wordsCountUnorderedMap.cbegin(),
//                  wordsCountUnorderedMap.cend(),
//                  [&wordsCountOrdered](auto const &pair) {
//                      wordsCountOrdered.emplace(pair.second, pair.first);
//                  });


    std::for_each_n(wordsCountOrdered.crbegin(),
                    std::min<size_t>(wordsCountOrdered.size(), 20),
                    [](auto const &pair) { std::cout << pair.second << ": " << pair.first << std::endl; });

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << diff.count() << "ms" << std::endl;

    // "Normal" map:    39ms
    // Unordered map:   31ms

    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */