#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
    exit(1);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1 - len2) > d) {
        return false;
    }
    int i = 0;
    int j = 0;
    int diff = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff++;
            if (diff > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }
    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> current_level_visited;
        for (int i = 0; i < level_size; ++i) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();
            for (const string& word : word_list) {
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    current_level_visited.insert(word);
                    ladder_queue.push(new_ladder);
                }
            }
        }
        for (const string& word : current_level_visited) {
            visited.insert(word);
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    if (word_list.empty()) {
        cerr << "Error: Loaded word list is empty!" << endl;
        exit(1);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i != ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << " \n";
}

void verify_word_ladder() {
    set<string> word_list;
    string filename1 = "../src/words.txt";
    load_words(word_list, filename1);
    vector<string> ladders[] = {
        generate_word_ladder("cat", "dog", word_list),
        generate_word_ladder("marty", "curls", word_list),
        generate_word_ladder("code", "data", word_list),
        generate_word_ladder("work", "play", word_list),
        generate_word_ladder("sleep", "awake", word_list),
        generate_word_ladder("car", "cheat", word_list)
    };
    for (const auto& ladder : ladders) {
        if (!ladder.empty()) {
            print_word_ladder(ladder);
        }
    }
}