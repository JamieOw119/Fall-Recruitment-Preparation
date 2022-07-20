#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

// timeout
class Solution {
public:
    bool hasCycle;

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
    {
        vector<bool> visited(numCourses+1, false);
        unordered_map<int, vector<int>> graph;
        hasCycle = false;

        for(auto edge: prerequisites)
        {
            int v = edge[0];
            int u = edge[1];
            if(u == v)
            {
                return false;
            }
            dfs(v, u, numCourses, visited, graph);
            if(hasCycle)
            {
                return false;
            }
            visited.empty();
            visited.insert(visited.begin(), numCourses, false);
            graph[u].push_back(v);
        }
        return true;
    }

private:
    void dfs(int u, int target, int n, vector<bool>& visited, unordered_map<int, vector<int>>& graph)
    {
        visited[u] = true;
        for(auto v: graph[u])
        {
            if(v == target)
            {
                hasCycle = true;
                return;
            }
            else if(!visited[v])
            {
                dfs(v, target, n, visited, graph);
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Solution slt;
    int n = 2;
    vector<vector<int>> edges;
    edges.push_back(vector<int>{1, 0});
    edges.push_back(vector<int>{2, 0});
    edges.push_back(vector<int>{0, 2});
    cout<<slt.canFinish(n, edges)<<endl;
    return 0;
}
