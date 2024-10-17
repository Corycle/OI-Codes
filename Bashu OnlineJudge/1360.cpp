#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,L,R,ans,a[N],q[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=a[i+n]=read();
		ans=max(ans,a[i]);
	}
	for(int i=1;i<=n*2;i++){
		while(L<=R&&i-q[L]>n/2)L++;
		if(L<=R)ans=max(ans,i-q[L]+a[q[L]]+a[i]);
		while(L<=R&&a[i]-i>=a[q[R]]-q[R])R--;
		q[++R]=i;
	}
	printf("%d",ans);
	return 0;
}