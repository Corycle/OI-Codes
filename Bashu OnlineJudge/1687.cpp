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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N];
int Min(){
	int Ans=inf;
	if(a[n-1]-a[1]==n-2&&a[n]-a[n-1]>2)return 2;
	if(a[n]-a[2]==n-2&&a[2]-a[1]>2)return 2;
	for(int i=1,j=1;i<=n;i++){
		while(j<n&&a[j+1]-a[i]<=n-1)j++;
		Ans=min(Ans,n-(j-i+1));
	}
	return Ans;
}
int Max(){
	return max(a[n-1]-a[1],a[n]-a[2])-(n-2);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	printf("%d\n%d",Min(),Max());
	return 0;
}