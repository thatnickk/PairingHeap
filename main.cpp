#include <bits/stdc++.h>

using namespace std;

class Node{
    public:
        int key;
        Node *copilStanga;
        Node *copilUrmator;
        Node *prev;
        Node(int key){
            this->key = key;
            copilStanga = NULL;
            copilUrmator = NULL;
            prev = NULL;
        }
};

class PairingHeap{
    Node *root;

    void clean(Node *node){
        if(node != NULL){
            clean(node->copilStanga);
            clean(node->copilUrmator);
            delete node;
        }
    }

    Node *lipire(Node *&one, Node *two){
        if(two == NULL){
            return one;
        }
        if (two->key < one->key){
            two->prev = one->prev;
            one->prev = two;
            one->copilUrmator = two->copilStanga;
            if(one->copilUrmator != NULL){
                one->copilUrmator->prev = one;
            }
            two->copilStanga = one;
            one = two;
            return two;
        }
        else{
            two->prev = one;
            one->copilUrmator = two->copilUrmator;
            if(one->copilUrmator != NULL){
                one->copilUrmator->prev = one;
            }
            two->copilUrmator = one->copilStanga;
            if(two->copilUrmator != NULL){
                two->copilUrmator->prev = two;
            }
            one->copilStanga = two;
            return one;
        }
    }

    Node *twopassmerge(Node *copilPrim){
        if(copilPrim->copilUrmator == NULL){
            return copilPrim;
        }
        vector<Node *> treeArray(5);
        int numCopii = 0;
        while (copilPrim != NULL){
            if(numCopii == treeArray.size()){
                treeArray.resize(numCopii * 2);
            }
            treeArray[numCopii] = copilPrim;
            copilPrim->prev->copilUrmator = NULL;
            copilPrim = copilPrim->copilUrmator;
            numCopii++;
        }
        if(numCopii = treeArray.size()){
            treeArray.resize(numCopii + 1);
        }
        treeArray[numCopii] = NULL;
        int i,j;
        for (i = 0; i + 1 < numCopii; i+=2){
            lipire(treeArray[i], treeArray[i+1]);
        }
        j = i - 2;
        if (j == numCopii - 3){
            lipire(treeArray[j], treeArray[j+2]);
        }
        while (j >= 2){
            lipire(treeArray[j-2], treeArray[j]);
            j-=2;
        }
        return treeArray[0];
    }

    Node *clone(Node *node){
        if (node == NULL){
            return NULL;
        }
        else{
            Node *n = new Node(node->key);
            if((n->copilStanga = clone(node->copilStanga)) != NULL){
                n->copilStanga->prev = n;
            }
            if((n->copilUrmator = clone(node->copilUrmator)) != NULL){
                n->copilUrmator->prev = n;
            }
            return n;
        }
    }


    public:
        PairingHeap(){
            root = NULL;
        }
        PairingHeap(PairingHeap &newone){
            root = NULL;
            *this = newone;
        }
        ~PairingHeap(){
            golire();
        }
        void golire(){
            clean(root);
            root = NULL;
        }
        Node *Insert(int &x){
            Node *newnode = new Node(x);
            if (root == NULL){
                root = newnode;
            }
            else{
                lipire(root, newnode);
            }
            return newnode;
        }
        void Build(vector<int> v){
            for (auto x : v){
                Insert(x);
            }
        }
        int &findMin(){
            return root->key;
        }
        void deleteMin(){
            Node *rootvechi = root;
            if(root->copilStanga == NULL){
                root = NULL;
            }
            else{
                root = twopassmerge(root->copilStanga);
            }
            delete rootvechi;
        }
        void meld(PairingHeap &p){
            root = lipire(root, p.root);
            p.golire();
        }

};

int main(){
    ifstream fin("mergeheap.in");
    ofstream fout("mergeheap.out");
    int n, q, opt, x, m;
    fin >> n >> q;
    vector<PairingHeap> heaps(n);
    for (int i = 0; i < q; i++){
        fin>> opt;
        switch (opt){
            case 1:
                fin>>m;
                fin>>x;
                heaps[m].Insert(x);
                break;
            case 2:

                break;

        }
    }
    return 0;
}
