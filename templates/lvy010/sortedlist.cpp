//3096
#include <bits/extc++.h>
using pii = pair<int, int>;
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        __gnu_pbds::tree<pii, __gnu_pbds::null_type, greater<pii>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tr1, tr2;
        vector<int> a, b;
        a.push_back(nums[0]);
        tr1.insert({nums[0], 0});
        b.push_back(nums[1]);
        tr2.insert({nums[1], 1});
        for (int i = 2; i < nums.size(); i++) {
            int ca = tr1.order_of_key({nums[i], i}), cb = tr2.order_of_key({nums[i], i});
            if (ca < cb) {
                b.push_back(nums[i]);
                tr2.insert({nums[i], i});
            } else if (ca > cb) {
                a.push_back(nums[i]);
                tr1.insert({nums[i], i});
            } else {
                if (tr1.size() <= tr2.size()) {
                    a.push_back(nums[i]);
                    tr1.insert({nums[i], i});
                } else {
                    b.push_back(nums[i]);
                    tr2.insert({nums[i], i});
                }
            }
        }
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};
