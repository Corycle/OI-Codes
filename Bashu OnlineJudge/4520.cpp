#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int mid,maxn,minn,ans,n,m,l,w[50010];
int find(int x)
{
    int num=0,now=0;
    for (int i=1;i<=n+1;i++)
    if (w[i]-w[now]>=x)
    num++,now=i;
    if (num>n-m) return 1;//切忌写>=，因为把最后一块石头加上了。
    else return 0;
}
main()
{
    scanf("%d%d%d",&l,&n,&m);
        for (int i=1;i<=n;i++) scanf("%d",&w[i]);
    w[n+1]=l;
    maxn=l;
    while (minn<=maxn)
    {
        int k=(maxn+minn)/2;
        if (find(k)) ans=k,minn=k+1; 
        else maxn=k-1;
    }
    printf("%d",ans);
}