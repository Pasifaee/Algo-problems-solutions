#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    /* INPUT */

    int capacity, cost, banned_num;
    std::cin >> capacity >> cost >> banned_num;
    int banned[banned_num];
    for (int i = 0; i < banned_num; i++) {
        std::cin >> banned[i];
    }
    int v, e; // Number of vertices and edges.
    std::cin >> v >> e;
    // Creating adjacency list.
    std::vector<int> adjacency[v + 1];
    for (int i = 0; i < e; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;
        adjacency[v1].push_back(v2);
        adjacency[v2].push_back(v1);
    }
    // Getting powerbanks values.
    int powerbanks[v];
    for (int i = 0; i < v; i++) {
        std::cin >> powerbanks[i];
    }

    /* SOLVING */

    // Finding any of the shortest paths (with BFS). //

    std::queue<int> to_visit;
    bool visited[v + 1] = {false}; // Initializing all visited values to false.
    int dist[v + 1] = {0}; // Distance from vertex v to vertex i.
    int prev[v + 1]; // Vertex preceding vertex v in the shortest path.

    to_visit.push(1);
    dist[1] = 0;
    prev[1] = -1;
    visited[1] = true;

    while (!to_visit.empty()) {
        int current = to_visit.front();
        to_visit.pop();
        if (current == v) { // We are in the last vertex.
            break;
        }
        for (int adj : adjacency[current]) {
            if (!visited[adj]) {
                to_visit.push(adj);
                dist[adj] = dist[current] + 1;
                prev[adj] = current;
                visited[adj] = true;
            }
        }
    }

    int shortest_dist = dist[v];
    if (shortest_dist == 0) { // We didn't ever visit the last vertex.
        std::cout << "-1\n";
        return 0;
    }
    int shortest_path[shortest_dist + 1];
    int path_v = v;
    for (int i = shortest_dist; i >= 0; i--) {
        shortest_path[i] = path_v;
        path_v = prev[path_v];
    }

    // Maximizing energy. //

    // Creating is_banned array.
    std::sort(banned, banned + banned_num);
    bool is_banned[capacity + 1] = {false};
    for (int ban : banned) {
        is_banned[ban] = true;
    }
    // achievable[n][k].first == true when value k can be achieved while being
    // in the vertex distant by n from the vertex 1
    // achievable[n][k].second == true when achievable[n][k].fst == true and
    // we used n-th powerbank to achieve value k
    std::pair<bool, bool> achievable[shortest_dist + 1][capacity + 1];
    // Initializing achievable with false.
    for (int i = 0; i <= shortest_dist; i++) {
        for (int j = 0; j <= capacity; j++) {
            achievable[i][j].first = false;
            achievable[i][j].second = false;
        }
    }

    achievable[0][capacity] = {true, false};
    for (int i = 0; i < shortest_dist; i++) {
        for (int j = 0; j <= capacity; j++) {
            if (achievable[i][j].first) {
                int new_energy = j - cost;
                if (new_energy >= 0) {
                    achievable[i + 1][new_energy].first = true;
                    new_energy += powerbanks[i + 1];
                    if (new_energy >= 0 && new_energy <= capacity && !is_banned[new_energy]) {
                        achievable[i + 1][new_energy].first = true;
                        achievable[i + 1][new_energy].second = true;
                    }
                }
            }
        }
    }

    // Searching for the maximum achievable energy.
    int max_energy = -1;
    for (int i = capacity; i >= 0; i--) {
        if (achievable[shortest_dist][i].first) {
            max_energy = i;
            break;
        }
    }

    if (max_energy == -1) { // No energy level was achievable.
        std::cout << "-1\n";
        return 0;
    }

    // charged[i] == true when accumulator needs to be charged in the
    // vertex distant by i from the vertex 1 to maximize energy.
    bool charged[shortest_dist + 1] = {false};
    int energy = max_energy;
    for (int i = shortest_dist; i >= 0; i--) {
        if (achievable[i][energy].second) {
            charged[i] = true;
        }

        if (achievable[i][energy].second) {
            energy -= powerbanks[i];
        }
        energy += cost;
    }

    std::vector<int> charged_by_place;
    for (int i = 0; i <= shortest_dist; i++) {
        if (charged[i]) {
            charged_by_place.push_back(shortest_path[i]);
        }
    }

    /* OUTPUT */

    std::cout << shortest_dist + 1 << " " << max_energy << " " << charged_by_place.size() << "\n";
    for (int i = 0; i <= shortest_dist; i++) {
        std::cout << shortest_path[i] << " ";
    }
    std::cout << "\n";
    for (int charged_here : charged_by_place) {
        std::cout << charged_here << " ";
    }
    std::cout << "\n";
}
