#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

// this class should be assigned or defined before clas Solution,
// if not, it will cause undefined error.
class UnionFind {
private:
    vector<int> parents;
    vector<int> rank;

public:
    int unionCount = 0;

    UnionFind(vector<int>& parents)
    {
        this->parents = parents;
        this->rank.insert(this->rank.begin(), parents.size(), 1);
    }

    int find(int x)
    {
        if(parents[x] == x)
        {
            return x;
        }
        return parents[x] = find(parents[x]);
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

bool cmp(const vector<int>& v1, const vector<int>& v2)
{
    return v1[2] < v2[2];
}

class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        sort(connections.begin(), connections.end(), cmp);
        vector<int> parents(n+1);
        for(int i=1; i<=n; i++)
        {
            parents[i] = i; 
        }
        UnionFind uf(parents);
        int sum = 0;
        int count = 0;

        for(auto connection: connections)
        {
            int u = connection[0];
            int v = connection[1];
            int w = connection[2];
            if(uf.find(u) != uf.find(v))
            {
                uf.Union(u, v);
                sum += w;
                count ++;
                if(count == n-1)
                {
                    return sum;
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> connections;
    connections.push_back({1,2,7});
    connections.push_back({1,4,5});
    connections.push_back({2,3,8});
    connections.push_back({2,4,9});
    connections.push_back({2,5,7});
    connections.push_back({3,5,5});
    connections.push_back({4,5,15});
    connections.push_back({4,6,6});
    connections.push_back({5,6,8});
    connections.push_back({6,7,11});
    connections.push_back({5,7,9});
    int n = 7;
    Solution slt;
    cout<<slt.minimumCost(n, connections)<<endl;
    return 0;
}