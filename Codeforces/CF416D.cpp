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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N];
int n,Ans;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int pos=1;
	while(pos<=n){
		Ans++;
		int lst=pos;
		while(pos<=n&&a[pos]==-1)pos++;if(pos>n)break;int x1=pos;
		pos++;
		while(pos<=n&&a[pos]==-1)pos++;if(pos>n)break;int x2=pos;
		if((a[x2]-a[x1])%(x2-x1))continue;
		int dlt=(a[x2]-a[x1])/(x2-x1);
		if(a[x1]-1ll*dlt*(x1-lst)<=0)continue;
		while(pos<=n){
			pos++;
			if(a[pos]==-1){
				if(a[pos-1]+dlt<=0)break;
				a[pos]=a[pos-1]+dlt;
			}
			if(a[pos]!=a[pos-1]+dlt)break;
		}
	}
	printf("%d\n",Ans);
	return 0;
}
