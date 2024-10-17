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
const int N=1e7+5;
const int M=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,p[M],m[N];
ll ans,d[N];
bool vis[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	d[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])p[++p[0]]=i,d[i]=2,m[i]=2;
		for(int j=1;j<=p[0]&&i*p[j]<=n;j++){
			vis[i*p[j]]=1;
			if(!(i%p[j])){
				d[i*p[j]]=d[i]/m[i]*(m[i]+1);
				m[i*p[j]]=m[i]+1;
				break;
			}
			d[i*p[j]]=d[i]*2,m[i*p[j]]=2;
		}
	}
	for(int i=1;i<=n;i++)ans+=i*d[i];
	cout<<ans;
	return 0;
}

