//lc3737

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
// 使用 pair<key, index> 支持重复 key
using ordered_set = tree<pair<int, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int idx = 0; // 插入时自增，用来保证 st 中的元素互不相同
        ordered_set* st = new ordered_set();
        st->insert({0, ++idx});
        long long ans = 0;
        int s = 0;
        for (int x : nums) {
            s += x == target ? 1 : -1;
            // order_of_key(key) 计算 st 中的严格小于 key 的元素个数
            ans += st->order_of_key({s, 0});
            st->insert({s, ++idx});
        }
        delete st;
        return ans;
    }
};
