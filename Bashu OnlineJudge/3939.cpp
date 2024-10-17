#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int a,b,c;
int Ans,tot,cnt,Min;
int h[N],p[N],vis[N],flag[N],P[4][N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
bool DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis[y]){
			vis[y]=1;
			if(!p[y]||DFS(p[y])){
				p[y]=x;
				return true;
			}
		}
	}
	return false;
}
int Hungary(){
	int tmp=0;
	for(int i=1;i<=b;i++){
		for(int j=1;j<=c;j++)vis[j]=0;
		if(DFS(i))tmp++;
	}
	return tmp;
}
void Solve(int x){
	int ans=0;cnt=0;
	for(int i=1;i<=b;i++)h[i]=0;
	for(int i=1;i<=c;i++)p[i]=0;
	for(int i=1;i<=a;i++){
		if((x>>(i-1))&1){flag[i]=0;ans++;}
		else flag[i]=1;
	}
	for(int i=1;i<=tot;i++){
		if(flag[P[1][i]]){
			Add(P[2][i],P[3][i]);
		}
	}
	Ans=min(Ans,ans+Hungary());
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		Ans=inf;tot=0;
		a=read();b=read();c=read();
		Min=min(a,min(b,c));
		for(int i=1;i<=a;i++){
			for(int j=1;j<=b;j++){
				for(int k=1;k<=c;k++){
					int x=read();
					if(x){
						tot++;
						P[1][tot]=i;
						P[2][tot]=j;
						P[3][tot]=k;
					}
				}
			}
		}
		if(Min==b){swap(a,b);swap(P[1],P[2]);}
		if(Min==c){swap(a,c);swap(P[1],P[3]);}
		int maxn=1<<a;
		for(int i=0;i<maxn;i++)Solve(i);
		printf("%d\n",Ans);
	}
	return 0;
}