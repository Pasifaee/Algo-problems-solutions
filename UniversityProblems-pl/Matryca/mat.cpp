#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000001

size_t min(size_t a, size_t b) {
    if (a < b) return a;
    else return b;
}

int main() {
    char word[MAX_LEN];
    fgets(word, MAX_LEN, stdin);
    size_t word_len = strlen(word);
    if (word[word_len - 1] == '\n') {
        word[word_len - 1] = 0;
        word_len--;
    }

    // Minimal distance between two different letters in [word].
    size_t min_dist = word_len;
    // Last letter seen in the word (not counting '*').
    char last_letter;
    int last_letter_idx = -1;
    // Searching for the first letter in [word].
    for (int i = 0; word[i]; i++) {
        if (word[i] != '*') {
            last_letter = word[i];
            last_letter_idx = i;
            break;
        }
    }
    if (last_letter_idx == -1) {
        printf("1\n");
        return 0;
    }

    for (size_t i = last_letter_idx + 1; word[i]; i++) {
        if (word[i] != '*') {
            if (word[i] != last_letter) {
                min_dist = min(min_dist, i - last_letter_idx);
            }
            last_letter_idx = i;
            last_letter = word[i];
        }
    }
    printf("%zu\n", word_len - min_dist + 1);
}