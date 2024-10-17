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
const int N=15005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N];
int n,m,Ans,nxt[N],f[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",a+1);
	n=strlen(a+1);m=read();
	for(int t=1;t<=n;t++){
		nxt[t]=t-1;
		for(int i=t+1,j=t-1;i<=n;i++){
			while(j>t-1&&a[i]!=a[j+1])j=nxt[j];
			if(a[i]==a[j+1])j++;
			nxt[i]=j;
		}
		for(int i=t,j=t-1;i<=n;i++){
			while(j>t-1&&(a[i]!=a[j+1]||(j+1-t+1)*2>=(i-t+1)))j=nxt[j];
			if(a[i]==a[j+1])j++;
			f[i]=j;
//			cout<<t<<": "<<i<<": "<<f[i]<<endl;
			if(i>=t+m*2)Ans+=(f[i]-t+1>=m);
		}
	}
	printf("%d\n",Ans);
	return 0;
}