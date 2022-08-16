#include <bits/stdc++.h>

/**
 * Prefix Function algorithm. \n
 * \n
 * Reference: https://cp-algorithms.com/string/prefix-function.html \n
 *
 * @param s String to compute Prefix Function of. \n
 * @return Vector p where p[i] is the length of longest proper prefix of the substring s[0...i] which is also a suffix
 * of this substring.
 */
auto prefix_function(const std::string& s) -> std::vector<int>
{
    int match_index = 0; // next letter I want to match
    const auto size = s.size();
    std::vector<int> p(size, 0); // vector to store partial answers
    // p[i] contains the length of the biggest suffix which is also a prefix of substring s[0..i]
    for (int current_index = 1; current_index < size; current_index++)
    {
        while (match_index) // try to save up on partial matches whenever possible
        {
            if (s[current_index] == s[match_index]) // we will be able to match
                break;
            else
                // we have already matched [0..match_index-1], so we can try to save this partial
                // going forward with current_index is augmenting the suffix portion of a match
                // while trying to match further is trying to augment the prefix portion of the match
                // so they both must be the same, and the best we can do is "the length of the biggest
                // suffix which is also a prefix", which is what is stored in p.
                match_index = p[match_index - 1];
        }
        if (s[current_index] == s[match_index]) // successful match
            p[current_index] = ++match_index;
    }
    return p;
}

/**
 * KMP algorithm for substring search. \n
 * \n
 * Uses special construct explained here: https://cp-algorithms.com/string/prefix-function.html \n
 * @param text Text to search pattern in. \n
 * @param pattern Pattern to be searched. \n
 * @return Vector with starting positions of pattern in text, or empty if none.
 */
auto KMP(const std::string& text, const std::string& pattern) -> std::vector<int>
{
    // WARNING, the special symbol used must NOT be present anywhere in the strings.
    const auto special_string = pattern + '$' + text;
    const auto p = prefix_function(special_string);
    // all p values that are equal to pattern.size() were matches
    const auto pattern_size = static_cast<int>(pattern.size());
    std::vector<int> matches; // starting position of matches, may be empty
    for (int i = 0; i < text.size(); i++)
    {
        // we have added characters to the start of the string
        const auto index = pattern_size + 1 + i;
        if (p[index] == pattern_size) // we have matched all pattern
            matches.push_back(i - (pattern_size - 1));
    }
    return matches;
}

int32_t main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    const auto n = static_cast<int>(s.size());

    const auto p = prefix_function(s);
    // looking at the last index, we can get all suffixes that are prefixes too
    std::vector<int> candidates;
    int possible_ans = p[n - 1];
    while (possible_ans)
    {
        candidates.push_back(possible_ans);
        possible_ans = p[possible_ans - 1];
    }
    std::reverse(candidates.begin(), candidates.end()); // increasing order

    // do a binary search in the candidates list
    // if we can match a large suffix, we can match the smaller one *containing* it (p[large-1])
    // these are indices in our candidates list, we will binary search it
    const auto list_size = static_cast<int>(candidates.size());
    int l = -1;        // special value that starts as true
    int r = list_size; // one past end, always false

    auto check = [&](int index)
    {
        // special flags
        if (index == -1)
            return true;
        if (index == list_size)
            return false;
        const auto substring_size = candidates[index];
        const auto substring = s.substr(0, substring_size);
        // we could reuse the prefix function we have already calculated here, but whatever
        // we need to match it in the middle, prefix and suffix don't count
        for (int i = 1; i < n - 1; i++)
            if (p[i] == substring_size)
                return true;
        return false;
    };

    while (r - l > 1)
    {
        int m = l + (r - l) / 2;
        if (check(m))
            l = m;
        else
            r = m;
    }
    if (l == -1)
        std::cout << "Just a legend\n";
    else
        std::cout << s.substr(0, candidates[l]) << "\n";

    return 0;
}