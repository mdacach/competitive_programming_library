// code for https://codeforces.com/contest/20/problem/C
#include <bits/stdc++.h>

#define int int64_t

const int INF = 1e18;
const int MAX_NODES = 1e5 + 10;

using Edge = std::pair<int, int>;
using MinPriorityQueue = std::priority_queue<Edge, std::vector<Edge>, std::greater<>>;

std::vector<Edge> adj[MAX_NODES];
std::vector<int> min_dist(MAX_NODES, INF);
std::vector<int> parent(MAX_NODES);

void dijkstra(int source)
{
    min_dist[source] = 0;
    MinPriorityQueue pq;
    pq.emplace(0, source);
    while (!pq.empty())
    {
        const auto [_, current_node] = pq.top();
        pq.pop();
        for (auto [neighbor, weight] : adj[current_node])
        {
            const auto dist = min_dist[current_node] + weight;
            if (dist >= min_dist[neighbor])
                continue; // already visited
            min_dist[neighbor] = dist;
            parent[neighbor] = current_node;
            pq.emplace(dist, neighbor);
        }
    }
}

// source must be the same source as dijkstra!!!
auto shortest_path(int source, int end)
{
    std::vector<int> path;
    int current_node = end;
    while (current_node != source)
    {
        path.push_back(current_node);
        current_node = parent[current_node];
    }
    path.push_back(1);
    std::reverse(path.begin(), path.end());
    return path;
}

int32_t main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        std::cin >> a >> b >> w;
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }
    dijkstra(1);
    if (min_dist[n] == INF)
        std::cout << -1 << "\n";
    else
    {
        for (const auto x : shortest_path(1, n))
            std::cout << x << " ";
    }

    return 0;
}