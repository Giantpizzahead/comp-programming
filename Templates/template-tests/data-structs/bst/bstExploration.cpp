/**
Takeaways:
Although order statistic trees are convenient, they are quite hard to extend with custom functionality, so it's not
worth it to use those in contest.
All three of the BBSTs I implemented in this exploration have similar run times. They all run in under a second for
N = 10^6, so they'll definitely work for contest problems where N is only 10^5. So, it comes down to usefulness and
ease of implementation.
AVL trees are useful in that they are just an extension of a plain BST, so you can test your algorithm to make sure it
works for average test cases before coding the balanced part. However, AVL trees are not the easiest to implement, and
they aren't as powerful as treaps or splay trees.
Treaps are probably the easiest to code out of the three, and they make the most intuitive sense to me. In addition,
they can be turned into persistent data structures, an added benefit that the other structures cannot do.
So, when in doubt, use a treap.

Statistics:

N = 1000000, maxNum = 1000000
chances = 1 1 1 1
avl tree:         0.347590s
treap:            0.379694s
normal bst:       0.463977s
splay tree:       0.514569s
order statistics: 0.605214s
segment tree:     1.585885s

N = 1000000, maxNum = 1000000
chances = 10 1 1 1
avl tree:         0.703220s
normal bst:       0.784709s
treap:            0.843544s
splay tree:       0.962887s
order statistics: 1.516426s

N = 10000000, maxNum = 100
chances = 1 1 1 1
normal bst:       0.381928s
treap:            0.503976s
avl tree:         0.532959s
splay tree:       0.932136s

N = 1000000, maxNum = 1000000000
chances = 1 1 1 1
avl tree:         0.359795s
normal bst:       0.471683s
treap:            0.492292s
order statistics: 0.505706s
splay tree:       0.602208s

N = 100000, maxNum = 100000
chances = 1 1 1 1
query numbers are in a somewhat increasing order
avl tree:         0.009451s
treap:            0.009686s
splay tree:       0.015794s
order statistics: 0.038012s
segment tree:     0.063349s
normal bst:       1.591823s
 */

#pragma GCC optimize("O2")
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <sstream>
#include <string>

#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
const int MAXN = 1e7;
const double TLE_TIME = 0.5*4;

int N;
int maxNum;
int insertChance;
int removeChance;
int indexOfChance;
int valueAtChance;
char queryType[MAXN];
int queryX[MAXN], queryA[MAXN];
bool checkAnswers;
vector<int> choices;
unordered_multiset<int> queryNums;

/**
 * reset() = Resets the data structure.
 * size() = Returns the # of elements in the data structure.
 * insert(int x) = Inserts the value x into the data structure.
 * remove(int x) = Deletes the value x from the data structure (if it exists). If multiple elements have this value,
 * only deletes one of them. Returns a bool depending on whether or not the element was found.
 * indexOf(int x) = Returns the index of x in the data structure (# of elements that are smaller), or -1 if the element
 * is not found.
 * valueAt(int i) = Returns the value of the ith smallest element in the data structure, or -1 if i >= size().
 */
struct BaseBST {
    virtual void reset() = 0;
    virtual int size() = 0;
    virtual void insert(int x) = 0;
    virtual bool remove(int x) = 0;
    virtual int indexOf(int x) = 0;
    virtual int valueAt(int i) = 0;
};

/**
 * Naive vector implementation. Keeps a sorted list with naive insertions and deletions.
 * 
 * insert = O(N)
 * remove = O(N)
 * indexOf = O(log(N))
 * valueAt = O(1)
 */
struct SortedVector : public BaseBST {
    vector<int> arr;

    void reset() {
        arr.clear();
    }

    int size() {
        return arr.size();
    }

    void insert(int x) {
        arr.push_back(x);
        for (int i = arr.size() - 1; i > 0; i--) {
            if (arr[i-1] <= arr[i]) break;
            swap(arr[i-1], arr[i]);
        }
    }

