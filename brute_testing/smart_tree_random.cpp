// generating a tree in a not-so-stupid way
#include <bits/stdc++.h>

// generate random value in [a, b]
int rand(int a, int b)
{
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[])
{
    srand(atoi(argv[1])); // seed the randomness
    int n = rand(2, 20);
    printf("%d\n", n);
    std::vector<std::pair<int, int>> edges;
    for (int i = 2; i <= n; ++i)
    {
        edges.emplace_back(rand(1, i - 1), i);
    }

    std::vector<int> perm(n + 1); // re-naming vertices
    for (int i = 1; i <= n; ++i)
    {
        perm[i] = i;
    }
    std::random_shuffle(perm.begin() + 1, perm.end());

    std::random_shuffle(edges.begin(), edges.end()); // random order of edges

    for (auto& [a, b] : edges)
    {
        if (rand() % 2)
        {
            std::swap(a, b); // random order of two vertices
        }
        printf("%d %d\n", perm[a], perm[b]);
    }
}
