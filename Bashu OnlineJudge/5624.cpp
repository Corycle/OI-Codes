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
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[N],f[N][N];
double Slope(int x,int y){
	if(x==y)return inf;
	return (double)(a[x]-a[y])/(x-y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int r=1;r<=n;r++){
		f[r][r]=1;
		int lst=r,sum=1;
		for(int l=r-1;l>=1;l--){
			if(Slope(l,r)<Slope(lst,r)){
				sum+=min(f[l+1][lst],f[l+1][lst-1]);
				lst=l;
			}
			f[l][r]=sum+min(f[l][lst],f[l][lst-1]);
		}
	}
	for(int l=1;l<=n;l++){
		for(int r=l;r<=n;r++)Ans^=f[l][r];
	}
	printf("%d",Ans);
	return 0;
}