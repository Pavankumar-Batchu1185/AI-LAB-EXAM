
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<numeric>
#include<stack>
#include<queue>
#include<set>

using namespace std;
typedef pair<int,int>PII;

struct State{
    int m,c,boat;

    bool operator<(const State& other) const
    {
        if(m!=other.m) return m<other.m;
        if(c!=other.c) return c<other.c;
        return boat<other.boat;
    }

    bool operator==(const State& other) const
    {
        return m==other.m && c==other.c && boat==other.boat;
    }
};

void printPath(map<State,State>& parent,State target)
{
    vector<State>path;

    State start={-1,-1,-1};

    while(!(target==start))
    {
       path.push_back(target);
       target=parent[target];
    }

    reverse(path.begin(),path.end());

    for(auto s: path)
    {
         cout << "(" << s.m << ", " << s.c << ", " << s.boat << ")" << endl;
    }
}

bool isValid(State s,int totalM,int totalC)
{
    if(s.m<0 || s.c<0 || s.m>totalM || s.c>totalC) return false;

    int rightM=totalM-s.m;
    int rightC=totalC-s.c;

    if(s.m>0 && s.m<s.c) return false;
    if(rightM>0 && rightM<rightC) return false;
    return true;
}
void BFS(int totalM,int totalC,int boat_side)
{
   queue<State>q;
   set<State>visited;
   map<State,State>parent;

   State start={totalM,totalC,boat_side};
   State goal={0,0,1};

   q.push(start);
   visited.insert(start);
   parent[start]={-1,-1,-1};

   vector<PII> possible_moves={
    {2,0},{0,2},{1,1},{1,0},{0,1}
   };

   while(!q.empty())
   {
    State curr=q.front();
    q.pop();

    if(curr==goal)
    {
        cout<<"Solution found: \n";
        printPath(parent,curr);
        return;
    }

    for(auto move:possible_moves)
    {
        State new_state=curr;

        if(curr.boat==0)//boat left->right
        {
            new_state.m-=move.first;
            new_state.c-=move.second;
            new_state.boat=1;
        }

        else //boat right->left
        {
            new_state.m+=move.first;
            new_state.c+=move.second;
            new_state.boat=0;
        }

        if(isValid(new_state,totalM,totalC) && visited.find(new_state)==visited.end())
        {
          visited.insert(new_state);
          parent[new_state]=curr;
          q.push(new_state);
        }
    }
   }
   cout << "No solution exists." << endl; 
}

void DFS(int totalM,int totalC,int boat_side)
{
   stack<State>st;
   set<State>visited;
   map<State,State>parent;

   State start={totalM,totalC,boat_side};
   State goal={0,0,1};

   st.push(start);
   visited.insert(start);
   parent[start]={-1,-1,-1};

   vector<PII> possible_moves={
    {2,0},{0,2},{1,1},{1,0},{0,1}
   };

   while(!st.empty())
   {
    State curr=st.top();
    st.pop();

    if(curr==goal)
    {
        cout<<"Solution found: \n";
        printPath(parent,curr);
        return;
    }

    for(auto move:possible_moves)
    {
        State new_state=curr;

        if(curr.boat==0)//boat left->right
        {
            new_state.m-=move.first;
            new_state.c-=move.second;
            new_state.boat=1;
        }

        else //boat right->left
        {
            new_state.m+=move.first;
            new_state.c+=move.second;
            new_state.boat=0;
        }

        if(isValid(new_state,totalM,totalC) && visited.find(new_state)==visited.end())
        {
          visited.insert(new_state);
          parent[new_state]=curr;
          st.push(new_state);
        }
    }
   }
   cout << "No solution exists." << endl; 
}


void DLS(int totalM, int totalC, int boat_side, int depthLimit)
{
    stack<pair<State, int>> st; 
    set<State> visited;
    map<State, State> parent;

    State start = {totalM, totalC, boat_side};
    State goal  = {0, 0, 1};

    st.push({start, 0});
    visited.insert(start);
    parent[start] = {-1, -1, -1};

    vector<PII> possible_moves = {
        {2,0},{0,2},{1,1},{1,0},{0,1}
    };

    while (!st.empty())
    {
        auto [curr, depth] = st.top();
        st.pop();

        if (curr == goal)
        {
            cout << "Solution found:" << endl;
            printPath(parent, curr);
            return;
        }

        if (depth >= depthLimit) continue;  

        for (auto move : possible_moves)
        {
            State new_state = curr;

            if (curr.boat == 0)
            {
                new_state.m -= move.first;
                new_state.c -= move.second;
                new_state.boat = 1;
            }
            else
            {
                new_state.m += move.first;
                new_state.c += move.second;
                new_state.boat = 0;
            }

            if (isValid(new_state, totalM, totalC) && visited.find(new_state) == visited.end())
            {
                visited.insert(new_state);
                parent[new_state] = curr;
                st.push({new_state, depth + 1});
            }
        }
    }
    cout << "No solution found within depth limit " << depthLimit << "." << endl;
}


int main()
{
    cout<<"Missionaries and Cannibals problem using bfs and dfs"<<endl;

    int missionaries;
    cout<<"Enter the no.of missionaries present ";
    cin>>missionaries;
    cout<<endl;

    int cannibals;
    cout<<"Enter the no.of cannibals present ";
    cin>>cannibals;
    cout<<endl;

    int boat=0;
    //0- on left,1-on right

    cout<<"BFS output : "<<endl;
    BFS(missionaries,cannibals,boat);

    cout<<endl;
     cout<<"DFS output : "<<endl;
    DFS(missionaries,cannibals,boat);

   cout<<endl;
   cout << "DLS output (depth=3):" << endl;
   DLS(missionaries, cannibals, boat, 3);

    return 0;
}
