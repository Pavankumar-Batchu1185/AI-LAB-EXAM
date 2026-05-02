
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class Graph
{
    private:
      int V;
      vector<vector<int>>adjacency_list;
    public:
      Graph(int V)
      {
        this->V=V;
        adjacency_list.resize(V);
      }
      void addEdge(int src,int dest)
      {
        if(src >= 0 && src < V && dest >= 0 && dest < V)
       {
        adjacency_list[src].push_back(dest);
        adjacency_list[dest].push_back(src);
        }
      }
      bool isSafe(int vertex, string color,vector<string>&color_of_vertex)
      {
          for(auto neighbour:this->adjacency_list[vertex])
          {
            if(color_of_vertex[neighbour]==color)
            {
                return false;
            }
          }
          return true;
      }
      void solve(vector<string>&colors,vector<string>&color_of_vertex,vector<vector<string>>& ans, int colored_count,int startVertex)
      {
          if (colored_count == V) 
        {
            ans.push_back(color_of_vertex);
            return;
        }

        int vertex = -1;
        for (int i = 0; i < V; i++) 
        {
            int candidate = (startVertex + i) % V;
            if (color_of_vertex[candidate] == "") 
            {
                vertex = candidate;
                break;
            }
        }

        if (vertex == -1) return;

        for (auto& color : colors) 
        {
            if (isSafe(vertex, color, color_of_vertex)) 
            {
                color_of_vertex[vertex] = color;
                solve(colors, color_of_vertex, ans, colored_count + 1, startVertex);
                color_of_vertex[vertex] = "";
            }
        }
      }
};
int main()
{
    int vertices;
    cout<<"Graph Coloring Problem using Backtracking"<<endl;

    cout<<"Enter the number of vertices in the graph:";
    cin>>vertices;
    cout<<endl;
    Graph g(vertices);

    cout<<"Enter the edges of the graph"<<endl;
    while(true)
    {
        int src,dest;
        cout<<"Enter the source and destination of edge.Or enter -1 -1 to exit:"<<endl;
        cin>> src >> dest;
        if(src==-1 && dest==-1) break;
        
        g.addEdge(src,dest);
    }

    int k;
    cout << "Enter the number of colors (k): ";
    cin >> k;

    vector<string>colors;
    cout<<"Enter the colors:"<<endl;
    for(int i=0; i<k; i++)
    {
        string color;
        cin>>color;
        colors.push_back(color);
    }

    vector<vector<string>> ans;
    vector<string>color_of_vertex(vertices, "");

    int startvertex;
    cout<<"Enter the start vertex from which you want to start coloring the graph ";
    cin>>startvertex;
    cout<<endl;

    g.solve(colors,color_of_vertex,ans,0,startvertex);

    if (ans.empty()) 
    {
        cout << "\nNo valid coloring exists with " << k << " colors." << endl;
    } 
    else 
    {
        cout << "\nTotal valid colorings found: " << ans.size() << endl;
        for (int s = 0; s < ans.size(); s++) 
        {
            cout << "\nSolution " << s + 1 << ":" << endl;
            for (int i = 0; i < vertices; i++) 
            {
                cout << "  Vertex " << i << " -> " << ans[s][i] << endl;
            }
        }
    }
    return 0;
}