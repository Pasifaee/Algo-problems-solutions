#include <stdio.h>

#define MAX 1000
#define MOD 1000000000

int LSL[MAX][MAX], LSR[MAX][MAX];

int main() {
	int n;
	scanf("%d", &n);
	int list[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}

	// Initializing LSL for 1-element sublists.
	for (int i = 0; i < n; i++) {
		LSL[i][i] = 1;
	}

	for (int len = 2; len <= n; len++) {
		// Completing LSL.
		for (int i = 0; i <= n - len; i++) {
			int j = i + len - 1;
			if (list[i] < list[i + 1]) {
				LSL[i][j] += LSL[i + 1][j];
			}
			if (list[i] < list[j]) {
				LSL[i][j] += LSR[i + 1][j];
			}
			LSL[i][j] %= MOD;
		}

		// Completing LSR.
		for (int j = n - 1; j >= len - 1; j--) {
			int i = j - len + 1;
			if (list[j - 1] < list[j]) {
				LSR[i][j] += LSR[i][j - 1];
			}
			if (list[i] < list[j]) {
				LSR[i][j] += LSL[i][j - 1];
			}
			LSR[i][j] %= MOD;
		}
	}

	printf("%d", (LSL[0][n - 1] + LSR[0][n - 1]) % MOD);
}
