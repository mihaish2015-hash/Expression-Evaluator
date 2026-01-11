#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double value;
    char sign;
} pair;

void applyOp(double *a, char b, double c)
{
    if (b == '+')
        (*a) += c;
    if (b == '-')
        (*a) -= c;
    if (b == '/')
        (*a) /= c;
    if (b == '*')
        (*a) *= c;
}

void collapseStack(pair *s, int *top, double nr){
    int ind = *top;
    while (s[ind].sign != '+' && s[ind].sign != '-')
        ind--;
    for (int i = ind + 2; i <= *top; i++)
        applyOp(&(s[ind + 1].value), s[i - 1].sign, s[i].value);
    if(*top > ind) {
        applyOp(&(s[ind + 1].value), s[*top].sign, nr);
        applyOp(&(s[ind].value), s[ind].sign, s[ind + 1].value);
        (*top) = ind;
    } else
        applyOp(&(s[ind].value), s[ind].sign, nr);
}

void processToken(pair *s, int *top, char c, double *nr)
{
    if (s[*top].sign == ')') {
        *nr = s[*top].value;
        (*top)--;
    }
    if (c == '+' || c == '-') {
        collapseStack(s, top, *nr);
        s[*top].sign = c;
    }
    else if (c == '*')
        s[++(*top)] = (pair){*nr, '*'};
    else if (c == '/')
        s[++(*top)] = (pair){*nr, '/'};
    else if (c == '(') {
        s[++(*top)] = (pair){0, '('};
        s[++(*top)] = (pair){0, '+'};
    } else if (c == ')') {
        collapseStack(s, top, *nr);
        (*top)--;
        s[*top] = (pair){s[(*top)+1].value, c};
    }
    *nr = 0;
}

int main()
{
    char c;
    int top=0;
    double nr = 0, frac = 1;
    pair s[1000];
    s[++top]=(pair){0, '+'};
    while(scanf("%c", &c) == 1){
        if(c>='0' && c<='9') {
            if(frac < 1) {
                nr += (c - '0') * frac;
                frac /= 10;
            } else
                nr = nr * 10 + c - '0';
        }
        else if (c == '.')
            frac /= 10;
        else if (strchr("+-*/()", c)) {
            processToken(s, &top, c, &nr);
            frac = 1;
        }
    }
    if(s[top].sign == ')'){
        nr = s[top].value;
        top--;
    }
    collapseStack(s, &top, nr);
    printf("%lf",s[top].value);
}
