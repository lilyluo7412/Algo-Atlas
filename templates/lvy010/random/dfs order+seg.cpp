//树上DFS序的经典题 3515
class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {

        ////////////////线段树开始
        //针对本题只实现区间修改和单点查询
        //由于是区间修改 所以必须有延迟标记
        //由于是单点查询 所以不需要记录区间和之类的数据（注意区间和会超int上限）
        //tree[i]表示的是i代表的区间的延迟标记 即区间增加的数值
        vector<int> tree(n * 4);

        //下推标记
        auto pushdown = [&](int p){
            if (!tree[p]) return;
            tree[p * 2] += tree[p];
            tree[p * 2 + 1] += tree[p];
            tree[p] = 0;
        };
        //单点查询实现
        auto query = [&](auto&& self, int p, int s, int t, int i)->int{
            if(s == t) return tree[p];
            int mid = (s + t) / 2;
            pushdown(p);
            if(i <= mid) return self(self, p * 2, s, mid, i);
            else return self(self, p * 2 + 1, mid + 1, t, i);
        };

        //区间修改实现
        auto update = [&](auto&& self, int p, int s, int t, int l, int r, int v)->void{
            if(s >= l && t <= r){
                tree[p] += v;
                return;
            }
            int mid = (s + t) / 2;
            pushdown(p);
            if(l <= mid) self(self, p * 2, s, mid, l, r, v);
            if(r > mid) self(self, p * 2 + 1, mid + 1, t, l, r, v);
        };
        //对外API 单点查询
        auto Query = [&](int i)->int{
            return query(query, 1, 0, n - 1, i);
        };
        //对外API 区间增加
        auto Update = [&](int l, int r, int v)->void{
            update(update, 1, 0, n - 1, l, r, v);
        };
        ////////////////线段树结束

        //带权邻接表建图 使用map更加方便
        //对比unordered_map常数相差不大 且无卡哈希风险
        //本题根节点是1 转为从0开始
        vector<map<int, int>> g(n);
        for(auto& e : edges){
            e[0]--; e[1]--;
            g[e[0]][e[1]] = e[2];
            g[e[1]][e[0]] = e[2];
        }

        //标准dfs序
        //节点x以及x的子树所占用的区间为闭区间[in[x], out[x] - 1]
        vector<int> in(n); 
        //表示进入x节点的时间
        vector<int> out(n); 
        //表示退出x节点的时间
        int time = 0;
        auto dfs = [&](auto&& self, int u, int p, int d)->void{
            in[u] = time++;
            Update(in[u], in[u], d);
            for(auto [v, w] : g[u]){
                if(v == p) continue;
                self(self, v, u, d + w);
            }
            out[u] = time;
        };
        dfs(dfs, 0, -1, 0);

        vector<int> ans;
        for(auto& q : queries){
            if(q[0] == 1){
                int u = q[1] - 1, v = q[2] - 1;
                if(in[u] > in[v]) swap(u, v);
                int old = Query(in[v]) - Query(in[u]); //边u->v的动态权值
                //也可以用下面方式查询和维护
                /*
                int old = g[u][v];
                g[u][v] = g[v][u] = q[3];
                */
                Update(in[v], out[v] - 1, q[3] - old);
            }
            else{
                ans.push_back(Query(in[q[1] - 1]));
            }
        }
        return ans;
    }
};
