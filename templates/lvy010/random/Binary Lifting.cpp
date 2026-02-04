
//树上倍增
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;
const int LOG = 20; // 2^20 足够覆盖 1e5 节点

vector<int> adj[MAXN];
int up[LOG][MAXN]; // up[k][u] 表示 u 向上跳 2^k 步的祖先
int depth[MAXN];   // 节点深度

// DFS 预处理深度和 2^0 级祖先（父节点）
void dfs(int u, int fa) {
    up[0][u] = fa;
    depth[u] = depth[fa] + 1;
    for (int v : adj[u]) {
        if (v != fa) dfs(v, u);
    }
}

// 预处理倍增表
void init(int root, int n) {
    dfs(root, 0);
    for (int k = 1; k < LOG; k++) {
        for (int u = 1; u <= n; u++) {
            up[k][u] = up[k-1][up[k-1][u]];
        }
    }
}

// 将 u 向上跳 k 步
int jump(int u, int k) {
    for (int i = 0; i < LOG; i++) {
        if (k & (1 << i)) u = up[i][u];
    }
    return u;
}

// 求 LCA
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    // 1. 将 u 跳到与 v 同深度
    u = jump(u, depth[u] - depth[v]);
    if (u == v) return u;
    // 2. 两个节点一起往上跳，直到父节点相同
    for (int k = LOG-1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return up[0][u];
}

int main() {
    int n, m;
    cin >> n >> m;
    // 建图
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // 初始化（根节点设为1）
    init(1, n);
    // 查询
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
    return 0;
}
