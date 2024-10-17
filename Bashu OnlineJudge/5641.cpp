#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
const int N=200005;
const int M=100000;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>V[N];
int n,m,tot,Max1,Max2,c[N];
struct Node{int pos,t;}p[N];
struct Ques{int type,x,y;}q[N];
int lowbit(int x){return x&(-x);}
void Add(int x,int y){
	for(int i=x+M;i<=2e5;i+=lowbit(i))c[i]+=y;
}
int Ask(int x){
	int ans=0;
	for(int i=x+M;i>=1;i-=lowbit(i))ans+=c[i];
	return ans;
}
int main(){
//	freopen("flea.in","r",stdin);
//	freopen("flea.out","w",stdout);
	int Q=read();
	for(int i=1;i<=Q;i++){
		q[i].type=read();
		if(q[i].type!=2){
			q[i].x=read();
			q[i].y=read();
		}
		if(q[i].type==3)Max1=max(Max1,q[i].y);
		if(q[i].type==1)Max2=max(Max2,q[i].y);
	}
	if(Max1<=100){//Subtask2 23 Points
		for(int i=1;i<=Q;i++){
			if(q[i].type==1)if(q[i].x<=Max1)V[q[i].x].push_back(q[i].y);
			if(q[i].type==2){
				for(int j=Max1;j>=1;j--){
					for(int k=0;k<V[j].size();k++){
						int pos=j+V[j][k];
						if(pos<=Max1){
							V[pos].push_back(V[j][k]);
						}
					}
					V[j].clear();
				}
			}
			if(q[i].type==3){
				int ans=0;
				for(int j=q[i].x;j<=q[i].y;j++){
					ans+=V[j].size();
				}
				printf("%d\n",ans);
			}
		}
		return 0;
	}
	if(Max2==1){//Subtask3 13 Points
		int dlt=0;
		for(int i=1;i<=Q;i++){
			if(q[i].type==1)Add(q[i].x-dlt,1);
			if(q[i].type==2)dlt++;
			if(q[i].type==3)printf("%d\n",Ask(q[i].y-dlt)-Ask(q[i].x-dlt-1));
		}
		return 0;
	}
	/*==========这个是裸暴力==========*/
	for(int i=1;i<=Q;i++){
		if(q[i].type==1)p[++tot]=(Node){q[i].x,q[i].y};
		if(q[i].type==2)for(int j=1;j<=tot;j++)p[j].pos+=p[j].t;
		if(q[i].type==3){
			int ans=0;
			for(int j=1;j<=tot;j++){
				if(q[i].x<=p[j].pos&&p[j].pos<=q[i].y)ans++;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}