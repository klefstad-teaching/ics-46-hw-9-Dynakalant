#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"


TEST(Replace, Me) {
  EXPECT_TRUE(true);
}

TEST(Word_Ladder, Works) {
  set<string> testr;
  load_words(testr, "src/words.txt");
  vector<string> result = generate_word_ladder("code", "coders", testr);
  print_word_ladder(result);
}

TEST(Edit_distance, Works) {
  std::cout << edit_distance_within("apple", "bapple", 1) << '\n';
  std::cout << edit_distance_within("apple", "adple", 1) << '\n';
}


TEST(Dijkstras, Works) {
  Graph testr;
  file_to_graph("src/medium.txt", testr);
  vector<int> s = dijkstra_shortest_path(testr, 0, testr.previous);
  vector<int> e = extract_shortest_path(s, testr.previous, 3);

  print_path(e, 3);
}
