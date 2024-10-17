#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
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
int n,x,y,tp;
int a[N],b[N],c[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(b[tp]!=a[i])b[++tp]=a[i];
		c[tp]++;
	}
	for(int i=1;i<=tp;i++)if(c[i]>c[x])x=i;
	for(int i=1;i<=tp;i++)if(i!=x&&c[i]&1)y=i;
	printf("%d %d",b[x],b[y]);
	return 0;
}