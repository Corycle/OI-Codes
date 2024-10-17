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
const int N=805;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,tot;
vector<int>G[N];
int A[N],B[N][3],b[N];
int Ans[N],vis[N],Match[N];
int Rand(int n){return rand()%n;}
void Add(int x,int y){
	G[x].push_back(y);
	G[y].push_back(x);
}
bool Find(int x){
	vis[x]=1;
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		if(!Match[y]){
			Match[Match[x]=y]=x;
			return true;
		}
	}
	for(int i=G[x].size()-1;i>=1;i--){
		swap(G[x][i],G[x][Rand(i)]);
	}
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i],c=Match[y];
		if(!vis[c]){
			Match[Match[y]=x]=y;Match[c]=0;
			if(Find(c))return true;
			Match[Match[y]=c]=y;Match[x]=0;
		}
	}
	return false;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	int T=read();
	while(T--){
		n=read();m=read();p=read();tot=0;
		for(int i=1;i<=n+m*3;i++)G[i].clear();
		for(int i=1;i<=n;i++)A[i]=++tot;
		for(int i=1;i<=m;i++){
			b[B[i][0]=++tot]=i;
			b[B[i][1]=++tot]=i;
			b[B[i][2]=++tot]=i;
			Add(B[i][0],B[i][1]);
			Add(B[i][1],B[i][2]);
			Add(B[i][2],B[i][0]);
		}
		for(int i=1;i<=p;i++){
			int x=read(),y=read();
			Add(x,B[y][0]);
			Add(x,B[y][1]);
			Add(x,B[y][2]);
		}
		int ans=0,KFC=5;
		while(KFC--){
			int tmp=0;
			memset(Match,0,sizeof(Match));
			for(int i=1;i<=tot;i++){
				memset(vis,0,sizeof(vis));
				if(!Match[i]&&Find(i))tmp++;
			}
			if(ans<tmp){
				ans=tmp;
				for(int i=1;i<=n;i++)Ans[i]=Match[i];
			}
		}
		printf("%d\n",ans-n);
		for(int i=1;i<=n;i++)printf("%d ",b[Ans[A[i]]]);
		printf("\n");
	}
	return 0;
}