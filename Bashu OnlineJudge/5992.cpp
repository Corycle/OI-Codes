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
const int N=1e6+5;
const int M=31;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],op[N],p1[N],p2[N],Ans[N];
struct Node{int l,L,R,id;};
vector<Node>F[N];
int Calc(int k,int pos,int v){
	if(p1[k]<pos&&p2[k]<pos)return v<<k;
	return (p1[k]>p2[k]?0:1)<<k;
}
int Solve1(int k,int pos,int x,int L){
	int ans=0;
	for(;k>=0;k--)ans+=Calc(k,pos,1);
	return ans;
}
int Solve2(int k,int pos,int x,int R){
	int ans=0;
	for(;k>=0;k--){
		int v0=Calc(k,pos,0),v1=Calc(k,pos,1);
		if(v0<v1&&x+(1<<k)<=R){x+=(1<<k);ans+=v1;}
		else ans+=v0;
	}
	return ans;
}
int main(){
//	freopen("easy.in","r",stdin);
//	freopen("easy.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){op[i]=read();a[i]=read();}
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),L=read(),R=read();
		F[r].push_back((Node){l,L,R,i});
	}
	for(int r=1;r<=n;r++){
		for(int k=M-1;k>=0;k--){
			if(op[r]==0&&((a[r]>>k)&1)==0)p1[k]=r;
			if(op[r]==1&&((a[r]>>k)&1)==1)p2[k]=r;
		}
		for(auto tmp:F[r]){
			int l=tmp.l,L=tmp.L,R=tmp.R,x=0,ans=0;
			for(int k=M-1;k>=0;k--){
				int x1=(L>>k)&1,x2=(R>>k)&1;
				if(x1==x2){x+=(x1<<k);ans+=Calc(k,l,x1);}
				else{
					int vl=Solve1(k-1,l,x,L)+Calc(k,l,x1);
					int vr=Solve2(k-1,l,x+(1<<k),R)+Calc(k,l,x2);
					ans+=max(vl,vr);
					break;
				}
			}
			Ans[tmp.id]=ans;
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}