/*
换根DP
先DFS算出以0为根需反转边总数
再reroot快速推导所有节点作根的反转次数
正负标记边正反方向
*/
class Solution {
    vector<vector<pair<int, int>>> g;
    vector<int> ans;

    void dfs(int x, int fa) {
        for (auto &[y, dir] : g[x]) {
            if (y != fa) {
                ans[0] += dir < 0;
                dfs(y, x);
            }
        }
    }

    void reroot(int x, int fa) {
        for (auto &[y, dir] : g[x]) {
            if (y != fa) {
                ans[y] = ans[x] + dir; // dir 就是从 x 换到 y 的「变化量」
                reroot(y, x);
            }
        }
    }

public:
    vector<int> minEdgeReversals(int n, vector<vector<int>> &edges) {
        g.resize(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].emplace_back(y, 1);
            g[y].emplace_back(x, -1); // 从 y 到 x 需要反向
        }

        ans.resize(n);
        dfs(0, -1);
        reroot(0, -1);
        return ans;
    }
};
