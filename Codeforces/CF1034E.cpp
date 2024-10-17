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
const int N=(1<<21)+5;
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,num[N];
char s[N],t[N];
ll a[N],b[N],c[N],P[M];
void FWT(ll a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j]+=a[j-i]*f;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();scanf("%s%s",s,t);
	P[0]=1;for(int i=1;i<=n;i++)P[i]=P[i-1]*4;
	for(int i=1;i<(1<<n);i++)num[i]=num[i>>1]+(i&1);
	for(int i=0;i<(1<<n);i++)a[i]=(s[i]-'0')*P[num[i]];
	for(int i=0;i<(1<<n);i++)b[i]=(t[i]-'0')*P[num[i]];
	FWT(a,n,1);FWT(b,n,1);
	for(int i=0;i<(1<<n);i++)c[i]=a[i]*b[i];
	FWT(c,n,-1);
	for(int i=0;i<(1<<n);i++)c[i]/=P[num[i]];
	for(int i=0;i<(1<<n);i++)printf("%lld",c[i]&3);
	return 0;
}
