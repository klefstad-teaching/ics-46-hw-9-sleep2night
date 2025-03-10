#include "ladder.h"

void error(string word1, string word2, string msg){
    cerr << word1 << " " << word2 << " " << msg;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size();
    int len2 = str2.size();

    if(abs(len1 - len2) > d) return false;

    vector<int> prev(len2+1), curr(len2 + 1);
    for(int j = 0; j <= len2; ++j) prev[j] = j;

    for(int i = 1; i <= len1; ++i){
        curr[0] = i;
        for(int j = 1; j <= len2; ++j){
            if(str1[i-1] == str2[j-1]) curr[j] = prev[j-1];
            else curr[j] = 1 + min({prev[j], curr[j-1], prev[j-1]});
        }
        if(exceeds_d(curr, d)) return false;
        swap(prev, curr)
    }
    return prev[n] <= d;
}

bool exceeds_d(const vector<int>& v, int d){
    for(int val : v)
        if(val <= d) return false;
    return true;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}