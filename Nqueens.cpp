
#include<iostream>
#include<vector>
#include<string>
using namespace std;


bool isSafe(vector<vector<char>>&board,int row,int col,int n)
{
   if(row<0 || col<0 || row==n || col==n) return false;
 
   for(int i=row-1;i>=0;i--)
   {
    if(board[i][col]=='Q')
    {
        return false;
    }
   }

   int i=row-1,j=col-1;
    while(i>=0 && j>=0)
    {
        if(board[i][j]=='Q')
        {
            return false;
        }
        i--;
        j--;
    }

    i=row-1,j=col+1;
    while(i>=0 && j<n)
    {
        if(board[i][j]=='Q')
        {
            return false;
        }
        i--;
        j++;
    }
    return true;
}
void solve(vector<vector<char>>&board,vector<vector<string>>&ans,int row,int n)
{
    if(row==n)
    {
        vector<string>temp;
        for(int i=0;i<n;i++)
        {
            string str="";
            for(int j=0;j<n;j++)
            {
                str+=board[i][j];
            }
            temp.push_back(str);
        }
        ans.push_back(temp);
        return;
    }
    
     for(int col=0;col<n;col++)
     {
     if(board[row][col]=='.' && isSafe(board,row,col,n))
     {
     board[row][col]='Q';
     solve(board,ans,row+1,n);
     board[row][col]='.';
     }
    }
}
vector<vector<string>> Nqueens (vector<vector<char>>&board,int n)
{
    vector<vector<string>>ans;
    solve(board, ans,0,n);
    return ans;
}
int main()
{
    int n;
    cout<<"N-queens problem using Backtracking"<<endl;
    cout<<"Enter the number of queens you want to place on the chessboard: ";
    cin>>n;

    vector<vector<char>>board(n,vector<char>(n,'.'));

    vector<vector<string>>ans=Nqueens(board,n);

    cout<<"The number of possible distinct arrangements are:"<<endl;
    cout<<ans.size()<<endl;
    
    cout<<"The possible arrangements are:"<<endl;
    for(auto temp:ans)
    {
        cout<<"Arrangement: "<<endl;
        for(auto t:temp)
        {
            cout<<t<<endl;
        }
        cout<<endl;
    }
    return 0;
}