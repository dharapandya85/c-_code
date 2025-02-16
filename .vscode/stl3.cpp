#include<bits/stdc++.h>
using namespace std;
void print(map<int,string> &m)
{
    cout<<m.size()<<endl;
    for(auto &pr:m)
    {
        cout<<pr.first<<" "<<pr.second<<endl;
    }
}
int main()
{
    map<int,string > m;
    m[1]="abc";
    m[2]="cdc";
    m[3]="acd";
     m[6]="a";
     m[5]="cde";
    print(m);

    
}