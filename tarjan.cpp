#include <vector>
#include <algorithm>
using namespace std;
//强连通分量+缩点
//Tarjan 找强连通分量 → 每个分量缩成一个点 → 建出有向无环新图（DAG）
//可直接做拓扑、统计入度出度等
const int MAXN = 2e5 + 10; // 按题目改

vector<int> g[MAXN];
int dfn[MAXN], low[MAXN], idx;
int stk[MAXN], in_stk[MAXN], top;
int scc[MAXN], scc_cnt; // scc[i] = 节点 i 所属的强连通分量编号

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk[++top] = u;
    in_stk[u] = 1;

    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stk[top--];
            in_stk[v] = 0;
            scc[v] = scc_cnt;
        } while (v != u);
    }
}

// 缩点：建出新图
vector<int> ng[MAXN]; // 缩点后的新图
int in_deg[MAXN], out_deg[MAXN];

void build_new_graph(int n) {
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (scc[u] != scc[v]) {
                ng[scc[u]].push_back(scc[v]);
            }
        }
    }

    // 去重（可选，避免重复边）
    for (int i = 1; i <= scc_cnt; i++) {
        sort(ng[i].begin(), ng[i].end());
        ng[i].erase(unique(ng[i].begin(), ng[i].end()), ng[i].end());
        out_deg[i] = ng[i].size();
        for (int v : ng[i]) in_deg[v]++;
    }
}

// 使用方式
void init(int n) {
    idx = top = scc_cnt = 0;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        ng[i].clear();
        dfn[i] = low[i] = scc[i] = in_stk[i] = in_deg[i] = out_deg[i] = 0;
    }
}

int main() {
    int n, m;
    // 读入建图...
    init(n);
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    build_new_graph(n);
    return 0;
}
