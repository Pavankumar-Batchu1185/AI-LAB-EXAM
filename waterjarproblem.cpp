
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<numeric>
#include<map>

using namespace std;
typedef pair<int,int>PII;

void printPath(map<PII,PII>&parent,PII target)
{
    vector<PII>path;

    while(target!=make_pair(-1,-1))
    {
        path.push_back({target});
        target=parent[target];
    }

    reverse(path.begin(),path.end());
    for(auto p:path)
    {
        cout<<"("<<p.first<<", "<<p.second<<")"<<endl;
    }
}


void DFS(int& capacity_x,int& capacity_y,int target)
{
    vector<vector<bool>>visited(capacity_x+1,vector<bool>(capacity_y+1,false));
    map<PII,PII>parent;
    stack<PII>st;
    
    st.push({0,0});
    visited[0][0]=true;
    parent[{0,0}]={-1,-1};

    while(!st.empty())
    {
        PII temp=st.top();
        st.pop();
        int a=temp.first;
        int b=temp.second;

         if(a==target || b==target)
        {
                cout<<"Solution found "<<endl;
                printPath(parent,temp);
                return;
        }

        
        int transfer_from_x=min(a,capacity_y-b);
        int transfer_from_y=min(b,capacity_x-a);

        vector<PII>possible_states={
            {capacity_x,b},{a,capacity_y},{0,b},{a,0},
            {a-transfer_from_x,b+transfer_from_x},
            {a+transfer_from_y,b-transfer_from_y}
        };

        for(auto state:possible_states)
        {
            if(visited[state.first][state.second]) continue;
            st.push(state);
            visited[state.first][state.second]=true;
            parent[{state.first,state.second}]={a,b};
        }
    }
    cout<<"No solution found."<<endl;
}

void BFS(int& capacity_x,int& capacity_y,int target)
{
    vector<vector<bool>>visited(capacity_x+1,vector<bool>(capacity_y+1,false));
    map<PII,PII>parent;
   queue<PII>q;
    q.push({0,0});
    visited[0][0]=true;
    parent[{0,0}]={-1,-1};
    while(!q.empty())
    {
        PII temp=q.front();
        q.pop();
        int a=temp.first;
        int b=temp.second;

        if(a==target || b==target)
        {
                cout<<"Solution found "<<endl;
                printPath(parent,temp);
                return;
        }

      
        int transfer_from_x=min(a,capacity_y-b);
        int transfer_from_y=min(b,capacity_x-a);

        vector<PII>possible_states={
            {capacity_x,b},{a,capacity_y},{0,b},{a,0},
            {a-transfer_from_x,b+transfer_from_x},
            {a+transfer_from_y,b-transfer_from_y}
        };

        for(auto state:possible_states)
        {
            if(visited[state.first][state.second]) continue;
            q.push(state);
            visited[state.first][state.second]=true;
            parent[{state.first,state.second}]={a,b};
        }
    }
    cout << "No solution found." << endl;
}

void DLS(int capacity_x, int capacity_y, int target,int depthLimit)
{
    vector<vector<bool>>visited(capacity_x+1,vector<bool>(capacity_y+1,false));
    map<PII,PII>parent;
    stack<pair<PII, int>> st;  
    st.push({{0, 0}, 0});
    visited[0][0] = true;
    parent[{0, 0}] = {-1, -1};

    while (!st.empty())
    {
        auto [temp, depth] = st.top();
        st.pop();
        int a = temp.first, b = temp.second;

        if (a == target || b == target)
        {
            cout << "Solution found" << endl;
            printPath(parent, temp);
            return;
        }

        if (depth >= depthLimit) continue;  

        int transfer_from_x = min(a, capacity_y - b);
        int transfer_from_y = min(b, capacity_x - a);

        vector<PII> possible_states = {
            {capacity_x, b}, {a, capacity_y}, {0, b}, {a, 0},
            {a - transfer_from_x, b + transfer_from_x},
            {a + transfer_from_y, b - transfer_from_y}
        };

        for (auto state : possible_states)
        {
            if (visited[state.first][state.second]) continue;
            st.push({state, depth + 1});
            visited[state.first][state.second] = true;
            parent[{state.first, state.second}] = {a, b};
        }
    }
    cout << "No solution found within depth limit " << depthLimit << "." << endl;
}


int main()
{
    cout<<"Water Jar Problem using BFS-DFS"<<endl;
    
    int capacity_x,capacity_y,target;
    cout<<"Enter the capacity for jug A: ";
    cin>>capacity_x;
    cout<<endl;

    cout<<"Enter the capacity of jug B: ";
    cin>>capacity_y;
    cout<<endl;

    cout<<"Enter the target amount of litres you want in any of the jug ...";
    cin>>target;
    cout<<endl;

    if(target <= 0 || target > max(capacity_x, capacity_y) || target % gcd(capacity_x, capacity_y) != 0)
    {
        cout<<"No solution possible"<<endl;
        return 0;
    }

    
    cout<<"DFS output: "<<endl;
    DFS(capacity_x,capacity_y,target);
    
    cout<<"BFS output: "<<endl;
    BFS(capacity_x,capacity_y,target);

    DLS(capacity_x, capacity_y, target, 3);
    

    return 0;
}