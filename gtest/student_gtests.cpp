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

