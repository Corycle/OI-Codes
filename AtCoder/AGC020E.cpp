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
const int Mod=998244353;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
string S;
int F(string);
int G(string);
map<string,int>f,g;
int mod(int x){return x>=Mod?x-Mod:x;}
int F(string s){
	if(f.find(s)!=f.end())return f[s];
	int len=s.length(),ans=0;
	for(int i=0;i<len;i++){
		ans=mod(ans+1ll*F(s.substr(0,i))*G(s.substr(i,len-i))%Mod);
	}
	return f[s]=ans;
}
int G(string s){
	if(g.find(s)!=g.end())return g[s];
	int len=s.length(),ans=0;
	if(len==1)return g[s]=s[0]-'0'+1;
	for(int i=1;i<=len/2;i++){
		if(len%i)continue;
		string t="";
		for(int j=0;j<i;j++){
			char c='1';
			for(int k=j;k<len;k+=i){
				if(s[k]=='0'){c='0';break;}
			}
			t=t+c;
		}
		ans=mod(ans+F(t));
	}
	return g[s]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	f[""]=1;cin>>S;cout<<F(S);
	return 0;
}
