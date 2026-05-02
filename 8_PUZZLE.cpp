#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<numeric>
#include<climits>

using namespace std;

typedef pair<int,string>PIS;

string goalState="123456780";

int misplacedTiles(const string&state)
{
    int count=0;
    for(int i=0;i<9;i++)
    {
        if(state[i]!='0' && state[i]!=goalState[i])
            count++;
    }
    return count;
}

int manhattanDistance(const string&state)
{
    int dist=0;
    for(int i=0;i<9;i++)
    {
        if(state[i]=='0') continue;
        int val=state[i]-'1';
        dist+=abs(val/3 - i/3)+abs(val%3 - i%3);
    }
    return dist;
}

vector<string>getNeighbours(const string&state)
{
    vector<string>neighbours;
    int zeroPos=state.find('0');
    int row=zeroPos/3;
    int col=zeroPos%3;

    vector<vector<int>>directions={{0,1},{1,0},{0,-1},{-1,0}};

    for(auto d:directions)
    {
        int newRow=row+d[0];
        int newCol=col+d[1];
        if(newRow>=0 && newRow<3 && newCol>=0 && newCol<3)
        {
            string newState=state;
            swap(newState[zeroPos],newState[newRow*3+newCol]);
            neighbours.push_back(newState);
        }
    }
    return neighbours;
}

void printState(const string&state)
{
    for(int i=0;i<9;i++)
    {
        cout<<(state[i]=='0' ? '_' : state[i])<<" ";
        if((i+1)%3==0) cout<<endl;
    }
    cout<<endl;
}

void printPath(map<string,string>&parent,string target)
{
    vector<string>path;
    while(target!="")
    {
        path.push_back(target);
        target=parent[target];
    }
    reverse(path.begin(),path.end());

    cout<<"Solution in "<<path.size()-1<<" moves:"<<endl;
    for(size_t i=0;i<path.size();i++)
    {
        printState(path[i]);
        if(i!=path.size()-1) cout<<"  |"<<endl<<"  v"<<endl<<endl;
    }
}

bool isSolvable(const string&state)
{
    int inversions=0;
    for(int i=0;i<9;i++)
    {
        for(int j=i+1;j<9;j++)
        {
            if(state[i]=='0' || state[j]=='0') continue;
            if(state[i]>state[j]) inversions++;
        }
    }
    return inversions%2==0;
}

void BestFirstSearch(string start)
{
    if(start==goalState)
    {
        cout<<"Already at goal!"<<endl;
        return;
    }

    priority_queue<PIS,vector<PIS>,greater<PIS>>pq;
    set<string>visited;
    map<string,string>parent;

    pq.push({misplacedTiles(start),start});
    parent[start]="";

    while(!pq.empty())
    {
        PIS temp=pq.top();
        pq.pop();

        string curr=temp.second;
        if(visited.count(curr)) continue;
        visited.insert(curr);

        if(curr==goalState)
        {
            cout<<"Best First Search - Solution Found!"<<endl;
            printPath(parent,curr);
            return;
        }

        for(auto neighbour:getNeighbours(curr))
        {
            if(visited.count(neighbour)) continue;
            if (parent.find(neighbour) == parent.end()) 
            {
                parent[neighbour] = curr;
            }
            pq.push({misplacedTiles(neighbour),neighbour});
        }
    }
    cout<<"No solution exists!"<<endl;
}

void Astar(string start)
{
    if(start==goalState)
    {
        cout<<"Already at goal!"<<endl;
        return;
    }

    priority_queue<PIS,vector<PIS>,greater<PIS>>pq;
    set<string>visited;
    map<string,string>parent;
    map<string,int>g_cost;

    g_cost[start]=0;
    pq.push({manhattanDistance(start),start});
    parent[start]="";

    while(!pq.empty())
    {
        PIS temp=pq.top();
        pq.pop();

        string curr=temp.second;
        if(visited.count(curr)) continue;
        visited.insert(curr);

        if(curr==goalState)
        {
            cout<<"A* Search - Solution Found!"<<endl;
            cout<<"Total moves: "<<g_cost[curr]<<endl;
            printPath(parent,curr);
            return;
        }

        for(auto neighbour:getNeighbours(curr))
        {
            if(visited.count(neighbour)) continue;
            int new_cost=g_cost[curr]+1;

            if(!g_cost.count(neighbour) || new_cost<g_cost[neighbour])
            {
                g_cost[neighbour]=new_cost;
                parent[neighbour]=curr;
                pq.push({new_cost+manhattanDistance(neighbour),neighbour});
            }
        }
    }
    cout<<"No solution exists!"<<endl;
}

int main()
{
    cout<<"Enter the initial state (1-8 and 0 for blank, row by row):"<<endl;
    string start="";
    for(int i=0;i<9;i++)
    {
        char c;
        cin>>c;
        start+=c;
    }

    cout<<"\nInitial State:"<<endl;
    printState(start);
    cout<<"Goal State:"<<endl;
    printState(goalState);

    if(!isSolvable(start))
    {
        cout<<"This puzzle configuration is not solvable!"<<endl;
        return 0;
    }

    cout<<"Best First Search Output:"<<endl;
    BestFirstSearch(start);

    cout<<"\nA* Search Output:"<<endl;
    Astar(start);

    return 0;
}