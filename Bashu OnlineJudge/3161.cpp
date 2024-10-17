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
int n,h[100005],cnt,step,m,f[100005];
int l[100005],r[100005],c[200005];
struct edge{
	int to,next;
}d[200005];
void hqq_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs(int x){
	l[x]=++step;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(l[y])continue;
		dfs(y);
	}
	r[x]=++step;
}
int lowbit(int x){
	return (x&(-x));
}
void Add(int x,int y){
	for(int i=x;i<=step;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n-1;i++){
		int x=read(),y=read();
		hqq_add(x,y);
		hqq_add(y,x);
	}
	dfs(1);
	for(int i=1;i<=n;i++){
		f[i]=1;
		Add(l[i],1);//Add(r[i]+1,-1);
	}
	m=read();
	while(m--){
		char s[1];
		scanf("%s",s);
		int x=read();
		if(s[0]=='C'){
			f[x]=-f[x];
			Add(l[x],f[x]);//Add(r[x]+1,-f[x]);
		}
		if(s[0]=='Q')printf("%d\n",Ask(r[x])-Ask(l[x]-1));
	}
	return 0;
}