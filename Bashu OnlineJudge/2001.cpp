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
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
char s[2005],ans[20005];
int p1,p2,p3,tp;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	p1=read();p2=read();p3=read();
	cin>>s;
	int l1=strlen(s);
	for(i=l1;i>=1;i--)s[i]=s[i-1];
	s[0]=0;
//	for(i=0;i<=l1;i++){
//		cout<<s[i];
//	}
	for(i=1;i<=l1;i++){
		int f=0;
		if(s[i]!='-'){
			ans[tp++]=s[i];
			f=1;
		}
		else{
			char l=s[i-1],r=s[i+1];
			if(l>=r){
				ans[tp++]=s[i];
				continue;
			}
			if(l>='a'&&l<='z'&&r>='0'&&r<='9'||r>='a'&&r<='z'&&l>='0'&&l<='9'){
				ans[tp++]=s[i];
				continue;
			}
			if(l>='a'&&l<='z'&&r>='a'&&r<='z'){
				if(p1==3){
					for(j=l+1;j<r;j++){
						for(k=1;k<=p2;k++){
							ans[tp++]='*';
						}
					}
					f=1;
				}
				if(p1==1){
					if(p3==1){
						for(j=l+1;j<r;j++){
							for(k=1;k<=p2;k++){
								ans[tp++]=char(j);
							}
						}
						f=1;
					}
					if(p3==2){
						for(j=r-1;j>l;j--){
							for(k=1;k<=p2;k++){
								ans[tp++]=char(j);
							}
						}
						f=1;
					}
				}
				if(p1==2){
					if(p3==1){
						for(j=l+1;j<r;j++){
							for(k=1;k<=p2;k++){
								ans[tp++]=char(j-96+64);
							}
						}
						f=1;
					}
					if(p3==2){
						for(j=r-1;j>l;j--){
							for(k=1;k<=p2;k++){
								ans[tp++]=char(j-96+64);
							}
						}
						f=1;
					}
				}
			}
			if(r>='0'&&r<='9'&&l>='0'&&l<='9'){
				if(p1==3){
					for(j=l+1;j<r;j++){
						for(k=1;k<=p2;k++){
							ans[tp++]='*';
						}
					}
					continue;
				}
				if(p3==1){
					for(j=l+1;j<r;j++){
						for(k=1;k<=p2;k++){
							ans[tp++]=char(j);
						}
					}
					f=1;
				}
				if(p3==2){
					for(j=r-1;j>l;j--){
						for(k=1;k<=p2;k++){
							ans[tp++]=char(j);
						}
					}
					f=1;
				}
			}
		}
		if(f==0){
			ans[tp++]=s[i];
		}
	}
	for(i=0;i<tp;i++){
		cout<<ans[i];
	}
	return 0;
}