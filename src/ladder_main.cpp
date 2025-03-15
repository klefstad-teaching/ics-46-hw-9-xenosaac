#include "ladder.h"

int main() {
    set<string> words;
    load_words(words, "words.txt");
    
    print_word_ladder(generate_word_ladder("cat", "dog", words));
    print_word_ladder(generate_word_ladder("car", "cheat", words));

    verify_word_ladder();
    return 0;
}