    bool remove(int x) {
        for (auto i = arr.begin(); i != arr.end(); i++) {
            if (*i == x) {
                arr.erase(i);
                return true;
            }
        }
        return false;
    }

    int indexOf(int x) {
        auto ptr = lower_bound(arr.begin(), arr.end(), x);
        if (ptr == arr.end() || *ptr != x) return -1;
        else return ptr - arr.begin();
        // for (int i = 0; i < arr.size(); i++) {
        //     if (arr[i] == x) return i;
        // }
        // return -1;
    }

    int valueAt(int i) {
        return (i >= size() ? -1 : arr[i]);
    }
};

/**
 * Multiset implementation. This doesn't help much, since multisets do not store any index information.
 * 
 * insert = O(log(N))
 * remove = O(log(N))
 * indexOf = O(log(N)) if not found, else O(N)
 * valueAt = O(N)
 */
struct SortedSet : public BaseBST {
    multiset<int> ms;

    void reset() {
        ms.clear();
    }

    int size() {
        return ms.size();
    }

    void insert(int x) {
        ms.insert(x);
    }

    bool remove(int x) {
        auto ptr = ms.find(x);
        if (ptr == ms.end()) return false;
        ms.erase(ptr);
        return true;
    }

    int indexOf(int x) {
        auto ptr = ms.find(x);
        if (ptr == ms.end()) return -1;
        // Must do linear search to find # elements smaller
        int i = 0;
        for (auto iter = ms.begin(); iter != ms.end(); iter++) {
            if (ptr == iter) return i;
            i++;
        }
    }

    int valueAt(int i) {
        for (auto iter = ms.begin(); iter != ms.end(); iter++) {
            if (i-- == 0) return *iter;
        }
        return -1;
    }
};

/**
 * Segment tree implmentation. Surprisingly slow when the maximum number is big (due to unordered_map).
 * 
 * insert = O(log(N))
 * remove = O(log(N))
 * indexOf = O(log(N))
 * valueAt = O(log(N))
 */
struct SegmentTree : public BaseBST {
    // vals[i] = # of elements in the range [lb, ub]
    unordered_map<uint, int> vals;

    void reset() {
        vals.clear();
    }

    int size() {
        return vals[1];
    }

    void insert(int i, uint n, int lb, int ub) {
        if (lb == ub) {
            vals[n]++;
            return;
        }
        if (i > (lb+ub)/2) insert(i, n*2+1, (lb+ub)/2+1, ub);
        else insert(i, n*2, lb, (lb+ub)/2);
        vals[n]++;
    }

    void insert(int x) {
        insert(x, 1, 1, maxNum);
    }

    bool exists(int i, uint n = 1, int lb = 1, int ub = maxNum) {
        if (lb == ub) return vals[n] != 0;
        else if (i > (lb+ub)/2) return exists(i, n*2+1, (lb+ub)/2+1, ub);
        else return exists(i, n*2, lb, (lb+ub)/2);
    }

    bool remove(int i, uint n, int lb, int ub) {
        if (lb == ub) {
            vals[n]--;
            return true;
        }
        bool returnVal;
        if (i > (lb+ub)/2) returnVal = remove(i, n*2+1, (lb+ub)/2+1, ub);
        else returnVal = remove(i, n*2, lb, (lb+ub)/2);
        if (returnVal) vals[n]--;
        return returnVal;
    }

    bool remove(int x) {
        if (!exists(x)) return false;
        else return remove(x, 1, 1, maxNum);
    }

    int indexOf(int i, uint n, int lb, int ub) {
        if (lb == ub) return 0;
        else if (i > (lb+ub)/2) return vals[n*2] + indexOf(i, n*2+1, (lb+ub)/2+1, ub);
        else return indexOf(i, n*2, lb, (lb+ub)/2);
    }

    int indexOf(int x) {
        if (!exists(x)) return -1;
        else return indexOf(x, 1, 1, maxNum);
    }

