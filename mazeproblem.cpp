#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>

using namespace std;
typedef pair<int,int>PII;

int ROWS,COLS;

void printPath(map<PII,PII>&parent,PII target)
{
    vector<PII>path;

    while(target!=make_pair(-1,-1))
    {
        path.push_back(target);
        target=parent[target];
    }

    reverse(path.begin(),path.end());
    for(auto p:path)
        cout<<"("<<p.first<<", "<<p.second<<")"<<endl;
}

bool isValid(vector<vector<int>>&maze,vector<vector<bool>>&visited,int r,int c)
{
    return r>=0 && r<ROWS && c>=0 && c<COLS && maze[r][c]==0 && !visited[r][c];
}

void BFS(vector<vector<int>>&maze,PII start,PII goal)
{
    queue<PII>q;
    vector<vector<bool>>visited(ROWS,vector<bool>(COLS,false));
    map<PII,PII>parent;

    q.push(start);
    visited[start.first][start.second]=true;
    parent[start]={-1,-1};

    vector<PII>directions={{-1,0},{1,0},{0,-1},{0,1}};

    while(!q.empty())
    {
        PII curr=q.front();
        q.pop();
        int r=curr.first;
        int c=curr.second;

        if(curr==goal)
        {
            cout<<"Solution found"<<endl;
            printPath(parent,curr);
            return;
        }

        for(auto d:directions)
        {
            int nr=r+d.first;
            int nc=c+d.second;

            if(isValid(maze,visited,nr,nc))
            {
                visited[nr][nc]=true;
                parent[{nr,nc}]={r,c};
                q.push({nr,nc});
            }
        }
    }
    cout<<"No solution found."<<endl;
}

void DFS(vector<vector<int>>&maze,PII start,PII goal)
{
    stack<PII>st;
    vector<vector<bool>>visited(ROWS,vector<bool>(COLS,false));
    map<PII,PII>parent;

    st.push(start);
    visited[start.first][start.second]=true;
    parent[start]={-1,-1};

    vector<PII>directions={{-1,0},{1,0},{0,-1},{0,1}};

    while(!st.empty())
    {
        PII curr=st.top();
        st.pop();
        int r=curr.first;
        int c=curr.second;

        if(curr==goal)
        {
            cout<<"Solution found"<<endl;
            printPath(parent,curr);
            return;
        }

        for(auto d:directions)
        {
            int nr=r+d.first;
            int nc=c+d.second;

            if(isValid(maze,visited,nr,nc))
            {
                visited[nr][nc]=true;
                parent[{nr,nc}]={r,c};
                st.push({nr,nc});
            }
        }
    }
    cout<<"No solution found."<<endl;
}

void DLS(vector<vector<int>>&maze,PII start,PII goal,int depthLimit)
{
    stack<pair<PII,int>>st;
    vector<vector<bool>>visited(ROWS,vector<bool>(COLS,false));
    map<PII,PII>parent;

    st.push({start,0});
    visited[start.first][start.second]=true;
    parent[start]={-1,-1};

    vector<PII>directions={{-1,0},{1,0},{0,-1},{0,1}};

    while(!st.empty())
    {
        auto[curr,depth]=st.top();
        st.pop();
        int r=curr.first;
        int c=curr.second;

        if(curr==goal)
        {
            cout<<"Solution found"<<endl;
            printPath(parent,curr);
            return;
        }

        if(depth>=depthLimit) continue;

        for(auto d:directions)
        {
            int nr=r+d.first;
            int nc=c+d.second;

            if(isValid(maze,visited,nr,nc))
            {
                visited[nr][nc]=true;
                parent[{nr,nc}]={r,c};
                st.push({{nr,nc},depth+1});
            }
        }
    }
    cout<<"No solution found within depth limit "<<depthLimit<<"."<<endl;
}

int main()
{
    cout<<"Maze Problem using BFS, DFS and DLS"<<endl;

    cout<<"Enter number of rows: ";
    cin>>ROWS;
    cout<<endl;

    cout<<"Enter number of columns: ";
    cin>>COLS;
    cout<<endl;

    cout<<"Enter the maze row by row (0=open, 1=wall):"<<endl;
    vector<vector<int>>maze(ROWS,vector<int>(COLS));
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            cin>>maze[i][j];

    PII start,goal;
    cout<<"Enter start position (row col): ";
    cin>>start.first>>start.second;
    cout<<endl;

    cout<<"Enter goal position (row col): ";
    cin>>goal.first>>goal.second;
    cout<<endl;

    if(maze[start.first][start.second]==1 || maze[goal.first][goal.second]==1)
    {
        cout<<"Start or goal is a wall. Invalid input."<<endl;
        return 0;
    }

    cout<<"BFS output: "<<endl;
    BFS(maze,start,goal);

    cout<<endl;
    cout<<"DFS output: "<<endl;
    DFS(maze,start,goal);

    cout<<endl;
    cout<<"DLS output (depth=3): "<<endl;
    DLS(maze,start,goal,3);

    return 0;
}