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
int n,Ans,a[N];
int Solve(int x){
	int ans=0;
	for(int i=1;i<=n;i++)ans+=(a[i]-x)*(a[i]-x);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=inf;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=-100;i<=100;i++)Ans=min(Ans,Solve(i));
	printf("%d\n",Ans);
	return 0;
}
