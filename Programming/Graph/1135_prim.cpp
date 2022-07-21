#include <unordered_map>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution
{
public:
    int minimumCost(int n, vector<vector<int>> &connections)
    {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto connection: connections)
        {
            graph[connection[0]].push_back({connection[1], connection[2]});
            graph[connection[1]].push_back({connection[0], connection[2]});
        }
        int sum = 0;
        vector<int> dists(n+1, INT_MAX);
        vector<bool> visited(n+1, false);
        dists[1] = 0;
        int u = -1;
        while((u = getMin(dists, visited)) != -1)
        {
            visited[u] = true;
            // cout<<"Current: "<<u<<endl;
            for(auto v_w: graph[u])
            {
                int v = v_w.first;
                int w = v_w.second;
                if(!visited[v] && w < dists[v])
                {
                    // cout<<u<<' '<<v<<' '<<w<<endl;
                    dists[v] = w;
                }
            }
        }

        int isZero = true;
        for(int dist: dists)
        {
            if(isZero)
            {
                isZero = false;
                continue;
            }
            if(dist == INT_MAX)
            {
                return -1;
            }
            sum += dist;
        }
        return sum;
    }

private:
    int getMin(vector<int>& dists, vector<bool>& visited)
    {
        int n = dists.size()-1;
        int min = INT_MAX;
        int minVertex = -1;
        for(int u=1; u<=n; u++)
        {
            if(!visited[u] && dists[u] < min)
            {
                min = dists[u];
                minVertex = u;
            }
        }
        return minVertex;
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
