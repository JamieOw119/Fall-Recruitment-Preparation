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
        dists[k - 1] = 0;
        bool finished = true;

        for(int i=0; i<n; i++)
        {
            for(int u=0; u<n; u++)
            {
                for(auto v_weight: graph[u])
                {
                    int v = v_weight.first;
                    int weight = v_weight.second;
                    int dv = dists[u] + weight;
                    if(dv < dists[v])
                    {
                        dists[v] = dv;
                        finished = false;
                    }
                }
            }
            if(finished) break;
        }

        for(int u = 0; u < n; u++)
        {
            for(auto v_weight: graph[u])
            {
                int v = v_weight.first;
                int weight = v_weight.second;
                int dv = dists[u] + weight;
                if(dv < dists[v])
                {
                    return -1; // exists negative edge;
                }
            }
        }

        int max = INT_MIN;
        for(int dist: dists)
        {
            if(dist == INT_MAX) return -1;
            if(dist > max) max = dist;
        }
        return max;
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