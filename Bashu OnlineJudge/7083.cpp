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
const int N=2100000;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll m,num[N];
int n,tot,ch[N][2],tag[N];
void DFS(int x){
	if(x>n)return;
	num[ch[x][tag[x]]]=(1+num[x])/2;
	num[ch[x][tag[x]^1]]=num[x]-num[ch[x][tag[x]]];
	if(num[x]&1)tag[x]^=1;
	DFS(ch[x][0]);DFS(ch[x][1]);
}
int main(){
//	freopen("binary.in","r",stdin);
//	freopen("binary.out","w",stdout);
	n=read();m=read();tot=n;
	for(int i=1;i<=n;i++){
		for(int j=0;j<2;j++)ch[i][j]=read();
		for(int j=0;j<2;j++)if(!ch[i][j])ch[i][j]=++tot;
		tag[i]=read();
	}
	num[1]=m;DFS(1);
	for(int i=1;i<=n;i++)cout<<tag[i];
	return 0;
}