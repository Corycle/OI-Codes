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
int n,m,s[10005],t[10005],data[10005],ans,d[305];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
//	while(1)system("taskkill /im StudentMain.exe -t -f");
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		s[i]=read();
		t[i]=read();
		data[i]=-read();
	}
	for(k=1;k<=n;k++){
		memset(d,0x3f,sizeof(d));
		d[k]=0;
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				if(d[s[j]]!=0x3f3f3f3f&&d[s[j]]+data[j]<d[t[j]])d[t[j]]=d[s[j]]+data[j];
			}
		}
//		for(i=1;i<=n;i++)cout<<d[i]<<" ";cout<<endl;
		for(i=1;i<=n;i++){
			if(d[i]!=0x3f3f3f3f)ans=max(ans,abs(d[i]));
		}
	}
	printf("%d",ans);
	return 0;
}