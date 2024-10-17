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
#define re register int
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char f[100];
int n,m,root,K=2,D,q[3],tot,Minn;
struct KD{
	int d[3],maxx[3],minn[3];
	int ch[2];
}t[1200005];
inline bool cmp(KD x,KD y){
	return x.d[D]<y.d[D];
}
inline void Pushup(int x){
	int l=t[x].ch[0],r=t[x].ch[1];
	for(re i=0;i<K;i++){
		if(l){
			t[x].maxx[i]=max(t[x].maxx[i],t[l].maxx[i]);
			t[x].minn[i]=min(t[x].minn[i],t[l].minn[i]);
		}
		if(r){
			t[x].maxx[i]=max(t[x].maxx[i],t[r].maxx[i]);
			t[x].minn[i]=min(t[x].minn[i],t[r].minn[i]);
		}
	}
}
inline void Build(int &rt,int l,int r,int d){
	int mid=(l+r)>>1;
	rt=mid;D=d;
	nth_element(t+l,t+mid,t+r+1,cmp);
	for(re i=0;i<K;i++){
		t[rt].maxx[i]=t[rt].minn[i]=t[rt].d[i];
	}
	if(l<mid)Build(t[rt].ch[0],l,mid-1,d^1);
	if(mid<r)Build(t[rt].ch[1],mid+1,r,d^1);
	Pushup(rt);
}
inline void Insert(int x){
	int p=root;
	int d=0;
	while(1){
		for(re i=0;i<K;i++){
			t[p].maxx[i]=max(t[p].maxx[i],t[x].maxx[i]);
			t[p].minn[i]=min(t[p].minn[i],t[x].minn[i]);
		}
		if(t[x].d[d]<=t[p].d[d]){
			if(!t[p].ch[0]){t[p].ch[0]=x;return;}
			p=t[p].ch[0];
		}
		else{
			if(!t[p].ch[1]){t[p].ch[1]=x;return;}
			p=t[p].ch[1];
		}
		d=d^1;
	}
}
inline int dist(int x){
	int ans=0;
	for(re i=0;i<K;i++){
		ans+=abs(q[i]-t[x].d[i]);
	}
	return ans;
}
inline int Guess(int x){
	int ans=0;
	for(re i=0;i<K;i++){
		if(q[i]<t[x].minn[i])ans+=abs(q[i]-t[x].minn[i]);
		if(q[i]>t[x].maxx[i])ans+=abs(q[i]-t[x].maxx[i]);
	}
	return ans;
}
inline void Ask(int x){
	if(x==0)return;
	int dis=dist(x);
	Minn=min(Minn,dis);
	int dl=Guess(t[x].ch[0]);
	int dr=Guess(t[x].ch[1]);
	if(dl<dr){
		if(dl<Minn)Ask(t[x].ch[0]);
		if(dr<Minn)Ask(t[x].ch[1]);
	}
	else{
		if(dr<Minn)Ask(t[x].ch[1]);
		if(dl<Minn)Ask(t[x].ch[0]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(re i=1;i<=n;i++){
		t[i].d[0]=read();
		t[i].d[1]=read();
	}
	Build(root,1,n,0);
	tot=n;
	while(m--){
		int T=read();
		if(T==1){
			tot++;
			t[tot].maxx[0]=t[tot].minn[0]=t[tot].d[0]=read();
			t[tot].maxx[1]=t[tot].minn[1]=t[tot].d[1]=read();
			Insert(tot);
		}
		if(T==2){
			q[0]=read();q[1]=read();
			Minn=inf;Ask(root);
			printf("%d\n",Minn);
		}
	}
	return 0;
}