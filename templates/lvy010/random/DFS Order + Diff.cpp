/* 2445
dfs遍历给二叉树的每个节点标记连续的编号
再用差分数组统计每个节点被翻转的次数
最后统计被翻转奇数次（即最终为1）的节点数量
*/

#include <vector>
using namespace std;

class Solution {
private:
    int id;
    void dfs(int u, int p, vector<vector<int>>& adj, vector<int>& s, vector<int>& e) {
        s[u] = id;
        for (int v : adj[u])
            if (v != p)
                dfs(v, u, adj, s, e);
        e[u] = id++;
    }

public:
    int numberOfNodes(int n, vector<int>& q) {
        vector<vector<int>> adj(n);
        for (int u = 1; u < n; ++u) {
            int p = (u - 1) / 2;
            adj[p].push_back(u);
            adj[u].push_back(p);
        }

        vector<int> s(n), e(n);
        id = 0;
        dfs(0, -1, adj, s, e);

        vector<int> d(n + 1, 0);
        for (int x : q) {
            int u = x - 1;
            int l = s[u], r = e[u];
            d[l] ^= 1;
            if (r + 1 <= n) d[r + 1] ^= 1;
        }

        int c = 0, x = 0;
        for (int i = 0; i < n; ++i) {
            x ^= d[i];
            c += x & 1;
        }
        return c;
    }
};
