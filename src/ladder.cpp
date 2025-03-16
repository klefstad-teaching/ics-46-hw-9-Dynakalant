#include "ladder.h"
#include <algorithm>

bool is_adjacent(const string& word1, const string& word2) {
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
    std::queue<vector<string>> ladder_queue;//queue of vector of strings
    std::vector<string> init_ladder = {begin_word};
    ladder_queue.push(init_ladder);
    std::set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        std::vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size()-1];
        for (auto word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) != visited.end()) {
                visited.insert(word);
                std::vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    std::vector<string> empty_vector;
    return empty_vector;
}
