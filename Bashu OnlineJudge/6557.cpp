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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
struct Node{int x,y,v;}P[N];
int n,m,tot,top,flag,a[N],b[N];
bool cmp(int x,int y){return a[x]>a[y];}
struct Tree{int l,r,sum;}t[N*60];
namespace tree1{
	int Root[N];
	void Insert(int pos,int val,int &x,int y,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum+=val;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(pos,val,t[x].l,t[y].l,l,mid);
		if(pos>mid)Insert(pos,val,t[x].r,t[y].r,mid+1,r);
	}
}
namespace tree2{
	int Root[N];
	void Insert(int pos,int val,int &x,int l,int r){
		if(!x)x=++tot;t[x].sum+=val;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(pos,val,t[x].l,l,mid);
		if(pos>mid)Insert(pos,val,t[x].r,mid+1,r);
	}
}
int Query1(int pos,int x,int y,int l,int r){
	if(t[x].sum+t[y].sum==r-l+1)return 0;
	if(l==r)return l;
	int mid=(l+r)>>1,ans=0;
	if(pos>mid)ans=Query1(pos,t[x].r,t[y].r,mid+1,r);
	if(ans==0)ans=Query1(pos,t[x].l,t[y].l,l,mid);
	return ans;
}
int Query2(int pos,int x,int y,int l,int r){
	if(t[x].sum+t[y].sum==r-l+1)return n+1;
	if(l==r)return l;
	int mid=(l+r)>>1,ans=n+1;
	if(pos<=mid)ans=Query2(pos,t[x].l,t[y].l,l,mid);
	if(ans==n+1)ans=Query2(pos,t[x].r,t[y].r,mid+1,r);
	return ans;
}
void Update(){
	while(top){
		int x=P[top].x,y=P[top].y,v=P[top].v;top--;
		if(v==1)tree1::Insert(x,1,tree1::Root[a[x]+1],tree1::Root[a[x]+1],1,n);
		if(v==-1)tree1::Insert(x,-1,tree1::Root[a[x]],tree1::Root[a[x]],1,n);
		tree2::Insert(x,-v,tree2::Root[y],1,n);a[x]+=v;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=i;
	sort(b+1,b+n+1,cmp);
	int p=1;
	for(int i=m;i>=1;i--){
		tree1::Root[i]=tree1::Root[i+1];
		while(p<=n&&a[b[p]]==i){
			tree1::Insert(b[p],1,tree1::Root[i],tree1::Root[i],1,n);
			p++;
		}
	}
	int T=read();
	while(T--){
		scanf("%s",s);
		if(s[0]=='l'){Update();flag=0;continue;}
		if(s[0]=='r'){Update();flag=1;continue;}
		int x=read(),y=flag?m-read()+1:read();
		if(s[0]=='a'){tree2::Insert(x,1,tree2::Root[y],1,n);P[++top]=(Node){x,y,1};}
		if(s[0]=='d'){tree2::Insert(x,-1,tree2::Root[y],1,n);P[++top]=(Node){x,y,-1};}
		if(s[0]=='q'&&s[1]=='u')printf("%d\n",x-Query1(x,tree1::Root[y],tree2::Root[y],1,n));
		if(s[0]=='q'&&s[1]=='d')printf("%d\n",Query2(x,tree1::Root[y],tree2::Root[y],1,n)-x);
	}
	return 0;
}