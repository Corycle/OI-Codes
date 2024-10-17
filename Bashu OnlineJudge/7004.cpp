/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Ans,sum[3][N];
bool Check(){
	int num1=0,num2=0,num3=0;
	for(int i=1;i<=n;i++){
		if(num1<m)num1+=(s[i]=='J');
		else if(num2<m)num2+=(s[i]=='O');
		else if(num3<m)num3+=(s[i]=='I');
	}
	return num3==m;
}
int GetPos(int t,int x){
	if(sum[t][n]-sum[t][x-1]<m)return -1;
	int l=x,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(sum[t][mid]-sum[t][x-1]>=m){ans=mid;r=mid-1;}
		else l=mid+1;
	}
	return ans;
}
int main(){
//	freopen("joi.in","r",stdin);
//	freopen("joi.out","w",stdout);
	n=read();m=read();scanf("%s",s+1);
	if(!Check()){puts("-1");return 0;}
	if(n==m*3){puts("0");return 0;}
	for(int i=1;i<=n;i++){
		sum[0][i]=sum[0][i-1]+(s[i]=='J');
		sum[1][i]=sum[1][i-1]+(s[i]=='O');
		sum[2][i]=sum[2][i-1]+(s[i]=='I');
	}
	Ans=inf;
	for(int i=1;i<=n;i++){
		if(s[i]=='J'){
			int J=GetPos(0,i);
			if(J==-1)continue;
			int O=GetPos(1,J+1);
			if(O==-1)continue;
			int I=GetPos(2,O+1);
			if(I==-1)continue;
			Ans=min(Ans,(I-i+1)-(m*3));
		}
	}
	printf("%d\n",Ans);
	return 0;
}