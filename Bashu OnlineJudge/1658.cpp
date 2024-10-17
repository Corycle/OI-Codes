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
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],sum[N],vis[N];
void DFS(int x){
	//x&sum[i-1]=x
	if(vis[x])return;vis[x]=1;
	for(int i=0;i<=19;i++){
		if(x&(1<<i))DFS(x-(1<<i));
	}
}
int Solve(int x){
	int ans=0;
	for(int i=19;i>=0;i--){
		if(x&(1<<i)){
			ans+=(1<<i);
			if(!vis[ans])ans-=(1<<i);
		}
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]^a[i];
	}
	for(int i=1;i<=n;i++){
		//sum[i]^sum[j-1]+sum[j-1]
		//ans1=sum[i] ans2=!sum[i]
		DFS(sum[i-1]);
		int ans1=0,ans2=0;
		for(int j=19;j>=0;j--){
			if(sum[i]&(1<<j))ans1+=(1<<j);
			else ans2+=(1<<j);
		}
		printf("%d ",Solve(ans2)*2+ans1);
	}
	return 0;
}