#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>

using namespace std;

struct State
{
    vector<int>board;

    bool operator<(const State& other) const
    {
        return board<other.board;
    }

    bool operator==(const State& other) const
    {
        return board==other.board;
    }
};

vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};

void printBoard(State&s)
{
    cout<<endl;
    for(int i=0;i<9;i++)
    {
        if(s.board[i]==0)
            cout<<"_ ";
        else
            cout<<s.board[i]<<" ";
        if(i%3==2)
            cout<<endl;
    }
    cout<<endl;
}

void printPath(map<State,State>&parent,State target)
{
    vector<State>path;

    State s;
    s.board={-1};

    while(!(target==s))
    {
        path.push_back(target);
        target=parent[target];
    }

    reverse(path.begin(),path.end());
    
    cout<<"Total moves: "<<path.size()-1<<endl;

    for(auto s:path)
        printBoard(s);
}

bool isGoal(State&s,State&goal)
{
    return s==goal;
}

pair<int,int> toRowCol(int idx)
{
    return {idx/3, idx%3};
}

int toIndex(int row, int col)
{
    return row*3+col;
}


bool inBounds(int row, int col)
{
    return row>=0 && row<3 && col>=0 && col<3;
}

void BFS(State&start,State&goal)
{
    queue<State>q;
    set<State>visited;
    map<State,State>parent;

    State s;
    s.board={-1};

    q.push(start);
    visited.insert(start);
    parent[start]=s;

    while(!q.empty())
    {
        State curr=q.front();
        q.pop();

        if(isGoal(curr,goal))
        {
            cout<<"Solution found: "<<endl;
            printPath(parent,curr);
            return;
        }

        int zeroIdx=find(curr.board.begin(),curr.board.end(),0)-curr.board.begin();
        auto[zeroRow,zeroCol]=toRowCol(zeroIdx);

        for(auto&[dr,dc]:directions)
        {
            int newRow=zeroRow+dr;
            int newCol=zeroCol+dc;

            if(!inBounds(newRow,newCol)) continue;

            int newIdx=toIndex(newRow,newCol);

            State new_state=curr;
            swap(new_state.board[zeroIdx],new_state.board[newIdx]);

            if(visited.find(new_state)==visited.end())
            {
                visited.insert(new_state);
                parent[new_state]=curr;
                q.push(new_state);
            }
        }
    }
    cout<<"No solution found."<<endl;
}

void DFS(State&start,State&goal)
{
    stack<State>st;
    set<State>visited;
    map<State,State>parent;

    State s;
    s.board={-1};

    st.push(start);
    visited.insert(start);
    parent[start]=s;

    while(!st.empty())
    {
        State curr=st.top();
        st.pop();

        if(isGoal(curr,goal))
        {
            cout<<"Solution found: "<<endl;
            printPath(parent,curr);
            return;
        }

        int zeroIdx=find(curr.board.begin(),curr.board.end(),0)-curr.board.begin();
        auto[zeroRow,zeroCol]=toRowCol(zeroIdx);

        for(auto&[dr,dc]:directions)
        {
            int newRow=zeroRow+dr;
            int newCol=zeroCol+dc;

            if(!inBounds(newRow,newCol)) continue;

            int newIdx=toIndex(newRow,newCol);

            State new_state=curr;
            swap(new_state.board[zeroIdx],new_state.board[newIdx]);

            if(visited.find(new_state)==visited.end())
            {
                visited.insert(new_state);
                parent[new_state]=curr;
                st.push(new_state);
            }
        }
    }
    cout<<"No solution found."<<endl;
}

void DLS(State&start,State&goal,int depthLimit)
{
    stack<pair<State,int>>st;
    set<State>visited;
    map<State,State>parent;

    State s;
    s.board={-1};

    st.push({start,0});
    visited.insert(start);
    parent[start]=s;

    while(!st.empty())
    {
        auto[curr,depth]=st.top();
        st.pop();

        if(isGoal(curr,goal))
        {
            cout<<"Solution found: "<<endl;
            printPath(parent,curr);
            return;
        }

        if(depth>=depthLimit) continue;

        int zeroIdx=find(curr.board.begin(),curr.board.end(),0)-curr.board.begin();
        auto[zeroRow,zeroCol]=toRowCol(zeroIdx);

        for(auto&[dr,dc]:directions)
        {
            int newRow=zeroRow+dr;
            int newCol=zeroCol+dc;

            if(!inBounds(newRow,newCol)) continue;

            int newIdx=toIndex(newRow,newCol);

            State new_state=curr;
            swap(new_state.board[zeroIdx],new_state.board[newIdx]);

            if(visited.find(new_state)==visited.end())
            {
                visited.insert(new_state);
                parent[new_state]=curr;
                st.push({new_state,depth+1});
            }
        }
    }
    cout<<"No solution found within depth limit "<<depthLimit<<"."<<endl;
}

int main()
{
    cout<<"8-Puzzle Problem using BFS, DFS and DLS"<<endl;
    cout<<endl;

    State start,goal;
    start.board.resize(9);
    goal.board.resize(9);

    cout<<"Enter the start state (3x3, use 0 for blank): "<<endl;
    for(int i=0;i<9;i++)
        cin>>start.board[i];
    cout<<endl;

    cout<<"Enter the goal state (3x3, use 0 for blank): "<<endl;
    for(int i=0;i<9;i++)
        cin>>goal.board[i];
    cout<<endl;

    cout<<"BFS output: "<<endl;
    BFS(start,goal);

    cout<<"DFS output: "<<endl;
    DFS(start,goal);

    cout<<"DLS output (depth=3): "<<endl;
    DLS(start,goal,3);

    return 0;
}