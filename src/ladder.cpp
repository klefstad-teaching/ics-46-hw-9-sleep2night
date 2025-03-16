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
        swap(prev, curr);
    }
    return prev[len2] <= d;
}

bool exceeds_d(const vector<int>& v, int d){
    for(int val : v)
        if(val <= d) return false;
    return true;
}

bool is_adjacent(const string& word1, const string& word2){
    string w1 = to_lower(word1);
    string w2 = to_lower(word2);
    return edit_distance_within(w1, w2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if(begin_word == end_word || word_list.find(end_word) == word_list.end()) return {};

    queue<vector<string>> ladder_q;
    ladder_q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while(!ladder_q.empty()){
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string last_word = ladder.back();

        for(const string& word : word_list){
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end()){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if(word == end_word) return new_ladder;
                ladder_q.push(new_ladder);
            }
        }
    }
    return {};
}
string to_lower(const string& str){
    string lowercase = str;
    for(char& c : lowercase)
        c = tolower(c);
    return lowercase;
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if(!file.is_open()) {error("Function","load_words", "Can't open file"); return;}
    string word;
    while(file >> word)
        word_list.insert(to_lower(word));
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){cout << "No word ladder found." << endl; return;}
    cout << "Word ladder found: ";
    for(const string& s : ladder)
        cout << s << " ";
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}