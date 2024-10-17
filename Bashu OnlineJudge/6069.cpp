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
const int N=25005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans,a[N],vis[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();Ans=n;
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+n+1);
		for(int i=1;i<=a[n];i++)vis[i]=0;
		for(int i=1;i<=n;i++){
			if(vis[a[i]]){Ans--;continue;}
			vis[a[i]]=1;
			for(int j=1;j+a[i]<=a[n];j++){
				if(vis[j])vis[j+a[i]]=1;
			}
		}
		printf("%d\n",Ans);
	}
	return 0;
}