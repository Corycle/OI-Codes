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
#include<bitset>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N];
bitset<N>f,g;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	if(a[1]!=a[2]){printf("%d",a[1]);return 0;}
	n=unique(a+1,a+n+1)-a-1;
	f[0]=1;
	for(int i=a[n],j=n;i>=1;i--){
		if(a[j]==i){
			f[i]=1;
			for(int k=i;k<=a[n];k+=i)g[k]=1;
			j--;
		}
		else if(((f>>i)&g).any())f[i]=1;
	}
	for(int i=a[1]-1;i>=0;i--){
		if(f[i]){printf("%d",i);return 0;}
	}
	return 0;
}