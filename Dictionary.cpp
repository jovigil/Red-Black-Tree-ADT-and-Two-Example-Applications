//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for Dictionary ADT
// joey vigil
// jovigil
// pa8
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include "Dictionary.h"
#define NIL_KEY ""    // chosen value for nil node key
#define NIL_VAL 0       // chosen value for nil node val
#define RED 0           // chosen values for red and black for Node color field
#define BLACK 1

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
   color = BLACK;
}


// Class Constructors & Destructors -------------------------------------------

// Constructor
Dictionary::Dictionary(){
    nil = new Node(NIL_KEY, NIL_VAL);
    nil->parent = nil->right = nil->left = nil;
    root = nil;     // init other Node ptrs to nil since empty dict
    current = nil;
    num_pairs = 0;;
}

// Copy constructor
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node(NIL_KEY, NIL_VAL);
    nil->parent = nil->right = nil->left = nil;
    root = nil;     // init other Node ptrs to nil since empty dict
    current = nil;
    num_pairs = 0;
    if ( D.num_pairs == 0){ return; };  // skip deep copy if D is empty
    preOrderCopy(D.root, D.nil);
    current = D.current;
}

// Destructor
Dictionary::~Dictionary(){
    clear();
    if ( nil != nullptr ){
        delete nil;
        nil = nullptr;
    }
}


// private helpers (members)---------------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if ( R != nil ){
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if ( R != nil ){
        s.append(R->key);
        if ( R->color == RED ){
            s.append(" (RED)");
        }
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M){
    treeInsert(M, root);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if ( R != N ){
        BST_insert(R);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if ( R != nil ){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    while ( R != nil && k != R->key ){  // iterative version of TreeSearch
        if ( k < R->key ){
            R = R->left;
        } else {
            R = R->right;
        }
    }
    return R;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if ( R == nil ){
        return nil; // check for R is leaf case
    }
    Node* Rc = R;
    while ( Rc->left != nil ){
        Rc = Rc->left;
    }
    return Rc;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if ( R == nil ){
        return nil; // check for R is leaf case
    }
    Node* Rc = R;
    while ( Rc->right != nil ){
        Rc = Rc->right;
    }
    return Rc;
}


// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if ( N == nil || findMax(root) == N ){
        return nil; // check for N is tree's max and N is nil cases
    }
    if ( N->right != nil ){
        return findMin(N->right);
    }
    Node* Y = N->parent;
    while ( Y != nil && N == Y->right ){
        N = Y;
        Y = Y->parent;
    }
    return Y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if ( N == nil || findMin(root) == N ){
        return nil; // check for N is tree's max and N is nil cases
    }
    if ( N->left != nil ){
        return findMax(N->left);
    }
    Node*Y = N->parent;
    while ( N != nil && N == Y->left ){
        N = Y;
        Y = Y->parent;
    }
    return Y;
}

// treeInsert()
// Inserts the Node ptd to by R into the tree
// Pre: !contains()
void Dictionary::treeInsert(Node* R, Node* N){
    if ( contains(R->key ) ){
        throw std::invalid_argument("Dictionary: treeInsert(): key already present");
    }
    Node* y = nil;
    Node* x = N;
    while ( x != nil ){
        y = x;
        if ( R->key < x->key ){
            x = x->left;
        } else { x = x->right; }
    }
    R->parent = y;
    if ( y == nil ){
        N = R;
    } else if ( R->key < y->key ){
        y->left = R;
    } else {
        y->right = R;
    }
    num_pairs++;
}

// transplant()
// Replaces the subtree rooted at u with the subtree
// rooted at v.
// Pre: contains(u)
void Dictionary::transplant(Node* u, Node* v){
    if ( u->parent == nil ){
        root = v;
    } else if ( u == u->parent->left ){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if ( v != nil ){
        v->parent = u->parent;
    } 
}


// RBT Helper Functions -------------------------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node* Y = N->right;
    if ( Y == nil ){
        return;     // check assumption
    }
    N->right = Y->left;
    if ( Y->left != nil ){
        Y->left->parent = N;
    }
    Y->parent = N->parent;
    if ( N->parent == nil ){
        root = Y;
    } else if ( N == N->parent->left ){
        N->parent->left = Y;
    } else {
        N->parent->right = Y;
    }
    Y->left = N;
    N->parent = Y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    Node* Y = N->left;
    if ( Y == nil ){
        return;     // check assumption
    }
    N->left = Y->right;
    if ( Y->right != nil ){
        Y->right->parent = N;
    }
    Y->parent = N->parent;
    if ( N->parent == nil ){
        root = Y;
    } else if ( N == N->parent->right ){
        N->parent->right = Y;
    } else {
        N->parent->left = Y;
    }
    Y->right = N;
    N->parent = Y;
}

