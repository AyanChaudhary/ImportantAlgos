#include<bits/stdc++.h>
using namespace std;

void computeLps(vector<int>&lps,string &pat){
    lps[0]=0;
    int i=1,len=0,n=pat.size();
    while(i<n){
        if(pat[i]==pat[len]){
            lps[i]=len+1;
            len++;
            i++;
        }else{
            if(len)len=lps[len-1];
            else i++;
        }
    }
}
int solve(string pat,string txt){
    int n=pat.size(),m=txt.size();
    vector<int>lps(n+1,0);
    computeLps(lps,pat);
    int i=0,j=0,occurance=0;
    while(j<m){
        if(pat[i]==txt[j]){
            i++,j++;
        }else{
            if(i)i=lps[i-1];
            else j++;
        }
        if(i==n)occurance++,i=lps[i-1];
    }
    return occurance;
}
int main(){


    return 0;
}