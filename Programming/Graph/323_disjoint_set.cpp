#include <vector>
#include <iostream>

using namespace std;

// this class should be assigned or defined before clas Solution,
// if not, it will cause undefined error.
class UnionFind {
private:
    vector<int> parents;
    vector<int> rank;

    int find(int x)
    {
        if(parents[x] == x)
        {
            return x;
        }
        return parents[x] = find(parents[x]);
    }

public:
    int unionCount = 0;

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
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parents(n, -1);
        for(int i=0; i<n; i++)
        {
            parents[i] = i;   
        }
        UnionFind uf(parents);
        for(auto edge: edges)
        {
            uf.Union(edge[0],  edge[1]);
        }
        return n - uf.unionCount;
    }
};


int main(int argc, char const *argv[])
{
    Solution slt;
    int n = 5;
    vector<vector<int>> edges;
    edges.push_back(vector<int>{0, 1});
    edges.push_back(vector<int>{1, 2});
    edges.push_back(vector<int>{3, 4});
    int count = slt.countComponents(n, edges);
    cout<<"Count: "<<count<<endl;
    return 0;
}