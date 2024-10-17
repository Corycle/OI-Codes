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
struct dp{
  int zero,one;
}ans[150001];
int len,t=1;
const int mod=10007;
string str;
stack<char>s;
void solve(char ch,dp &a,dp &b){
	if(ch=='+'){
		a.one=(a.one*(b.zero+b.one)+a.zero*b.one)%mod;
		a.zero=a.zero*b.zero%mod;
	}
	else {
		a.zero=(a.zero*(b.zero+b.one)+a.one*b.zero)%mod;
		a.one=a.one*b.one%mod;
	}
}
int main(){
	int i,j,k;
	scanf("%d",&len);
	cin>>str;
	str+=')';
	ans[1].zero=ans[1].one=1;
	s.push('(');
	for(i=0;i<=len;i++)
	if(str[i]=='(')s.push('(');
	else if(str[i]==')'){
		for(;s.top()!='(';s.pop(),t--){
			solve(s.top(),ans[t-1],ans[t]);
		}
		s.pop();
	}
	else{
		for(;s.top()<=str[i]&&s.top()!='(';s.pop(),t--){
			solve(s.top(),ans[t-1],ans[t]);
		}
		s.push(str[i]);
		ans[++t].zero=1;
		ans[t].one=1;
	}
	cout<<ans[1].zero;
	return 0;
}