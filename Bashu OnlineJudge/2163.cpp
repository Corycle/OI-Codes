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
#define inf 1044266559
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,f[105][105],sum[105];
struct tree{
	int l,r;
}t[1005];
void init(int x){
	int i,j,k;
	if(t[x].l)init(t[x].l);
	if(t[x].r)init(t[x].r);
	sum[x]+=sum[t[x].l]+sum[t[x].r];
}
void bfs(int x,int y){
	int i,j,k;
	if(f[x][y]!=-inf)return;
	if(t[x].l&&!t[x].r){
		bfs(t[x].l,y-1);
		if(f[t[x].l][y-1]!=-inf)f[x][y]=max(f[x][y],f[t[x].l][y-1]+f[x][1]);
	}
	if(!t[x].l&&t[x].r){
		bfs(t[x].r,y-1);
		if(f[t[x].r][y-1]!=-inf)f[x][y]=max(f[x][y],f[t[x].r][y-1]+f[x][1]);
	}
	if(t[x].l&&t[x].r){
		for(i=0;i<y;i++){
			if(sum[t[x].l]<i||sum[t[x].r]<y-i-1)continue;
			bfs(t[x].l,i);
			bfs(t[x].r,y-1-i);
			if(f[t[x].l][i]!=-inf&&f[t[x].r][y-1-i]!=-inf){
				f[x][y]=max(f[x][y],f[t[x].l][i]+f[t[x].r][y-1-i]+f[x][1]);
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	memset(f,-0x3f,sizeof(f));
	n=read();m=read();
	for(i=2;i<=n;i++)f[i][1]=read();
	for(i=1;i<=n;i++){
		f[i][0]=0;sum[i]=1;
		t[i].l=read();
		t[i].r=read();
	}
	f[1][1]=0;
	init(1);
	bfs(1,m+1);
	printf("%d",f[1][m+1]);
	return 0;
}