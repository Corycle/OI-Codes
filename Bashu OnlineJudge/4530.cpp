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
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int a[N],root[N];
struct Tree{
	int l,r,data;
}t[N*20];
int Build(int l,int r){
	int x=++tot;
	if(l==r){
		t[x].data=a[l];
		return x;
	}
	int mid=(l+r)>>1;
	t[x].l=Build(l,mid);
	t[x].r=Build(mid+1,r);
	return x;
}
int Change(int x,int pos,int data,int l,int r){
	int y=++tot;
	t[y]=t[x];
	if(l==r){
		t[y].data=data;
		return y;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)t[y].l=Change(t[x].l,pos,data,l,mid);
	else t[y].r=Change(t[x].r,pos,data,mid+1,r);
	return y;
}
int Ask(int x,int pos,int l,int r){
	if(l==r)return t[x].data;
	int mid=(l+r)>>1;
	if(pos<=mid)return Ask(t[x].l,pos,l,mid);
	else return Ask(t[x].r,pos,mid+1,r);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	root[0]=Build(1,n);
	for(int i=1;i<=m;i++){
		int op=read(),x=read(),y=read();
		if(op==1){
			int z=read();
			root[i]=Change(root[x],y,z,1,n);
		}
		if(op==2){
			int ans=Ask(root[x],y,1,n);
			printf("%d\n",ans);
			root[i]=root[x];
		}
	}
	return 0;
}