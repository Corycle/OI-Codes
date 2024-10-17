#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
struct edge{
	long long l,r,s1,s2,fa;
}p[105];
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,f[105];
inline long long read(){
	long long s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
inline long long gcd(long long x,long long y){
	if(x<y)swap(x,y);
	return y==0?x:gcd(y,x%y);
}
void hqq_dp(int rt){
	if(p[rt].l)hqq_dp(p[rt].l);
	if(p[rt].r)hqq_dp(p[rt].r);
	long long mod,t,x,y;
	if(p[rt].l==0&&p[rt].r==0){
		mod=gcd(p[rt].s1,p[rt].s2);
		t=p[rt].s1*p[rt].s2/mod;
	}
	if(p[rt].l!=0&&p[rt].r==0){
		x=f[p[rt].l];
		mod=gcd(x*p[rt].s1,p[rt].s2);
		t=x*p[rt].s1*p[rt].s2/mod;//最小公倍数  
	}
	if(p[rt].l==0&&p[rt].r!=0){
		y=f[p[rt].r];
		mod=gcd(y*p[rt].s2,p[rt].s1);
		t=y*p[rt].s2*p[rt].s1/mod;//最小公倍数  
	}
	if(p[rt].l!=0&&p[rt].r!=0){
		int x,y;
		x=f[p[rt].l];y=f[p[rt].r];
		mod=gcd(x*p[rt].s1,y*p[rt].s2);
		t=x*p[rt].s1*y*p[rt].s2/mod;
	}
	x=t/p[rt].s1;
	y=t/p[rt].s2;
	f[rt]=x+y;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
//	cout<<gcd(8,10)<<endl<<gcd(5,20)<<endl;
	n=read();
	for(i=1;i<=n;i++)p[i].fa=i;
	for(i=1;i<=n;i++){
		p[i].s1=read();p[i].s2=read();
		p[i].l=read();p[i].r=read();
		p[p[i].l].fa=p[p[i].r].fa=i;
	}
	int rt=1;
	while(p[rt].fa!=rt)rt=p[rt].fa;
	hqq_dp(rt);
//	cout<<rt<<endl;
//	for(i=1;i<=n;i++)printf("%d ",f[i]);
	printf("%d",f[rt]);
	return 0;
}