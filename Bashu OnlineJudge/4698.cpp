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
#define set_it set<Node>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=4e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Y,Ans;
vector<int>G[N];
int n,m,tot,fa[N];
ll Sqr(ll x){return x*x;}
struct Circle{ll x,y,r;}C[N];
struct Node{
	ll id,dlt;
	double GetPos(){return C[id].x-dlt*sqrt(Sqr(C[id].r)-Sqr(C[id].y-Y));}
	friend bool operator<(Node A,Node B){return A.id!=B.id?A.GetPos()<B.GetPos():A.dlt>B.dlt;}
}F[N];
set<Node>S;
bool cmp(Node A,Node B){
	return C[A.id].y-A.dlt*C[A.id].r<C[B.id].y-B.dlt*C[B.id].r;
}
void DFS(int x,int dlt){
	Ans+=Sqr(C[x].r)*dlt;
	for(auto y:G[x])DFS(y,-dlt);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		C[i].x=read();
		C[i].y=read();
		C[i].r=read();
		F[++tot]=(Node){i,1};
		F[++tot]=(Node){i,-1};
	}
	sort(F+1,F+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		int id=F[i].id,dlt=F[i].dlt;
		if(dlt==1){
			Y=C[id].y-C[id].r;
			if(S.size()){
				set_it it=S.lower_bound(F[i]);
				if(it!=S.end()){
					if((*it).dlt==1)fa[id]=fa[(*it).id];
					if((*it).dlt==-1)fa[id]=(*it).id;
				}
			}
			S.insert((Node){id,1});
			S.insert((Node){id,-1});
		}
		if(dlt==-1){
			S.erase((Node){id,1});
			S.erase((Node){id,-1});
			G[fa[id]].push_back(id);
		}
	}
	DFS(0,-1);
	printf("%lld",Ans);
	return 0;
}