/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[105];
int n,m,a[N],b[N],ans[N],Ans[N];
struct Student{int scores;string Name;}P[N];
bool cmp(Student A,Student B){
	return A.scores!=B.scores?A.scores>B.scores:A.Name<B.Name;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)cin>>P[i].Name;
	for(int i=1;i<=m;i++){
		a[i]=read();b[i]=read();
		scanf("%s",s+1);
		int len=strlen(s+1);
		for(int j=1;j<=len;j++){
			if(s[j]=='A')Ans[i]|=(1<<1);
			if(s[j]=='B')Ans[i]|=(1<<2);
			if(s[j]=='C')Ans[i]|=(1<<3);
			if(s[j]=='D')Ans[i]|=(1<<4);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)ans[j]=0;
		for(int k=1;k<=4;k++){
			scanf("%s",s+1);
			for(int j=1;j<=m;j++){
				if(s[j]=='X')ans[j]|=(1<<k);
			}
		}
		for(int j=1;j<=m;j++){
			if(ans[j]==Ans[j])P[i].scores+=a[j];
			else if(ans[j]&&(ans[j]&Ans[j])==ans[j])P[i].scores+=b[j];
		}
	}
	sort(P+1,P+n+1,cmp);
	for(int i=1;i<=n;i++){
		cout<<P[i].Name<<" "<<P[i].scores<<endl;
	}
	return 0;
}