    int valueAt(int i, uint n, int lb, int ub) {
        if (lb == ub) return lb;
        else if (i >= vals[n*2]) return valueAt(i - vals[n*2], n*2+1, (lb+ub)/2+1, ub);
        else return valueAt(i, n*2, lb, (lb+ub)/2);
    }

    int valueAt(int i) {
        if (i >= size()) return -1;
        else return valueAt(i, 1, 1, maxNum);
    }
};

/**
 * Binary search tree implementation, with no self-balancing. The invariant is that all elements on the left are less
 * than the current element, while all elements to the right are greater than the current element. A count is stored
 * at each node to handle mutiple elements with the same value.
 * 
 * insert = O(log(N)) average, O(N) worst
 * remove = O(log(N)) average, O(N) worst
 * indexOf = O(log(N)) average, O(N) worst
 * valueAt = O(log(N)) average, O(N) worst
 */
struct NormalBST : public BaseBST {
    struct Node {
        int v;
        int c = 1;
        int stSize = 1;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int v) : v(v) {}

        void updateSTSize() {
            int leftSTSize = (left ? left->stSize : 0);
            int rightSTSize = (right ? right->stSize : 0);
            stSize = leftSTSize + rightSTSize + c;
        }

        void reset() {
            if (left) left->reset();
            if (right) right->reset();
            delete this;
        }

        void insert(int x) {
            if (x == v) {
                c++;
            } else if (x < v) {
                if (!left) left = new Node(x);
                else left->insert(x);
            } else {
                if (!right) right = new Node(x);
                else right->insert(x);
            }
            updateSTSize();
        }

        Node* furthestRight() {
            if (!right) return this;
            else return right->furthestRight();
        }

        int preRemove(int x) {
            if (x == v) {
                c--;
                stSize--;
                if (c == 0) return 2;
                else return 1;
            } else if (x < v) {
                if (!left) return 0;
                else {
                    int result = left->preRemove(x);
                    updateSTSize();
                    return result;
                }
            } else {
                if (!right) return 0;
                else {
                    int result = right->preRemove(x);
                    updateSTSize();
                    return result;
                }
            }
        }

        Node* remove(int x) {
            if (x == v) {
                Node* newPtr;
                if (left && right) {
                    // Guaranteed that c = 0
                    // Can return either furthest right node in left ST, or furthest left node in right ST
                    newPtr = left->furthestRight();
                    // Set info
                    v = newPtr->v;
                    c = newPtr->c;
                    // Now removing leaf node
                    left = left->remove(newPtr->v);
                    updateSTSize();
                    return this;
                } else {
                    if (!right) newPtr = left;
                    else newPtr = right;
                    delete this;
                    return newPtr;
                }
            } else if (x < v) {
                Node* newLeft = left->remove(x);
                left = newLeft;
                updateSTSize();
                return this;
            } else {
                Node* newRight = right->remove(x);
                right = newRight;
                updateSTSize();
                return this;
            }
        }

        int indexOf(int x) {
            int leftSTSize = (left ? left->stSize : 0);
            int rightSTSize = (right ? right->stSize : 0);
            if (x < v) {
                if (!left) return -1;
                else return left->indexOf(x);
            } else if (x == v) {
                return leftSTSize;
            } else {
                if (!right) return -1;
                else {
                    int returnVal = right->indexOf(x);
                    if (returnVal == -1) return -1;
                    else return leftSTSize + returnVal + c;
                }
            }
        }

        int valueAt(int i) {
            int leftSTSize = (left ? left->stSize : 0);
            int rightSTSize = (right ? right->stSize : 0);
            if (leftSTSize > i) {
                return left->valueAt(i);
            } else if (leftSTSize + c > i) {
                return v;
            } else {
                return right->valueAt(i - leftSTSize - c);
            }
        }

