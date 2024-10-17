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
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fa[N];
struct Node{int l,r;}P[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool Cross(Node A,Node B){
	if(A.l<B.l&&B.l<A.r&&A.r<B.r)return true;
	if(B.l<A.l&&A.l<B.r&&B.r<A.r)return true;
	return false;
}
int main(){
//	freopen("angelus.in","r",stdin);
//	freopen("angelus.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		for(int i=1;i<=m*2;i++)fa[i]=i;
		for(int i=1;i<=m;i++){
			P[i].l=read();P[i].r=read();
			if(P[i].l>P[i].r)swap(P[i].l,P[i].r);
		}
		for(int i=1;i<=m;i++){
			for(int j=i+1;j<=m;j++){
				if(Cross(P[i],P[j])){
					fa[Find(i)]=fa[Find(j+m)];
					fa[Find(i+m)]=fa[Find(j)];
				}
			}
		}
		int flag=1;
		for(int i=1;i<=m;i++){
			if(Find(i)==Find(i+m)){
				flag=0;break;
			}
		}
		if(flag)printf("sane\n");
		else printf("non\n");
	}
	return 0;
}