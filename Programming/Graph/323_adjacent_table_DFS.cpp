#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> graph;
        vector<bool> visited(n, false);

        for(auto edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int count = 0;
        for(int u=0; u<n; u++)
        {
            if(visited[u] == false)
            {
                count ++;
                dfs(u, visited, graph);
            }
        }
        return count;
    }

private:
    void dfs(int u, vector<bool>& visited, unordered_map<int, vector<int>>& graph)
    {
        visited[u] = true;
        for(auto v: graph[u])
        {
            if(visited[v] == false)
            {
                dfs(v, visited, graph);
            }
        }
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
