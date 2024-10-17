#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,phi[N],vis[N],prime[N];
void Prepare(){
	phi[1]=1;
	for(int i=2;i<=1e6;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&i*prime[j]<=1e6;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=phi[i]*phi[prime[j]];
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare();
	while(scanf("%d",&n)!=EOF){
		printf("%d\n",phi[n-1]);
	}
	return 0;
}