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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,p,root;
vector<ll>s[N];
struct Tree{ll ch[2],fa,len,high,bj,sum;}t[N];
ll Sum(ll x){return x*(x+1)/2;}
void Add(ll x,ll y){
	t[x].bj+=y;
	t[x].high+=y;
}
void Pushup(ll x){//维护Treap 
	t[x].len=t[t[x].ch[0]].len+t[t[x].ch[1]].len+1;
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum;
	t[x].sum+=Sum(t[x].len)*(t[x].high-t[t[x].fa].high);
}
void Pushdown(ll x){
	if(t[x].bj){//标记下传 
		if(t[x].ch[0])Add(t[x].ch[0],t[x].bj);
		if(t[x].ch[1])Add(t[x].ch[1],t[x].bj);
		t[x].bj=0;
	}
}
void Update(ll x){
	if(x!=root)Update(t[x].fa);
	Pushdown(x);
}
void Rotate(ll x){//Treap的旋转 
	ll y=t[x].fa;ll z=t[y].fa;
	ll l=(x!=t[y].ch[0]);ll r=l^1;
	if(z!=0){
		if(t[z].ch[0]==y)t[z].ch[0]=x;
		else t[z].ch[1]=x;
	}
	else root=x;
	t[x].fa=z;t[y].fa=x;
	t[y].ch[l]=t[x].ch[r];
	if(t[x].ch[r]){
		t[t[x].ch[r]].fa=y;
		Pushdown(t[x].ch[r]);
		Pushup(t[x].ch[r]);
	}
	t[x].ch[r]=y;
	Pushup(y);Pushup(x);
}
ll Build(ll l,ll r){//初始建图 
	if(l>r)return 0;
	ll mid=(l+r)>>1;
	ll x=mid;
	t[x].len=r-l+1;
	t[x].ch[0]=Build(l,mid-1);
	t[x].ch[1]=Build(mid+1,r);
	if(t[x].ch[0])t[t[x].ch[0]].fa=x;
	if(t[x].ch[1])t[t[x].ch[1]].fa=x;
	return x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(ll i=1;i<=p;i++){
		ll x=read(),y=read();
		s[x].push_back(y);
	}
	ll ans=0;
	root=Build(1,m);
	//初始状态高度都是0，我们只需要先把这棵树建出来 
	for(ll i=n;i>=1;i--){//每一行 
		Add(root,1);
		Pushup(root);
		for(ll j=0;j<s[i].size();j++){//黑点的纵坐标 
			ll x=s[i][j];Update(x);//下传根到x这条链的标记 
			while(x!=root)Rotate(x);//将x旋转到根 
			t[x].high=0;
			if(t[x].ch[0]){Pushdown(t[x].ch[0]);Pushup(t[x].ch[0]);}
			if(t[x].ch[1]){Pushdown(t[x].ch[1]);Pushup(t[x].ch[1]);}
			Pushup(x);
		}
		ans+=t[root].sum;
	}
	printf("%lld",Sum(n)*Sum(m)-ans);
	return 0;
}