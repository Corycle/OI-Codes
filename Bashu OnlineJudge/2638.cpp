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
map<char,char>m1;
map<char,int>m2;
string s1,s2,s3;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>s1>>s2>>s3;
	int l1=s1.length(),l2=s2.length(),l3=s3.length();
	if(l1!=l2){
		printf("Failed");
		return 0;
	}
	for(i=0;i<l1;i++){
		if((m2[s2[i]]!=0&&m1[s1[i]]!=s2[i])||(m2[s2[i]]==0&&m1[s1[i]]!=0)||(m1[s1[i]]!=0&&m1[s1[i]]!=s2[i])){
			printf("Failed");
			return 0;
		}
		m1[s1[i]]=s2[i];
		m2[s2[i]]=1;
	}
	for(i='A';i<='Z';i++){
		if(m2[i]==0){
			printf("Failed");
			return 0;
		}
	}
	for(i=0;i<l3;i++){
		if(m1[s3[i]]==0){
			printf("Failed");
			return 0;
		}
	}
	for(i=0;i<l3;i++){
		printf("%c",m1[s3[i]]);
	}
	return 0;
}