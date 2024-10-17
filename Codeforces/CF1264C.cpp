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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
#define set_it set<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
set<int>F;
int n,m,Ans,flag,E[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
struct Node{
	int Sum,Ans;
	friend Node operator+(Node A,Node B){return (Node){(int)(1ll*A.Sum*B.Sum%Mod),mod(1ll*B.Sum*A.Ans%Mod+B.Ans)};}
}Answer;
struct Segment_Tree{
	Node t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p]=(Node){E[l],E[l]};return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Answer=Answer+t[p];return;}
		int mid=(l+r)>>1;Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int Query(int l,int r){Answer=(Node){1,0};tree.Query(l,r,1,1,n);return Answer.Ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();F.insert(1);F.insert(n+1);
	for(int i=1;i<=n;i++)E[i]=100ll*Pow(read(),Mod-2)%Mod;
	tree.Build(1,1,n);Ans=Query(1,n);
	while(m--){
		int x=read();
		if(F.find(x)!=F.end()){
			set_it p=F.find(x),l=--p,r=++++p;
			Ans=mod(Ans-Query((*l),x-1)+Mod);
			Ans=mod(Ans-Query(x,(*r)-1)+Mod);
			Ans=mod(Ans+Query((*l),(*r)-1));
			F.erase(x);
		}
		else{
			F.insert(x);
			set_it p=F.find(x),l=--p,r=++++p;
			Ans=mod(Ans-Query((*l),(*r)-1)+Mod);
			Ans=mod(Ans+Query((*l),x-1));
			Ans=mod(Ans+Query(x,(*r)-1));
		}
		printf("%d\n",Ans);
	}
	return 0;
}
