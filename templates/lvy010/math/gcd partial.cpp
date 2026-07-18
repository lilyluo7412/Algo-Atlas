//3312


class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = ranges::max(nums);
        vector<int> cnt_x(mx + 1);
        for (int x : nums) {
            cnt_x[x]++;
        }

        vector<long long> cnt_gcd(mx + 1);
        for (int i = mx; i > 0; i--) {
            int c = 0;
            for (int j = i; j <= mx; j += i) {
                c += cnt_x[j];
                cnt_gcd[i] -= cnt_gcd[j]; // gcd 是 2i,3i,4i,... 的数对不能统计进来
            }
            cnt_gcd[i] += (long long) c * (c - 1) / 2; // c 个数选 2 个，组成 c*(c-1)/2 个数对
        }

        // 原地求前缀和
        partial_sum(cnt_gcd.begin(), cnt_gcd.end(), cnt_gcd.begin());

        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            ans[i] = ranges::upper_bound(cnt_gcd, queries[i]) - cnt_gcd.begin();
        }
        return ans;
    }
};
