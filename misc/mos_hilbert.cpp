// https://codeforces.com/contest/86/problem/D
// with Hilbert order: https://codeforces.com/blog/entry/61203
#include <bits/stdc++.h>

//#define int int64_t

const int BLOCK_SIZE = 450;

inline int64_t gilbertOrder(int x, int y, int pow, int rotate)
{
    if (pow == 0)
    {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = { 3, 0, 0, 1 };
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = gilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

struct Query
{
    int left, right, index;
    int64_t ord;
    bool operator<(const Query& other) const
    {
            return ord < other.ord;
//        const int this_block = left / BLOCK_SIZE;
//        const int other_block = other.left / BLOCK_SIZE;
//        if (this_block != other_block)
//            return this_block < other_block;
//        else
//            return this_block % 2 ? right < other.right : right > other.right;
    };

    inline void calcOrder() {
        ord = gilbertOrder(left, right, 21, 0);
    }
};

struct Answer
{
    std::array<int, static_cast<int>(1e6 + 5)> frequency{};
    int64_t sum = 0;

    void insert(int x)
    {
        const auto previous_frequency = frequency[x];
        const auto previous_contribution = 1LL * previous_frequency * previous_frequency * x;
        const auto new_contribution = 1LL * (previous_frequency + 1) * (previous_frequency + 1) * x;
        frequency[x]++;
        sum += new_contribution - previous_contribution;
    }

    void remove(int x)
    {
        assert(frequency[x]);
        const auto previous_frequency = frequency[x];
        const auto previous_contribution = 1LL * previous_frequency * previous_frequency * x;
        const auto new_contribution = 1LL * (previous_frequency - 1) * (previous_frequency - 1) * x;
        frequency[x]--;
        sum += new_contribution - previous_contribution;
    }
};

auto main() -> int32_t
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, t;
    std::cin >> n >> t;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    std::vector<Query> queries(t);
    for (int query_index = 0; query_index < t; query_index++)
    {
        int l, r;
        std::cin >> l >> r;
        queries[query_index] = { l, r, query_index };
        queries[query_index].calcOrder();
    }
    std::sort(queries.begin(), queries.end());
    std::vector<int64_t> answers(t);
    int current_left = 0;
    int current_right = 0;
    Answer answer;
    for (auto [this_left, this_right, index, order] : queries)
    {
        for (int r = current_right + 1; r <= this_right; r++)
            answer.insert(a[r]);
        for (int l = current_left - 1; l >= this_left; l--)
            answer.insert(a[l]);
        for (int l = current_left; l < this_left; l++)
            if (l)
                answer.remove(a[l]);
        for (int r = current_right; r > this_right; r--)
            answer.remove(a[r]);
        current_left = this_left;
        current_right = this_right;
        answers[index] = answer.sum;
    }
    for (auto x : answers)
        std::cout << x << "\n";

    return 0;
}