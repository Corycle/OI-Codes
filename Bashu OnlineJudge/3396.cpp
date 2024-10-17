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
const int N=500005;
const int M=30;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Line_Basis{
	int p[M],b[M];
	void Insert(int x,int t){
		for(int i=M-1;i>=0;i--){
			if((x>>i)&1){
				if(!p[i]){p[i]=x;b[i]=t;return;}
				if(t>b[i]){swap(p[i],x);swap(b[i],t);}
				x^=p[i];
			}
		}
	}
	int Query(int x,int t){
		for(int i=M-1;i>=0;i--){
			if(b[i]<t)continue;
			if((x>>i)&1)x^=p[i];
		}
		return x;
	}
}F[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		F[i]=F[i-1];
		F[i].Insert(a[i],i);
	}
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),x=read();
		if(F[r].Query(x,l))puts("NO");
		else puts("YES");
	}
	return 0;
}