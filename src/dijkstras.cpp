#include "ladder.h"
#include <algorithm>
#include <unordered_set>
#include <iterator>

void error(string wordA, string wordB, string msg) {
    cout << "Error: " << msg << " between words: " << wordA << " and " << wordB << endl;
}

bool edit_distance_within(const string& s1, const string& s2, int threshold) {
    if (s1 == s2) return true;
    
    const int lenA = s1.length(), lenB = s2.length();
    if (abs(lenA - lenB) > threshold) return false;

    int idx1 = 0, idx2 = 0;
    bool has_discrepancy = false;

    while (idx1 < lenA || idx2 < lenB) {
        bool chars_match = (idx1 < lenA && idx2 < lenB && s1[idx1] == s2[idx2]);
        
        if (chars_match) {
            ++idx1;
            ++idx2;
            continue;
        }
        
        if (has_discrepancy) return false;
        has_discrepancy = true;

        if (lenA > lenB) ++idx1;
        else if (lenB > lenA) ++idx2;
        else { ++idx1; ++idx2; }
    }
    return has_discrepancy;
}

bool is_adjacent(const string& first, const string& second) {
    return edit_distance_within(first, second, 1);
}

vector<string> generate_word_ladder(const string& start, const string& end, const set<string>& wordbank) {
    deque<vector<string>> ladder_queue;
    ladder_queue.emplace_back(1, start);
    
    unordered_set<string> visitedWords{start};

    for (; !ladder_queue.empty(); ladder_queue.pop_front()) {
        const auto current_path = ladder_queue.front();
        const string& last_word = current_path.back();

        for (auto it = wordbank.begin(); it != wordbank.end(); ++it) {
            const string& candidate = *it;
            
            if (!is_adjacent(last_word, candidate)) continue;
            if (visitedWords.count(candidate)) continue;
            
            visitedWords.insert(candidate);
            vector<string> new_path(current_path);
            new_path.emplace_back(candidate);

            if (candidate == end) return new_path;
            
            ladder_queue.emplace_back(move(new_path));
        }
    }
    return vector<string>{};
}

void load_words(set<string>& lexicon, const string& filename) {
    ifstream input_file(filename);
    string line;
    while (getline(input_file, line)) {
        if (!line.empty()) lexicon.insert(line);
    }
}

void print_word_ladder(const vector<string>& path) {
    if (path.empty()) {
        cout << "No word ladder found.\n";
        return;
    }
    
    cout << "Word ladder found: " << path.front();
    for (auto it = next(path.begin()); it != path.end(); ++it) {
        cout << ' ' << *it;
    }
    cout << " \n";
}

#define verify_condition(expr) cout << #expr << (expr ? " valid" : " invalid") << '\n'

void verify_word_ladder() {
    set<string> lexicon;
    load_words(lexicon, "words.txt");

    const vector<tuple<string, string, size_t>> testCases = {
        {"cat", "dog", 4},
        {"marty", "curls", 6},
        {"code", "data", 6},
        {"work", "play", 6},
        {"sleep", "awake", 8},
        {"car", "cheat", 4}
    };

    for (const auto& [start, end, expected] : testCases) {
        const auto result = generate_word_ladder(start, end, lexicon);
        verify_condition(result.size() == expected);
    }
}