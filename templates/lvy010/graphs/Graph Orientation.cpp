/*
一个图中连通三元组的最小度数

度数小→度数大
度数相等则小编号→大编号
经典三元环trio枚举优化
*/
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> d(n);
        for (auto &e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            d[u].insert(v), d[v].insert(u);
        }
        
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            if (d[u].size() < d[v].size() || (d[u].size() == d[v].size() && u < v))
                adj[u].emplace_back(v);
            else
                adj[v].emplace_back(u);
        }

        int ans = INT_MAX;
        for (int u = 0; u < n; ++u)
            for (int v : adj[u])
                for (int w : adj[v])
                    if (d[u].count(w))
                        ans = min(ans, (int)(d[u].size() + d[v].size() + d[w].size() - 6));
        
        return ans == INT_MAX ? -1 : ans;
    }
};
