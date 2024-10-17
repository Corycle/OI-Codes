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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int nxt[N],f[N];
char a[N],b[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%s%s",a+1,b+1);
		int n=strlen(a+1),m=strlen(b+1);
		int ans=0;
		for(int i=2,j=0;i<=n;i++){
			while(j>0&&a[i]!=a[j+1])j=nxt[j];
			if(a[i]==a[j+1])j++;
			nxt[i]=j;
		}
		for(int i=1,j=0;i<=m;i++){
			while(j>0&&(j==n||b[i]!=a[j+1]))j=nxt[j];
			if(b[i]==a[j+1])j++;
			f[i]=j;
			if(f[i]==n)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}