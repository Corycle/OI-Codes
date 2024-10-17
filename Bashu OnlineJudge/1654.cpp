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
#define inf 0x3f3f3f3f
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int a[6][11],f[6][26];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	for(i=1;i<=5;i++){
		for(j=1;j<=10;j++){
			a[i][j]=read();
		}
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(j=1;j<=25;j++){
		for(i=1;i<=5;i++){
			for(k=1;k<=min(10,j);k++){
				f[i][j]=min(f[i][j],f[i-1][j-k]+a[i][k]);
			}
		}
	}
	printf("%d",f[5][25]);
	return 0;
}