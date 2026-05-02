#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<numeric>
#include<climits>

using namespace std;

typedef pair<int,int>PII;

class Graph{
    private:
    int V;
    vector<vector<PII>>adjacency_list;
    vector<int>heuristic;//h(n)

    public:
    Graph(int V)
    {
        this->V=V;
        adjacency_list.resize(V);
        heuristic.resize(V);
    }

    void addEdge(int src,int dest,int cost)
    {
        adjacency_list[src].push_back({dest,cost});
        adjacency_list[dest].push_back({src,cost});
    }

    void inputHeuristic()
    {
        for(int i=0;i<V;i++)
        {
            cout<<"Enter heuristic for vertex "<<i<<": ";
            cin>>heuristic[i];
        }
    }

    void printPath(map<int,int>&parent,int target)
    {
        vector<int>path;
        while(target!=-1)
        {
            path.push_back(target);
            target=parent[target];
        }
        reverse(path.begin(),path.end());

        for(int i = 0; i < path.size(); i++) 
        {
                cout << path[i];
                if(i != path.size() - 1) cout << " -> ";
        }
        cout<<endl;
    }
    void BestFirstSearch(int start,int goal)
    {
        priority_queue<PII,vector<PII>,greater<PII>>pq;
        vector<bool>visited(V,false);
        map<int,int>parent;

        pq.push({heuristic[start],start});
        parent[start]=-1;

        while(!pq.empty())
        {
            PII temp=pq.top();
            pq.pop();

            int curr_vertex=temp.second;
            if(visited[curr_vertex]) continue;
            visited[curr_vertex]=true;

            if(curr_vertex==goal)
            {
                cout<<"Solution found"<<endl;
                cout<<"Path: ";
                printPath(parent,curr_vertex);
                return;
            }

            for(auto neighbour:adjacency_list[curr_vertex])
            {
                if(visited[neighbour.first]) continue;
                if (!visited[neighbour.first] && parent.find(neighbour.first) == parent.end()) {
                    parent[neighbour.first] = curr_vertex;
                }
                pq.push({heuristic[neighbour.first],neighbour.first});
            }
        }
        cout<<"Goal not reachable!"<<endl;
    }


     void Astar(int start,int goal)
    {
        priority_queue<PII,vector<PII>,greater<PII>>pq;
        vector<bool>visited(V,false);
        map<int,int>parent;

        vector<int>g_cost(V,INT_MAX/2);
        g_cost[start]=0;

        pq.push({heuristic[start]+g_cost[start],start});
        parent[start]=-1;

        while(!pq.empty())
        {
            PII temp=pq.top();
            pq.pop();

            int curr=temp.second;
            if(visited[curr]) continue;
            visited[curr]=true;

            if(curr==goal)
            {
                cout << "Solution found!" << endl;
                cout << "Path: ";
                printPath(parent, curr);
                cout << "Total cost: " << g_cost[curr] << endl;
                return;
            }

            for(auto neighbour:adjacency_list[temp.second])
            {
                if(visited[neighbour.first]) continue;

                int new_cost=g_cost[curr]+neighbour.second;

                if(new_cost < g_cost[neighbour.first])
                {
                g_cost[neighbour.first]=new_cost;
                pq.push({heuristic[neighbour.first]+g_cost[neighbour.first],neighbour.first});
                parent[neighbour.first]=curr;
                }
            }
        }
        cout << "Goal not reachable!" << endl;
    }
};

int main()
{
    cout<<"Enter the number of vertices you want in the graph: "<<endl;
    int vertices;
    cin>>vertices;

    Graph g(vertices);

    cout << "Enter edges (src dest cost). Enter -1 to stop." << endl;
    while(true)
    {
        int src,dest,cost;
        cout<<"Enter the source and destination vertex along with cost you want or -1  to stop: ";
        cin>>src;
        if(src==-1) break;
        cin>>dest>>cost;
        cout<<endl;
        g.addEdge(src,dest,cost);
    }

    g.inputHeuristic();

   int start,goal;

   cout<<"Enter the start vertex: "<<endl;
   cin>>start;

   cout<<"Enter the goal vertex: "<<endl;
   cin>>goal;

   cout<<"Best First Search Output:"<<endl;
   g.BestFirstSearch(start,goal);

   cout<<"\nA* Search Output:"<<endl;
   g.Astar(start,goal);

    return 0;
}