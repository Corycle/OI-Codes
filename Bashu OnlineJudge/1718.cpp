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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,S,C,Ans1,Ans2;
int a[N][N],vis[N][N];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
void Update(int x,int y){
	vis[x][y]=1;S++;
	for(int i=0;i<4;i++){
		int fx=x+dx[i],fy=y+dy[i];
		C+=a[x][y]-a[fx][fy];
	}
}
void Solve(int sx,int sy){
	queue<int>q1;q1.push(sx);
	queue<int>q2;q2.push(sy);
	S=C=0;Update(sx,sy);
	while(q1.size()){
		int x=q1.front();q1.pop();
		int y=q2.front();q2.pop();
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(a[fx][fy]&&!vis[fx][fy]){
				q1.push(fx);q2.push(fy);
				Update(fx,fy);
			}
		}
	}
	if(Ans1<S){Ans1=S;Ans2=C;}
	if(Ans1==S)Ans2=min(Ans2,C);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			a[i][j]=(s[j]=='#');
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]&&!vis[i][j]){
				Solve(i,j);
			}
		}
	}
	printf("%d %d",Ans1,Ans2);
	return 0;
}