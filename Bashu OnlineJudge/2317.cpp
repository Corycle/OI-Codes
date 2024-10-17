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
int a[15],f[105],n;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	for(i=1;i<=10;i++)a[i]=read();
	n=read();
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(i=1;i<=n;i++){
		for(j=1;j<=10;j++){
			if(i-j<0)break;
			f[i]=min(f[i],f[i-j]+a[j]);
		}
	}
	printf("%d",f[n]);
	return 0;
}