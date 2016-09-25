#include <iostream>
#include <string>
#include <vector>

using namespace std;


template<typename T>
class TreeNode {

    public:
    TreeNode(T v) {
        value = v;
        left = NULL;
        right = NULL;
    }

    // releasing allocated memory in destructor to avoid memory leaks
    // one can verify that this is working properly with valgrind: 
    // > valgrind --tool=memcheck --leak-check=yes ./a.out
    ~TreeNode() {
        if (left) delete left;
        if (right) delete right;        
    }
    
    void insert(T a) {
        // a reference to the correct child pointer 
        TreeNode * &child = (a < value) ? left : right;

        // using the reference, we avoided code duplication
        if(!child)
            child = new TreeNode(a);
        else
            child->insert(a);
    }

    void insert(vector<T> & va) {
        // note that one has to use the typename keyword, otherwise does not compile
        for(typename vector<T>::iterator it = va.begin(); it!=va.end(); it++)
            insert(*it); 
    }

    // insertion with easier syntax 
    TreeNode & operator<<(T v) {
        insert(v);
        return *this;
    }

    // prints the contents of the tree in-order (sorted)
    // note that one has to use the friend keyword, otherwise does not compile
    friend ostream& operator<< (ostream & os, const TreeNode & t) {
        if (t.left)
            os << *(t.left) << " ";
        os  << t.value;
        if (t.right)
            os << " " << *(t.right) ;
        return os;
    }

    
    private:

    T value;
    TreeNode * left;
    TreeNode * right;

};



int main(int argc, const char *argv[])
{
    TreeNode<string> ts("hello");
    ts << "world" << "my" << "name" << "is" << "hugo";

    TreeNode<int> ti(9);
    
    ti << 4 << 56 << 1 << -4 << 17 << 22 << 0;

    cout << ts << endl << ti << endl; 


    return 0;
}
