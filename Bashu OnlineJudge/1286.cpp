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
char s1[1005],s2[1005];
int ans=1;
bool pd(){
	int i,j,k;
	k=strlen(s1)-1;
	for(i=0;i<=k;i++){
		if(s1[i]!=s2[i])return true;
	}
	return false;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>s1;
	memcpy(s2,s1,sizeof(s1));
	sort(s2,s2+strlen(s2));
	while(pd()){
		ans++;
		next_permutation(s2,s2+strlen(s2));
	}
	cout<<ans;
	return 0;
}