#include <iostream>
#include <string>

using namespace std;

class Node{
    public:
        string name;
        int weight;
        Node* left;
        Node* right; 
    
    
    
};

class Binary_search_tree{
    private:
        Node* examining_node;
        
    public:
        //Declaration
        Node* root;
        int count;
        int num;
        int temp;
        int min_weight;
        int leaf = 0;
        string possible_duplicate_value;
    
        Binary_search_tree(){
            
            root = nullptr;
        }
        
        bool greater_than_or_less_than_name(string name_at_front_list, string name_on_new_node){
            //intitalizes counter variable for string indices
            int i = 0;
            while ((name_at_front_list[i] != '\0' && name_on_new_node[i] != '\0'))
            {
                if (name_at_front_list[i] == name_on_new_node[i])
                {
                    i++;
                    //ifthey are the same dont do anything
                    continue;
                }
                else
                {
                    if(name_at_front_list[i]>name_on_new_node[i])
                    {
                        return true;
                    }
                    else
                    {
                        if (name_at_front_list[i] < name_on_new_node[i])
                        {
                        return false; //false means that name on the newnode alphabetically comes after name at the front of the list
                        }
                    }
                }
                i++;
            }
            return -1;
        }

        void add(int num, string name){
            Node* n = new Node();
            n->name = name;
            n->weight = num;
            
            if (root == nullptr)
            {
                root = n;
                min_weight = root->weight;
            }
            else{
                    examining_node = root;
                    while (true){
                        //function traverses through current tree and sets a duplicate name in the possible_duplicate_value variable
                        search_duplicate_values(examining_node, name);
                        if (possible_duplicate_value == n->name)
                        {
                            cout<<"Error the name you entered has already been entered please enter a new weight and name"<<endl;
                            delete n;
                            break;
                        }
                        else if (greater_than_or_less_than_name(examining_node->name, n->name) == false){
                            if (examining_node->right == 0)
                            {
                                examining_node->right = n;
                                break;
                            }
                            else{
                                examining_node = examining_node->right;
                            }
                        }
                        else{
                            if (greater_than_or_less_than_name(examining_node->name, n->name) == true){
                                        if (examining_node->left == 0)
                                        {
                                        examining_node->left = n;
                                        break;
                        
                                        }
                                        else{
                                            examining_node = examining_node->left;
                                        }
                                    }
                        }
        
                        }
                            
                    }
                    
                }
                
        
        
            
    void preOrderTraversal(Node* root)
        {
 
            //base case
            if (root == nullptr) {
                return;
            }
            cout<<root->name<<" "<<root->weight<<endl;
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
            
        }
    
    void inOrderTraversal(Node* root){
    
        if (root == nullptr)
        {
            return;
        }
        
        inOrderTraversal(root->left);
        cout<<root->name<<" "<<root->weight<<endl;
        inOrderTraversal(root->right);

    }
    
    void postOrderTraversal(Node* root){
        if (root == nullptr)
        {
            return;
        }
        
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout<<root->name<<" "<<root->weight<<endl;
        
    }
    
    //function goes to left most node as that is the first in alphabteical order
    void find_first_name_alphbt_order(Node* root){
        examining_node = root;
        while (examining_node->left!= nullptr)
        {
            examining_node = examining_node->left;
        }
        cout<<"The first name that comes in alphatbetical order is "<<examining_node->name<<endl;
        
        
    }

    
    int height_func(Node* root){
        if (root == nullptr)
        {
            return -1;
        }
       return max(height_func(root->left), height_func(root->right)) + 1;
       
       
    }
    
    //search func asked in rubric
    void search_func(Node* root, string name)
    {
        if (root == nullptr)
        {
            return;
        }
        search_func(root->left, name);
        search_func(root->right, name);
        if (root->name == name)
        {
            cout<<"The name "<<name<<" exists in the structure and the corresponding weight is "<<root->weight<<endl;
        }
        
    }
    
