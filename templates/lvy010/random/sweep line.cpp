//Discretization + difference/segment tree for sweep line traversal implementation
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 200010;

// 扫描线事件：x坐标，y区间[l,r]，权值val(+1/-1)
struct Event {
    ll x, l, r, val;
    bool operator<(const Event& e) const { return x < e.x; }
} ev[N];

// 离散化数组+线段树节点（维护覆盖长度、覆盖次数）
ll ys[N];
struct Node {
    int l, r, cnt;
    ll len;
} tr[N << 2];

// 线段树更新
void pushup(int u) {
    if (tr[u].cnt) tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];
    else if (tr[u].l == tr[u].r) tr[u].len = 0;
    else tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
}

// 线段树建树
void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

// 线段树区间修改
void update(int u, int l, int r, int val) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].cnt += val;
        pushup(u);
        return;
    }
    int mid = l + r >> 1;
    if (l <= mid) update(u << 1, l, r, val);
    if (r > mid) update(u << 1 | 1, l, r, val);
    pushup(u);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n, idx = 0, yidx = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ev[idx++] = {x1, y1, y2, 1};  // 入边
        ev[idx++] = {x2, y1, y2, -1}; // 出边
        ys[yidx++] = y1, ys[yidx++] = y2;
    }
    // 离散化y坐标
    sort(ys, ys + yidx);
    yidx = unique(ys, ys + yidx) - ys;
    // 排序事件
    sort(ev, ev + idx);
    // 建树（离散化后下标）
    build(1, 0, yidx - 2);
    ll res = 0;
    for (int i = 0; i < idx; i++) {
        if (i) res += tr[1].len * (ev[i].x - ev[i-1].x);
        // 查找y的离散化下标
        int l = lower_bound(ys, ys + yidx, ev[i].l) - ys;
        int r = lower_bound(ys, ys + yidx, ev[i].r) - ys - 1;
        update(1, l, r, ev[i].val);
    }
    cout << res << endl;
    return 0;
}
