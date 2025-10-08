#include <iostream>
#include <stack>
using namespace std;
stack <pair<long long,char>> s;
char a;
long long nr,val;
void op(long long &a,char &b,long long &c){
    if(b=='+')a+=c;
    else if(b=='-')a-=c;
    else a*=c;
}
void f(stack <pair<long long,char>>&s){
    op(s.top().first,s.top().second,nr);
    while(s.top().second!='+' && s.top().second!='-'){
        val=s.top().first;
        s.pop();
        op(s.top().first,s.top().second,val);
    }
}
int main()
{
    s.push(make_pair(0,'+'));
    while(cin >>a){
        if(a>='0' && a<='9')nr=nr*10+a-'0';
        else{
            if(s.top().second==')'){
                nr=s.top().first;
                s.pop();
            }
            if(a=='+' || a=='-'){
                f(s);
                s.top().second=a;
            }
            else if(a=='*')s.push(make_pair(nr,'*'));
            else if(a=='('){
                s.push(make_pair(0,'('));
                s.push(make_pair(0,'+'));
            }
            else{
                f(s);
                val=s.top().first;
                s.pop();
                s.top()=make_pair(val,a);
            }
            nr=0;
        }
    }
    if(s.top().second==')'){
        nr=s.top().first;
        s.pop();
    }
    f(s);
    cout <<s.top().first;
}