// RB_Insert()
void Dictionary::RB_Insert(Node* N){
    Node* Y = nil;
    Node* X = root;
    while ( X != nil ){
        Y = X;
        if ( N->key < X->key ){
            X = X->left;
        } else {
            X = X->right;
        }
    }
    N->parent = Y;
    if ( Y == nil ){
        root = N;
    } else if ( N->key < Y->key ){
        Y->left = N;
    } else {
        Y->right = N;
    }
    N->left = nil;
    N->right = nil;
    N->color = RED;
    RB_InsertFixUp(N);
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    Node* Y;
    while ( N->parent->color == RED ){
        if ( N->parent == N->parent->parent->left ){
            Y = N->parent->parent->right;
            if ( Y->color == RED ){
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if ( N == N->parent->right ){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        } else {
            Y = N->parent->parent->left;
            if ( Y->color == RED ){
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            } else {
                if ( N == N->parent->left ){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if ( u->parent == nil ){
        root = v;
    } else if ( u == u->parent->left ){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    Node* W;
    while ( N != root && N->color == BLACK ){
        if ( N == N->parent->left ){
            W = N->parent->right;
            if ( W->color == RED ){
                W->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                W = N->parent->right;
            }
            if ( W->left->color == BLACK &&
            W->right->color == BLACK ){
               W->color = RED;
               N = N->parent; 
            } else {
                if ( W->right->color == BLACK ){
                    W->left->color = BLACK;
                    W->color = RED;
                    RightRotate(W);
                    W = N->parent->right;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            W = N->parent->left;
            if ( W->color == RED ){
                W->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                W = N->parent->left;
            }
            if ( W->right->color == BLACK && 
            W->left->color == BLACK ){
                W->color = RED;
                N = N->parent;
            } else {
                if ( W->left->color == BLACK ){
                    W->right->color = BLACK;
                    W->color = RED;
                    LeftRotate(W);
                    W = N->parent->left;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* X, *Y = N;
    int Y_oc = Y->color;    // save original color
    if ( N->left == nil ){
        X = N->right;
        RB_Transplant(N, N->right);
    } else if ( N->right == nil ){
        X = N->left;
        RB_Transplant(N, N->left);
    } else {
        Y = findMin(N->right);
        Y_oc = Y->color;
        X = Y->right;
        if ( Y->parent == N ){
            X->parent = Y;
        } else {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }
    if ( Y_oc == BLACK ){
        RB_DeleteFixUp(X);
    }
}

// Access functions -----------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if ( search(root, k) != nil ){
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if ( !contains(k) ){    // check precondition
        throw std::invalid_argument("Dictionary: getValue(): key not found");
    }
    Node* K = search(root, k);  // find pair with key == k
    return K->val;              // return the value assctd with it
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if ( current != nil ){
        return true;
    }
    return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if ( current == nil ){    // check precondition
        throw std::logic_error("Dictionary: currentKey(): iterator undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if ( current == nil ){    // check precondition
        throw std::logic_error("Dictionary: currentVal(): iterator undefined");
    }
    return current->val;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;     // init other Node ptrs to nil since empty dict
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* found = search(root, k);
    if ( found != nil ){
        found->key = k;
        found->val = v;
    } else {
        Node* R = new Node(k, v);
        R->left = R->right = R->parent = nil;
        RB_Insert(R);
        if ( num_pairs == 0 ){  // set new node to root if first
            root = R;
        }
    }
    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if ( !contains(k) ){    // check precondition
        throw std::invalid_argument("Dictionary: remove(): key not found");
    }
    Node* Z = search(root, k);  // get ptr to node w/ key==k
    RB_Delete(Z);
    delete Z;
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if ( num_pairs == 0 ) {  return; }   // empty case
    Node* first = findMin(root);
    current = first;    // set current to first
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if ( num_pairs == 0 ) { return; }   // empty case
    Node* last = findMax(root);
    current = last; // set current to last
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if ( current == nil ){    // check precondition
        throw std::logic_error("Dictionary: next(): iterator undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if ( current == nil ){    // check precondition
        throw std::logic_error("Dictionary: prev(): iterator undefined");
    }
    current = findPrev(current);
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    std::string thisWalk;
    inOrderString(thisWalk, root);
    std::string Dwalk;
    D.inOrderString(Dwalk, D.root);
    if ( thisWalk != Dwalk ){
        return false;
    }
    return true;
}


// Overloaded Operators -------------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if ( this != &D ){  // if not self assignment
        Dictionary temp(D);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(nil, temp.nil);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}









