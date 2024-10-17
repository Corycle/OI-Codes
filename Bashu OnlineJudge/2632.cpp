#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<algorithm> 
#include<cstring>
using namespace std;
int n,k,i,a[100001],b[100001],ans=0;
int main(){    
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(i=1;i<=n-1;i++)b[i]=a[i+1]-a[i];
    sort(b+1,b+n);
    for(i=1;i<=k;i++)ans+=b[i];
    printf("%d",ans);
    return 0;
}