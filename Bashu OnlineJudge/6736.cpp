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
ll q[K],a[N][K];
ll n,m,D,ID,Min,now,root;
ll Sqr(ll x){return x*x;}
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
		ll mid=(l+r)>>1;D=d;p=mid;
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
			ans+=Sqr(t[p].d[i]-q[i]);
		}
		return ans;
	}
	ll Guess(ll p){
		ll ans=0;
		for(ll i=0;i<K;i++){
			if(q[i]>t[p].Max[i])ans+=Sqr(t[p].Max[i]-q[i]);
			if(q[i]<t[p].Min[i])ans+=Sqr(t[p].Min[i]-q[i]);
		}
		return ans;
	}
	void Query(ll p){
		if(!p)return;
		ll dis=Dist(p);
		if(t[p].id!=now){
			if(dis<Min){Min=dis;ID=t[p].id;}
			else if(dis==Min)ID=min(ID,t[p].id);
		}
		ll dl=Guess(t[p].ch[0]);
		ll dr=Guess(t[p].ch[1]);
		if(dl<dr){
			if(dl<=Min)Query(t[p].ch[0]);
			if(dr<=Min)Query(t[p].ch[1]);
		}
		else{
			if(dr<=Min)Query(t[p].ch[1]);
			if(dl<=Min)Query(t[p].ch[0]);
		}
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		tree.t[i].id=i;
		tree.t[i].d[0]=a[i][0]=read();
		tree.t[i].d[1]=a[i][1]=read();
	}
	tree.Build(root,1,n,0);
	for(ll i=1;i<=n;i++){
		now=i;
		q[0]=a[i][0];q[1]=a[i][1];
		Min=inf;tree.Query(root);
		printf("%lld\n",ID);
	}
	return 0;
}