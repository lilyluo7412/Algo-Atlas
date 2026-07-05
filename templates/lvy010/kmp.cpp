/*
KMP to fetch all match positions of two substrings in the main string,
then binary searches to check if any position of the second substring lies 
within range k of each first substring’s index and collects valid indices.
3008
*/
class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> posA = kmp(s, a);
        vector<int> posB = kmp(s, b);

        vector<int> ans;
        for (int i: posA) {
            auto it = lower_bound(posB.begin(), posB.end(), i);
            if (it != posB.end() && *it - i <= k ||
                it != posB.begin() && i - *--it <= k) {
                ans.push_back(i);
            }
        }
        return ans;
    }

private:
    vector<int> kmp(string &text, string &pattern) {
        int m = pattern.length();
        vector<int> pi(m);
        int c = 0;
        for (int i = 1; i < m; i++) {
            char v = pattern[i];
            while (c && pattern[c] != v) {
                c = pi[c - 1];
            }
            if (pattern[c] == v) {
                c++;
            }
            pi[i] = c;
        }

        vector<int> res;
        c = 0;
        for (int i = 0; i < text.length(); i++) {
            char v = text[i];
            while (c && pattern[c] != v) {
                c = pi[c - 1];
            }
            if (pattern[c] == v) {
                c++;
            }
            if (c == m) {
                res.push_back(i - m + 1);
                c = pi[c - 1];
            }
        }
        return res;
    }
};


