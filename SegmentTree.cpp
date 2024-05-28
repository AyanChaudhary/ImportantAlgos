class SGTree{
    vector<ll>seg;
    vector<ll>lazy;
public:
    SGTree(ll n){
        seg.resize(4*n);
        lazy.resize(4*n,0);
    }
    void build(int idx,int low,int high,vector<int>&a){
        if(low==high){
            seg[idx]=a[low];
            return;
        }
        int mid=(low+high)>>1;
        build(2*idx+1,low,mid,a);
        build(2*idx+2,mid+1,high,a);
        seg[idx]=(seg[2*idx+1]+seg[2*idx+2]);
    }
    // static query
    ll query(int idx,int low,int high,int l,int r,vector<int>&a){
        if(lazy[idx]!=0){
            seg[idx]+=(high-low+1)*lazy[idx];
            if(low!=high){
                lazy[2*idx+1]+=lazy[idx];
                lazy[2*idx+2]+=lazy[idx];
            }
            lazy[idx]=0;
        }
        if(low>r || high<l)return 0;
        if(low>=l && high<=r)return seg[idx];
        int mid=(low+high)>>1;
        ll lft=query(2*idx+1,low,mid,l,r,a);
        ll rt=query(2*idx+2,mid+1,high,l,r,a);
        return (lft+rt);
    }
    // pointUpdate
    void pointUpdate(int idx,int low,int high,int i,int val){
        if(low==high){
            seg[idx]=val;
            return;
        }
        int mid=(low+high)>>1;
        if(i<=mid)pointUpdate(2*idx+1,low,mid,i,val);
        else pointUpdate(2*idx+2,mid+1,high,i,val);
        seg[idx]=(seg[2*idx+1]+seg[2*idx+2]);
    }
    // rangeUpdate
    void rangeUpdate(int idx,int low,int high,int l,int r,int val){
        if(lazy[idx]!=0){
            seg[idx]+=(high-low+1)*lazy[idx];
            if(low!=high){
                lazy[2*idx+1]+=lazy[idx];
                lazy[2*idx+2]+=lazy[idx];
            }
            lazy[idx]=0;
        }
        if(low>r || high<l)return;
        if(low>=l && high<=r){
            seg[idx]+=(high-low+1)*val;
            if(low!=high){
                lazy[2*idx+1]+=val;
                lazy[2*idx+2]+=val;
            }
            return;
        }
        int mid=(low+high)>>1;
        rangeUpdate(2*idx+1,low,mid,l,r,val);
        rangeUpdate(2*idx+2,mid+1,high,l,r,val);
        seg[idx]=(seg[2*idx+1]+seg[2*idx+2]);
    }
};
