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
const ll inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
priority_queue<ll,vector<ll>,greater<ll> >q;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		ll n=read(),Ans=0;
		while(q.size())q.pop();
		for(ll i=1;i<=n;i++)q.push(read());
		while(q.size()>=2){
			ll x=q.top();q.pop();
			ll y=q.top();q.pop();
			q.push(x+y);Ans+=x+y;
		}
		printf("%lld\n",Ans);
	}
	return 0;
}