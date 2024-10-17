#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,t[105],v[105],amt[105],cnt=0,f[100005],sum[11][11];
void complete(int v,int t){//完成 
	for(int i=t;i<=m;i++)
	if(f[i-t]+v>f[i])f[i]=f[i-t]+v;
}
void zeroone(int v,int t){//01
	for(int i=m;i>=t;i--){
		if(f[i-t]+v>f[i])f[i]=f[i-t]+v;
	}
}
int main() {  
	int i,j,k,t1,v1;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d%d",&t1,&v1);
		sum[t1][v1]++;
	}
	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++)
		if(sum[i][j]){
			amt[++cnt]=sum[i][j];
			t[cnt]=i;
			v[cnt]=j;
		}
	}
	for(int i=1;i<=cnt;i++){
		if(amt[i]*t[i]>m){
			complete(v[i],t[i]);
			continue;
		}
		k=1;
		while(k<=amt[i]){
			zeroone(v[i]*k,t[i]*k);
			amt[i]-=k;
			k*=2;
		}
		if(amt[i])zeroone(v[i]*amt[i],t[i]*amt[i]);
	}
	printf("%d",f[m]);
}