    //gives number of leaves 
    void num_of_leaves(Node* root){
        
            
        if (root == nullptr)
        {
            return;
        }
        
        num_of_leaves(root->left);
        num_of_leaves(root->right);
        if (root->left == nullptr && root->right == nullptr)
        {
            leaf++;
        }
        
    }
    //finds the lowest weight in the function
    void lowest_weight(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        
        lowest_weight(root->left);
        lowest_weight(root->right);
        if (root->weight < min_weight)
            {
                min_weight = root->weight;
            }
    }
    
    //helper function for add function
    void search_duplicate_values(Node* root, string name)
    {
        if (root == nullptr)
        {
            return;
        }
        
        search_duplicate_values(root->left, name);
        search_duplicate_values(root->right,name);
        if (root->name == name)
        {
            possible_duplicate_value = name; 
        }
    }
    
};

int main(){
    
    //Declare tree object
    Binary_search_tree tree1;
    
    //declaration for input variables
    int weight;
    string name;
    
    
    //for loop is intialized to 16 to also account for the 1 additional duplicate value run
    //the other 15 runs are to enter values into the tree
    cout<<"Please enter a name press enter then enter a weight and press enter"<<endl;
    for (int i = 0; i < 16; i++)
    {
        cin>>weight; 
        cin>>name;
        tree1.add(weight, name);
    }
    

    

    
    
    //traversals
    cout<<"EXECUTING PRE ORDER TRAVERSAL: "<<endl;
    tree1.preOrderTraversal(tree1.root);
    cout<<endl;
    cout<<"EXECUTING IN ORDER TRAVERSAL: "<<endl;
    tree1.inOrderTraversal(tree1.root);
    cout<<endl;
    cout<<"EXECUTING POST ORDER TRAVERSAL: "<<endl;
    tree1.postOrderTraversal(tree1.root);
    cout<<endl<<endl;

    
    cout<<"The height of the tree is "<<tree1.height_func(tree1.root)<<endl;



    tree1.num_of_leaves(tree1.root);
    cout<<"The number of leaves is "<<tree1.leaf<<endl;
    
    cout<<endl;
    cout<<"Please enter a name and if it exists in the tree their weight will be displayed"<<endl;
    cin>>name;
    tree1.search_func(tree1.root, name);
    cout<<endl;
    //stores the lowest weight in min_weight
     tree1.lowest_weight(tree1.root);

     cout<<"The lowest weight in tree is "<<tree1.min_weight<<endl;
     
    tree1.find_first_name_alphbt_order(tree1.root);

}


/*
Last login: Sun Oct  6 15:40:23 on ttys002
/tmp/codelite-exec.sh ; exit;
gotadroponthisflexingpoop@Gots-MBP ~ % /tmp/codelite-exec.sh ; exit;
Please enter a name press enter then enter a weight and press enter
154
Muhammad
125
Musa
100
Talha
125
Yasa
170
Maliooz
130
Musa
Error the name you entered has already been entered please enter a new weight and name
165
Taha
123
Jennie
500
Umar
188
Jack
199
Martin
99
Luther
125
King
400
Benjamin
250
Joe
500
Trump
EXECUTING PRE ORDER TRAVERSAL: 
Muhammad 154
Maliooz 170
Jennie 123
Jack 188
Benjamin 400
Luther 99
King 125
Joe 250
Martin 199
Musa 125
Talha 100
Taha 165
Yasa 125
Umar 500
Trump 500

EXECUTING IN ORDER TRAVERSAL: 
Benjamin 400
Jack 188
Jennie 123
Joe 250
King 125
Luther 99
Maliooz 170
Martin 199
Muhammad 154
Musa 125
Taha 165
Talha 100
Trump 500
Umar 500
Yasa 125

EXECUTING POST ORDER TRAVERSAL: 
Benjamin 400
Jack 188
Joe 250
King 125
Luther 99
Jennie 123
Martin 199
Maliooz 170
Taha 165
Trump 500
Umar 500
Yasa 125
Talha 100
Musa 125
Muhammad 154


The height of the tree is 5
The number of leaves is 5

Please enter a name and if it exists in the tree their weight will be displayed
Trump
The name Trump exists in the structure and the corresponding weight is 500

The lowest weight in tree is 99
The first name that comes in alphatbetical order is Benjamin
Hit any key to continue...

*/