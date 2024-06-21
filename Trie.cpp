class Node{
    Node* a[2]={};
public:
    Node(){    
    }
    bool doesExist(int idx){
        return a[idx]!=NULL;
    }
    void put(int idx,Node*temp){
        a[idx]=temp;
    }
    Node*get(int idx){
        return a[idx];
    }
};
class Trie{
    Node*root;
public:
    Trie(){
        root=new Node();
        insert(0);
    }
    void insert(int val){
        Node*temp=root;
        repr(i,31,0){
            int bit=((val>>i)&1);
            if(!temp->doesExist(bit))
            	temp->put(bit,new Node());
            temp=temp->get(bit);
        }
    }
    
};
