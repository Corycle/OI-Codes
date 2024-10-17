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
#include<bitset>
#define ll long long
#define Bitset bitset<M>
using namespace std;
const int inf=0x3f3f3f3f;
const int M=(1<<12)+5;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
Bitset F[N];
int n,m,K,tot,Sta;
struct Node{
	int id,val;
	friend bool operator<(Node A,Node B){return A.val>B.val;}
};
vector<Node>P[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();m=read();Sta=(1<<K)-1;tot=K;
	for(int i=1;i<=K;i++){
		for(int j=1;j<=n;j++)P[j].push_back((Node){i,read()});
		for(int S=0;S<=Sta;S++)if((S>>(i-1))&1)F[i][S]=1;
	}
	for(int i=1;i<=n;i++)sort(P[i].begin(),P[i].end());
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==1)F[++tot]=F[x]|F[y];
		if(op==2)F[++tot]=F[x]&F[y];
		if(op==3){
			int sta=0;
			for(auto tmp:P[y]){
				sta|=(1<<(tmp.id-1));
				if(F[x][sta]){printf("%d\n",tmp.val);break;}
			}
		}
	}
	return 0;
}
