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
        vector<vector<int>> dists(n, vector<int>(n, INT_MAX));
        for (int u = 0; u < n; u++)
            dists[u][u] = 0;
        for (auto time : times)
        {
            dists[time[0] - 1][time[1] - 1] = time[2];
        }
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    long ik = dists[i][k], kj = dists[k][j], ij = dists[i][j];
                    if (ik + kj < ij)
                    {
                        dists[i][j] = (int)(ik + kj);
                    }
                }
            }
        }
        int max = INT_MIN;
        for (int dist : dists[k - 1])
        {
            if (dist == INT_MAX)
                return -1;
            if (dist > max)
                max = dist;
        }
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                long dv = (long)dists[k - 1][u] + (long)dists[u][v];
                if (dv < dists[k - 1][v])
                {
                    return -1;
                }
            }
        }
        return max;
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