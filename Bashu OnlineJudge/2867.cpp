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
int n,m,sum;
int a[N][N],b[N][N];
bool Check(int x,int y){
	if(sum%(x*y))return false;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[i][j]=a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int dlt=b[i][j];
			if(!dlt)continue;
			for(int k=1;k<=x;k++){
				for(int l=1;l<=y;l++){
					b[i+k-1][j+l-1]-=dlt;
					if(b[i+k-1][j+l-1]<0)return false;
				}
			}
		}
	}
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			sum+=a[i][j];
		}
	}
	int ans=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(Check(i,j)){
				ans=min(ans,sum/(i*j));
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}