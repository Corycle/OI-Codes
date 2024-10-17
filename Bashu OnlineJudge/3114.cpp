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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],vis[N],Ans[N];
int main(){
//	freopen("patrol.in","r",stdin);
//	freopen("patrol.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		a[i]=read();
		vis[a[i]]=1;
	}
	int pos=1;
	for(int i=1;i<=n;i++){
		while(pos<=m&&a[pos]<i){
			Ans[++Ans[0]]=a[pos];
			pos++;
		}
		if(!vis[i])Ans[++Ans[0]]=i;
	}
	while(pos<=m){
		Ans[++Ans[0]]=a[pos];
		pos++;
	}
	for(int i=1;i<=n;i++)printf("%d\n",Ans[i]);
	return 0;
}