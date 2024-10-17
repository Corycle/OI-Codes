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
const ll inf=1e18;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K;
vector<ll>w[N];
void Merge(vector<ll>&A,vector<ll>&B){
	int s1=A.size()-1,s2=B.size()-1;vector<ll>C;
	C.resize(s1+s2+1);for(int i=1;i<=s1+s2;i++)C[i]=-inf;
	for(int i=0;i<=min(3,s1);i++){
		for(int j=0;j<=min(3,s2);j++){
			int l1=i,l2=j;
			C[l1+l2]=max(C[l1+l2],A[l1]+B[l2]);
			while(l1+4<=s1&&l2+4<=s2){
				(A[l1+4]-A[l1]>B[l2+4]-B[l2])?l1+=4:l2+=4;
				C[l1+l2]=max(C[l1+l2],A[l1]+B[l2]);
			}
			while(l1+4<=s1){l1+=4;C[l1+l2]=max(C[l1+l2],A[l1]+B[l2]);}
			while(l2+4<=s2){l2+=4;C[l1+l2]=max(C[l1+l2],A[l1]+B[l2]);}
		}
	}
	B.resize(s1+s2+1);for(int i=1;i<=s1+s2;i++)B[i]=C[i];
}
void Solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	Solve(l,mid);Solve(mid+1,r);
	Merge(w[mid],w[r]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=K;i++)w[i].push_back(inf);
	for(int i=1;i<=n;i++){int x=read(),y=read();w[x].push_back(y);}
	for(int i=1;i<=K;i++)sort(w[i].begin(),w[i].end(),[](ll x,ll y){return x>y;});
	for(int i=1;i<=K;i++){for(int j=2;j<w[i].size();j++)w[i][j]+=w[i][j-1];w[i][0]=0;w[i][1]=-inf;}
	Solve(1,K);
	for(int i=1;i<=n;i++)printf("%lld\n",w[K][i]<0?-1:w[K][i]);
	return 0;
}