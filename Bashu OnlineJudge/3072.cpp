#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p;
int fx[N],fy[N],tx[N],ty[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=p;i++){
		int op=read(),x=read(),y=read();
		if(op==1){fx[x]=y;tx[x]=i;}//这一行最后染色时间 
		if(op==2){fy[x]=y;ty[x]=i;}//这一列最后染色时间 
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(tx[i]>ty[j]){printf("%d ",fx[i]);continue;}
			if(tx[i]<ty[j]){printf("%d ",fy[j]);continue;}
			printf("0 ");
		}
		printf("\n");
	}
	return 0;
}