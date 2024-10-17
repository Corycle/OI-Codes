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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int prime[N],mu[N],vis[N],cnt,sum[N]; 
void Prepare(){
	mu[1]=sum[1]=1;
	for(int i=2;i<=50000;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt;j++){
			if(i*prime[j]>50000)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else mu[i*prime[j]]=-mu[i];
		}
		sum[i]=sum[i-1]+mu[i];
	}
}
int Ask(int n,int m,int i){
	int lst=0,ans=0;
//	for(int k=1;k<=min(n/i,m/i);k++){
//		ans+=mu[k]*(n/(i*k))*(m/(k*i));
//	}
	n/=i;m/=i;
	if(n>m)swap(n,m);
	for(int k=1;k<=n;k=lst+1){
		lst=min(n/(n/k),m/(m/k));
		ans+=(n/k)*(m/k)*(sum[lst]-sum[k-1]);
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	Prepare();
	while(T--){
		int a=read(),b=read(),c=read(),d=read(),k=read();
		int ans=Ask(b,d,k)+Ask(a-1,c-1,k)-Ask(a-1,d,k)-Ask(b,c-1,k);
		printf("%d\n",ans);
	} 
	return 0;
}