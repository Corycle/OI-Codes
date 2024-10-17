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
const int M=100005;
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,n1,n2;
int h[N],fa[N];
struct Edge{
	int s,t,data,usd;
}e[M];
bool cmp(Edge x,Edge y){
	return x.data>y.data;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool MST(){
	int num1=1,num2=0;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		num1++;fa[x]=y;
		if(!e[i].data){
			num2++;
			e[i].usd=1;
		}
		if(num1==n)break;
	}
	if(num1<n||num2>p)return false;
	num1=1;num2=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=n1+1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(e[i].usd){
			fa[x]=y;
			num1++;
			num2++;
		}
	}
	for(int i=n1+1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(!e[i].usd&&x!=y&&num2<p){
			e[i].usd=1;
			fa[x]=y;
			num1++;
			num2++;
		}
	}
	for(int i=1;i<=n1;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		num1++;fa[x]=y;
		e[i].usd=1;
		if(num1==n)break;
	}
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
		if(e[i].data==1)n1++;
		if(e[i].data==0)n2++;
	}
	int v=MST();
	if(!v)printf("no solution");
	else{
		for(int i=1;i<=m;i++){
			if(e[i].usd){
				printf("%d %d %d\n",e[i].s,e[i].t,e[i].data);
			}
		}
	}
	return 0;
}