/*
1. 可复用：只需要替换  cost()  函数，就能适配不同的划分代价问题。
​
2. 时间复杂度：O(k·n log n)，比朴素 DP 的 O(k·n²) 效率高很多。
​
3. 适用场景：当 DP 转移满足决策单调性时（即最优分割点随区间右移单调不减），就可以用这个模板
*/
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1e18;

// 1. 定义代价计算函数
// 示例：计算区间 [l, r) 的代价
long long cost(int l, int r, vector<long long>& presum) {
    long long s = presum[r] - presum[l];
    return s * (s + 1) / 2;
}

// 2. 分治优化核心函数
void solve(int l, int r, int optL, int optR, vector<vector<long long>>& dp, vector<long long>& presum, int k) {
    if (l > r) return;
    int mid = (l + r) / 2;
    long long best = INF;
    int bestOpt = optL;
    // 在 [optL, min(optR, mid-1)] 范围内寻找最优分割点
    for (int i = optL; i <= min(optR, mid - 1); ++i) {
        long long current = dp[k-1][i] + cost(i, mid, presum);
        if (current < best) {
            best = current;
            bestOpt = i;
        }
    }
    dp[k][mid] = best;
    // 递归处理左右区间
    solve(l, mid - 1, optL, bestOpt, dp, presum, k);
    solve(mid + 1, r, bestOpt, optR, dp, presum, k);
}

// 3. 主 DP 函数
vector<vector<long long>> divideAndConquerDP(int K, int n, vector<long long>& presum) {
    vector<vector<long long>> dp(K+1, vector<long long>(n+1, INF));
    // 初始化：划分1段时的代价
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = cost(0, i, presum);
    }
    // 分治优化求解
    for (int k = 2; k <= K; ++k) {
        solve(1, n, 1, n, dp, presum, k);
    }
    return dp;
}

// 4. 问题入口函数
long long solveProblem(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> presum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        presum[i+1] = presum[i] + nums[i];
    }
    auto dp = divideAndConquerDP(k, n, presum);
    return dp[k][n];
}
