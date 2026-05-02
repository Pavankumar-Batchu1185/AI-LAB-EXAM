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
    vector<int>queens;

    bool operator<(const State& other) const
    {
        return queens<other.queens;
    }

    bool operator==(const State& other) const
    {
        return queens==other.queens;
    }
};

void printPath(map<State,State>&parent,State target)
{
    vector<State>path;

    State start;
    start.queens={-1};

    while(!(target==start))
    {
        path.push_back(target);
        target=parent[target];
    }

    reverse(path.begin(),path.end());

    for(auto s:path)
    {
        for(int i=0;i<s.queens.size();i++)
            cout<<"("<<i<<","<<s.queens[i]<<") ";
        cout<<endl;
    }
}

void printBoard(State&s)
{
    cout<<endl;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(s.queens[i]==j)
                cout<<"Q ";
            else
                cout<<". ";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool isSafe(vector<int>&queens,int row,int col)
{
    for(int i=0;i<row;i++)
    {
        if(queens[i]==col) return false;
        if(abs(queens[i]-col)==abs(i-row)) return false;
    }
    return true;
}

bool isGoal(State&s)
{
    return s.queens.size()==8;
}

void BFS()
{
    queue<State>q;
    set<State>visited;
    map<State,State>parent;

    State start;
    State s;
    s.queens={-1};

    q.push(start);
    visited.insert(start);
    parent[start]=s;

    while(!q.empty())
    {
        State curr=q.front();
        q.pop();

        if(isGoal(curr))
        {
            cout<<"Solution found: "<<endl;
            printPath(parent,curr);
            printBoard(curr);
            return;
        }

        int row=curr.queens.size();

        for(int col=0;col<8;col++)
        {
            if(isSafe(curr.queens,row,col))
            {
                State new_state=curr;
                new_state.queens.push_back(col);

                if(visited.find(new_state)==visited.end())
                {
                    visited.insert(new_state);
                    parent[new_state]=curr;
                    q.push(new_state);
                }
            }
        }
    }
    cout<<"No solution found."<<endl;
}

void DFS()
{
    stack<State>st;
    set<State>visited;
    map<State,State>parent;

    State start;
    State s;
    s.queens={-1};

    st.push(start);
    visited.insert(start);
    parent[start]=s;

    while(!st.empty())
    {
        State curr=st.top();
        st.pop();

        if(isGoal(curr))
        {
            cout<<"Solution found: "<<endl;
            printPath(parent,curr);
            printBoard(curr);
            return;
        }

        int row=curr.queens.size();

        for(int col=0;col<8;col++)
        {
            if(isSafe(curr.queens,row,col))
            {
                State new_state=curr;
                new_state.queens.push_back(col);

                if(visited.find(new_state)==visited.end())
                {
                    visited.insert(new_state);
                    parent[new_state]=curr;
                    st.push(new_state);
                }
            }
        }
    }
    cout<<"No solution found."<<endl;
}

void DLS(int depthLimit)
{
    stack<pair<State,int>>st;
    set<State>visited;
    map<State,State>parent;

    State start;
    State s;
    s.queens={-1};

    st.push({start,0});
    visited.insert(start);
    parent[start]=s;

    while(!st.empty())
    {
        auto[curr,depth]=st.top();
        st.pop();

        if(isGoal(curr))
        {
            cout<<"Solution found: "<<endl;
            printPath(parent,curr);
            printBoard(curr);
            return;
        }

        if(depth>=depthLimit) continue;

        int row=curr.queens.size();

        for(int col=0;col<8;col++)
        {
            if(isSafe(curr.queens,row,col))
            {
                State new_state=curr;
                new_state.queens.push_back(col);

                if(visited.find(new_state)==visited.end())
                {
                    visited.insert(new_state);
                    parent[new_state]=curr;
                    st.push({new_state,depth+1});
                }
            }
        }
    }
    cout<<"No solution found within depth limit "<<depthLimit<<"."<<endl;
}

int main()
{
    cout<<"8-Queens Problem using BFS, DFS and DLS"<<endl;

    cout<<endl;
    cout<<"BFS output: "<<endl;
    BFS();

    cout<<"DFS output: "<<endl;
    DFS();

    cout<<"DLS output (depth=3): "<<endl;
    DLS(3);

    return 0;
}