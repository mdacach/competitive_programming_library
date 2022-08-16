nclude <bits/stdc++.h>

int64_t number_of_inversions = 0;
template <typename Iterator>
auto inner_merge_sort(Iterator start, Iterator end)
{
    auto size = std::distance(start, end);
    if (size == 1)
        return std::vector<typename Iterator::value_type>{ *start };

    auto middle = std::next(start, size / 2);
    const auto left = inner_merge_sort(start, middle);
    const auto right = inner_merge_sort(middle, end);

    auto left_iterator = std::begin(left);
    auto right_iterator = std::begin(right);

    auto current_vector = std::vector<typename Iterator::value_type>{};
    current_vector.reserve(size);
    auto take_from_left = [&](auto current_iterator)
    {
        current_vector.push_back(*left_iterator);
        number_of_inversions += std::distance(std::begin(right), right_iterator);
        std::advance(left_iterator, 1);
    };
    auto take_from_right = [&](auto current_iterator)
    {
        current_vector.push_back(*right_iterator);
        std::advance(right_iterator, 1);
    };

    for (auto current_iterator = start; current_iterator != end; ++current_iterator)
    {
        if (left_iterator == std::end(left))
            take_from_right(current_iterator);
        else if (right_iterator == std::end(right))
            take_from_left(current_iterator);
        else
        {
            auto from_left = *left_iterator;
            auto from_right = *right_iterator;
            if (from_left < from_right)
                take_from_left(current_iterator);
            else
                take_from_right(current_iterator);
        }
    }

    return current_vector;
}

auto merge_sort(const std::vector<int>& values)
{
    return inner_merge_sort(std::begin(values), std::end(values));
}

auto solve() -> void
{
    int n;
    std::cin >> n;

    std::vector<int> bottom(n);
    for (auto& x : bottom)
        std::cin >> x;

    merge_sort(bottom);
    std::cout << number_of_inversions << '\n';
    number_of_inversions = 0;
}

auto main() -> int32_t
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--)
        solve();

    return 0;
}
