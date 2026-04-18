// 模板来自我的题单 https://leetcode.cn/circle/discuss/mOr1u6/
// 根据题目用 FenwickTree<int> t(n) 或者 FenwickTree<long long> t(n) 初始化
template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    // 使用下标 1 到 n
    FenwickTree(int n) : tree(n + 1) {}

    // a[i] ^= val
    // 1 <= i <= n
    // 时间复杂度 O(log n)
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] ^= val;
        }
    }

    // 求前缀异或和 a[1] ^ ... ^ a[i]
    // 1 <= i <= n
    // 时间复杂度 O(log n)
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res ^= tree[i];
        }
        return res;
    }
};

// 模板来自我的题单 https://leetcode.cn/circle/discuss/K0n2gO/
class LcaBinaryLifting {
    vector<int> depth;
    vector<vector<int>> pa;

public:
    vector<int> tin; // DFS 时间戳
    vector<int> tout;
    vector<int> path_xor_from_root; // 从根开始的路径的字母出现次数的奇偶性

    LcaBinaryLifting(vector<vector<int>>& edges, string& s) {
        int n = edges.size() + 1;
        int m = bit_width((uint32_t) n);
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        depth.resize(n);
        pa.resize(m, vector<int>(n, -1));
        tin.resize(n);
        tout.resize(n);
        path_xor_from_root.resize(n);
        path_xor_from_root[0] = 1 << (s[0] - 'a');
        int clock = 0;

        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            pa[0][x] = fa;
            tin[x] = ++clock;
            for (int y : g[x]) {
                if (y != fa) {
                    depth[y] = depth[x] + 1;
                    path_xor_from_root[y] = path_xor_from_root[x] ^ (1 << (s[y] - 'a'));
                    dfs(y, x);
                }
            }
            tout[x] = clock;
        };
        dfs(0, -1);

        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (int p = pa[i][x]; p != -1) {
                    pa[i + 1][x] = pa[i][p];
                }
            }
        }
    }

    // 返回 node 的第 k 个祖先节点
    // 如果不存在，返回 -1
    int get_kth_ancestor(int node, int k) {
        for (; k > 0 && node >= 0; k &= k - 1) {
            node = pa[countr_zero((uint32_t) k)][node];
        }
        return node;
    }

    // 返回 x 和 y 的最近公共祖先（节点编号从 0 开始）
    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) {
            swap(x, y);
        }
        y = get_kth_ancestor(y, depth[y] - depth[x]); // 使 y 和 x 在同一深度
        if (y == x) {
            return x;
        }
        for (int i = pa.size() - 1; i >= 0; i--) {
            int px = pa[i][x], py = pa[i][y];
            if (px != py) {
                x = px;
                y = py; // 同时往上跳 2^i 步
            }
        }
        return pa[0][x];
    }
};

class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        LcaBinaryLifting g(edges, s);
        FenwickTree<int> f(n); // 注意树状数组是异或运算
        vector<bool> ans;

        string op;
        int x, y;
        char c;

        for (auto& q : queries) {
            stringstream ss(q);
            ss >> op >> x;
            if (op[0] == 'u') {
                ss >> c;
                int val = (1 << (s[x] - 'a')) ^ (1 << (c - 'a')); // 擦除旧的，换上新的
                s[x] = c;
                // 子树 x 全部异或 val，转换成对区间 [tin[x], tout[x]] 的差分更新
                f.update(g.tin[x], val);
                f.update(g.tout[x] + 1, val);
            } else {
                ss >> y;
                int lca = g.get_lca(x, y);
                int res = g.path_xor_from_root[x] ^ g.path_xor_from_root[y] ^ f.pre(g.tin[x]) ^ f.pre(g.tin[y]) ^ (1 << (s[lca] - 'a'));
                ans.push_back((res & (res - 1)) == 0); // 至多一个字母的出现次数是奇数
            }
        }

        return ans;
    }
};
