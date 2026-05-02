#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<set>
#include<string>

using namespace std;

long long find_value(string str, unordered_map<char, int>& mapping)
{
    long long value=0;
    for(char ch:str)
    {
        value=value*10 + mapping[ch];
    }
    return value;
}
void solve(string s1, string s2, string s3,vector<char>&temp,unordered_map<char,int> &mapping,vector<bool>&used_digits,int index,int & count)
{
    if(index==temp.size())
    {
        long long num1=0, num2=0, num3=0;
        num1=find_value(s1, mapping);
        num2=find_value(s2, mapping);
        num3=find_value(s3, mapping);

        if(num1+num2==num3)
        {
          count++;
          cout<<"Solution found : "<<endl;

          cout<<s1<<" = "<<num1<<endl;
          cout<<s2<<" = "<<num2<<endl;
          cout<<s3<<" = "<<num3<<endl;
          cout << "(" << num1 << " + " << num2 << " = " << num3 << ")" << endl;
        }
        return;
    }

    char ch=temp[index];

    for(int digit=0;digit<=9;digit++)
    {
        if(used_digits[digit]) continue;
        if((ch==s1[0] || ch==s2[0] || ch==s3[0]) &&  digit==0) continue;

        used_digits[digit]=true;
        mapping[ch]=digit;
        solve(s1,s2,s3,temp,mapping,used_digits,index+1,count);
        mapping.erase(ch);
        used_digits[digit]=false;
    }
}
int main()
{
    cout<<"Crypt arithmetic problem using backtracking..."<<endl;

    cout<<"Enter the three strings:"<<endl;
    string s1,s2,s3;
    cin>>s1>>s2>>s3;

    cout << "\nProblem: " << s1 << " + " << s2 << " = " << s3 << endl;

    set<char>letters;
    for(char ch:s1+s2+s3)
    {
        letters.insert(ch);
    }

    vector<char>temp(letters.begin(),letters.end());
    vector<bool>used_digits(10,false);

    if(temp.size()>10)
    {
        cout<<"No solution possible"<<endl;
        return 0;
    }

    unordered_map<char, int> mapping;

    int count=0;
    solve(s1,s2,s3,temp,mapping,used_digits,0,count);

     if(count==0)
        cout << "No solution exists " << endl;
     

    return 0;
}
