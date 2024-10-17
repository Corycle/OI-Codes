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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K;
char s[N];
int f[N],sum[N];
struct cmp{
	bool operator()(int x,int y){
		return f[x]!=f[y]?f[x]>f[y]:sum[x]<sum[y];
	}
};
priority_queue<int,vector<int>,cmp>q;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+(s[i]=='G'?1:-1);
	}
	q.push(0);
	for(int i=1;i<=n;i++){
		while(q.top()<i-K)q.pop();
		int j=q.top();
		f[i]=f[j]+((sum[i]-sum[j])>=0);
		q.push(i);
	}
	printf("%d",f[n]);
	return 0;
}