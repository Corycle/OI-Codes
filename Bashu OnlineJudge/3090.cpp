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
char s[30005];
int len;
void print(int l,int r){
	int i,j=0,k=0;
	int li,ri;
	if(s[l]>'9'||s[l]<'0')j=1;
	while(s[l]>='0'&&s[l]<='9'&&l<=r){
		j=j*10+s[l]-'0';
		l++;
	}
	if(l>r)return;
//	cout<<j<<" "<<l<<" "<<r<<endl;
//	system("pause");
	while(j--){
		k=0;
		for(i=l;i<=r;i++){
			if(k==0&&s[i]!='['&&s[i]!=']')printf("%c",s[i]);
			if(s[i]=='['){
				k++;
				if(k==1)li=i;
			}
			if(s[i]==']'){
				k--;
				if(k==0)ri=i;
				if(k==0)print(li+1,ri-1);
			}
		}
	}
}
char ans[30005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%s",&s);
	len=strlen(s)-1;
	print(0,len);
	return 0;
}