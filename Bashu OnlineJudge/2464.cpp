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
int a,b,c,p1,p2,p3,n,t[12],f[12][102][102],maxn,ans;
//f[i][j][k]表示第i条生产线生产j个汉堡，k个薯条的情况下最多可生产饮料的个数 
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	a=read();b=read();c=read();
	p1=read();p2=read();p3=read();
	n=read();
	for(i=1;i<=n;i++)t[i]=read();
	int maxn=min(100/a,min(100/b,100/c));
    //因为题目“假设汉堡、薯条和饮料的日产量不超过100个。”
	memset(f,-1,sizeof(f));
	f[0][0][0]=0;
	for(i=1;i<=n;i++){
		for(j=0;j<=maxn*a;j++){
			for(k=0;k<=maxn*b;k++){
				for(int j1=0;j1<=j;j1++){
					for(int k1=0;k1<=k;k1++){
						if(f[i-1][j-j1][k-k1]!=-1&&t[i]-j1*p1-k1*p2>=0){ //保证状态是合法的 
							if(f[i][j][k]>=maxn*c)break;//不能直接输出maxn，否则会错。
							f[i][j][k]=max(f[i][j][k],f[i-1][j-j1][k-k1]+(t[i]-j1*p1-k1*p2)/p3);
						}
					}
				}
			}
		}
	}
	for(i=0;i<=maxn*a;i++){
    	for(j=0;j<=maxn*b;j++){
			ans=max(ans,min(i/a,min(j/b,f[n][i][j]/c)));
		}
	}
	printf("%d",ans);
	return 0;
}
