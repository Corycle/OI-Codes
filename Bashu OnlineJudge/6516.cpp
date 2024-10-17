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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,op,a[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();op=read();
		for(int i=1;i<=n;i++)a[i]=read()&1;
		if(n==1){if(a[1]&1)puts("B");else puts("A");continue;}
		if(op==0&&(n&1)==0){puts("A");continue;}
		if(op==1&&(n&1)==1){puts("A");continue;}
		int k=(n-1)/2,s=0,t=0;
		for(int i=1;i<=n;i++){
			if(a[i]&1){t^=1;s+=t;}
			else t=0;
		}
		if(s<=k)puts("A");
		else puts("B");
	}
	return 0;
}