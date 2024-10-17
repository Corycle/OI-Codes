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
int n,sum,flag;
int a[N][N],ans[N],vis[N];
void DFS(int x,int num){
	if(num>=sum)return;
	if(x==0){sum=num;return;}
	if(a[x][x]){//不是自由元
		int v=a[x][n+1];
		for(int i=x+1;i<=n;++i){
			if(a[x][i])v^=vis[i];
		}
		DFS(x-1,num+v);
	}
	else{
		DFS(x-1,num);vis[x]=1;
		DFS(x-1,num+1);vis[x]=0;
	}
}
void Deal(int x){
	int k=0;
	for(int i=x;i<=n;i++){
		if(a[i][x]){k=i;break;}
	}
	if(!k){flag=1;return;}
	swap(a[x],a[k]);
	for(int i=1;i<=n;i++){
		if(i==x||!a[i][x])continue;
		for(int j=x;j<=n+1;j++){
			a[i][j]^=a[x][j];
		}
	}
}
void Gauss(){
	for(int i=1;i<=n;i++)Deal(i);
	if(flag){
		sum=inf;
		DFS(n,0);
	}
	else{
		for(int i=1;i<=n;i++){
			sum+=a[i][n+1];
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=20;
	for(int i=1;i<=n;i++){
		a[i][i]=1;
		if(i!=1)a[i][i-1]=1;
		if(i!=n)a[i][i+1]=1;
		a[i][n+1]=read();
	}
	Gauss();
	printf("%d",sum);
	return 0;
}