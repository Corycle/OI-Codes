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
int n,m,f[2005][2005],t,maxx[2005],maxx2;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();t=read();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='1'){
				f[i][j]=min(f[i-1][j],min(f[i][j-1],f[i-1][j-1]))+1;
				maxx[f[i][j]]++;
				maxx2=max(maxx2,f[i][j]);
			}
		}
	}
	while(t--){
		i=read();
		int ans=0;
		for(j=i;j<=maxx2;j++)ans+=maxx[j];
		printf("%d\n",ans);
	}
	return 0;
}