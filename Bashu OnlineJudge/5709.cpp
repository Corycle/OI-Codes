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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Ans,tmp,rd[N],cd[N],a[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=n*(n-1)*(n-2)/6;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(j<=(i+(n-1)/2)){
				rd[j]++;cd[i]++;a[i][j]=1;
			}
			else{
				rd[i]++;cd[j]++;a[j][i]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)tmp+=(cd[i]-1)*cd[i]/2;
	for(int i=1;i<=n;i++)tmp+=(rd[i]-1)*rd[i]/2;
	printf("%lld\n",Ans-tmp/2);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%lld ",a[i][j]);
		}
		puts("");
	}
	return 0;
}