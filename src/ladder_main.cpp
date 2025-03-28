#include "ladder.h"

int main() {
    set<string> word_list;
    string filename = "../src/words.txt";
    load_words(word_list, filename);
    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;
    if (start_word == end_word) {
        error(start_word, end_word, "Start and end words must be different.");
    }
    vector<string> result = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(result);
    return 0;
}