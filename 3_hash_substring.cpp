/*
    Finds a pattern in a text using Rabin-Karp's algorithm.
    The key trick of the algorithm is to pre-compute the 
    hashes in O(N) from the last one to the first using
    the fact that these values are similar.

    Input: two strings, the pattern P and the text T.
           1 <= |P| <= |T| <= 5*10^5
           Only latin letters
           Total length of the occurences of P in T doesn't
           exceed 10^8.
    Output: print all the positions of the occurences of P in
            T in ascending order. Use 0-based indexing of the
            positions in the text T. 
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

// Hashes a string
ull poly_hash(const string &s, const ull &prime, const ull &x) {
    ull hash = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        hash = (hash * x + s[i]) % prime;
    }
    return hash;
}

// Pre-computes the hashes
std::vector<long long> pre_compute_hashes(const string &s, const ull &pattern_length, const ull &prime, const ull &x) {
    int text_length = s.length(); 
    std::vector<long long> h(text_length - pattern_length + 1, 0);
    // Last chars with length of pattern
    std::string s2 = s.substr(text_length - pattern_length, pattern_length);
    // Get very last hash
    h[text_length - pattern_length] = poly_hash(s2, prime, x);
    long long y = pow(x, pattern_length);
    for (int i = text_length - pattern_length - 1; i >= 0; i--) {
        long long index = pattern_length + i;
        char first = s[i], second = s[index];
        h[i] = ((x * h[i+1] + s[i] - y * s[i + pattern_length] + prime) % prime + prime) % prime;
    }
    return h;
}

// Rabin-Karp algorithm
std::vector<int> rabin_karp(const string &s, const string &p) {
    ull prime = 997;
    ull x = 1;
    int text_length = s.length();
    int pattern_length = p.length();
    std::vector<int> result;
    ull pattern_hash = poly_hash(p, prime, x);
    std::vector<long long> hashes = pre_compute_hashes(s, pattern_length, prime, x);
    for (int i = 0; i <= text_length - pattern_length; i++) {
        if (pattern_hash != hashes[i]) continue;
        if (p.compare(s.substr(i, pattern_length)) == 0) result.push_back(i);
    }
    return result;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& t = input.text;
    const string& p = input.pattern; 
    std::vector<int> ans = rabin_karp(t, p);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
