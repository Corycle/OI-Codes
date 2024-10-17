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
const int Mod=1e9+7;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,num,Ans;
struct Node{
	int x,y;
	friend bool operator<(Node A,Node B){
		return A.x!=B.x?A.x<B.x:A.y<B.y;
	}
}a[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=K;i++){
		a[i].x=read();
		a[i].y=read();
	}
	Ans=1;
	sort(a+1,a+K+1);
	int p=1ll*(1+n)*n/2%Mod;
	for(int i=1;i<=K;i++){
		int j=i,sum=0;num++;
		while(a[j+1].x==a[i].x)j++;
		for(int k=i;k<=j;k++){
			if(a[k].x!=a[k-1].x||a[k].y!=a[k-1].y)sum+=a[k].y;
		}
		Ans=1ll*Ans*(p-sum+Mod)%Mod;
		i=j;
	}
	Ans=1ll*Ans*Pow(p,m-num)%Mod;
	printf("%d",Ans);
	return 0;
}