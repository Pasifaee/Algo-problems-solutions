#include <stdio.h>

long long max(long long a, long long b) {
    if (a >= b) return a;
    else return b;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    long long prices[n];
    for (size_t i = 0; i < n; i++) {
        scanf("%lld", &prices[i]);
    }

    // creating suffix sum array
    long long prices_sum[n], sum = 0;
    for (size_t i = n; i-- > 0;) {
        sum += prices[i];
        prices_sum[i] = sum;
    }

    // creating array of last numbers of other parity to the left
    int last_odd = -1, last_even = -1;
    int last_other_left[n];
    for (int i = 0; i < n; i++) {
        if (prices[i] % 2 == 0) {
            last_even = i;
            last_other_left[i] = last_odd;
        }
        else {
            last_odd = i;
            last_other_left[i] = last_even;
        }
    }

    // creating array of last numbers of other parity to the right
    last_odd = -1, last_even = -1;
    int last_other_right[n];
    for (int i = n; i-- > 0;) {
        if (prices[i] % 2 == 0) {
            last_even = i;
            last_other_right[i] = last_odd;
        }
        else {
            last_odd = i;
            last_other_right[i] = last_even;
        }
    }

    // number of questions
    size_t q;
    scanf("%zu", &q);
    size_t k;
    long long res;
    for (size_t i = 0; i < q; i++) {
        scanf("%zu", &k);
        res = prices_sum[n - k];
        if (res % 2 == 1) {
            printf("%lld\n", res);
            continue;
        }
        else {
            if (k == n) {
                printf("-1\n");
                continue;
            }
            long long in_sum = prices[n - k], out_sum = prices[n - k - 1];
            long long res1, res2;
            if ((in_sum + out_sum) % 2 == 1) {
                res1 = res + out_sum - in_sum;
                if (last_other_right[n - k] != -1 && last_other_left[n - k - 1] != -1) {
                    in_sum = prices[last_other_right[n - k]];
                    out_sum = prices[last_other_left[n - k - 1]];
                    res2 = res + out_sum - in_sum;
                }
                else {
                    res2 = -1;
                }
            }
            else {
                if (last_other_right[n - k] != -1) {
                    long long in_sum_2 = prices[last_other_right[n - k]];
                    res1 = res + out_sum - in_sum_2;
                }
                else {
                    res1 = -1;
                }
                if (last_other_left[n - k - 1] != -1) {
                    long long out_sum_2 = prices[last_other_left[n - k - 1]];
                    res2 = res + out_sum_2 - in_sum;
                }
                else {
                    res2 = -1;
                }
            }
            res = max(res1, res2);
            printf("%lld\n", res);
        }
    }

}