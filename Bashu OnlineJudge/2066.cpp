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
const int M=10005;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[M],f[N][M];
bool cmp(int x,int y){return x>y;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=m;i++)a[i]=read();
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++)a[i]+=a[i-1];
	memset(f,-0x3f,sizeof(f));f[0][0]=0;
	for(int i=1;i<=n;i++){
		int num=read(),val=read();
		for(int j=0;j<=m;j++)f[i][j]=f[i-1][j];
		for(int j=0;j<=m;j++){
			int k=min(m,j+num);
			f[i][k]=max(f[i][k],f[i-1][j]+a[k]-a[j]-val);
			Ans=max(Ans,f[i][k]);
		}
	}
	printf("%d",Ans);
	return 0;
}