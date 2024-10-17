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
const int N=6005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,tot,a[N],p[N],vis[N];
void Add(int x,int y){G[x].push_back(y);G[y].push_back(x);}
bool DFS(int x){
	vis[x]=tot;
	for(auto y:G[x])if(!p[y]){p[p[y]=x]=y;return true;}
	random_shuffle(G[x].begin(),G[x].end());
	for(auto y:G[x]){
		if(vis[p[y]]!=tot){
			int z=p[y];
			p[p[y]=x]=y;p[z]=0;
			if(DFS(z))return true;
			p[p[y]=z]=y;p[x]=0;
		}
	}
	return false;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	while(1){
		n=read();m=read();
		if(!n&&!m)break;
		int Ans=0,Num=n;
		for(int i=1;i<=m;i++){
			int num=read();
			for(int j=1;j<=num;j++)a[j]=read();
			if(num<=3){
				for(int x=1;x<=num;x++)for(int y=x+1;y<=num;y++)Add(a[x],a[y]);
			}
			else{
				int K=num+(num&1);
				for(int j=1;j<=K;j++)Add(Num+j,Num+j%K+1);
				for(int j=1;j<=num;j++){Add(a[j],Num+j);Add(a[j],Num+j%K+1);}
				Num+=K;
			}
		}
		for(int i=1;i<=Num;i++)if(!p[i]){tot++;Ans+=DFS(i);}
		printf("%d\n",Ans-(Num-n)/2);
		for(int i=1;i<=Num;i++){p[i]=0;G[i].clear();}
	}
	return 0;
}