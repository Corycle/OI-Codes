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
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Answer;
int f[N],h[N],num[N],tmp[N];
struct edge{int to,next;}d[N];
bool cmp(int x,int y){return f[x]<f[y];}
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x){
	int tot=0;
	for(int i=h[x];i;i=d[i].next)DFS(d[i].to);
	for(int i=h[x];i;i=d[i].next)tmp[++tot]=d[i].to;
	sort(tmp+1,tmp+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		int y=tmp[i];
		if(f[x]+f[y]-1<=m){
			f[x]+=f[y]-1;
			Answer++;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=read();
	for(int i=1;i<=n;i++){
		int num=read();f[i]+=num;
		while(num--)Add(i,read()+1);
	}
	DFS(1);
	printf("%d",Answer);
	return 0;
}