class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        int u = 1 << n;
        // 计算每个 time 子集的最大值
        vector<int> max_time(u);
        for (int i = 0; i < n; i++) {
            int t = time[i];
            int high_bit = 1 << i;
            for (int mask = 0; mask < high_bit; mask++) {
                max_time[high_bit | mask] = max({max_time[high_bit | mask], max_time[mask], t});
            }
        }
        // 把 max_time 中的大小大于 k 的集合改为 inf
        for (uint32_t i = 0; i < u; i++) {
            if (popcount(i) > k) {
                max_time[i] = INT_MAX;
            }
        }

        vector dis(m, vector<double>(u, DBL_MAX));
        using T = tuple<double, int, int>;
        priority_queue<T, vector<T>, greater<>> pq;

        auto push = [&](double d, int stage, int mask) {
            if (d < dis[stage][mask]) {
                dis[stage][mask] = d;
                pq.emplace(d, stage, mask);
            }
        };

        push(0, 0, u - 1); // 起点

        while (!pq.empty()) {
            auto [d, stage, left] = pq.top();
            pq.pop();
            if (left == 0) { // 所有人都过河了
                return d;
            }
            if (d > dis[stage][left]) {
                continue;
            }
            // 枚举 sub 这群人坐一艘船
            for (int sub = left; sub > 0; sub = (sub - 1) & left) {
                if (max_time[sub] == INT_MAX) {
                    continue;
                }
                // sub 过河
                double cost = max_time[sub] * mul[stage];
                int cur_stage = (stage + int(cost)) % m; // 过河后的阶段
                // 所有人都过河了
                if (sub == left) {
                    push(d + cost, cur_stage, 0);
                    continue;
                }
                // 枚举回来的人（可以是之前过河的人）
                for (int s = (u - 1) ^ left ^ sub, lb; s > 0; s ^= lb) {
                    lb = s & -s;
                    double return_time = max_time[lb] * mul[cur_stage];
                    push(d + cost + return_time, (cur_stage + int(return_time)) % m, left ^ sub ^ lb);
                }
            }
        }
        return -1;
    }
};
