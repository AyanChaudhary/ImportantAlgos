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

// more general
struct node{
    ll sum;
    ll lazyQ;
    ll lazyVal;
    node(ll sm=0,ll lq=0,ll lv=0){
        sum=sm;
        lazyQ=lq;
        lazyVal=lv;
    }
};
class SGTree{
public:
    vector<node>seg;
    SGTree(int n){
        seg.resize(4*n);
    }
    node merge(node a,node b){
        return node(a.sum+b.sum);
    }
    void push(int idx,int low,int high){
        if(seg[idx].lazyQ!=0){
            if(seg[idx].lazyQ==1){
                seg[idx].sum+=(high-low+1)*seg[idx].lazyVal;
                if(low!=high){
                    if(seg[idx<<1].lazyQ==0)seg[idx<<1].lazyQ=seg[idx].lazyQ;
                    if(seg[idx<<1|1].lazyQ==0)seg[idx<<1|1].lazyQ=seg[idx].lazyQ;
                    seg[idx<<1].lazyVal+=seg[idx].lazyVal;
                    seg[idx<<1|1].lazyVal+=seg[idx].lazyVal;
                }
            }else{
                seg[idx].sum=(high-low+1)*seg[idx].lazyVal;
                if(low!=high){
                    seg[idx<<1].lazyQ=seg[idx].lazyQ;
                    seg[idx<<1|1].lazyQ=seg[idx].lazyQ;
                    seg[idx<<1].lazyVal=seg[idx].lazyVal;
                    seg[idx<<1|1].lazyVal=seg[idx].lazyVal;
                }
            }
            seg[idx].lazyQ=0;
            seg[idx].lazyVal=0;
        }
    }
    void build(int idx,int low,int high,vector<int>&a){
        if(low==high){
            seg[idx].sum=a[low];
            return;
        }
        int mid=(low+high)>>1;
        build(2*idx,low,mid,a);
        build(2*idx+1,mid+1,high,a);
        seg[idx]=merge(seg[2*idx],seg[2*idx+1]);
    }
    node query(int idx,int low,int high,int l,int r){
        push(idx,low,high);
        if(low>r || high<l)return node();
        if(low>=l && high<=r)return seg[idx];
        int mid=(low+high)>>1;
        return merge(query(idx<<1,low,mid,l,r),query(idx<<1|1,mid+1,high,l,r));
    }
    void update(int idx,int low,int high,int l,int r,int op,int val){
        push(idx,low,high);
        if(low>r || high<l)return;
        else if(low>=l && high<=r){
            if(op==1)seg[idx].lazyQ=1;
            else seg[idx].lazyQ=2;
            seg[idx].lazyVal=val;
            push(idx,low,high);
            return;
        }
        int mid=(low+high)>>1;
        update(idx<<1,low,mid,l,r,op,val);
        update(idx<<1|1,mid+1,high,l,r,op,val);
        seg[idx]=merge(seg[idx<<1],seg[idx<<1|1]);
    }
};
      
