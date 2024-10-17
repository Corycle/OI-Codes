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
const int N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll T;
int n,K,a[N],b[N],p[N],vis[N];
int gcd(int x,int y){
	return y==0?x:gcd(y,x%y);
}
int mod(int x){return x>=n?x-n:x;}
void Solve(int x){
	if(!x)return;
	int len1=n/gcd(x,n);//环长 
	int len2=K%(2*len1);//走两圈就抵消了，这是剩下的 
	for(int i=0;i<n;i++){b[i]=a[i];vis[i]=0;}
	for(int i=0;i<n;i++){
		if(vis[i])continue;
		int tot=0,sum=0;
		for(int j=i;!vis[j];j=mod(j+x)){p[++tot]=j;vis[j]=1;}//找到整个环 
		int pos=p[tot]; 
		for(int j=0;j<len2;j++){sum^=b[pos];pos=mod(pos+x);}
		a[p[tot]]=sum;
		for(int j=tot-1;j>=1;j--){
			pos=mod(pos-x+n);
			sum^=b[pos]^b[p[j]];
			a[p[j]]=sum;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();T=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(ll i=1;i<=T;i<<=1)if(T&i)Solve(i%n);
	for(int i=0;i<n;i++)printf("%d ",a[i]);
	return 0;
}