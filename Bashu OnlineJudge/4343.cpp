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
const int N=(1<<12)+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,p[M],fac[M],a[N];
bool Check(int l,int r){for(int i=l+1;i<=r;i++)if(a[i]!=a[i-1]+1)return false;return true;}
void Change(int l,int r,int k){for(int i=1;i<=p[k];i++)swap(a[l+i-1],a[r+i-1]);}
void DFS(int k,int num){
	if(k==n+1){Ans+=fac[num];return;}
	int t1=0,t2=0;
	for(int i=1;i<=(1<<n);i+=p[k]){
		if(!Check(i,i+p[k]-1)){
			if(!t1)t1=i;
			else if(!t2)t2=i;
			else return;
		}
	}
	if(!t1&&!t2)DFS(k+1,num);
	else if(t1&&!t2){
		Change(t1,t1+p[k-1],k-1);
		DFS(k+1,num+1);
		Change(t1,t1+p[k-1],k-1);
	}
	else{
		for(int x=0;x<=1;x++){
			for(int y=0;y<=1;y++){
				Change(t1+x*p[k-1],t2+y*p[k-1],k-1);
				if(Check(t1,t1+p[k]-1)&&Check(t2,t2+p[k]-1)){
					DFS(k+1,num+1);
					Change(t1+x*p[k-1],t2+y*p[k-1],k-1);
					break;
				}
				Change(t1+x*p[k-1],t2+y*p[k-1],k-1);
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();fac[0]=p[0]=1;
	for(int i=1;i<=(1<<n);i++)a[i]=read();
	for(int i=1;i<=n;i++)p[i]=p[i-1]<<1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
	DFS(1,0);
	printf("%lld",Ans);
	return 0;
}