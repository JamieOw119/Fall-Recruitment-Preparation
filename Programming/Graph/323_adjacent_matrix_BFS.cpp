#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<bool> visited(n, false);
        vector<vector<bool>> graph(n, vector<bool>(n, false));
        for(auto edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            graph[u][v] = true;
            graph[v][u] = true;
        }
        
        int count = 0;
        for(int u=0; u<n; u++)
        {
            if(visited[u] == false)
            {
                count ++;
                bfs(u, n, visited, graph);
            }
        }
        return count;
    }

private:
    void bfs(int u, int n, vector<bool>& visited, vector<vector<bool>>& graph)
    {
        visited[u] = true;
        queue<int> que;
        que.push(u);

        while(!que.empty())
        {
            int u = que.front();
            que.pop();
            for(int v = 0; v < n; v ++)
            {
                if(visited[v] == false && graph[u][v] == true)
                {
                    {
                        que.push(v);
                        visited[v] = true;
                    }
                }
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
