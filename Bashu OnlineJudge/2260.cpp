#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
int d[10000000];
int main()
{
    int l;
    while(cin>>l)
    {
        memset(d,0,sizeof(d));
        int n;
        cin>>n;
        for(int i=0;i<n;i++)
            cin>>d[i];

        int maxs=0,mins=0;
        for(int i=0;i<n;i++)
        {
            mins=max(mins,min(l+1-d[i],d[i]));//最少时间是所有人距离桥最近的最大值
            maxs=max(maxs,max(l+1-d[i],d[i]));//最多时间是所有人距离桥最远的最大值
        }
        cout<<mins<<' '<<maxs<<endl;
    }
}