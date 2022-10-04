#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    int count=1;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        int a[n];
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        int totalCapacity=2*k;
        string ans="YES";
        if(n>totalCapacity)
        {
            ans="NO";
        }
        else
        {
            map<int,int>mp;
            for(int i=0;i<n;i++)
            {
                mp[a[i]]++;
            }
            for(auto it:mp)
            {
                if(it.second>2)
                {
                    ans="NO";
                    break;
                }
            }

        }
        cout<<"Case #"<<count++<<": "<<ans<<endl;
    }
}
