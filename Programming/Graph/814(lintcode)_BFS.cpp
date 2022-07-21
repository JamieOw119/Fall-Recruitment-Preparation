#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
    int shortestPath(vector<UndirectedGraphNode*> graph, UndirectedGraphNode* A, UndirectedGraphNode* B)
    {
        if(A == B)
        {
            return 0;
        }
        unordered_map<int, int> dis;
        queue<UndirectedGraphNode*> q;
        dis[A->label] = 0;
        q.push(A);

        while(!q.empty())
        {
            auto t = q.front();
            q.pop();
            if(t == B)
            {
                return dis[t->label];
            }
            for(auto i: t->neighbors)
            {
                if(dis.find(i->label) == dis.end())
                {
                    dis[i->label] = dis[t->label] + 1;
                    q.push(i);
                }
            }
        }
        return -1;
    }
};
