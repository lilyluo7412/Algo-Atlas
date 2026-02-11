#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1e5 + 5;

int a[MAXN];          // 原数组
long long sum[MAXN];  // 每块的和
int add[MAXN];        // 每块的懒标记（增量）
int block_size;       // 块大小
int n;

// 初始化分块
void init() {
    block_size = sqrt(n);
    for (int i = 1; i <= n; i++) {
        int bid = i / block_size;
        sum[bid] += a[i];
    }
}

// 区间加 [l, r] += val
void update(int l, int r, int val) {
    int bl = l / block_size;
    int br = r / block_size;
    if (bl == br) {
        // 同一块，暴力修改
        for (int i = l; i <= r; i++) {
            a[i] += val;
            sum[bl] += val;
        }
    } else {
        // 左边碎块
        for (int i = l; i < (bl + 1) * block_size; i++) {
            a[i] += val;
            sum[bl] += val;
        }
        // 中间整块
        for (int i = bl + 1; i < br; i++) {
            add[i] += val;
        }
        // 右边碎块
        for (int i = br * block_size; i <= r; i++) {
            a[i] += val;
            sum[br] += val;
        }
    }
}

// 区间查询 [l, r] 的和
long long query(int l, int r) {
    long long res = 0;
    int bl = l / block_size;
    int br = r / block_size;
    if (bl == br) {
        for (int i = l; i <= r; i++) {
            res += a[i] + add[bl];
        }
    } else {
        for (int i = l; i < (bl + 1) * block_size; i++) {
            res += a[i] + add[bl];
        }
        for (int i = bl + 1; i < br; i++) {
            res += sum[i] + (long long)add[i] * block_size;
        }
        for (int i = br * block_size; i <= r; i++) {
            res += a[i] + add[br];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // 读入 n、数组 a
    // init();
    // 处理 update / query
    return 0;
}
