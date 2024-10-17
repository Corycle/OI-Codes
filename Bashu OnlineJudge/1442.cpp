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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot,root;
struct tree{
	int l,r,ln,rn;
	int num,data;
}t[100005];
void insert(int v,int x){
	if(v==0){
		v=++tot;
		t[v].data=x;
		t[v].num=1;
		return;
	}
	if(x==t[v].data){
		t[v].num++;
		return;
	}
	if(x<t[v].data){
		t[v].ln++;
		int p=0;
		if(t[v].l==0)p=1;
		insert(t[v].l,x);
		if(p)t[v].l=tot;
	}
	else{
		t[v].rn++;
		int p=0;
		if(t[v].r==0)p=1;
		insert(t[v].r,x);
		if(p)t[v].r=tot;
	}
}
void bianli(int x){
	if(t[x].l)bianli(t[x].l);
	for(int i=1;i<=t[x].num;i++)printf("%d ",t[x].data);
	if(t[x].r)bianli(t[x].r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int x=read();
		insert(1,x);
		if(i==1){
			t[1].l=t[1].r=0;
		}
	}
	bianli(1);
	return 0;
}