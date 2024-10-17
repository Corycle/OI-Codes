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
const int M=1005;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,K,tot,m=10;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int fa[M],sum[M],a[N][N],id[N][N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Delete(int sx,int sy){
	queue<int>q1,q2;
	q1.push(sx);q2.push(sy);
	int type=a[sx][sy];a[sx][sy]=0;
	while(q1.size()){
		int x=q1.front();q1.pop();
		int y=q2.front();q2.pop();
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(a[fx][fy]==type){
				a[fx][fy]=0;
				q1.push(fx);q2.push(fy);
			}
		}
	}
}
void Down(){
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++){
			if(a[i][j]==0){
				for(int k=i;k>=1;k--){
					if(a[k][j]){
						swap(a[i][j],a[k][j]);
						break;
					}
				}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			id[i][j]=++tot;
			a[i][j]=s[j]-'0';
		}
	}
	while(1){
		int num=0;
		for(int i=1;i<=tot;i++){fa[i]=i;sum[i]=1;}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int k=0;k<4;k++){
					int x=i+dx[k],y=j+dy[k];
					if(a[i][j]&&a[x][y]&&a[i][j]==a[x][y]){
						int fx=Find(id[i][j]);
						int fy=Find(id[x][y]);
						if(fx==fy)continue;
						fa[fx]=fy;sum[fy]+=sum[fx];
					}
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int k=id[i][j];
				if(k==fa[k]&&sum[k]>=K){
					Delete(i,j);num++;
				}
			}
		}
		if(!num)break;
		Down();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}