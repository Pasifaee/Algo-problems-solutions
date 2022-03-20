#include <iostream>
#include <algorithm>

int main() {
	bool res = true;

	int n, m;
	std::cin >> n >> m;

	long long etykiety[n + 1];
	for (int i = 1; i <= n; i++) etykiety[i] = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int zawodnik;
			std::cin >> zawodnik;
			if (j >= n / 2) {
				etykiety[zawodnik] |= (1LL << i);
			}
		}
	}

	std::sort(etykiety + 1, etykiety + n + 1);
	for (int i = 2; i <= n; i++) {
		if (etykiety[i] == etykiety[i - 1]) {
			res = false;
			break;
		}
	}

	if (res) std::cout << "TAK\n";
	else std::cout <<"NIE\n";

	return 0;
}
