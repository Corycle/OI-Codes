#include<cstdio>
#include<iostream>
using namespace std;
int main(){
	int a,b,c,d;
	char e;
	int n;
	scanf("%d",&n);
	while(n--){
		int flag=0;
		string s;
		cin>>s;
		int n1=s.length()-1;
		a=b=c=d=0;
		for(int i=0;i<=n1;i++){
			e=s[i];
			if(e=='<') a++;
			if(e=='>') a--;
			if(a<0){
				flag=1;
				break;
			}
			if(e=='(') b++;
			if(e==')') b--;
			if((b<0||(a)&&b>0)&&(e=='('||e==')')){
				flag=1;
				break;
			}
			if(e=='[') c++;
			if(e==']') c--;
			if((c<0||((b||a)&&c>0))&&(e=='['||e==']')){
				flag=1;
				break;
			}
			if(e=='{') d++;
			if(e=='}') d--;
			if((d<0||((a||b||c)&&d>0))&&(e=='{'||e=='}')){
				flag=1;
				break;
			} 
		}
		if(flag) printf("NO\n");
		else if(a==0&&b==0&&c==0&&d==0){
			printf("YES\n");
			continue;
		}
		else printf("NO\n");
	} 
	return 0;
}