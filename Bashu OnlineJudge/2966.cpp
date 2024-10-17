#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
(x*n+ans*1)/(n+ans)<=y;
x*n+ans<=n*y+ans*y;
ans(1-y)<=n*(y-x);
ans(y-1)>=n*(x-y);
ans>=n*(x-y)/(y-1);
*/
ll x,y,n,ans;
double xx,yy;
int main(){
	while(scanf("%lf%lf%lld",&xx,&yy,&n)!=EOF){
		x=round(xx*10000),y=round(yy*10000);
		if(x!=100000){
			x+=500;x*=n;
			if(x%10000==0)x-=10000;
			else x-=x%10000;
		}
		else x*=n;
		ll l=0,r=100000000000;
		ans=0;
		do{
			ll m=l+r>>1;
			if(x+m*10000<((y+500)*(n+m)))ans=m,r=m;
			else l=m;
		}while(l+1<r);
		if(xx<=yy)ans=0;
		printf("%lld\n",ans);
	}
	return 0;
}