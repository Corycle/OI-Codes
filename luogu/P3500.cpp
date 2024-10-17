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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,a[N],b[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){a[i]=read();G[a[i]].push_back(i);}
	for(int i=1;i<N;i++)G[i].push_back(n+1);
	int Case=read();
	while(Case--){
		m=read();
		int pos=0,flag=1;
		for(int i=1;i<=m;i++)b[i]=read();
		for(int i=1;i<=m;i++){
			int p=upper_bound(G[b[i]].begin(),G[b[i]].end(),pos)-G[b[i]].begin();
			if(G[b[i]][p]>n){flag=0;break;}
			pos=G[b[i]][p];
		}
		puts(flag?"TAK":"NIE");
	}
	return 0;
}
