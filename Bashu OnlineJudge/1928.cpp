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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,p,Ans;
ll c[N],v[N];
struct Node{ll a,b;}P[N];
bool cmp(ll A,ll B){return A>B;}
bool Cmp(Node A,Node B){return A.b>B.b;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(ll i=1;i<=n;i++)c[i]=read();
	for(ll i=1;i<=m;i++){
		P[i].a=read();
		P[i].b=read();
	}
	for(ll i=1;i<=p;i++)v[i]=read();
	sort(c+1,c+n+1,cmp);
	sort(v+1,v+p+1,cmp);
	sort(P+1,P+m+1,Cmp);
	ll L=1,R=n,pos1=1,pos2=1,sum=-1;
	for(ll i=1;i<=n;i++){
		if(sum==-1){
			sum=0;
			while(c[L]&&pos2<=m){
				ll dlt=min(c[L],P[pos2].a);
				c[L]-=dlt;P[pos2].a-=dlt;
				sum+=P[pos2].b*dlt;
				if(!P[pos2].a)pos2++;
			}
		}
		if(sum>=v[pos1]){c[L++]=0;Ans+=sum;sum=-1;}
		else{c[R--]=0;Ans+=v[pos1++];}
	}
	printf("%lld",Ans);
	return 0;
}