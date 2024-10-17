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
const int N=2e6+5;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,dlt,b[N];
struct Node{int op,t,x,y;}P[N];
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=m;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree[2];
void Update(int i,int f){
	if(P[i].t==0)tree[0].Add(P[i].x,f*P[i].y);
	if(P[i].t==1){tree[1].Add(P[i].x+1,-f*P[i].y);dlt+=f*P[i].y;}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].op=read();P[i].t=read();
		if(P[i].op==1){
			P[i].x=read();
			P[i].y=read();
			b[++m]=P[i].x;
		}
	}
	sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
	for(int i=1;i<=n;i++){
		if(P[i].op==1)P[i].x=lower_bound(b+1,b+m+1,P[i].x)-b;
	}
	for(int i=1;i<=n;i++){
		if(P[i].op==1)Update(i,1);
		if(P[i].op==2)Update(P[i].t,-1);
		int sum=-dlt,pos=0;
		for(int j=20;j>=0;j--){
			if(pos+(1<<j)>m)continue;
			int tmp=sum+tree[0].c[pos+(1<<j)]-tree[1].c[pos+(1<<j)];
			if(tmp<0){sum=tmp;pos+=(1<<j);}
		}
		int ans=tree[0].Ask(pos);
		if(pos!=m){
			int val=tree[1].Ask(pos+1);
			if(dlt+val>=ans){
				ans=dlt+val;
				sum=0;pos=0;
				for(int j=20;j>=0;j--){
					if(pos+(1<<j)>m)continue;
					int tmp=sum+tree[1].c[pos+(1<<j)];
					if(tmp>=val){sum=tmp;pos+=(1<<j);}
				}
			}
		}
		if(!ans)puts("Peace");
		else printf("%d %d\n",b[pos],ans*2);
	}
	return 0;
}