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
const int M=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],sta[M],Ans[2];
int f1[2][M][M],f2[2][M][M];
int tot[2],b[2][M],sum[2][M];
int vis1[2][2][M][M],vis2[2][2][M][M];
bool Check(int x,int y){return ((x&y)==y);}
bool Check1(int x,int y){
	for(int k=2;k<=m;k++){
		if(Check(x,sta[k])&&Check(y,sta[k-1]))return false;
		if(Check(x,sta[k-1])&&Check(y,sta[k]))return false;
	}
	return true;
}
bool Check2(int x,int y){
	for(int k=1;k<=m;k++){
		if(Check(x,sta[k])&&Check(y,sta[k]))return false;
	}
	return true;
}
void DFS(int x,int lst,int t,int Sum){
	if(x>m){b[t][++tot[t]]=Sum;return;}
	if(!lst)
	DFS(x+2,1,t,Sum|sta[x]);
	DFS(x+2,0,t,Sum);
}
void Prepare(){
	memset(a,0,sizeof(a));
	memset(f1,0,sizeof(f1));
	memset(f2,0,sizeof(f2));
	memset(sum,0,sizeof(sum));
	tot[0]=0;DFS(1,0,0,0);
	tot[1]=0;DFS(2,0,1,0);
	for(int t=0;t<=1;t++){
		sort(b[t]+1,b[t]+tot[t]+1);
		for(int i=1;i<=tot[t];i++){
			for(int j=1;j<=m;j++){
				if(Check(b[t][i],sta[j]))sum[t][i]++;
			}
		}
	}
	for(int t1=0;t1<=1;t1++)
	for(int t2=0;t2<=1;t2++)
	for(int i=1;i<=tot[t1];i++)
	for(int j=1;j<=tot[t2];j++){
		vis1[t1][t2][i][j]=vis1[t2][t1][j][i]=Check1(b[t1][i],b[t2][j]);
		vis2[t1][t2][i][j]=vis2[t2][t1][j][i]=Check2(b[t1][i],b[t2][j]);
	}
}
void Solve(){
	for(int t=0;t<=1;t++){
		for(int i=1;i<=tot[t];i++){
			if(Check(a[1],b[t][i])){
				f2[t][i][1]=sum[t][i];
			}
		}
	}
	for(int p=2;p<=n;p++){
		for(int t=0;t<=1;t++){
			for(int i=1;i<=tot[t];i++)
			for(int k=1;k<=tot[t];k++)
			for(int j=1;j<=tot[t^1];j++){
				if(!vis2[t][t][i][k])continue;
				if(!vis1[t][t^1][i][j])continue;
				if(!vis1[t][t^1][k][j])continue;
				if(!Check(a[p],b[t][i]))continue;
				if(!Check(a[p-2],b[t][k]))continue;
				if(!Check(a[p-1],b[t^1][j]))continue;
				f1[t][i][j]=max(f1[t][i][j],f2[t^1][j][k]+sum[t][i]);
			}
		}
		for(int t=0;t<=1;t++){
			for(int i=1;i<=tot[t];i++){
				for(int j=1;j<=tot[t^1];j++){
					f2[t][i][j]=f1[t][i][j];
					f1[t][i][j]=0;
				}
			}
		}
	}
}
int main(){
//	freopen("petal.in","r",stdin);
//	freopen("petal.out","w",stdout);
	for(int i=1;i<=10;i++)sta[i]=(1<<(i-1));
	while(scanf("%d%d",&n,&m)!=EOF){
		Prepare();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				a[i]|=read()*sta[j];
			}
		}
		Solve();
		Ans[0]=Ans[1]=0;
		for(int t=0;t<=1;t++)
		for(int i=1;i<=tot[t];i++)
		for(int j=1;j<=tot[t^1];j++){
			Ans[t]=max(Ans[t],f2[t][i][j]);
		}
		printf("%d\n",Ans[0]+Ans[1]);
	}
	return 0;
}