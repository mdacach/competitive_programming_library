// code for https://codeforces.com/contest/427/problem/C
#include <bits/stdc++.h>

#define int int64_t

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

std::vector<int> adj_original[N];
std::vector<int> adj_reversed[N];
std::vector<bool> visited_original(N);
std::vector<bool> visited_reversed(N);
std::vector<int> cost(N);
std::vector<int> component(N, -1);

std::vector<int> order;
void dfs_original(int u)
{
    if (visited_original[u])
        return;
    visited_original[u] = true;
    for (auto neighbor : adj_original[u])
        dfs_original(neighbor);
    order.push_back(u);
}

void dfs_reversed(int u, int c)
{
    if (visited_reversed[u])
        return;
    visited_reversed[u] = true;
    component[u] = c;
    for (auto neighbor : adj_reversed[u])
        dfs_reversed(neighbor, c);
}

int32_t main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> cost[i];
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        adj_original[u].push_back(v);
        adj_reversed[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (!visited_original[i])
            dfs_original(i); // populate order
    std::reverse(order.begin(), order.end());
    int c = 1;
    for (auto vertex : order)
    {
        if (!visited_reversed[vertex])
            dfs_reversed(vertex, c++);
    }
    std::map<int, std::vector<int>> component_to_vertices;
    for (int i = 1; i <= n; i++)
        component_to_vertices[component[i]].push_back(i);

    // get the least cost to build a station
    // and number of ways
    int total_ways = 1;
    int total_cost = 0;
    for (const auto& [c, vertices] : component_to_vertices)
    {
        int min = 1e9;
        for (auto v : vertices) {
            min = std::min(min, cost[v]);
        }
        int cnt = 0;
        for (auto v : vertices)
            cnt += cost[v] == min;

        total_cost += min;
        total_ways *= cnt;
        total_ways %= MOD;
    }

    std::cout << total_cost << " " << total_ways << "\n";

    return 0;
}
