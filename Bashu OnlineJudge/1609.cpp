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
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m,sh1,wolf,sh=1,w;
char m1[255][255];
bool s1[255][255];
int zhao(int i,int j){
	int t1[5]={0,1,-1,0,0};
	int t2[5]={0,0,0,1,-1};
	s1[i][j]=true;
	if(i==1||i==n||j==m||j==1){
		sh=0;
		w=0;
		return 0;
	}
	int p;
	for(p=1;p<=4;p++){
		if(m1[i+t1[p]][j+t2[p]]=='o'&&s1[i+t1[p]][j+t2[p]]==false){
			sh++;
			zhao(i+t1[p],j+t2[p]);
		}
		if(m1[i+t1[p]][j+t2[p]]=='v'&&s1[i+t1[p]][j+t2[p]]==false){
			w++;
			zhao(i+t1[p],j+t2[p]);
		}
		if(m1[i+t1[p]][j+t2[p]]=='.'&&s1[i+t1[p]][j+t2[p]]==false)
			zhao(i+t1[p],j+t2[p]);
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>m1[i][j];
			if(m1[i][j]=='o')sh1++;
			if(m1[i][j]=='v')wolf++;
		}
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(m1[i][j]=='o'&&s1[i][j]==false){
			zhao(i,j);
			if(sh>w)wolf-=w;
			else sh1-=sh;
			}
			sh=1;w=0;
		}
	}
	cout<<sh1<<" "<<wolf;
	return 0;
}