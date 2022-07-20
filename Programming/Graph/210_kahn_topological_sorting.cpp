#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Solution {
private:
    vector<vector<int>> edges;
    vector<int> indeg;
    vector<int> result;
 
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
    {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for(const auto & info: prerequisites)
        {
            edges[info[1]].push_back(info[0]);
            indeg[info[0]]++;
        }

        queue<int> q;
        for(int u=0; u<numCourses; u++)
        {
            if(indeg[u] == 0)
            {
                q.push(u);
            }
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u);
            for(auto v: edges[u])
            {
                indeg[v] --;
                if(indeg[v] == 0)
                {
                    q.push(v);
                }
            }
        }
        return (result.size() == numCourses)? result: vector<int>{};
    }
};

int main(int argc, char const *argv[])
{
    Solution slt;
    int n = 4;
    vector<vector<int>> edges;
    edges.push_back(vector<int>{1, 0});
    edges.push_back(vector<int>{2, 0});
    edges.push_back(vector<int>{3, 1});
    edges.push_back(vector<int>{3, 2});
    for(auto item: slt.findOrder(n, edges))
    {
        cout<<item<<' ';
    }
    return 0;
}
