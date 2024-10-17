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
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,pos[N],c[N];
ll s[N],ans,k;
struct ques{
	int l,r,id;
	ll x,y;
}q[N];
bool cmp1(ques x,ques y){
	if(pos[x.l]==pos[y.l])return x.r<y.r;
	return pos[x.l]<pos[y.l];
}
bool cmp2(ques x,ques y){
	return x.id<y.id;
}
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
ll Sqr(ll x){
	return x*x;
}
void update(int p,int addv){
	ans-=Sqr(s[c[p]]);
	s[c[p]]+=addv;
	ans+=Sqr(s[c[p]]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();k=read();
	int blk=(int)(sqrt(n));
	for(int i=1;i<=n;i++){
		c[i]=read();
		pos[i]=(i-1)/blk+1;
	}
	for(int i=1;i<=m;i++){
		q[i].id=i;
		q[i].l=read();
		q[i].r=read();
	}
	sort(q+1,q+m+1,cmp1);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		for(;r<q[i].r;r++)update(r+1,1);
		for(;r>q[i].r;r--)update(r,-1);
		for(;l<q[i].l;l++)update(l,-1);
		for(;l>q[i].l;l--)update(l-1,1);
		q[i].x=ans;
	}
	sort(q+1,q+m+1,cmp2);
	for(int i=1;i<=m;i++){
		printf("%lld\n",q[i].x);
	}
	return 0;
}