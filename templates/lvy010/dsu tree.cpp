/*
树上启发式合并
对每个颜色 c
找出树上同色两点之间的最大距离
（深度和减两倍LCA深度）
*/
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    vector<int> a(n);
    int root = 0;
    fo(i, 0, n)
    {
        cin >> a[i];
        int x;
        cin >> x;
        x--;
        if (x != -1)
            g[x].pb(i);
        else
            root = i;
    }
    vector<int> ans(k + 1);
    auto dfs = [&](auto &&dfs, int x, int d) -> map<int, int>
    {
        map<int, int> f;
        f[a[x]] = d;
        each(y, g[x])
        {
            auto fy = dfs(dfs, y, d + 1);
            if (fy.size() > f.size())
                swap(f, fy);
            for (auto &[c, nd] : fy)
            {
                if (f.count(c))
                {
                    ans[c] = max(ans[c], f[c] + nd - 2 * d);
                }
                f[c] = max(f[c], nd);
            }
        }
        return f;
    };
    dfs(dfs, root, 0);
    fo(i, 1, k + 1) cout << ans[i] << endl;
}
