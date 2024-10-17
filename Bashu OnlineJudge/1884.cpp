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
int n,m,a[N],b[N],f[N],lst[N],nxt[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read(),C=read();
	while(Case--){
		n=read();m=read();
		for(int i=1;i<=C;i++)lst[i]=0;
		for(int i=1;i<=n;i++){int x=read();a[i]=lst[x]?i-lst[x]:0;lst[x]=i;}
		for(int i=1;i<=C;i++)lst[i]=0;
		for(int i=1;i<=m;i++){int x=read();b[i]=lst[x]?i-lst[x]:0;lst[x]=i;}
		for(int i=2,j=0;i<=m;i++){
			while(j>0&&b[i]!=b[j+1]){
				if(b[i]>=j+1&&b[j+1]==0)break;//也算匹配成功 
				else j=nxt[j];
			}
			if(b[i]==b[j+1]||(b[i]>=j+1&&b[j+1]==0))j++;
			nxt[i]=j;
		}
		int Ans=0;
		for(int i=1,j=0;i<=n;i++){
			while(j>0&&(j==m||a[i]!=b[j+1])){
				if(j!=m&&a[i]>=j+1&&b[j+1]==0)break;
				else j=nxt[j];
			}
			if(a[i]==b[j+1]||(a[i]>=j+1&&b[j+1]==0))j++;
			f[i]=j;
			if(f[i]==m)Ans++;
		}
//		for(int i=1;i<=m;i++)cout<<b[i]<<" ";cout<<endl;
//		for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
//		for(int i=1;i<=m;i++)cout<<nxt[i]<<" ";cout<<endl;
//		for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<endl;
		printf("%d\n",Ans);
		for(int i=1;i<=n;i++){
			if(f[i]==m)printf("%d ",i-m+1);
		}
//		puts("");
		puts("");
	}
	return 0;
}