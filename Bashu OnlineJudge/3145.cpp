#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,last[200005],sum[200005],cnt[200005],ans,now;
int main(){
	int i,j,k;
	n=read();k=read();p=read();
	for(i=1;i<=n;i++){
		int x=read(),y=read();
		if(y<=p){
			now=i;
		}
		if(now>=last[x]){
			sum[x]=cnt[x];
		}
		last[x]=i;
		ans+=sum[x];
		cnt[x]++;
	}
	printf("%d",ans);
	return 0;
}