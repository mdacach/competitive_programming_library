#include <bits/stdc++.h>

// generate a random number in [a, b]
int rand(int a, int b)
{
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[])
{
    // seed the randomness
    srand(atoi(argv[1])); // atoi(s) converts an array of chars to int
    int n = rand(2, 10);
    std::cout << n << '\n';
    std::set<int> used;
    for (int i = 0; i < n; ++i)
    {
        int x;
        do
        {
            x = rand(1, 10);
        } while (used.count(x));
        std::cout << x << ' ';
        used.insert(x);
    }
    std::cout << '\n';
}
