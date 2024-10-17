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
int n,m,x,y,a[105][105],f[105][105],ans;
queue<int>q1,q2,q3;
int s1[10]={0,1,1,-1,-1,1,-1,0,0};
int s2[10]={0,1,-1,1,-1,0,0,1,-1};
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
//	while(1)system("taskkill /im StudentMain.exe -t -f");
	m=read();n=read();y=read();x=read();
	for(i=n;i>=1;i--){
		for(j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='.')a[i][j]=1;
		}
	}
//	for(i=1;i<=n;i++){
//		for(j=1;j<=m;j++){
//			cout<<a[i][j]<<" ";
//		}
//		cout<<endl;
//	}
	q1.push(x);q2.push(y);q3.push(0);
	f[x][y]=1;
	while(q1.size()){
		int qx=q1.front(),qy=q2.front(),qz=q3.front();
//		cout<<qx<<" "<<qy<<" "<<qz<<endl;
//		for(i=1;i<=n;i++){
//			for(j=1;j<=m;j++){
//				cout<<f[i][j]<<" ";
//			}
//			cout<<endl;
//		}
//		system("pause");
		q1.pop();q2.pop();q3.pop();
		for(i=1;i<=8;i++){
			int nx=s1[i]+qx,ny=s2[i]+qy,nz=qz+1;
			if(a[nx][ny]==1&&f[nx][ny]==0){
				f[nx][ny]=1;
				q1.push(nx);q2.push(ny);q3.push(nz);
				ans=max(ans,nz);
			}
		}
	}
	printf("%d",ans);
	return 0;
}