        void print() {
            if (left) {
                cout << "< ";
                left->print();
            }
            cout << "(" << v << ", " << c << ", " << stSize << ") ";
            if (right) {
                cout << "> ";
                right->print();
            }
            cout << "B ";
        }
    };

    Node* root = nullptr;

    void reset() {
        if (root) root->reset();
        root = nullptr;
    }

    int size() {
        if (!root) return 0;
        else return root->stSize;
    }

    void insert(int x) {
        if (!root) root = new Node(x);
        else root->insert(x);
    }

    bool remove(int x) {
        if (!root) return false;
        int preRes = root->preRemove(x);
        if (preRes == 0) return false;
        else if (preRes == 1) return true;

        root = root->remove(x);
        // if (root) root->print();
        // cout << endl;
        return true;
    }

    int indexOf(int x) {
        if (!root) return -1;
        else return root->indexOf(x);
    }

    int valueAt(int i) {
        if (i >= size()) return -1;
        else return root->valueAt(i);
    }
};

/**
 * AVL tree implementation. Uses "balance factors" to ensure that the height of the tree remains logarithmic. Rotations
 * are technically constant time, but they can still be costly.
 * 
 * insert = O(log(N))
 * remove = O(log(N))
 * indexOf = O(log(N))
 * valueAt = O(log(N))
 */
struct AVLTree : public BaseBST {
    struct Node {
        int v, c = 1, s = 1, h = 0, bf = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int v) : v(v) {}

        void merge() {
            int ls = left ? left->s : 0;
            int rs = right ? right->s : 0;
            s = ls + rs + c;
            int lh = left ? left->h : -1;
            int rh = right ? right->h : -1;
            h = max(lh, rh) + 1;
            bf = rh - lh;
        }

        Node* checkBalance() {
            if (bf == -2) {
                if (left->bf <= 0) return leftLeftCase();
                else return leftRightCase();
            } else if (bf > 1) {
                if (right->bf >= 0) return rightRightCase();
                else return rightLeftCase();
            } else {
                return this;
            }
        }

        Node* leftLeftCase() {
            return rotateRight();
        }

        Node* leftRightCase() {
            left = left->rotateLeft();
            return leftLeftCase();
        }

        Node* rightRightCase() {
            return rotateLeft();
        }

        Node* rightLeftCase() {
            right = right->rotateRight();
            return rightRightCase();
        }

        Node* rotateLeft() {
            Node* newRoot = right;
            right = right->left;
            newRoot->left = this;
            merge();
            newRoot->merge();
            return newRoot;
        }

        Node* rotateRight() {
            Node* newRoot = left;
            left = left->right;
            newRoot->right = this;
            merge();
            newRoot->merge();
            return newRoot;
        }

        void reset() {
            if (left) left->reset();
            if (right) right->reset();
            delete this;
        }

        Node* insert(int x) {
            if (x == v) {
                c++;
                s++;
                return this;
            } else if (x < v) {
                if (!left) left = new Node(x);
                else left = left->insert(x);
            } else {
                if (!right) right = new Node(x);
                else right = right->insert(x);
            }
            merge();
            return checkBalance();
        }

        Node* furthestLeft() {
            if (!left) return this;
            else return left->furthestLeft();
        }

        Node* remove(int x) {
            if (x == v) {
                c--;
                s--;
                if (c == 0) {
                    // 'Remove' this node
                    Node* newPtr;
                    if (left && right) {
                        Node* newPtr = right->furthestLeft();
                        c = newPtr->c;
                        v = newPtr->v;
                        newPtr->c = 1;
                        right = right->remove(newPtr->v);
                    } else {
                        if (!left) newPtr = right;
                        else newPtr = left;
                        delete this;
                        return newPtr;
                    }
                }
            } else if (x < v) {
                if (!left) return this;
                else left = left->remove(x);
            } else {
                if (!right) return this;
                else right = right->remove(x);
            }
            merge();
            return checkBalance();
        }

        int indexOf(int x) {
            if (x == v) return (left ? left->s : 0);
            else if (x < v) {
                if (!left) return -1;
                return left->indexOf(x);
            } else {
                if (!right) return -1;
                int res = right->indexOf(x);
                if (res == -1) return -1;
                else return (left ? left->s : 0) + c + res;
            }
        }

