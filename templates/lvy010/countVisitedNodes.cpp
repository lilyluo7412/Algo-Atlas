/*
lc2876
builds reversed graph & uses topological sort to isolate cycle nodes
DFS backward to calculate total reachable nodes for every point in functional graph with exactly one outgoing edge per node.
*/

class Solution {
public:
    vector<int> countVisitedNodes(vector<int>& g) {
        int n = g.size();
        vector<vector<int>> rg(n); // 反图
        vector<int> deg(n);
        for (int x = 0; x < n; x++) {
            int y = g[x];
            rg[y].push_back(x);
            deg[y]++;
        }

        // 拓扑排序，剪掉 g 上的所有树枝
        // 拓扑排序后，deg 值为 1 的点必定在基环上，为 0 的点必定在树枝上
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int x = q.front(); q.pop();
            int y = g[x];
            deg[y]--;
            if (deg[y] == 0) {
                q.push(y);
            }
        }

        vector<int> ans(n);

        // 在反图上遍历树枝
        auto rdfs = [&](this auto&& rdfs, int x, int depth) -> void {
            ans[x] = depth;
            for (int y : rg[x]) {
                if (deg[y] == 0) { // 树枝上的点在拓扑排序后，入度均为 0
                    rdfs(y, depth + 1);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (deg[i] <= 0) {
                continue;
            }
            vector<int> ring;
            for (int x = i; ; x = g[x]) {
                deg[x] = -1; // 将基环上的点的入度标记为 -1，避免重复访问
                ring.push_back(x); // 收集在基环上的点
                if (g[x] == i) {
                    break;
                }
            }
            for (int x : ring) {
                rdfs(x, ring.size()); // 为方便计算，以 ring.size() 作为初始深度
            }
        }

        return ans;
    }
};
