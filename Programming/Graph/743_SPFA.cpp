#include <queue>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        vector<vector<pair<int, int>>> edge(n + 1);
        for (auto t : times)
        {
            edge[t[0]].emplace_back(t[1], t[2]);
        }
        vector<bool> inq(n + 1, 0);
        vector<int> dis(n + 1, INT_MAX >> 1);
        queue<int> q;
        q.push(k);
        dis[k] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (auto edge_pair : edge[u])
            {
                int v = edge_pair.first;
                int d = edge_pair.second;
                if (dis[u] + d < dis[v])
                {
                    dis[v] = dis[u] + d;
                    if (!inq[v])
                    {
                        q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        int ans = -1;
        for (int i = 1; i <= n; ++i)
        {
            ans = max(ans, dis[i]);
        }
        return (ans == INT_MAX >> 1 ? -1 : ans);
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> times;
    times.push_back({2, 1, 1});
    times.push_back({2, 3, 1});
    times.push_back({3, 4, 1});
    int n = 4, k = 2;
    Solution slt;
    cout << slt.networkDelayTime(times, n, k) << endl;
    return 0;
}