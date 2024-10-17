#include<iostream>  
#include<algorithm>  
using namespace std;  
int n,x,s[1005];  
int main()
{  
    cin>>x>>n;  
    int i,j,sum=0,ans=0;  
    for(i=1;i<=n;i++)
    cin>>s[i];  
    sort(s+1,s+1+n);  
    if(s[1]!=1)
    {  
        cout<<-1;  
        return 0;  
    }  
    while(true)
    {  
        if(sum>=x)
        {  
            cout<<ans;
            return 0;  
        }  
        for(i=n;i>=1;i--)  
            if(s[i]<=sum+1)
            {
               sum+=s[i];
               ans++;
               break;
            }  
    }  
    return 0;
}