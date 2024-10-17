/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bitset<N>F[2];
int n,Ans,a[N],b[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
	}
	int t=0;F[t][0]=1;
	for(int i=1;i<=n;i++){
		t^=1;F[t].reset();
		for(int j=a[i];j<=b[i];j++){
			F[t]|=(F[t^1]<<(j*j));
		}
	}
	for(int i=0;i<N;i++)Ans+=F[t][i];
	printf("%d",Ans);
	return 0;
}