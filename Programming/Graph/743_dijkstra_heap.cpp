#include <queue>
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
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
        dists[k - 1] = 0;
        pq.push(pair<int, int>{k - 1, 0});

        while(!pq.empty())
        {
            pair<int, int> u_dist = pq.top();
            pq.pop();
            int u = u_dist.first;
            visited[u] = true;
            for(auto v_weight: graph[u])
            {
                int v = v_weight.first;
                int weight = v_weight.second;
                if(!visited[v])
                {
                    long dv = (long)dists[u] + (long)weight;
                    if(dv < dists[v])
                    {
                        dists[v] = dv;
                        pq.push(pair<int, int>{v, dv});
                    }
                }
            }
        }

        int max = -1;
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
    struct cmp {
        bool operator()(const pair<int, int>& p1, const pair<int, int>& p2)
        {
            return p1.second > p2.second;
        }
    };
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
