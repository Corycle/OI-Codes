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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int a[N],root[N];
struct Tree{
	int l,r,data;
}t[N*20];
int Build(int l,int r){
	int rt=++cnt;
	if(l==r){
		t[rt].data=a[l];
		return rt;
	}
	int mid=(l+r)>>1;
	t[rt].l=Build(l,mid);
	t[rt].r=Build(mid+1,r);
	return rt;
}
int Change(int num,int l,int r,int x,int y){
	if(x<l||x>r)return num;
	int rt=++cnt;
	t[rt]=t[num];
	if(l==r){
		t[rt].data=y;
		return rt;
	}
	int mid=(l+r)>>1;
	t[rt].l=Change(t[rt].l,l,mid,x,y);
	t[rt].r=Change(t[rt].r,mid+1,r,x,y);
	return rt;
}
void Ask(int num,int l,int r,int x){
	if(x<l||x>r)return;
	if(l==r){
		printf("%d\n",t[num].data);
		return;
	}
	int mid=(l+r)>>1;
	Ask(t[num].l,l,mid,x);
	Ask(t[num].r,mid+1,r,x);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	root[0]=Build(1,n);
	for(int i=1;i<=m;i++){
		int op=read();
		if(op==1){
			int x=read(),y=read(),z=read();
			root[i]=root[x];
			root[i]=Change(root[i],1,n,y,z);
		}
		if(op==2){
			int x=read(),y=read();
			root[i]=root[x];
			Ask(root[i],1,n,y);
		}
	}
	return 0;
}
/*
支持如下几种操作:
　　在某个历史版本上修改某一个位置上的值
　　访问某个历史版本上的某一位置的值
	
	利用主席树 
*/
