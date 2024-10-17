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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int fa[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n*3;i++)fa[i]=i;
	char op[5];
	for(int i=1;i<=m;i++){
		scanf("%s",op);
		int x=read(),y=read();
		fa[Find(x+n+n)]=Find(y+n+n);
		if(op[0]=='S'){
			if(Find(x)==Find(y+n)){printf("0");return 0;}
			if(Find(x+n)==Find(y)){printf("0");return 0;}
			fa[Find(x)]=Find(y);fa[Find(x+n)]=Find(y+n);
		}
		if(op[0]=='D'){
			if(Find(x)==Find(y)){printf("0");return 0;}
			if(Find(x+n)==Find(y+n)){printf("0");return 0;}
			fa[Find(x)]=Find(y+n);fa[Find(x+n)]=Find(y);
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(fa[i]==i)cnt++;
	}
	printf("1");
	for(int i=1;i<=cnt;i++)printf("0");
	return 0;
}