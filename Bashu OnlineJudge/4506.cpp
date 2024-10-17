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
int n,m,a[105][105],b[105][105];
string s;
void change(char c){
	int i,j,k;
	memset(b,0,sizeof(b));
	if(c=='A'){
		for(j=1;j<=m;j++){
			for(i=n;i>=1;i--){
				b[j][n-i+1]=a[i][j];
			}
		}
		swap(n,m);
	}
	if(c=='B'){
		for(j=m;j>=1;j--){
			for(i=1;i<=n;i++){
				b[m-j+1][i]=a[i][j];
			}
		}
		swap(n,m);
	}
	if(c=='C'){
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				b[i][j]=a[i][m-j+1];
			}
		}
	}
	if(c=='D'){
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				b[i][j]=a[n-i+1][j];
			}
		}
	}
	memcpy(a,b,sizeof(a));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			a[i][j]=read();
		}
	}
	cin>>s;
	int len=s.length()-1;
	for(i=0;i<=len;i++){
		change(s[i]);
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}