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
#include<set>
#define ll long long
#define set_it set<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=19260817;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
struct Node{
	int cnt,ans;
	int Ask(){if(cnt)return 0;return ans;}
	void Mul(int x){if(!x)cnt++;else ans=1ll*ans*x%Mod;}
	void Div(int x){if(!x)cnt--;else ans=1ll*ans*Pow(x,Mod-2)%Mod;}
};
int n,m,tot,Ans,len[N];
vector<int>a[N];
map<int,int>vis;
map<int,Node>F;//F[x]:x出现的方案数 
map<int,int>G[N];//G[id][x]:x在序列id中出现的方案数 
map<int,set<int> >S[N];//S[id][x]:x在序列id中出现的位置 
ll Sum(ll n){return n*(n+1)/2%Mod;}
void Prepare(int id,int x){
	S[id][x].insert(0);
	S[id][x].insert(len[id]+1);
	G[id][x]=Sum(len[id]);
}
void Insert(int id,int pos){
	int x=a[id][pos];
	if(!vis[x]){F[x].ans=tot;vis[x]=1;}
	if(!S[id][x].size())Prepare(id,x);
	
	Ans=(Ans+F[x].Ask())%Mod;
	F[x].Div(G[id][x]);
	S[id][x].insert(pos);
	set_it P=S[id][x].find(pos);
	set_it L=--P,R=++++P;--P;
	G[id][x]=((G[id][x]-Sum(*R-*L-1)+Sum(*P-*L-1)+Sum(*R-*P-1))%Mod+Mod)%Mod;
	F[x].Mul(G[id][x]);
	Ans=(Ans-F[x].Ask()+Mod)%Mod;
}
void Delete(int id,int pos){
	int x=a[id][pos];
	
	Ans=(Ans+F[x].Ask())%Mod;
	F[x].Div(G[id][x]);
	set_it P=S[id][x].find(pos);
	set_it L=--P,R=++++P;--P;
	G[id][x]=((G[id][x]+Sum(*R-*L-1)-Sum(*P-*L-1)-Sum(*R-*P-1))%Mod+Mod)%Mod;
	S[id][x].erase(pos);
	F[x].Mul(G[id][x]);
	Ans=(Ans-F[x].Ask()+Mod)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();tot=1;
	for(int i=1;i<=n;i++){
		len[i]=read();
		tot=1ll*tot*Sum(len[i])%Mod;//总方案数 
	}
	for(int i=1;i<=n;i++){
		a[i].push_back(0);
		for(int j=1;j<=len[i];j++){
			a[i].push_back(read());
			Insert(i,j);
		}
	}
	printf("%d\n",Ans);
	while(m--){
		int x=read(),y=read(),z=read();
		Delete(x,y);a[x][y]=z;Insert(x,y);
		printf("%d\n",Ans);
	}
	return 0;
}