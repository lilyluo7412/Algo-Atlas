/*
3962
discretized Fenwick Tree storing element count and sum
iterates all subarrays to maintain inner
outer elements dynamically
swaps up to k extreme values between inside and outside
computes the maximum subarray sum after swaps.
*/
class FenwickTree {
    const int high_bit;
    const vector<int>& sorted;
    vector<int> cnt;
    vector<long long> sum;

public:
    FenwickTree(const vector<int>& sorted) : 
        cnt(sorted.size() + 1), 
        sum(sorted.size() + 1), 
        sorted(sorted), 
        high_bit(1 << (bit_width(sorted.size()) - 1)) {}

    // 添加 num 个 val，其中 val 离散化后的值为 i（i 从 1 开始）
    // 如果 num < 0，表示减少 -num 个 val
    void update(int i, int num, int val) {
        for (; i < cnt.size(); i += i & -i) {
            cnt[i] += num;
            sum[i] += val;
        }
    }

    // 返回第 k 小的数（k 从 1 开始）
    int kth(int k) const {
        int i = 0;
        for (int b = high_bit; b > 0; b >>= 1) {
            int nxt = i | b;
            if (nxt < cnt.size() && cnt[nxt] < k) {
                k -= cnt[nxt];
                i = nxt;
            }
        }
        return sorted[i];
    }

    // 返回前 k 小的数之和（k 从 1 开始）
    long long pre_sum(int k) const {
        long long s = 0;
        int i = 0;
        for (int b = high_bit; b > 0; b >>= 1) {
            int nxt = i | b;
            if (nxt < cnt.size() && cnt[nxt] < k) {
                k -= cnt[nxt];
                s += sum[nxt];
                i = nxt;
            }
        }
        // 加上等于第 k 小的数
        return s + 1LL * sorted[i] * k;;
    }
};

class Solution {
public:
    long long maxSum(vector<int>& nums, int k) {
        // 离散化
        int n = nums.size();
        vector<int> sorted = nums;
        ranges::sort(sorted);
        sorted.erase(ranges::unique(sorted).begin(), sorted.end());
        vector<int> rank(n); // rank[i] 是 nums[i] 离散化后的值（从 1 开始）
        FenwickTree all_tree(sorted); // 包含所有元素的树状数组
        long long total = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            rank[i] = ranges::lower_bound(sorted, x) - sorted.begin() + 1;
            all_tree.update(rank[i], 1, x);
            total += x;
        }

        long long ans = LLONG_MIN;

        // 枚举子数组左端点
        for (int left = 0; left < n; left++) {
            FenwickTree in_tree(sorted);
            FenwickTree out_tree = all_tree;
            int need_swap = 0;
            long long sub_sum = 0;

            // 枚举子数组右端点
            for (int right = left; right < n; right++) {
                // x 从子数组外移到子数组内
                int x = nums[right];
                int rk = rank[right];
                sub_sum += x;
                in_tree.update(rk, 1, x);
                out_tree.update(rk, -1, -x);

                bool inc = false;
                int sz = right - left + 1;
                if (need_swap < k && need_swap < sz && need_swap < n - sz) {
                    // 能否多交换一次
                    if (in_tree.kth(need_swap + 1) < out_tree.kth(n - sz - need_swap)) {
                        inc = true;
                        need_swap++;
                    }
                }

                if (!inc && need_swap > 0) {
                    // 是否要减少交换次数
                    if (in_tree.kth(need_swap) >= out_tree.kth(n - sz - need_swap + 1)) {
                        need_swap--;
                    }
                }

                // 计算通过交换导致的元素和的增量
                long long delta = 0;
                if (need_swap > 0) {
                    long long in_sum = in_tree.pre_sum(need_swap);
                    long long out_sum = total - sub_sum - out_tree.pre_sum(n - sz - need_swap);
                    delta = out_sum - in_sum;
                }

                ans = max(ans, sub_sum + delta);
            }
        }

        return ans;
    }
};
