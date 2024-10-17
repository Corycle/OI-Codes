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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char a[N];
int n,nxt[N],len[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	scanf("%s",a+1);
	for(int i=2,j=0;i<=n;i++){
		while(j>0&&a[i]!=a[j+1])j=nxt[j];
		if(a[i]==a[j+1])j++;
		nxt[i]=j;
	}
	for(int i=1;i<=n;i++){
		len[i]=(nxt[i]==0?i:len[nxt[i]]);
		Ans+=i-len[i];
	}
	printf("%lld",Ans);
	return 0;
}