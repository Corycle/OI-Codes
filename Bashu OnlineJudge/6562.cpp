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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<int,int>C[N],L[N];
int n,m1,m2,Ans=1,num,num1,num2;
int p1[N],p2[N],vis[N],vis1[N],vis2[N];
void DFS(int x){
	num++;
	vis[x]=1;
	if(p1[x]){
		if(!vis1[min(x,p1[x])]){vis1[min(x,p1[x])]=1;num1++;}
		if(!vis[p1[x]])DFS(p1[x]);
	}
	if(p2[x]){
		if(!vis2[min(x,p2[x])]){vis2[min(x,p2[x])]=1;num2++;}
		if(!vis[p2[x]])DFS(p2[x]);
	}
}
int main(){
//	freopen("mate.in","r",stdin);
//	freopen("mate.out","w",stdout);
	n=read();m1=read();m2=read();
	for(int i=1;i<=m1;i++){int x=read(),y=read();p1[x]=y;p1[y]=x;}
	for(int i=1;i<=m2;i++){int x=read(),y=read();p2[x]=y;p2[y]=x;}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			num=num1=num2=0;
			DFS(i);
			if(num==num1+num2){//Circle
				int ans=num;
				C[num1][num2]++;
				Ans=1ll*Ans*ans%Mod*C[num1][num2]%Mod;
			}
			else{//Line
				int ans=(num1==num2?1:2);
				L[num1][num2]++;
				Ans=1ll*Ans*ans%Mod*L[num1][num2]%Mod;
			}
		}
	}
	printf("%d",Ans);
	return 0;
}