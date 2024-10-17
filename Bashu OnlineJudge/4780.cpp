/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=19961993;
const int N=100005;
const int M=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int cnt,vis[M],pos[M],prime[M];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int maxn){
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;pos[i]=cnt;}
		for(int j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
struct Tree{
	int num[65];
	void Init(){for(int i=1;i<=cnt;i++)num[i]=0;}
	void Add(int x){
		Init();
		for(int i=1;i<=cnt;i++){
			while(x%prime[i]==0){
				x/=prime[i];num[i]++;
			}
			if(!x)break;
		}
	}
}Ans;
void Pushup(Tree &p,Tree l,Tree r){
	for(int i=1;i<=cnt;i++){
		p.num[i]=l.num[i]+r.num[i];
	}
}
struct Segment_Tree{
	Tree t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p].Add(3);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(t[p],t[p<<1],t[p<<1|1]);
	}
	void Change(int x,int y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].Add(y);return;}
		int mid=(l+r)>>1;
		Change(x,y,lson);Change(x,y,rson);
		Pushup(t[p],t[p<<1],t[p<<1|1]);
	}
	void Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Pushup(Ans,Ans,t[p]);return;}
		int mid=(l+r)>>1;Ask(x,y,lson);Ask(x,y,rson);
	}
}tree;
int main(){
//	freopen("kingdom.in","r",stdin);
//	freopen("kingdom.out","w",stdout);
	Prepare(281);
	int n=100000;
	int m=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==1)tree.Change(x,y,1,1,n);
		if(op==0){
			ll ans=1;Ans.Init();
			tree.Ask(x,y,1,1,n);
			for(int i=1;i<=cnt;i++){
				if(Ans.num[i]){
					ans=ans*(prime[i]-1)%Mod;
					ans=ans*Pow(prime[i],Ans.num[i]-1)%Mod;
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}