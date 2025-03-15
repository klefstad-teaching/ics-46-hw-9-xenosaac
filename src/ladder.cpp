#include "ladder.h"
#include <algorithm>
#include <unordered_set>

void error(string term1, string term2, string message) {
    cout << "Error: " << message << " between terms: " << term1 << " and " << term2 << endl;
}

bool within_edit_threshold(const string& s, const string& t, int max_diff) {
    if (s == t) return true;
    
    int s_len = s.length(), t_len = t.length();
    int length_diff = s_len - t_len;
    if (abs(length_diff) > max_diff)
        return false;

    int i = 0, j = 0;
    bool discrepancy_found = false;

    do {
        if (i < s_len && j < t_len && s[i] == t[j]) {
            i++;
            j++;
            continue;
        }
        
        if (discrepancy_found) return false;
        discrepancy_found = true;
        
        if (s_len == t_len) {
            i++;
            j++;
        } else if (s_len > t_len) {
            i++;
        } else {
            j++;
        }
    } while (i < s_len || j < t_len);

    return discrepancy_found;
}

bool is_adjacent(const string& term1, const string& term2) {
    return within_edit_threshold(term1, term2, 1);
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
    
    cout << sequence[0];
    for (size_t i = 1; i < sequence.size(); ++i) {
        cout << " " << sequence[i];
    }

    cout << "\nTotal cost is " << (sequence.size() - 1) << '\n' << endl;
}

#define check_assert(condition) cout << #condition << (condition ? " valid" : " invalid") << endl;

void verify_word_ladder() {
    set<string> dictionary;
    load_words(dictionary, "words.txt");

    struct TestCase {
        string start;
        string end;
        size_t expected_length;  
    };

    vector<TestCase> tests = {
        {"cat", "dog", 4},
        {"marty", "curls", 6},
        {"code", "data", 6},
        {"work", "play", 6},
        {"sleep", "awake", 8},
        {"car", "cheat", 4}
    };

    for (const auto& test : tests) {
        vector<string> result = generate_word_ladder(test.start, test.end, dictionary);
        print_word_ladder(result);
        check_assert(result.size() == test.expected_length);
    }
}