        int valueAt(int i) {
            int ls = left ? left->s : 0;
            int rs = right ? right->s : 0;
            if (ls > i) return left->valueAt(i);
            else if (ls + c > i) return v;
            else return right->valueAt(i - ls - c);
        }

        bool checkInvariant() {
            if (bf < -1 || bf > 1) {
                cout << "INVARIANT VIOLATED" << endl;
            }
            if (left) left->checkInvariant();
            if (right) right->checkInvariant();
        }
    };

    Node* root = nullptr;

    void reset() {
        if (root) {
            root->reset();
            root = nullptr;
        }
    }

    int size() {
        return root ? root->s : 0;
    }

    void insert(int x) {
        if (!root) root = new Node(x);
        else root = root->insert(x);
    }

    bool remove(int x) {
        if (!root || indexOf(x) == -1) return false;
        root = root->remove(x);
        return true;
    }

    int indexOf(int x) {
        if (!root) return -1;
        // root->checkInvariant();
        return root->indexOf(x);
    }

    int valueAt(int i) {
        if (i >= size()) return -1;
        // root->checkInvariant();
        return root->valueAt(i);
    }
};

/**
 * Randomized treap implementation. Seems to be just a tiny bit faster than an AVL tree? The difference is so small
 * that it doesn't really matter. I would say that this is easier to implement though (no need to remember 4 cases).
 * 
 * insert = O(log(N))
 * remove = O(log(N))
 * indexOf = O(log(N))
 * valueAt = O(log(N))
 */
struct Treap : public BaseBST {
    struct Node {
        int v, p, c = 1, s = 1;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int v, int p) : v(v), p(p) {}

        void merge() {
            s = (left ? left->s : 0) + (right ? right->s : 0) + c;
        }

        Node* rotateLeft() {
            Node* newRoot = right;
            right = right->left;
            newRoot->left = this;
            merge();
            newRoot->merge();
            return newRoot;
        }

        Node* rotateRight() {
            Node* newRoot = left;
            left = left->right;
            newRoot->right = this;
            merge();
            newRoot->merge();
            return newRoot;
        }

        void reset() {
            if (left) left->reset();
            if (right) right->reset();
            delete this;
        }

        Node* insert(int x, int p) {
            if (x == v) {
                c++;
                s++;
                return this;
            } else if (x < v) {
                if (!left) left = new Node(x, p);
                else left = left->insert(x, p);
                merge();
                if (left && left->p > this->p) return rotateRight();
                else return this;
            } else {
                if (!right) right = new Node(x, p);
                else right = right->insert(x, p);
                merge();
                if (right && right->p > this->p) return rotateLeft();
                else return this;
            }
        }

        Node* meld(Node* a, Node* b) {
            if (!a) return b;
            else if (!b) return a;
            else if (a->p > b->p) {
                // a is new root
                a->right = meld(a->right, b);
                a->merge();
                return a;
            } else {
                // b is new root
                b->left = meld(a, b->left);
                b->merge();
                return b;
            }
        }

        Node* remove(int x) {
            if (x == v) {
                c--;
                s--;
                if (c == 0) {
                    // Remove node by melding children
                    Node* result = meld(left, right);
                    delete this;
                    return result;
                } else return this;
            } else if (x < v) {
                left = left->remove(x);
                merge();
                if (left && left->p > this->p) return rotateRight();
                else return this;
            } else {
                right = right->remove(x);
                merge();
                if (right && right->p > this->p) return rotateLeft();
                else return this;
            }
        }

        int indexOf(int x) {
            int ls = left ? left->s : 0;
            if (x == v) return ls;
            else if (x < v) {
                if (!left) return -1;
                else return left->indexOf(x);
            } else {
                if (!right) return -1;
                else {
                    int res = right->indexOf(x);
                    if (res == -1) return -1;
                    else return ls + c + res;
                }
            }
        }

        int valueAt(int i) {
            int ls = left ? left->s : 0;
            if (ls > i) return left->valueAt(i);
            else if (ls + c > i) return v;
            else return right->valueAt(i - ls - c);
        }

