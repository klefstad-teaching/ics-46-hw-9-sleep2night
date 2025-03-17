#include "ladder.h"

void error(string word1, string word2, string msg){
    cerr << word1 << " " << word2 << " " << msg;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    size_t len1 = str1.size();
    size_t len2 = str2.size();
    size_t i = 0;
    size_t j = 0;
    int cnt = 0;
    to_lower(str1);
    to_lower(str2);
    while(cnt <= d && i < len1 && j < len2){
        if(str1[i] != str2[j]){
            if(len1 < len2) --i;
            else if(len1 > len2) --j;
            ++cnt;
        }
        ++i;
        ++j;
    }
    if(i == len1) cnt += len2 - j;
    else if(j == len2) cnt += len1 - i;
    return cnt <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
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
    string s = str;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if(!file.is_open()) {error("Function","load_words", "Can't open file"); return;}
    string word;
    while(file >> word)
        word_list.insert(word);
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