#include<bits/stdc++.h>
using namespace std;
void printVec(vector<int>&v)
{
    cout<<"size:"<<v.size()<<endl;
    for(int i=0;i<v.size();++i)
    {
        cout<<v[i]<<" "<<endl;
    }
    cout<<endl;
}
int main()
{
    int N;
    cin>>N;  
    vector<vector<int> >v;
    for(int i=0;i<N;++i)
    {
        int n;
        cin>>n;
        v.push_back(vector<int>());
        for(int j=0;j<n;++j)
        {
            int x;
            cin>>x;
            v[i].push_back(x);
        }
       
    }
    v[0].push_back(10);
    
    for(int i=0;i<v.size();++i)
    {
        printVec(v[i]);
    }
    cout<<v[0][1];
}