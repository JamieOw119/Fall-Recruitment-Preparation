#include <unordered_map>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// time out
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) 
    {
        int n = edges.size();
        vector<bool> visited(n+1, false);
        unordered_map<int, vector<int>> graph;

        for(auto edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            if(bfs(u, v, n, visited, graph))
            {
                return vector<int>{u, v};
            }
            visited.empty();
            visited.insert(visited.begin(), n, false);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        return vector<int>{};
    }

private:
    bool bfs(int u, int target, int n, vector<bool>& visited, unordered_map<int, vector<int>>& graph)
    {
        queue<int> q;
        q.push(u);
        while(!q.empty())
        {
            int v = q.front();
            q.pop();
            visited[v] = true;
            for(auto w: graph[v])
            {
                if(w == target)
                {
                    return true;
                }
                if(!visited[w])
                {
                    q.push(w);
                }
            }  
        }
        return false;
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
