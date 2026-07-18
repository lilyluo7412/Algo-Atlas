#include <bits/stdc++.h>
using namespace std;

using ll = long long;

pair<ll, int> treeSlidingWindow(
    int n,
    const vector<vector<pair<int, int>>>& g,  // 邻接表: {to, weight}
    const vector<int>& color                  // 每个节点的“颜色”/值
) {
    pair<ll, int> best = {-1, 0};  // {max_length, start_depth}
    vector<ll> dis = {0};           // 路径前缀和
    unordered_map<int, int> last;   // 颜色 -> 上一次出现的深度 + 1

    function<void(int, int, int)> dfs = [&](int u, int fa, int top_depth) {
        int c = color[u];
        int old = last[c];
        top_depth = max(top_depth, old);  // 窗口左边界更新

        // 更新最优解：长度 = 当前前缀和 - 窗口起点前缀和
        ll len = dis.back() - dis[top_depth];
        if (len > best.first || (len == best.first && top_depth < best.second)) {
            best = {len, top_depth};
        }

        last[c] = dis.size();  // 记录当前颜色位置

        for (auto& [v, w] : g[u]) {
            if (v != fa) {
                dis.push_back(dis.back() + w);
                dfs(v, u, top_depth);
                dis.pop_back();
            }
        }

        last[c] = old;  // 回溯恢复
    };

    dfs(0, -1, 0);
    return best;
}

// 示例主函数
int main() {
    int n;
    cin >> n;
    vector<int> color(n);
    for (int i = 0; i < n; ++i) cin >> color[i];

    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        g[x].emplace_back(y, w);
        g[y].emplace_back(x, w);
    }

    auto [max_len, start_depth] = treeSlidingWindow(n, g, color);
    cout << max_len << " " << start_depth << endl;
    return 0;
}
