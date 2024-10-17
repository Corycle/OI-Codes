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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,tot;
int fa[N],sum[N];
vector<int>TO[N];
struct Node{int to,num;}tmp[N*10];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
bool cmp(Node A,Node B){return Find(A.to)<Find(B.to);}
vector<Node>G1[N],G2[N];
int Tmp[N*10];
void Update(int x,vector<Node>&G){
	tot=0;
	for(auto to:G){
		if(Find(to.to)!=x)tmp[++tot]=(Node){Find(to.to),to.num};
	}
	sort(tmp+1,tmp+tot+1,cmp);
	G.clear();
	for(int i=1,j=0;i<=tot;i=j+1){
		j=i;while(j<tot&&tmp[j+1].to==tmp[i].to)tmp[i].num+=tmp[++j].num;
		G.push_back(tmp[i]);
	}
	for(int i=1;i<=tot;i++)tmp[i]=(Node){0,0};
}
void Update(int x,vector<int>&G){
	tot=0;
	for(auto to:G)if(Find(to)!=x)Tmp[++tot]=Find(to);
	sort(Tmp+1,Tmp+tot+1);G.clear();
	for(int i=1;i<=tot;i++)if(Tmp[i]!=Tmp[i-1])G.push_back(Tmp[i]);
	for(int i=1;i<=tot;i++)Tmp[i]=0;
}
ll Calc(int x){
	ll ans=0;x=Find(x);
	Update(x,G1[x]);Update(x,G2[x]);
	for(auto y:G1[x])ans+=1ll*y.num*sum[y.to];
	for(auto y:G2[x])ans+=1ll*y.num*sum[x];
//	cout<<"----"<<endl;
//	cout<<"Calc: "<<x<<endl;
//	cout<<"G1[x]: ";for(auto to:G1[x])cout<<to.to<<":"<<to.num<<" ";cout<<endl;
//	cout<<"G2[x]: ";for(auto to:G2[x])cout<<to.to<<":"<<to.num<<" ";cout<<endl;
//	cout<<ans<<endl;
//	cout<<"----"<<endl;
	return ans;
}
void Merge(vector<Node>&A,vector<Node>&B){
	if(A.size()<B.size())swap(A,B);
	for(auto x:B)A.push_back(x);
	B.clear();
}
void Union(int x,int y){
	if(Find(x)==Find(y))return;
//	cout<<"Union: "<<x<<" "<<y<<endl;
	Ans-=Calc(x);
	Update(y,G1[x]);Update(y,G2[x]);
	Update(x,G1[y]);Update(x,G2[y]);
	Ans-=Calc(y);
	Ans+=1ll*sum[x]*sum[y]*2;
	fa[y]=x;sum[x]+=sum[y];
	Merge(G1[x],G1[y]);
	Merge(G2[x],G2[y]);
	Ans+=Calc(x);
	
	vector<int>New;
	map<int,int>Vis;
	Update(x,G1[x]);Update(x,G2[x]);
	for(auto to:G1[x])Vis[Find(to.to)]=1;
	for(auto to:G2[x])if(Vis[Find(to.to)])New.push_back(to.to);
	Vis.clear();for(auto to:New)Union(Find(x),Find(to));New.clear();
}
void Link(int x,int y){
	if(Find(x)==Find(y))return;
	for(auto to:TO[x])if(Find(to)==Find(y))return;
	TO[x].push_back(Find(y));Update(x,TO[x]);
	x=Find(x);y=Find(y);
	Ans+=sum[y];
	G1[x].push_back((Node){y,1});
	G2[y].push_back((Node){x,1});
	for(auto to:G1[y])if(Find(to.to)==x){Union(x,y);return;}
}
int main(){
//	freopen("joitter2.in","r",stdin);
//	freopen("joitter2.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)sum[i]=1;
	for(int i=1;i<=m;i++){
//		cout<<"==============="<<endl;
		int x=read(),y=read();
//		cout<<"Link:: "<<Find(x)<<" "<<Find(y)<<endl;
		Link(x,y);
		printf("%lld\n",Ans);
//		cout<<"==============="<<endl;
	}
	return 0;
}
