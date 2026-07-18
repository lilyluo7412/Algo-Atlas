class Solution {
public:
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size();
        int g[1 << n], h[1 << n];
        for (int i = 1; i < (1 << n); i++) {
            g[i] = 0;
            // 预处理合并后的长度
            for (int j = 0; j < n; j++) if (i >> j & 1) g[i] += lists[j].size();

            // 二分找到多个有序列表的中位数
            int head = -1e9, tail = 1e9;
            while (head < tail) {
                int mid = (head + tail) >> 1;
                int cnt = 0;
                // 里面再通过二分，计算每个列表里有几个小于等于 mid 的数
                for (int j = 0; j < n; j++) if (i >> j & 1) cnt += upper_bound(lists[j].begin(), lists[j].end(), mid) - lists[j].begin();
                if (cnt >= (g[i] + 1) / 2) tail = mid;
                else head = mid + 1;
            }
            h[i] = head;
        }

        const long long INF = 1e18;
        long long f[1 << n];
        // 枚举二进制 mask
        for (int i = 1; i < (1 << n); i++) {
            if (__builtin_popcount(i) == 1) { f[i] = 0; continue; }
            f[i] = INF;
            // 枚举子集
            for (int j = i; j; j = (j - 1) & i) if (j != i) {
                int k = i ^ j;
                long long c = f[j] + f[k] + g[j] + g[k] + abs(h[j] - h[k]);
                f[i] = min(f[i], c);
            }
        }
        return f[(1 << n) - 1];
    }
};
