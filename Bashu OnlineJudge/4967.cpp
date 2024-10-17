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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int h[N],deg[N],f[N][4];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
/*
	0.是要包含 x 的半条链 
	1.是不包含 x 的完整的链 
	2.是要包含 x 的完整的链 
	3.是要包含 x 的半条链 和 一条完整的链 
*/
void DFS(int x,int fa){
	f[x][1]=1;
	f[x][0]=deg[x];
	f[x][2]=deg[x];
	f[x][3]=deg[x];
	int tmp=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;DFS(y,x);
		Ans=max(Ans,f[x][1]+f[y][2]);
		Ans=max(Ans,f[x][1]+f[y][1]-1);
		Ans=max(Ans,f[x][0]+f[y][3]-1+(x!=1));
		Ans=max(Ans,f[x][2]+f[y][2]-1+(x!=1));
		Ans=max(Ans,f[x][2]+f[y][1]-1+(x!=1));
		Ans=max(Ans,f[x][3]+f[y][0]-1+(x!=1));
		
		f[x][3]=max(f[x][3],f[y][3]+deg[x]-1);
		f[x][3]=max(f[x][3],f[x][0]+f[y][1]-1);
		f[x][3]=max(f[x][3],f[x][0]+f[y][2]-1);
		f[x][3]=max(f[x][3],f[x][2]+f[y][0]-1);
		f[x][3]=max(f[x][3],f[y][0]+deg[x]+tmp-2);
		
		f[x][1]=max(f[x][1],f[y][1]);
		f[x][1]=max(f[x][1],f[y][2]+1);
		f[x][2]=max(f[x][2],f[y][0]+f[x][0]-1);
		
		f[x][0]=max(f[x][0],f[y][0]+deg[x]-1);
		f[x][2]=max(f[x][2],f[x][0]);
		f[x][3]=max(f[x][3],f[x][2]);
		
		tmp=max(tmp,max(f[y][1],f[y][2]));
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read(),type=read();
	while(T--){
		n=read();cnt=0;Ans=0;
		if(type>=1){read();read();}
		if(type>=2){read();read();}
		for(int i=1;i<=n;i++){
			for(int j=0;j<=3;j++)f[i][j]=0;
			h[i]=0;deg[i]=0;
		}
		for(int i=1;i<n;i++){
			int x=read(),y=read();
			Add(x,y);Add(y,x);
			deg[x]++;deg[y]++;
		}
		for(int i=2;i<=n;i++)deg[i]--;
		DFS(1,0);
		printf("%d\n",Ans);
	}
	return 0;
}