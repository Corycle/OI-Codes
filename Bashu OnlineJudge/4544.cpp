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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,sum,flag;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int a[N][N],v[N],ans[N];
void Deal(int x){
	int k=0;
	for(int i=x;i<=n;i++){
		if(a[i][x]){k=i;break;}
	}
	if(!k)return;
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
	//神  仙
	for(int i=1;i<=n;i++){
		int j=1;
		while(!a[i][j]&&j<=n+1)j++;
		if(j>n+1)sum++;
		else if(j==n+1)flag=1;
	}
	if(flag)return;
	//保  佑 
//	for(int i=n;i>=1;i--){
//		for(int j=n;j>i;j--)a[i][n+1]^=a[i][j]*ans[j];
//		if(a[i][i]==0&&a[i][n+1]==1){flag=1;return;}
//		ans[i]=a[i][n+1];
//	}
}
void Init(){
	flag=sum=0;
	memset(a,0,sizeof(a));
	memset(ans,0,sizeof(ans));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		Init();
		n=read();
		for(int i=1;i<=n;i++)v[i]=read();
		for(int i=1;i<=n;i++){
			a[i][i]=1;
			if(v[i]!=read())a[i][n+1]=1;
		}
		while(1){
			int x=read(),y=read();
			if(x+y==0)break;
			a[y][x]=1;
		}
		Gauss();
		if(!flag)printf("%d\n",1<<sum);
		else printf("Oh,it's impossible~!!\n");
	}
	return 0;
}
