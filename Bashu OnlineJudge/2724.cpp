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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int fa[N],vis[N];
int Father(int x){
	return x==fa[x]?x:fa[x]=Father(fa[x]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=10000;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		x=Father(x);y=Father(y);
//		if(x==y)vis[x]=1;
//		else{
		if(x>y)swap(x,y);
		fa[x]=y;
		if(!vis[x])vis[x]=1;
		else vis[y]=1;
//		}
	}
	for(int i=1;i<=10001;i++){
		if(!vis[i]){
			printf("%d",i-1);
			break;
		}
	}
	return 0;
}