typedef pair<int, int> PII;
typedef tuple<int, int, int> TIII;


class Solution {
public:
    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {
        vector<vector<PII>> g(n);
        for (auto& edge : edges) {
            int a = edge[0], b = edge[1], c = edge[2];
            g[a].emplace_back(b, c);
            g[b].emplace_back(a, c);
        }
        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));
        dist[s][0] = 0;
        vector<vector<bool>> seen(n, vector<bool>(k + 1, false));
        priority_queue<TIII, vector<TIII>, greater<TIII>> pq;
        pq.emplace(0, s, 0);

        while (!pq.empty()) {
            auto [td, u, tk] = pq.top();
            pq.pop();
            if (seen[u][tk]) continue;
            seen[u][tk] = true;
            for (auto& [v, nd] : g[u]) {
                if (dist[v][tk] > td + nd) {
                    dist[v][tk] = td + nd;
                    pq.emplace(td + nd, v, tk);
                }
                if (tk < k and dist[v][tk + 1] > td) {
                    dist[v][tk + 1] = td;
                    pq.emplace(td, v, tk + 1);
                }
            }
        }
        return *min_element(dist[d].begin(), dist[d].end());
    }
};
