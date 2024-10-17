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
#define pii pair<int,int>
#define lson l,mid
#define rson mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<pii>V[N];
int n,m,num,tot;
int a[N],b[N],c[N],rt[N],Ans[N];
int lowbit(int x){return x&(-x);}
void Add(int pos,int x){
	for(int i=n-pos+1;i<=n;i+=lowbit(i)){
		c[i]=min(c[i],x);
	}
}
int Sum(int pos){
	int ans=inf;
	for(int i=n-pos+1;i>=1;i-=lowbit(i)){
		ans=min(ans,c[i]);
	}
	return ans;
}
struct Segment_Tree{
	struct Tree{int l,r,Max;}t[N*4];
	int Ask(int x,int l,int r,int fx,int fy){
		if(fy<l||fx>r)return 0;
		if(fx<=l&&r<=fy)return t[x].Max;
		int mid=(l+r)>>1;
		return max(Ask(t[x].l,lson,fx,fy),Ask(t[x].r,rson,fx,fy));
	}
	void Insert(int &x,int y,int l,int r,int pos,int data){
		if(pos<l||pos>r)return;
		x=++tot;t[x]=t[y];
		t[x].Max=max(t[x].Max,data);
		if(l==r)return;
		int mid=(l+r)>>1;
		Insert(t[x].l,t[y].l,lson,pos,data);
		Insert(t[x].r,t[y].r,rson,pos,data);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);num=unique(b+1,b+n+1)-b-1;
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		V[r].push_back(make_pair(l,i));
	}
	memset(c,0x3f,sizeof(c));
	for(int i=1;i<=n;i++){
		int pos=lower_bound(b+1,b+num+1,a[i])-b;
		//大于a[i] 
		int l=tree.Ask(rt[i-1],1,num,pos,num);
		while(l){
			Add(l,a[l]-a[i]);
			int p=upper_bound(b+1,b+num+1,(a[i]+a[l])/2)-b-1;
			l=tree.Ask(rt[l-1],1,num,pos,p);
		}
		//小于a[i] 
		l=tree.Ask(rt[i-1],1,num,1,pos);
		while(l){
			Add(l,a[i]-a[l]);
			int p=lower_bound(b+1,b+num+1,(a[i]+a[l]+1)/2)-b-1;
			l=tree.Ask(rt[l-1],1,num,p,pos);
		}
		
		for(int j=0;j<V[i].size();j++){
			Ans[V[i][j].second]=Sum(V[i][j].first);
		}
		tree.Insert(rt[i],rt[i-1],1,num,pos,i);
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}