        void checkInvariant() {
            cout << "(" << v << ", " << s << ", " << p << ") ";
            if (left) {
                if (left->p > p) {
                    cout << "LEFT INVARIANT FAILED" << endl;
                    exit(0);
                }
                cout << "< ";
                left->checkInvariant();
            }
            if (right) {
                if (right->p > p) {
                    cout << "RIGHT INVARIANT FAILED" << endl;
                    exit(0);
                }
                cout << "> ";
                right->checkInvariant();
            }
            cout << "B ";
        }
    };

    Node* root = nullptr;

    void reset() {
        if (root) {
            root->reset();
            root = nullptr;
        }    
    }

    int size() {
        if (!root) return 0;
        else return root->s;
    }

    void insert(int x) {
        if (!root) root = new Node(x, rand());
        else root = root->insert(x, rand());
        // root->checkInvariant();
        // cout << endl;
    }

    bool remove(int x) {
        if (!root || root->indexOf(x) == -1) return false;
        else {
            root = root->remove(x);
            return true;
        }
    }

    int indexOf(int x) {
        if (!root) return -1;
        else return root->indexOf(x);
    }

    int valueAt(int i) {
        if (i >= size()) return -1;
        else return root->valueAt(i);
    }
};

/**
 * Splay tree implementation. Not really the cleanest (first time doing it).
 * 
 * All operations are amortized O(log(N)
 */
struct SplayTree : public BaseBST {
    struct Node {
        int v, c = 1, s = 1;
        Node* l = nullptr;
        Node* r = nullptr;

        Node (int v) : v(v) {}
    };

    Node* root = nullptr;

    void reset(Node* n) {
        if (n->l) reset(n->l);
        if (n->r) reset(n->r);
        delete n;
    }

    void merge(Node* n) {
        n->s = (n->l ? n->l->s : 0) + (n->r ? n->r->s : 0) + n->c;
    }

    Node* rotateLeft(Node* n) {
        Node* newRoot = n->r;
        n->r = newRoot->l;
        newRoot->l = n;
        merge(n);
        merge(newRoot);
        return newRoot;
    }

    Node* rotateRight(Node* n) {
        Node* newRoot = n->l;
        n->l = newRoot->r;
        newRoot->r = n;
        merge(n);
        merge(newRoot);
        return newRoot;
    }
    
    // Splays the node with the value x to the root of the tree (or the last accessed element if x is not found).
    Node* splay(Node* n, int x) {
        if (!n || n->v == x) return n;
        else if (x < n->v) {
            if (!n->l) return n;
            if (x < n->l->v) {
                // Zig-zig
                n->l->l = splay(n->l->l, x);
                n = rotateRight(n);
                if (n->l) n = rotateRight(n);
                return n;
            } else if (x > n->l->v) {
                // Zig-zag
                n->l->r = splay(n->l->r, x);
                if (n->l->r) n->l = rotateLeft(n->l);
                if (n->l) n = rotateRight(n);
                return n;
            } else {
                // Zig
                n = rotateRight(n);
                return n;
            }
        } else {
            if (!n->r) return n;
            if (x > n->r->v) {
                // Zag-zag
                n->r->r = splay(n->r->r, x);
                n = rotateLeft(n);
                if (n->r) n = rotateLeft(n);
                return n;
            } else if (x < n->r->v) {
                // Zag-zig
                n->r->l = splay(n->r->l, x);
                if (n->r->l) n->r = rotateRight(n->r);
                if (n->r) n = rotateLeft(n);
                return n;
            } else {
                // Zag
                n = rotateLeft(n);
                return n;
            }
        }
    }

    void splay(int x) {
        root = splay(root, x);
    }

    void reset() {
        if (root) {
            reset(root);
            root = nullptr;
        }
    }

    int size() {
        if (!root) return 0;
        else return root->s;   
    }

