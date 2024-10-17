#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
int n,w[25],f[1000005],sum,ans;
inline int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
int main(){
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		w[i]=read();
		sum+=w[i];
	}
	memset(f,-0xf,sizeof(f));
	f[0]=1;
	for(i=1;i<=n;i++){
		for(j=sum/2;j>=0;j--){
			if(j>=w[i])f[j]=max(f[j],f[j-w[i]]+1);
			if(f[j]>0)ans=max(ans,j);
		}
	}
	printf("%d",sum-ans*2);
	return 0;
}