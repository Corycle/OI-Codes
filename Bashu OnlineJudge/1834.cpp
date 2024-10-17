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
int n;
int a[N],c[N];
int lowbit(int x){return x&(-x);}
int Add(int x){for(int i=x;i<=n;i+=lowbit(i))c[i]++;}
int Ask(int x){int ans=0;for(int i=x;i>=1;i-=lowbit(i))ans+=c[i];return ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();a[n+1]=inf;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i>=1;i--){
		if(a[i]>a[i+1]){
			printf("%d\n",i);
			for(int j=1;j<=i;j++){
				printf("%d ",Ask(a[j])+(i-j));
				Add(a[j]);
			}
			return 0;
		}
		Add(a[i]);
	}
	return 0;
}