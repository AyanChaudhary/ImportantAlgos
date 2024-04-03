#include<bits/stdc++.h>
using namespace std;

class manacher{
    vector<int>p;
public:
    void build(string s){
        int n=s.size();
        p.assign(n,1);
        // cout<<s<<" ";
        int l=-1,r=1;
        for(int i=1;i<n;i++){
            p[i]=max(1,min(r-i,p[l+r-i]));
            while(i-p[i]>=0 && i+p[i]<n && s[i-p[i]]==s[i+p[i]])
                p[i]++;
            if(i+p[i]>r){
                l=i-p[i];
                r=i+p[i];
            }
        }
    }
    manacher(string s=""){
        string t;
        for(auto ch : s){
            t+=string("#")+ch;
        }
        build(t+"#");
    }
    int longestPalin(int cen,bool odd){
        int pos=2*cen+1+(!odd);
        return p[pos];
    }
    bool checkPalin(int l,int r){
        if(r-l+1<=longestPalin((l+r)>>1,l%2==r%2))
            return true;
        return false;
    }
};

int main(){

    

    return 0;
}
