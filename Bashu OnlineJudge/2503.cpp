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
const int Mod=10000;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,t,cnt;
int d[N],prime[N],vis[N],num[N],ans[N*100];
void Prepare(){
	for(int i=2;i<=1000;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&prime[j]*i<=1000;j++){
			vis[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}
void Update(int x,int addv){
	for(int i=1;i<=cnt&&prime[i]<=x;i++){
		int s=prime[i];
		while(s<=x){
			num[i]+=(x/s)*addv;
			s*=prime[i];
		}
	}
}
void Multi(int a[],int b){
	for(int i=1;i<=a[0];i++)a[i]*=b;
	for(int i=1;i<=a[0];i++){
		a[i+1]+=a[i]/Mod;
		a[i]%=Mod;
	}
	while(a[a[0]+1]){
		a[0]++;
		a[a[0]+1]=a[a[0]]/Mod;
		a[a[0]]%=Mod;
	}
}
void Print(int a[]){
	printf("%d",a[a[0]]);
	for(int i=a[0]-1;i>=1;i--){
		printf("%04d",a[i]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1;i<=n;i++){
		d[i]=read();
		if(!d[i]&&n!=1){
			printf("0");
			return 0;
		}
		d[i]--;t+=d[i];
	}
	if(n==1&&!t){printf("0");return 0;}
	if(t!=n-2){printf("0");return 0;}
	if(n==1){printf("1");return 0;}
	Update(n-2,1);
	for(int i=1;i<=n;i++){
		if(d[i])Update(d[i],-1);
	}
	ans[0]=ans[1]=1;
	for(int i=1;i<=cnt;i++){
		if(num[i]<0){printf("0");return 0;}
		for(int j=1;j<=num[i];j++){
			Multi(ans,prime[i]);
		}
	}
	Print(ans);
	return 0;
}