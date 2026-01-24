const int MOD = 1e9 + 7;
const int MAXN = 1e4 + 1;

int factorial[MAXN];

int add(int x, int y) {
    x += y;
    while (x >= MOD) x -= MOD;
    while (x < 0) x += MOD;
    return x;
}

int sub(int x, int y) {
    return add(x, -y);
}

int mul(int x, int y) {
    return (x * 1ll * y) % MOD;
}

int binpow(int x, int y) {
    int z = 1;
    while (y) {
        if (y & 1) z = mul(z, x);
        x = mul(x, x);
        y >>= 1;
    }
    return z;
}

int inv(int x) {
    return binpow(x, MOD - 2);
}

int divide(int x, int y) {
    return mul(x, inv(y));
}

void get_factorial() {
    factorial[0] = 1;
    for (int i = 1; i < MAXN; i++) factorial[i] = mul(i, factorial[i - 1]);
}

int comb(int n, int k) {
    if (k > n) return 0;
    return divide(factorial[n], mul(factorial[n - k], factorial[k]));
}

class Solution {
public:
    Solution() {
        get_factorial();
    }
//example lc2539
    int countGoodSubsequences(string s) {
        vector<int> cnt(26, 0);
        for (auto& ch: s) cnt[ch - 'a']++;

        int ans = 0, mx = *max_element(cnt.begin(), cnt.end());
        for (int i = 1; i <= mx; i++) {
            int cur = 1;
            for (auto& c: cnt) {
                if (c < i) continue;
                cur = mul(cur, add(comb(c, i), 1));
            }
            ans = add(ans, cur - 1);
        }
        return ans;
    }
};