    void insert(int x) {
        if (!root) {
            root = new Node(x);
            return;
        }
        splay(x);
        if (root->v == x) {
            root->c++;
            root->s++;
            return;
        }
        Node* n = new Node(x);
        if (root->v < x) {
            n->l = root;
            n->r = root->r;
            root->r = nullptr;
            merge(root);
            root = n;
        } else {
            n->r = root;
            n->l = root->l;
            root->l = nullptr;
            merge(root);
            root = n;
        }
        merge(n);
    }

    Node* join(Node* a, Node* b, int x) {
        if (!a) return b;
        else if (!b) return a;
        b = splay(b, x);
        b->l = a;
        merge(b);
        return b;
    }

    bool remove(int x) {
        splay(x);
        if (!root || root->v != x) return false;
        root->c--;
        root->s--;
        if (root->c == 0) {
            Node* newRoot = join(root->l, root->r, x);
            delete root;
            root = newRoot;
        }
        return true;
    }

    int indexOf(int x) {
        splay(x);
        if (!root || root->v != x) return -1;
        else return root->l ? root->l->s : 0;
    }

    int valueAt(Node* n, int i) {
        int ls = n->l ? n->l->s : 0;
        if (ls > i) return valueAt(n->l, i);
        else if (ls + n->c > i) return n->v;
        else return valueAt(n->r, i - ls - n->c);
    }

    int valueAt(int i) {
        if (i >= size()) return -1;
        int res = valueAt(root, i);
        splay(res);
        return res;
    }

    void print(Node* n) {
        if (!n) return;
        cout << "(" << n->v << ", " << n->s << ") ";
        if (n->l) {
            cout << "< ";
            print(n->l);
        }
        if (n->r) {
            cout << "> ";
            print(n->r);
        }
        cout << "B ";
    }
};

using namespace __gnu_pbds;
struct OrderStatistics : public BaseBST {
    typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
    ordered_set S;
    int t;

    void reset() {
        S.clear();
        t = 0;
    }

    int size() {
        return S.size();
    }

    void insert(int x) {
        S.insert({x, t++});
    }

    bool remove(int x) {
        auto p = S.lower_bound({x, -1});
        if (p == S.end() || p->first != x) return false;
        S.erase(p);
        return true;
    }

    int indexOf(int x) {
        auto p = S.lower_bound({x, -1});
        if (p == S.end() || p->first != x) return -1;
        return S.order_of_key({x, -1});
    }

    int valueAt(int i) {
        if (i >= size()) return -1;
        return S.find_by_order(i)->first;
    }
};

SortedVector sortedVector;
SortedSet sortedSet;
SegmentTree segmentTree;
NormalBST normalBST;
AVLTree avlTree;
Treap treap;
SplayTree splayTree;
OrderStatistics orderStatistics;

inline int randInt(int l, int r) {
    return random() % (r-l+1) + l;
}

void printBST(BaseBST& bst) {
    // if (SplayTree* splay = dynamic_cast<SplayTree*>(&bst)) {
    //     splay->print(splay->root);
    //     cout << endl;
    // }
    cout << "[";
    for (int i = 0; i < bst.size(); i++) {
        if (i != 0) cout << ", ";
        cout << bst.valueAt(i);
    }
    cout << "]" << endl;
}

void testBST(BaseBST& bst, string name) {
    // this_thread::sleep_for(chrono::milliseconds(100));
    name += ':';
    while (name.size() < 18) name += ' ';
    cout << name;
    auto startTime = chrono::system_clock::now();
    for (int i = 0; i < N; i++) {
        int result = 0;
        if (queryType[i] == 'I') {
            // Insert
            bst.insert(queryX[i]);
        } else if (queryType[i] == 'R') {
            // Remove
            result = bst.remove(queryX[i]);
        } else if (queryType[i] == 'L') {
            // Index of
            result = bst.indexOf(queryX[i]);
        } else if (queryType[i] == 'V') {
            // Value at
            result = bst.valueAt(queryX[i]);
        }
        if (checkAnswers && queryA[i] != result) {
            // Wrong answer
            cout << "---WRONG ANSWER---" << endl;
            cout << "Query " << i+1 << ": " << result << " != " << queryA[i] << endl;
            if (bst.size() <= 100) printBST(bst);
            exit(0);
        }
        if (N <= 30) {
            printBST(bst);
        }
        if (i % 5000 == 0) {
            // TLE check
            chrono::duration<double> duration = chrono::system_clock::now() - startTime;
            if (duration.count() > TLE_TIME) {
                cout << "TLE" << endl;
                return;
            }
        }
    }
    chrono::duration<double> duration = chrono::system_clock::now() - startTime;
    cout << duration.count() << "s" << endl;
    bst.reset();
}

