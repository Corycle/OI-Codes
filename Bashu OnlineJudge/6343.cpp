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
const int N=10005;
const int M=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K;
int a[N],b[N],f[N][M];
bool Check(int l,int r,int mid){
	if(mid==r)return f[l][m]<=K;
	if(mid<l) return f[r][m]<=K;
	for(int i=0;i<=m;i++){
		if(f[l][i]+f[r][m-i]<=K)return true;
	}
	return false;
}
void Rebuild(int l,int r){
	for(int i=0;i<=m;i++)f[r][i]=inf;
	f[r][0]=0;f[r][a[r]]=b[r];
	for(int i=r-1;i>=l;i--){
		for(int j=0;j<=a[i];j++)f[i][j]=f[i+1][j];
		for(int j=a[i];j<=m;j++){
			f[i][j]=min(f[i+1][j],f[i+1][j-a[i]]+b[i]);
		}
	}
}
void Update(int i,int mid){
	if(i>n)return;
	if(i==mid+1){f[i][0]=0;f[i][a[i]]=b[i];}
	else{
		for(int j=0;j<=a[i];j++)f[i][j]=f[i-1][j];
		for(int j=a[i];j<=m;j++){
			f[i][j]=min(f[i-1][j],f[i-1][j-a[i]]+b[i]);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
	}
//	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			f[i][j]=inf;
		}
	}
	int l=1,r=0,mid=0,Ans=inf;
	while(r<=n){
		if(Check(l,r,mid)){
			Ans=min(Ans,r-l+1);
			if(l<=mid)l++;
			else Rebuild(++l,mid=r);
		}
		else Update(++r,mid);
	}
	printf("%d",Ans==inf?-1:Ans);
	return 0;
}