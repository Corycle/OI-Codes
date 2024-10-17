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
const int N=2e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int p[N];
string s,t,S;
void Ex_KMP(){
	int n=S.length()-1;p[1]=n;
	for(int i=2,st=0,ed=0;i<=n;i++){
		if(ed>=i)p[i]=min(p[i-st+1],ed-i+1);
		while(i+p[i]<=n&&S[p[i]+1]==S[i+p[i]])p[i]++;
		if(i+p[i]-1>ed){st=i;ed=i+p[i]-1;}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	cin>>s>>t;S='#'+t+'&'+s;Ex_KMP();
	int T=read(),len=t.length();
	while(T--)printf("%d\n",p[len+1+read()]);
	return 0;
}