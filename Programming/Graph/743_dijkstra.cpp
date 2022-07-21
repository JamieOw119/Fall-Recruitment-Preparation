#include <vector>
#include <climits>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) 
    {
        unordered_map<int, vector<pair<int, int>>> graph;
        for(auto time: times)
        {
            graph[time[0]-1].push_back(pair<int, int>{time[1]-1, time[2]});
        }
        vector<int> dists(n, INT_MAX);
        vector<bool> visited(n, false);
        dists[k-1] = 0;
        int u = -1;
        int max = INT_MIN;

        while((u = getMin(dists, visited)) != -1)
        {
            visited[u] = true;
            for(auto v_weight: graph[u])
            {
                int v = v_weight.first;
                int weight = v_weight.second;
                if(!visited[v])
                {
                    int dv = dists[u] + weight;
                    if(dv < dists[v])
                    {
                        dists[v] = dv;
                    }
                }
            }
        }

        for(auto dist: dists)
        {
            if(dist == INT_MAX)
            {
                return -1;
            }
            if(dist > max)
            {
                max = dist;
            }
        }
        return max;
    }

private:
    int getMin(vector<int> &dists, vector<bool> &visited)
    {
        int min = INT_MAX;
        int minVertex = -1;
        for(int i=0; i<dists.size(); i++)
        {
            if(!visited[i] && dists[i] < min)
            {
                min = dists[i];
                minVertex = i;
            }
        }
        return minVertex;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> times;
    times.push_back({2,1,1});
    times.push_back({2,3,1});
    times.push_back({3,4,1});
    int n = 4, k = 2;
    Solution slt;
    cout<<slt.networkDelayTime(times, n, k)<<endl;
    return 0;
}
