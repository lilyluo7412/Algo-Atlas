/*
本题的难点在状态设计上，核心想法是把【没有填过的数】和当前元素的逆序对计算出来
这样子问题就不用考虑右边填过的数了。这样思考，可以简化逆序对的计算
使得每个子问题都只需考虑当前元素和左边没有填过的数的逆序对，
而不需要考虑当前元素和右边填过的数的逆序对
*/
class Solution {
    const int MOD = 1'000'000'007;
public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        vector<int> req(n, -1);
        req[0] = 0;
        for (auto& p : requirements) {
            req[p[0]] = p[1];
        }
        if (req[0]) {
            return 0;
        }

        int m = ranges::max(req);
        vector<vector<int>> memo(n, vector<int>(m + 1, -1)); // -1 表示没有计算过
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if (i == 0) {
                return 1;
            }
            int& res = memo[i][j]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            res = 0;
            if (int r = req[i - 1]; r >= 0) {
                if (j >= r && j - i <= r) {
                    res = dfs(dfs, i - 1, r);
                }
            } else {
                for (int k = 0; k <= min(i, j); k++) {
                    res = (res + dfs(dfs, i - 1, j - k)) % MOD;
                }
            }
            return res;
        };
        return dfs(dfs, n - 1, req[n - 1]);
    }
};
