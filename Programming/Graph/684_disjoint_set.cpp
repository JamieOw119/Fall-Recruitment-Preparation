#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

// this class should be assigned or defined before clas Solution,
// if not, it will cause undefined error.
class UnionFind {
private:
    vector<int> parents;
    vector<int> rank;

public:
    int unionCount = 0;

    int find(int x)
    {
        if(parents[x] == x)
        {
            return x;
        }
        return parents[x] = find(parents[x]);
    }

    UnionFind(vector<int>& parents)
    {
        this->parents = parents;
        this->rank.insert(this->rank.begin(), parents.size(), 1);
    }

    void Union(int x, int y)
    {
        int xroot = find(x);
        int yroot = find(y);
        if(xroot != yroot)
        {
            unionCount ++;
            if(rank[yroot] <= rank[xroot])
            {
                parents[yroot] = xroot;
            }
            else
            {
                parents[xroot] = yroot;
            }
            if(rank[yroot] == rank[xroot])
            {
                rank[xroot] ++;
            }
        }
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) 
    {
        int n = edges.size();
        vector<bool> visited(n+1, false);
        vector<int> parents(n+1, -1);
        for(int i=0; i<=n; i++)
        {
            parents[i] = i;   
        }
        UnionFind uf(parents);

        for(auto edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            if(uf.find(u) == uf.find(v))
            {
                return vector<int>{u, v};
            }
            else
            {
                uf.Union(u, v);
            }
        }
        return vector<int>{};
    }
};

int main(int argc, char const *argv[])
{
    Solution slt;
    vector<vector<int>> edges;
    edges.push_back(vector<int>{1, 2});
    edges.push_back(vector<int>{1, 3});
    edges.push_back(vector<int>{2, 3});
    vector<int> res = slt.findRedundantConnection(edges);
    cout<<res[0]<<' '<<res[1]<<endl;
    return 0;
}