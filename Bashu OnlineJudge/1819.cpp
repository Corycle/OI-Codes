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
int n,m,w[1005],v[1005],f[60005];
inline int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
bool s[1005][60005];
int main(){
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		w[i]=read();v[i]=read();
	}
	for(i=1;i<=n;i++){
		for(j=m;j>=w[i];j--){
			if(f[j]<=f[j-w[i]]+v[i]){
				f[j]=f[j-w[i]]+v[i];
				s[i][j]=true;
			}
		}
	}
	printf("%d\n",f[m]);
	for(i=n;i>=1;i--){
		if(s[i][m]==true){
			printf("%d\n",i);
			m-=w[i];
		}
	}
	return 0;
}