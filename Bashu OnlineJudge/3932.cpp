/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p1[N],p2[N];
ll Ans,sum1[N],sum2[N];
struct Point{ll x,y,p1,p2;}P[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		P[i].x=x+y;P[i].y=x-y;
		sum1[i]=P[i].x;
		sum2[i]=P[i].y;
	}
	Ans=9e18;
	sort(sum1+1,sum1+n+1);
	sort(sum2+1,sum2+n+1);
	for(int i=1;i<=n;i++)p1[i]=lower_bound(sum1+1,sum1+n+1,P[i].x)-sum1;
	for(int i=1;i<=n;i++)p2[i]=lower_bound(sum2+1,sum2+n+1,P[i].y)-sum2;
	for(int i=1;i<=n;i++)sum1[i]+=sum1[i-1];
	for(int i=1;i<=n;i++)sum2[i]+=sum2[i-1];
	for(int i=1;i<=n;i++){
		ll ans1=P[i].x*(p1[i]-1)-sum1[p1[i]-1]+sum1[n]-sum1[p1[i]]-(n-p1[i])*P[i].x;
		ll ans2=P[i].y*(p2[i]-1)-sum2[p2[i]-1]+sum2[n]-sum2[p2[i]]-(n-p2[i])*P[i].y;
		Ans=min(Ans,ans1+ans2);
	}
	printf("%lld",Ans/2);
	return 0;
}