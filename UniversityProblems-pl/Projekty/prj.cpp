#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    /* INPUT */
    int projects_num, e, to_do;
    std::cin >> projects_num >> e >> to_do;
    int prog[projects_num];
    for (int i = 0; i < projects_num; i++) {
        std::cin >> prog[i];
    }
    std::vector<int> projects[projects_num];
    int indeg[projects_num] = {0};
    for (int i = 0; i < e; i++) {
        int a, b;
        std::cin >> a >> b;
        projects[b - 1].push_back(a - 1);
        indeg[a - 1]++;
    }

    /* SOLVE */
    int res = 0;

    std::priority_queue<std::pair<int, int>> Q;
    for (int i = 0; i < projects_num; i++) {
        if (indeg[i] == 0) {
            Q.push(std::make_pair(-prog[i], i));
        }
    }

    while (to_do--) {
        int project = Q.top().second;
        int programmers = -Q.top().first;
        Q.pop();

        res = std::max(res, programmers);
        for (int adj : projects[project]) {
            indeg[adj]--;
            if (indeg[adj] == 0) {
                Q.push(std::make_pair(-prog[adj], adj));
            }
        }
    }

    std::cout << res << "\n";
    return 0;
}
