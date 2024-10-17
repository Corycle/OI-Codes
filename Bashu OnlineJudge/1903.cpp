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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],s[N],d[N],f[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		s[i]=read();d[i]=read();
	}
	f[1]=1;
	for(int t=1;t<=m;t++){
		for(int i=1;i<=n;i++){
			if(s[t]<a[i])continue;
			for(int j=max(i-d[t],0);j<=i;j++){
				if(!f[j])continue;
				if(min(s[f[j]],s[t])>=a[j]){
					f[i]=t;break;
				}
			}
		}
		if(f[n]){
			printf("%d",t-1);
			return 0;
		}
	}
	return 0;
}