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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,tot;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int a[N][N],id[N][N],ans[N];
void Deal(int x){
	int k=0;
	for(int i=x;i<=n;i++){
		if(a[i][x]){k=i;break;}
	}
	for(int i=x;i<=n+1;i++){
		swap(a[x][i],a[k][i]);
	}
	for(int i=1;i<=n;i++){
		if(i==x||!a[i][x])continue;
		for(int j=x;j<=n+1;j++){
			a[i][j]^=a[x][j];
		}
	}
}
void Gauss(){
	for(int i=1;i<=n;i++)Deal(i);
	for(int i=n;i>=1;i--){
		for(int j=n;j>i;j--)a[i][n+1]^=a[i][j]*ans[j];
		if(a[i][i]==0&&a[i][n+1]==1){
			printf("inf");
			exit(0);
		}
		ans[i]=a[i][n+1];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			id[i][j]=++tot;
			a[tot][tot]=1;
		}
	}
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			for(int k=0;k<4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(x<1||y<1||x>n||y>n)continue;
				a[id[i][j]][id[x][y]]=1;
			}
			a[id[i][j]][tot+1]=(s[j]=='w');
		}
	}
	n=tot;
	Gauss();
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i][n+1])ans++;
	}
	printf("%d",ans);
	return 0;
}