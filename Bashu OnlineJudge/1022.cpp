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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
int f[N],vis[N],prime[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	f[0]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt;j++){
			if(i*prime[j]>n)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	f[0]=1;
	for(int j=1;j<=cnt;j++){
		for(int i=prime[j];i<=n;i++){
			f[i]+=f[i-prime[j]];
		}
	}
	printf("%d",f[n]);
	return 0;
}