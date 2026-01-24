class UnionFind
{
public:
    vector<int> parent;
    vector<int> size;
    int part;

    UnionFind(int n)
    {
        for (int x = 0; x < n; x ++)
            parent.push_back(x);
        size.resize(n, 1);
        part = 0;
    }

    int Find(int x)
    {
        if (parent[x] != x)
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    bool Union(int x, int y)
    {
        int root_x = Find(x);
        int root_y = Find(y);
        if (root_x == root_y)   
            return false;
        if (size[root_x] > size[root_y])
            swap(root_x, root_y);
        parent[root_x] = root_y;
        size[root_y] += size[root_x];
        part --;
        return true;
    }

    bool connected(int x, int y)
    {
        return Find(x) == Find(y);
    }

};

class Solution 
{
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) 
    {
        int & Row = m,  & Col = n;
        UnionFind UF(Row * Col);
        unordered_set<int> seen;
        vector<int> res;
        for (auto && v: positions)
        {
            int & r = v[0],    & c = v[1];
            int ID = r * Col + c;
            if (seen.count(ID) > 0)
            {
                res.push_back(UF.part);
                continue;
            }
            seen.insert(ID);
            UF.part ++;
            for (auto [nr, nc] : vector<pair<int,int>>{{r-1,c}, {r+1,c}, {r,c-1}, {r,c+1}})
            {
                if (0 <= nr && nr < Row && 0 <= nc && nc < Col)
                {
                    int id2 = nr * Col + nc;
                    if (seen.count(id2) > 0)
                    {
                        UF.Union(ID, id2);
                    }
                }
            }
            res.push_back(UF.part);
        }

        return res;
    }
};
