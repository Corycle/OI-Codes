#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
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
int n,ans,a[N],f[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int Max=0;
		a[i]=read();
		for(int j=1;j<=100;j++){
			if(f[j]&&i%j==0)Max=max(Max,f[j]);
		}
		f[a[i]]=max(f[a[i]],Max+1);
		ans=max(ans,f[a[i]]);
	}
	printf("%d",ans);
	return 0;
}