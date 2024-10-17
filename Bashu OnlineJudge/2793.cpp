/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<bitset>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define Bitset bitset<N>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
char s[N];
Bitset a[N];
void Deal(int x){
	int pos=x;
	while(pos<=m&&!a[pos][x])pos++;
	if(pos==m+1){
		printf("Cannot Determine");
		exit(0);
	}
	Ans=max(Ans,pos);
	swap(a[pos],a[x]);
	for(int j=1;j<=m;j++){
		if(j==x)continue;
		if(a[j][x])a[j]^=a[x];
	}
}
void Gauss(){
	for(int i=1;i<=n;i++)Deal(i);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			a[i][j]=s[j]-'0';
		}
		a[i][n+1]=read();
	}
	Gauss();
	printf("%d\n",Ans);
	for(int i=1;i<=n;i++){
		if(a[i][n+1])printf("?y7M#\n");
		else printf("Earth\n");
	}
	return 0;
}