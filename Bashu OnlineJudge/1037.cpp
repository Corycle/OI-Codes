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
int a[10],sum[3005][10],f[3005][10];
void p(int num){
	int i,j,k=num;
	while(num){
		f[k][num%10]++;
		num/=10;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k=1;
	for(i=0;i<=9;i++)a[i]=read();
	for(i=1;i<=3000;i++){
		p(i);
		for(j=0;j<=9;j++){
			sum[i][j]=sum[i-1][j]+f[i][j];
		}
	}
	for(i=1;i<=3000;i++){
		for(j=1;j<=i;j++){
			int now[10],fl=1;
			memset(now,0,sizeof(now));
			for(int l=0;l<=9;l++){
				now[l]=sum[i][l]-f[j][l];
			}
			for(int l=0;l<=9;l++){
				if(now[l]!=a[l]){
					fl=0;
					break;
				}
			}
			if(fl){
				printf("%d %d\n",i,j);
				k=0;
			}
		}
	}
	if(k){
		printf("NO ANSWER");
	}
	return 0;
}