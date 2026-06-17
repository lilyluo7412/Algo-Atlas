class Solution {
/*
lc 2503 Maximum Score From Grid Queries with

在线访问:来一个询问回答一个
离线访问:把所有询问收集起来，一同处理一同回答。
*/
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries) {
        // 查询的下标按照查询值从小到大排序，方便离线
        int k = queries.size(), id[k];
        iota(id, id + k, 0);
        sort(id, id + k, [&](int i, int j) { return queries[i] < queries[j]; });

        vector<int> ans(k);
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq; // 最小堆
        pq.emplace(grid[0][0], 0, 0);
        grid[0][0] = 0; // 充当 vis 数组的作用
        int m = grid.size(), n = grid[0].size(), cnt = 0;
        for (int qi : id) {
            int q = queries[qi];
            while (!pq.empty() && get<0>(pq.top()) < q) {
                ++cnt;
                auto[_, i, j] = pq.top();
                pq.pop();
                for (auto &d : dirs) { // 枚举周围四个格子
                    int x = i + d[0], y = j + d[1];
                    if (0 <= x && x < m && 0 <= y && y < n && grid[x][y]) {
                        pq.emplace(grid[x][y], x, y);
                        grid[x][y] = 0; // 充当 vis 数组的作用
                    }
                }
            }
            ans[qi] = cnt;
        }
        return ans;
    }
};
