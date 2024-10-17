/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=270005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,Max;
int a[N],fa[N],vis[N],Ans[N],tag[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Solve1(){
	int lst=n;
	for(int i=n;i>=1;i--){
		int flag=0;
		for(int j=1;j<=512;j++){
			if(j*j<a[i])continue;
			if(j*j-a[i]>Max)break;
			if(vis[j*j-a[i]]){flag=1;break;}
		}
		if(flag){
			Ans[++Ans[0]]=i;
			for(int j=i+1;j<=lst;j++)vis[a[j]]=0;
			lst=i;
		}
		vis[a[i]]=1;
	}
}
void Solve2(){
	int lst=n;
	for(int i=1;i<=Max*2;i++)fa[i]=i;
	for(int i=1;i*i<=Max*2;i++)tag[i*i]=1;
	for(int i=n;i>=1;i--){
		int flag=0;
		if(vis[a[i]]){
			if(tag[a[i]*2]){
				for(int j=1;j<=512;j++){
					if(j*j<a[i])continue;if(j*j-a[i]>Max)break;
					if(vis[a[i]]==2||fa[a[i]+Max]!=a[i]+Max){flag=1;break;}
					if(vis[j*j-a[i]]&&j*j-a[i]!=a[i]){flag=1;break;}
				}
			}
		}
		else{
			for(int j=1;j<=512;j++){
				if(j*j<a[i])continue;if(j*j-a[i]>Max)break;
				if(vis[j*j-a[i]]){
					if(tag[2*(j*j-a[i])]&&vis[j*j-a[i]]==2){flag=1;break;}
					int x=a[i],y=j*j-a[i];
					int sx=Find(x),tx=Find(x+Max);
					int sy=Find(y),ty=Find(y+Max);
					if(sx!=sy){fa[ty]=sx;fa[tx]=sy;}
					else{flag=1;break;}
				}
			}
		}
		if(flag){
			Ans[++Ans[0]]=i;
			for(int j=i;j<=lst;j++){
				fa[a[j]]=a[j];
				fa[a[j]+Max]=a[j]+Max;
				vis[a[j]]=0;
			}
			lst=i;
		}
		vis[a[i]]++;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		Max=max(Max,a[i]);
	}
	if(K==1)Solve1();
	if(K==2)Solve2();
	printf("%d\n",Ans[0]+1);
	for(int i=Ans[0];i>=1;i--){
		printf("%d ",Ans[i]);
	}
	return 0;
}