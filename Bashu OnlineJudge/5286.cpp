#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int Read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*2+c-'0';c=getchar();}
	return s*f;
}
void FMT(int a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j]+=f*a[j-i];
		}
	}
}
int n,m,a[N],b[N],c[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	for(int Case=1;Case<=T;Case++){
		n=read();m=read();
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)a[Read()]++;
		for(int i=1;i<=n;i++)b[Read()]++;
		FMT(a,m,1);FMT(b,m,1);
		for(int i=1;i<(1<<m);i++)c[i]=a[i]*b[i];
		FMT(c,m,-1);
		int q=read();
		printf("Case #%d:\n",Case);
		while(q--){
			printf("%d\n",c[Read()]);
		}
	}
	return 0;
}