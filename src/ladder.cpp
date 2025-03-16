#include "ladder.h"

void error(string word1, string word2, string msg){
    cerr << word1 << " " << word2 << " " << msg;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size();
    int len2 = str2.size();

    if(abs(len1 - len2) > d) return false;

    vector<int> v1(len2 + 1), v2(len2 + 1);

    for(int j = 0; j <=len2; ++j) v1[j] = j;

    for(int i = 0; i < len1; ++i){
        v2[0] = i + 1;
        bool within_d = false;

        for(int j = 0; j < len2; ++j){
            int deleteCost = v1[j + 1] + 1;
            int insertCost = v2[j] + 1;
            int replaceCost = (str1[i] == str2[j]) ? v1[j] : v1[j] + 1;
            v2[j + 1] = min({deleteCost, insertCost, replaceCost});
            if(v2[j + 1] <= d) within_d = true;
        }
        if(!within_d) return false;
        swap(v1, v2);
    }
    return v1[len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    string begin = to_lower(begin_word);
    string end = to_lower(end_word);
    if(begin == end || word_list.find(end) == word_list.end()) return {};

    queue<vector<string>> ladder_q;
    ladder_q.push({begin});
    set<string> visited;
    visited.insert(begin);
    while(!ladder_q.empty()){
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();
        string last_word = ladder.back();

        for(const string& word : word_list){
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end()){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if(word == end) return new_ladder;
                ladder_q.push(new_ladder);
            }
        }
    }
    return {};
}
string to_lower(const string& str){
    string lowercase = str;
    transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
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
    // cout << is_adjacent("cat","cab") << endl;
    // vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    // print_word_ladder(ladder);
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}