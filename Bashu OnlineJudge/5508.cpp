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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],b[N],f[N][N];
bool Check(int p){
	memset(f,-1,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(f[i-1][j]==-1)continue;
			for(int k=0;k<=p/a[i];k++){
				int l=(p-a[i]*k)/b[i];
				int x=min(j+k,m);
				int y=min(f[i-1][j]+l,m);
				f[i][x]=max(f[i][x],y);
			}
		}
		if(f[i][m]==m)return true;
	}
	return false;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
	}
	int l=1,r=1e7,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}