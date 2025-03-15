#include "ladder.h"
#include <algorithm>
#include <unordered_set>

void error(string term1, string term2, string message) {
    cout << "Error: " << message << " between terms: " << term1 << " and " << term2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1 == str2) return true;
    
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1 - len2) > d) return false;

    int i = 0, j = 0;
    bool found_diff = false;

    while (i < len1 || j < len2) {
        if (i < len1 && j < len2 && str1[i] == str2[j]) {
            i++;
            j++;
            continue;
        }
        
        if (found_diff) return false;
        found_diff = true;
        
        if (len1 == len2) { i++; j++; }
        else if (len1 > len2) i++;
        else j++;
    }
    return found_diff;
}

bool is_adjacent(const string& term1, const string& term2) {
    return edit_distance_within(term1, term2, 1);
}

vector<string> generate_word_ladder(const string& origin, const string& target, const set<string>& vocabulary) {
    deque<vector<string>> processing_deque;
    processing_deque.push_back({origin});
    
    unordered_set<string> visited_terms = {origin};

    while (!processing_deque.empty()) {
        auto current_sequence = processing_deque.front();
        processing_deque.pop_front();
        string last_term = current_sequence.back();

        for (const auto& possible_term : vocabulary) {
            if (!is_adjacent(last_term, possible_term)) continue;
            
            if (visited_terms.count(possible_term)) continue;
            visited_terms.insert(possible_term);

            vector<string> new_sequence(current_sequence);
            new_sequence.push_back(possible_term);
            
            if (possible_term == target)
                return new_sequence;
            
            processing_deque.push_back(new_sequence);
        }
    }
    return {};
}

void load_words(set<string>& dictionary, const string& filename) {
    ifstream input_stream(filename);
    string entry;
    while (getline(input_stream, entry)) {
        if (!entry.empty())
            dictionary.insert(entry);
    }
}

void print_word_ladder(const vector<string>& sequence) {
    if (sequence.empty()) {
        cout << "No path exists\n";
        return;
    }
    for (size_t i = 0; i < sequence.size(); ++i) {
        cout << sequence[i] << " ";
    }
    cout << "\nTotal cost is " << (sequence.size() - 1) << endl;
}

#define check_assert(condition) cout << #condition << (condition ? " valid" : " invalid") << endl;

void verify_word_ladder() {
    set<string> dictionary;
    load_words(dictionary, "words.txt");
    check_assert(generate_word_ladder("cat", "dog", dictionary).size() == 4);
    check_assert(generate_word_ladder("marty", "curls", dictionary).size() == 6);
    check_assert(generate_word_ladder("code", "data", dictionary).size() == 6);
    check_assert(generate_word_ladder("work", "play", dictionary).size() == 6);
    check_assert(generate_word_ladder("sleep", "awake", dictionary).size() == 8);
    check_assert(generate_word_ladder("car", "cheat", dictionary).size() == 4);
}