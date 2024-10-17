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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,fa[N];
struct tree{
	int data,l,r;
}t[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(t[x].data<t[y].data)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	swap(t[x].l,t[x].r);
	return x;
}
int Delete(int x){
	int k=Merge(t[x].l,t[x].r);
	t[x].data/=2;
	t[x].l=t[x].r=0;
	return k;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%d",&n)!=EOF){
		memset(t,0,sizeof(t));
		for(int i=1;i<=n;i++){
			t[i].data=read();
			fa[i]=i;
		}
		int m=read();
		while(m--){
			int x=read(),y=read();
			x=Find(x);y=Find(y);
			if(x==y){
				printf("-1\n");
				continue;
			}
			int a=Delete(x);
			int b=Delete(y);
			int p=Merge(a,b);
			p=Merge(p,x);
			p=Merge(p,y);
			fa[x]=fa[y]=fa[p]=p;
			printf("%d\n",t[p].data);
		}
	}
	return 0;
}