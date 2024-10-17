#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
string A,B,s[N];
int len[N],Ans[N];
int n,ans,len1,len2;
void Solve(int l1,int l2,int num){
	int p=abs((len1-l1)-(len2-l2));
	if(num+p>=ans)return;
	while(l1<=len1&&l2<=len2){
		if(A[l1]==B[l2]){l1++;l2++;}
		else{
			Solve(l1,l2+1,num+1);//A 插入 
			Solve(l1+1,l2,num+1);//B 插入 
			Solve(l1+1,l2+1,num+1);//修改 
			return;
		}
	}
	if(l1==len1+1)ans=min(ans,num+len2-l2+1);
	if(l2==len2+1)ans=min(ans,num+len1-l1+1);
}
int main(){
//	freopen("say.in","r",stdin);
//	freopen("say.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		len[i]=s[i].length()-1;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			A=s[i];B=s[j];ans=9;
			len1=len[i];len2=len[j];
			Solve(0,0,0);
			Ans[ans]++;
		}
	}
	for(int i=1;i<=8;i++)printf("%d ",Ans[i]);
	return 0;
}