/*
  将每个点能引爆的最大价值求出
  贪心
*/
#include<cstdio>
#include<cstring>
#include<fstream>
#include<iostream>
#define maxn 200010
using namespace std;
int n,k,o,i;
long long ans;
int x[maxn];
int value[maxn],num[maxn];
long long sum[maxn];
bool v[maxn];
 
void quicksort(int l,int r)
{
    int i,j,z;
    long long x,y;
    i=l;j=r;
    x=sum[(l+r)/2];
    do
    {
        while (sum[i]>x) i++;
        while (sum[j]<x) j--;
        if (i<=j)
        {
            y=sum[i];
            sum[i]=sum[j];
            sum[j]=y;
            z=num[i];
            num[i]=num[j];
            num[j]=z;
            i++;j--;
        }
    }while (i<j);
    if (i<r) quicksort(i,r);
    if (l<j) quicksort(l,j);
}
 
int main()
{
    //freopen("bomp.in","r",stdin);
    //freopen("bomp.out","w",stdout);
    //scanf("%d%d",&n,&k);
    cin>>n>>k;
    for (i=1;i<=n;i++)
    {
        //scanf("%d%d",&x[i],&value[i]);
        cin>>x[i]>>value[i];
    }
    for (i=1;i<=n;i++)
    {
        int t;
        t=x[i];
        sum[i]=value[i];
        while (t)
        {
            sum[i]+=value[t];
            t=x[t];
        }
    }
    for (i=1;i<=n;i++) num[i]=i;
    quicksort(1,n);
    memset(v,0,sizeof(v));
    for (i=1;i<=n;i++)
    {
        int t=x[num[i]];
        v[num[i]]=1;
        while (t)
        {
            if (v[t]) 
                sum[i]-=value[t];
            v[t]=1;
            t=x[t];
        }
    }
    quicksort(1,n);
    ans=0;
    for (i=1;i<=k;i++) ans+=sum[i];
    cout<<ans<<endl;
    //printf("%lld\n",ans);
    return 0;
}