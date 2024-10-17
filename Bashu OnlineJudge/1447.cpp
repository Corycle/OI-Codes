/*
	Hash表示法
*/
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
const int Mod=129563;
const int Mul=3758;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int Hash[N],h[N];
int vis[N],Same[N];
struct edge{
	int to,next;
}d[N*N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
	d[++cnt]=(edge){x,h[y]};h[y]=cnt;
}
int DFS(int x){
	vis[x]=1;
	int tmp[N],tot=0,ans=2019;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		tmp[++tot]=DFS(y);
	}
	sort(tmp+1,tmp+tot+1);
	for(int i=1;i<=tot;i++){
		ans=((ans*Mul)^tmp[i])%Mod;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();n=read();
	memset(Hash,0x3f,sizeof(Hash));
	for(int k=1;k<=m;k++){
		cnt=0;
		memset(h,0,sizeof(h));
		for(int i=1;i<n;i++){
			Add(read(),read());
		}
		for(int i=1;i<=n;i++){
			memset(vis,0,sizeof(vis));
			Hash[k]=min(Hash[k],DFS(i));
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=m;i++){
		if(vis[i])continue;
		printf("%d",i);
		for(int j=i+1;j<=m;j++){
			if(Hash[i]==Hash[j]){
				printf("=%d",j);
				vis[j]=1;
			}
		}
		printf("\n");
	}
	return 0;
}