void runTests(bool stressTest) {
    N = 500000;
    maxNum = N;
    insertChance = 1;
    removeChance = 1;
    indexOfChance = 1;
    valueAtChance = 1;

    if (stressTest) {
        N = rand() % 30 + 1;
        maxNum = rand() % 10 + 1;
        insertChance = rand() % 5 + 1;
        removeChance = rand() % 5;
        indexOfChance = rand() % 5;
        valueAtChance = rand() % 5;
    }

    auto seed = chrono::system_clock::now().time_since_epoch().count();
    if (N <= 30) cout << "Seed: " << seed << endl;
    srand(seed);

    // Gen queries
    checkAnswers = (N <= 30000);
    for (int i = 0; i < insertChance; i++) choices.push_back('I');
    for (int i = 0; i < removeChance; i++) choices.push_back('R');
    for (int i = 0; i < indexOfChance; i++) choices.push_back('L');
    for (int i = 0; i < valueAtChance; i++) choices.push_back('V');
    random_shuffle(choices.begin(), choices.end());
    for (int i = 0; i < N; i++) {
        querySelect:
        queryType[i] = choices[rand() % choices.size()];
        if (queryType[i] == 'I') {
            // Insert
            queryX[i] = randInt(1, maxNum);
            // queryX[i] = randInt(max(i-100, 1), min(i+100, maxNum));
            queryNums.insert(queryX[i]);
            if (checkAnswers) {
                sortedVector.insert(queryX[i]);
                queryA[i] = 0;
            }
        } else if (queryType[i] == 'R') {
            // Remove
            queryX[i] = randInt(1, maxNum);
            // queryX[i] = randInt(max(i-100, 1), min(i+100, maxNum));
            if (queryNums.count(queryX[i])) queryNums.erase(queryNums.find(queryX[i]));
            if (checkAnswers) queryA[i] = sortedVector.remove(queryX[i]);
        } else if (queryType[i] == 'L') {
            // Index of
            queryX[i] = randInt(1, maxNum);
            if (checkAnswers) queryA[i] = sortedVector.indexOf(queryX[i]);
        } else if (queryType[i] == 'V') {
            // Value at
            if (queryNums.empty()) goto querySelect;
            queryX[i] = randInt(0, queryNums.size());
            if (checkAnswers) queryA[i] = sortedVector.valueAt(queryX[i]);
        }
        if (N <= 30) {
            stringstream sstream;
            sstream << i+1 << ": " << queryType[i] << " " << queryX[i] << " = " << queryA[i];
            string str = sstream.str();
            while (str.size() < 24) str += ' ';
            cout << str;
            printBST(sortedVector);
        }
    }
    queryNums.clear();
    sortedVector.arr.clear();

    cout << fixed << endl;
    cout << "N = " << N << ", maxNum = " << maxNum << endl;
    cout << "chances = " << insertChance << " " << removeChance << " " << indexOfChance << " " << valueAtChance << endl;
    cout << endl;

    testBST(orderStatistics, "order statistics");
    testBST(splayTree, "splay tree");
    testBST(treap, "treap");
    testBST(avlTree, "avl tree");
    testBST(normalBST, "normal bst");
    testBST(segmentTree, "segment tree");
    testBST(sortedSet, "sorted set");
    testBST(sortedVector, "sorted vector");
}

int main() {
    for (int i = 0; i < 1; i++) {
        runTests(false);
        cout << endl;
    }
}