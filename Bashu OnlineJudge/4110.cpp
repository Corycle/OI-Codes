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
const ll inf=9e18;
const ll N=200005;
const ll K=2;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<ll>G[N];
ll n,D,id,Ans,Min,Max,root;
ll q[K],f1[N],f2[N],vis[N];
struct Tree{ll id,ch[2],d[K],Max[K],Min[K];};
bool cmp(Tree A,Tree B){return A.d[D]<B.d[D];}
struct KD_Tree{
	Tree t[N];
	void Pushup(ll p){
		for(ll i=0;i<K;i++){
			if(t[p].ch[0]){
				t[p].Max[i]=max(t[p].Max[i],t[t[p].ch[0]].Max[i]);
				t[p].Min[i]=min(t[p].Min[i],t[t[p].ch[0]].Min[i]);
			}
			if(t[p].ch[1]){
				t[p].Max[i]=max(t[p].Max[i],t[t[p].ch[1]].Max[i]);
				t[p].Min[i]=min(t[p].Min[i],t[t[p].ch[1]].Min[i]);
			}
		}
	}
	void Build(ll &p,ll l,ll r,ll d){
		ll mid=(l+r)>>1;p=mid;D=d;
		nth_element(t+l,t+mid,t+r+1,cmp);
		for(ll i=0;i<K;i++){
			t[p].Max[i]=t[p].Min[i]=t[p].d[i];
		}
		if(l<mid)Build(t[p].ch[0],l,mid-1,d^1);
		if(r>mid)Build(t[p].ch[1],mid+1,r,d^1);
		Pushup(p);
	}
	ll Dist(ll p){
		ll ans=0;
		for(ll i=0;i<K;i++){
			ans+=abs(t[p].d[i]-q[i]);
		}
		return ans;
	}
	ll Guess(ll p){
		ll ans=0;
		for(ll i=0;i<K;i++){
			if(q[i]>t[p].Max[i])ans+=abs(t[p].Max[i]-q[i]);
			if(q[i]<t[p].Min[i])ans+=abs(t[p].Min[i]-q[i]);
		}
		return ans;
	}
	void Ask(ll p){
		if(!p)return;
		if(t[p].id!=id){
			ll dist=Dist(p);
			if(dist<Min||(dist==Min&&t[p].id<Ans)){
				Min=dist;Ans=t[p].id;
			}
		}
		ll dl=Guess(t[p].ch[0]);
		ll dr=Guess(t[p].ch[1]);
		if(dl<dr){
			if(dl<=Min)Ask(t[p].ch[0]);
			if(dr<=Min)Ask(t[p].ch[1]);
		}
		else{
			if(dr<=Min)Ask(t[p].ch[1]);
			if(dl<=Min)Ask(t[p].ch[0]);
		}
	}
}tree;
void DFS(ll x){
	vis[x]=1;
	for(auto y:G[x]){
		if(vis[y])continue;
		DFS(y);
		if(f1[x]<f1[y]+1){
			f2[x]=f1[x];f1[x]=f1[y]+1;
		}
		else f2[x]=max(f2[x],f1[y]+1);
	}
	Max=max(Max,f1[x]+f2[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		tree.t[i].id=i;
		tree.t[i].d[0]=read();
		tree.t[i].d[1]=read();
	}
	tree.Build(root,1,n,0);
	for(ll i=1;i<=n;i++){
		id=tree.t[i].id;
		q[0]=tree.t[i].d[0];
		q[1]=tree.t[i].d[1];
		Min=inf;Ans=0;
		tree.Ask(root);
		G[id].push_back(Ans);
		G[Ans].push_back(id);
	}
	ll Max1=0,Max2=0,Max3=0;
	for(ll i=1;i<=n;i++){
		if(!vis[i]){
			Max=0;DFS(i);
			Max3=max(Max3,Max);
			if(Max1<(Max+1)/2){
				Max2=Max1;Max1=(Max+1)/2;
			}
			else Max2=max(Max2,(Max+1)/2);
		}
	}
	printf("%lld",max(Max1+Max2+2,Max3));
	return 0;
}