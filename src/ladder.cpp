#include "ladder.h"
#include <algorithm>
#include <unordered_set>

void error(string word1, string word2, string msg) {
    std::cout << "Error on words: " << word1 << ", " << word2 << ": " << msg << '\n';
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    size_t size_diff = std::max(str1.size(), str2.size()) - std::min(str1.size(), str2.size());
    if (size_diff > d) return false;

    int m = str1.size() + 1;
    int n = str2.size() + 1;
    //function LevenshteinDistance(char s[1..m], char t[1..n]):
    // for all i and j, d[i,j] will hold the Levenshtein distance between
    // the first i characters of s and the first j characters of t
    std::vector<std::vector<int>> dis(m, std::vector<int>(n, 0));

    //return false; // stop autograder
    //set each element in d to zero

    // source prefixes can be transformed into empty string by
    // dropping all characters
    for (int i = 1; i < m; ++i) dis[i][0] = i;

    // target prefixes can be reached from empty source prefix
    // by inserting every character
    for (int j = 1; j < n; ++j) dis[0][j] = j;

    for (int j = 1; j < n; ++j) {
        for (int i = 1; i < m; ++i) {
            int substitutionCost;
            if (str1[i-1] == str2[j-1]) { substitutionCost = 0; }
            else { substitutionCost = 1; }

            int de = dis[i-1][j] + 1;
            int ins = dis[i][j-1] + 1;
            int sub = dis[i-1][j-1] + substitutionCost;
            dis[i][j] = std::min({de,                   // deletion
                                ins,                   // insertion
                                sub});  // substitution
            //if (i == j && dis[i][j] > d) return false;
        }
    }
    //for (auto a1 : dis) { for (auto a2: a1) { std::cout << a2 << ' '; } std::cout << '\n'; }
    //std::cout << "distance between " << str1 << " and " << str2 << ": " << dis[m-1][n-1] << '\n';
    return dis[m-1][n-1] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    //return edit_distance_within(word1, word2, 1);
    size_t size_diff = std::max(word1.size(), word2.size()) - std::min(word1.size(), word2.size());
    if (size_diff > 1) return false;

    size_t differences = 0;
    if (word1.size() == word2.size()) {
        for (size_t i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i]) differences += 1;
            if (differences > 1) return false;
        }
        return true;
    } else {
        string smaller = word1.size() < word2.size() ? word1 : word2;
        string larger = word1.size() > word2.size() ? word1 : word2;
        for (size_t i = 0; i < larger.size(); ++i) {
            if (smaller[i-differences] != larger[i]) differences += 1;
            if (differences > 1) return false;
        }
        return true;
    }
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        std::vector<string> e;
        return e;
    }
    if (!std::binary_search(word_list.begin(), word_list.end(), end_word)) {
        std::vector<string> empty_vector;
        return empty_vector;
    }
    std::queue<vector<string>> ladder_queue;//queue of vector of strings
    std::vector<string> init_ladder = {begin_word};
    ladder_queue.push(init_ladder);
    std::unordered_set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        std::vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size()-1];
        for (auto word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    std::vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    std::vector<string> empty_vector;
    return empty_vector;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; in >> word;) word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() == 0) { std::cout << "No word ladder found."; }
    else { std::cout << "Word ladder found: "; }
    for (string word : ladder) std::cout << word << ' ';
    std::cout << '\n';
}

void verify_word_ladder() {
    return;
}