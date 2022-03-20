#include <iostream>
#include <cmath>

#define M 1000000000

long long sum(long long const interval_tree[], int pow2, int element) {
    long long sum = 0;

    int position = int(pow(2, pow2)) + element;
    while (position > 1) {
        if (position % 2 == 0) sum = (sum + interval_tree[position + 1]) % M;
        position /= 2;
    }

    return sum;
}

void add(long long interval_tree[], int position, long long x) {
    while (position >= 1) {
        interval_tree[position] += x;
        interval_tree[position] %= M;
        position /= 2;
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    int permutation[n];
    for (int i = 0; i < n; i++) {
        std::cin >> permutation[i];
        permutation[i]--;
    }

    // making interval tree
    int pow2 = 1;
    while (pow(2, pow2) < n) pow2 *= 2;
    long long interval_tree[int(pow(2, pow2 + 1))];
    // new_inv[i] = number of p-inversions ending with element of value i
    // last_inv[i] = number of (p - 1)-inversions ...
    long long last_inv[n], new_inv[n];

    for (int i = 0; i < n; i++) {
        last_inv[i] = 1; // number of 1-inversions is 1 for each element
    }

    for (int p = 2; p <= k + 1; p++) {
        // resetting interval tree
        for (int i = 0; i < int(pow(2, pow2 + 1)); i++) {
            interval_tree[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            int current_el = permutation[i];
            new_inv[current_el] = sum(interval_tree, pow2, current_el);
            add(interval_tree,
                int(pow(2, pow2)) + current_el, last_inv[current_el]);
        }

        for (int i = 0; i < n; i++) {
            last_inv[i] = new_inv[i];
        }
    }

    std::cout << interval_tree[1] << "\n";
    return 0;
}
