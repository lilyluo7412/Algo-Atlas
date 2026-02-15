#include <bits/stdc++.h>
using namespace std;

// 求数组所有子数组的 GCD 种类数（OR/AND 只需要改 gcd 即可）
long long logTrick(vector<int>& a) {
    int n = a.size();
    long long res = 0;
    // 存 {当前gcd值, 以这个值结尾的子数组信息}
    map<int, int> mp; 

    for (int x : a) {
        map<int, int> tmp;
        // 1. 以当前数单独为子数组
        tmp[x]++;
        // 2. 接在前面的子数组后面
        for (auto& [g, cnt] : mp) {
            int new_g = gcd(g, x); 
            // OR: new_g = g | x;
            // AND: new_g = g & x;
            tmp[new_g] += cnt;
        }
        // 3. 统计不同GCD
        res += tmp.size();
        mp.swap(tmp);
    }
    return res;
}
