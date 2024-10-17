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
int n,fa[N],d[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
struct tree{
	int data,l,r;
}t[N];
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(t[x].data>t[y].data)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	swap(t[x].l,t[x].r);
	return x;
}
void Delete(int x){
	d[x]=1;
	printf("%d\n",t[x].data);
	fa[x]=Merge(t[x].l,t[x].r);
	fa[fa[x]]=fa[x];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
		t[i].data=read();
	}
	int m=read();
	while(m--){
		char s[1];
		scanf("%s",s);
		if(s[0]=='M'){
			int x=read(),y=read();
			if(d[x]||d[y])continue;
			x=Find(x);y=Find(y);
			if(x==y)continue;
			fa[x]=fa[y]=Merge(x,y);
		}
		if(s[0]=='K'){
			int x=read();
			if(d[x]){
				printf("0\n");
				continue;
			}
			Delete(Find(x));
		}
	}
	return 0;
}