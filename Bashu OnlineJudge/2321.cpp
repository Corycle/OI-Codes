/*
	Hash表示法
*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=160883;
const int Mul=9110;
const int N=3001;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s1[N],s2[N];
int a[N],b[N];
int DFS(int L,int R,int s[]){
	if(L+1==R)return 1;
	int ans=1908,tot=0,tmp[N];
	for(int i=L;i<=R;i++){
		int j,sum=0;
		for(j=i;j<=R;j++){
			sum+=s[j];
			if(sum==0)break;
		}
		tmp[++tot]=DFS(i+1,j-1,s);
		i=j;
	}
	sort(tmp+1,tmp+tot+1);
	for(int i=1;i<=tot;i++){
		ans=((ans*Mul)^tmp[i])%Mod;//Hash
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%s%s",s1+1,s2+1);
		int len1=strlen(s1+1);
		int len2=strlen(s2+1);
		if(len1!=len2){
			printf("different\n");
			continue;
		}
		for(int i=1;i<=len1;i++){
			a[i]=s1[i]=='0'?1:-1;
			b[i]=s2[i]=='0'?1:-1;
		}
		if(DFS(1,len1,a)!=DFS(1,len2,b))printf("different\n");
		else printf("same\n");
	}
	return 0;
}