#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
string s;
long int num[250],numtop,marktop=1;
char mark[250];
int dzh(char a,char b){
	if(a=='('&&b==')')return 0;//-1存  0()消  1算 
	if(a=='('||b=='(')return -1;
	if(b=='+'||b=='-'||a=='*'||a=='/'||b==')'||a==b)return 1;
	return -1;
}
int dzhh(int a,int b,char c){
	switch(c){
		case '+':return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':return a/b;
	}
}
int main(){
	long int i=0,j,k,l;
	cin>>s;s+=')';
	mark[1]='(';
	while(i<s.length()){
		k=l=0;
		while(s[i]>='0'&&s[i]<='9'){
			l=l*10+s[i]-'0';
			i++;
			k=1;
		}
		if(k==1){
			numtop++;
			num[numtop]=l;
		}
		switch(dzh(mark[marktop],s[i])){
			case 1:
				num[numtop-1]=dzhh(num[numtop-1],num[numtop],mark[marktop]);
				numtop--;
				marktop--;
				break;
			case 0:
				marktop--;
				i++;
				break;
			case -1:
				marktop++;
				mark[marktop]=s[i];
				i++;
		}
	}
	cout<<num[1];
    return 0;
}