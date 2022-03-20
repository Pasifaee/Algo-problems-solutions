#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

#define INF INT_MAX

int main() {
    int n;
    std::cin >> n;
    int islands[n][2];
    std::pair<int, int> x[n];
    std::pair<int, int> y[n];
    for (int i = 0; i < n; i++) {
        std::cin >> islands[i][0] >> islands[i][1];
        x[i].first = islands[i][0];
        y[i].first = islands[i][1];
        x[i].second = i;
        y[i].second = i;
    }
    std::sort(x, x + n);
    std::sort(y, y + n);

    std::vector<int> graph[n];
    for (int i = 0; i < n - 1; i++) {
        int v1 = x[i].second, v2 = x[i + 1].second;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
        v1 = y[i].second, v2 = y[i + 1].second;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    int dist[n];
    for (int i = 1; i < n; i++) dist[i] = INF;
    dist[0] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> priority_queue;
    for (int i = 0; i < n; i++) {
        priority_queue.push(std::make_pair(dist[i], i));
    }

    while (!priority_queue.empty()) {
        std::pair<int, int> current = priority_queue.top();
        priority_queue.pop();
        int island = current.second, d = current.first;
        if (d > dist[island]) continue;
        for (int adj : graph[island]) {
            int cost = std::min(std::abs(islands[island][0] - islands[adj][0]),
                                std::abs(islands[island][1] - islands[adj][1]));
            if (d + cost < dist[adj]) {
                dist[adj] = d + cost;
                priority_queue.push(std::make_pair(dist[adj], adj));
            }
        }
    }

    std::cout << dist[n - 1] << "\n";

    return 0;
}