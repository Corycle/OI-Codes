#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    int ans=0;
    bool f;
    cin>>n;
    int a[n+1];
    for (int i=1;i<=n;i++)
        cin>>a[i];
    for (int i=n;i>=1;i--)
    for (int j=i-1;j>=1;j--)
        {
            if (a[j]>=a[i]) break;
            f=false;
            for (int k=j+1;k<=i-1;k++)
                if (a[k]>=a[i]||a[k]<=a[j])
                {
                    f=true;
                    break;
                }
            if (!f)ans=max(ans,i-j+1);
        }
    cout<<ans;
    return 0;
}