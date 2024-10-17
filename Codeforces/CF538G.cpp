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
#define ld long double
using namespace std;
const ll inf=4e18;
const int N=2e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char ans[N];
ll MinX,MaxX,MinY,MaxY;
struct Node{ll x,y,t,K,W;}P[N];
bool cmp(Node A,Node B){return A.W<B.W;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","W",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		P[i].t=read();
		ll x=read(),y=read();
		P[i].x=(x+y+P[i].t)/2;
		P[i].y=(y-x+P[i].t)/2;
		P[i].K=P[i].t/m;
		P[i].W=P[i].t%m;
		if((x+y+P[i].t)%2){puts("NO");return 0;}
	}
	P[++n]=(Node){0,0,0,-1,m};
	sort(P+1,P+n+1,cmp);
	MinX=MinY=-inf;MaxX=MaxY=inf;
	for(int i=1;i<=n;i++){
		ll K=P[i].K-P[i-1].K,W=P[i].W-P[i-1].W;
		ll X=P[i].x-P[i-1].x,Y=P[i].y-P[i-1].y;
		if(!K){
			if(P[i].x-P[i-1].x-W>0||P[i].x-P[i-1].x<0){puts("NO");return 0;}
			if(P[i].y-P[i-1].y-W>0||P[i].y-P[i-1].y<0){puts("NO");return 0;}
		}
		if(K>0){
			MinX=max(MinX,(ll)(ceil((ld)(X-W)/K)));
			MinY=max(MinY,(ll)(ceil((ld)(Y-W)/K)));
			MaxX=min(MaxX,(ll)(floor((ld)(X)/K)));
			MaxY=min(MaxY,(ll)(floor((ld)(Y)/K)));
		}
		if(K<0){
			K*=-1;
			MinX=max(MinX,(ll)(ceil((ld)(-X)/K)));
			MinY=max(MinY,(ll)(ceil((ld)(-Y)/K)));
			MaxX=min(MaxX,(ll)(floor((ld)(-X+W)/K)));
			MaxY=min(MaxY,(ll)(floor((ld)(-Y+W)/K)));
		}
	}
	if(MinX>MaxX||MinY>MaxY){puts("NO");return 0;}
	ll x=0,y=0,p=1;
	for(int i=1;i<=n;i++){
		ll dx=P[i].x-P[i].K*MinX;
		ll dy=P[i].y-P[i].K*MinY;
		for(;p<=P[i].W;p++){
			if(x<dx){
				x++;
				if(y<dy){ans[p]='U';y++;}
				else ans[p]='R';
			}
			else{
				if(y<dy){ans[p]='L';y++;}
				else ans[p]='D';
			}
		}
	}
	printf("%s",ans+1);
	return 0;
}
