class SGTree{
    vector<int>seg;
public:
    SGTree(int n){
        seg.resize(4*n);    
    }
    void build(int idx,int low,int high,int a[]){
        if(low==high){
            seg[idx]=a[high];
            return;
        }
        int m=(low+high)>>1;
        build(2*idx+1,low,m,a);
        build(2*idx+2,m+1,high,a);
        seg[idx]=seg[2*idx+1]+seg[2*idx+2];
    }
    // for finding min ele in a range
    int query(int idx,int low,int high,int l,int r,int a[]){
        // no overlap..
        if(high<l || low>r)return INT_MAX;
        // complete overlap [l low high r]..
        if(low>=l && high<=r)return seg[idx];

        // else partial overlap -> move in both directions
        int m=(low+high)>>1;
        int left=query(2*idx+1,low,m,l,r,a);
        int right=query(2*idx+2,m+1,high,l,r,a);
        return min(left,right);
    }
    void update(int idx,int low,int high,int i,int a[]){
        if(low==high){
            seg[idx]=a[i];
            return;
        }
        int m=(low+high)>>1;
        if(i<=m)update(2*idx+1,low,m,i,a);
        else update(2*idx+2,m+1,high,i,a);
        seg[idx]=min(seg[2*idx+1],seg[2*idx+2]);
    }
};
