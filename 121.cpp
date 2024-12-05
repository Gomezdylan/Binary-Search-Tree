#include<iostream>
#include<string>
#include<fstream>
#include<set>
using namespace std;


class record{
        public:
               	string name;
                string species;
                string gender;
                string personality;
                string hobby;
                string birthday;
                string catchphrase;
                string song;
                string style1;
                string style2;
                string color1;
                string color2;
                string wallpaper;
                string flooring;
                string furniture;
                string filename;
                string id;

                record(){}

};

class node{
        public:
               	node *right;
                node *left;
                record *data;
                node(record *newRecord){
                        data = newRecord;
                        left = NULL;
                        right = NULL;
                }
                void insert1(record *r);
                record* search1(string key);
                void inorder();
                void inorder2();
};


class tree{
        public:
               	node *root;
                tree(){
                       	root = NULL;
                }
                void insert1(record *r);
                void insert2(record *r);
                void inorder();
                void inorder2();
                record *search1(string key);
                record *search2(string key);
                record *deleted(string key);
                record *deleted2(string key);


};

class newTree{
        public:
        tree nameTree;  
        tree catchTree; // for catchphrase

        newTree(){}


};
int main(){
	newTree manager;
        ifstream ifile;
        ifile.open("villagers.csv");
        string line;
        getline(ifile, line);
        for(int i = 0; i < 10; i++){
                record *r = new record();
                getline(ifile, r->name, ',');
                getline(ifile, r->species, ',');
                getline(ifile, r->gender, ',');
                getline(ifile, r->personality, ',');
                getline(ifile, r->hobby, ',');
                getline(ifile, r->birthday, ',');
                getline(ifile, r->catchphrase, ',');
                getline(ifile, r->song, ',');
                getline(ifile, r->style1, ',');
                getline(ifile, r->style2, ',');
                getline(ifile, r->color1, ',');
                getline(ifile, r->color2, ',');
                getline(ifile, r->wallpaper, ',');
                getline(ifile, r->flooring, ',');
                getline(ifile, r->furniture, ',');
                getline(ifile, r->filename, ',');
                getline(ifile, r->id);

                manager.nameTree.insert1(r);
                manager.catchTree.insert2(r);
        }
	ifile.close();
        record *r = new record();
        int choice;
        string name;
        string catchphrase;

// ----------------------Menu---------------------------------
        while(true){
        cout << "Choose a number" << endl;
        cout << "     (1) Delete by Name" << endl;
        cout << "     (2) Delete by Catchphrase" << endl;
        cout << "     (3) Search by Name" << endl;
        cout << "     (4) Search by Catchphrase" << endl;
        cout << "     (5) Print in-order by name"  << endl;
        cout << "     (6) Print in-order by Catchphrase" << endl;
        cout << "     (7) Exit" << endl;
        cin >> choice;
// to choose a what tree I want to access just do the other object 
        switch(choice){
                case 1: // Delete by Name
                        cout << "Choose a name you would like to delete" << endl;
                        cin >> name;
                        {
                        record *deletedRecord = manager.nameTree.deleted(name);
                        if(deletedRecord != NULL){
                                manager.catchTree.deleted2(deletedRecord->catchphrase);
                                cout << "Deleted: " << name << endl;
                        } //else{
                            //    cout << "Node was not found!" << endl;
                       // }
                        }
                        break;

                case 2: // Delete by Catchphrase
                        cout << "Choose a catchphrase you would like to delete" << endl;
                        cin >> catchphrase;
                        {
                        record *deletedRecord = manager.catchTree.deleted2(catchphrase);
                        if(deletedRecord != NULL){
                                manager.nameTree.deleted(deletedRecord->name);
                                cout << "Deleted: " << catchphrase << endl;    
                        }
                        }

                        break;

                case 3: // Search by Name
                        cout << "Choose a name you are looking for" << endl;
                        cin >> name;
                        if(manager.nameTree.search1(name)){
                                cout << name << " has been found in the tree" << endl;
                        } else{
                                cout << name << " has not been found in the tree" << endl;
                        }
                        break;
                case 4: // Search by Catchphrase
                        cout << "Choose a catchphrase you are looking for" << endl;
                        cin >> catchphrase;
                        cout << "We are looking for this catchphrase in the tree: " << catchphrase << endl;
                        if(manager.catchTree.search2(catchphrase)){
                                cout << catchphrase << " has been found in the tree" << endl;
                        } else{
                                cout << catchphrase << " has not been found in the tree" << endl;
                        }
                        break;
                case 5: // Print in-order by name
                        manager.nameTree.inorder();
                        break;
                case 6: // Print in-order by catchphrase
                        manager.catchTree.inorder2();
                        break;
                case 7: // Exit the code
                        cout << "Exiting now";
                        return 0;                
                        break;
                default:
                        cout << "You did not choose a valid choice";
                        return 0;

        
        };

        }

}

void node::insert1(record *r){
        if(r->name < data->name){
                if(left == NULL){
                        left = new node(r);
                } else{
                       	left->insert1(r);
                }
        } else{
               	if(right == NULL){
                        right = new node(r);
                } else{
                       	right->insert1(r);
                }
        }
}
record* node::search1(string key){
        if(key == data->name){
                return data;
        }
	if(key < data->name && left != NULL){
                return left->search1(key);
        }
	if(key > data->name && right != NULL){
                return right->search1(key);
        }
return NULL;

}
void tree::insert1(record *r){
        if(root == NULL){
                root = new node(r);
        } else{
               	root->insert1(r);
        }
}


void tree::insert2(record *r){
        node *n = new node(r);
        if(root == NULL){
                root = n;
                return;
        }

        node *current = root;
        node *parent = NULL;

        while(current != NULL){
                parent = current;
                if(r->catchphrase < current->data->catchphrase){
                        current = current->left;
                } else{
                       	current = current->right;
                }
        }

	if(r->catchphrase < parent->data->catchphrase){
                parent->left = n;
        } else{
               	parent->right = n;
        }

}


record *tree::search2(string key){
        node *current = root;
        while(current != NULL){
                if(key == current->data->catchphrase){
                        return current->data;
                }
                if(key < current->data->catchphrase){
                        current = current->left;
 } else{
                       	current = current->right;
                }
        }
return NULL;
}

record *tree::search1(string key){
        if(root == NULL){
                return NULL;
        }
	return root->search1(key);
}
void node::inorder(){
        if(left != NULL){
                left->inorder();
        }
        if(data != NULL){
        cout << data->name << endl;
        }
        if(right != NULL){
                right->inorder();
        }

}
void tree::inorder(){
        if(root == NULL){
                cout << "There is nothing in the tree" << endl;
        } else{
                root->inorder();
        }

}

void node::inorder2(){
        if(left != NULL){
                left->inorder2();
        }
        if(data != NULL){
        cout << data->catchphrase << endl;
        }
        if(right != NULL){
                right->inorder2();
        }

}
void tree::inorder2(){
        if(root == NULL){
                cout << "There is nothing in the tree" << endl;
        } else{
                root->inorder2();
        }

}

record *tree::deleted(string key){
        node *current = root;
        node *parent = NULL;
        record *deletedRecord = NULL;
        // locate the node that we want to delete and keep track of its parent
        while(current != NULL && current->data->name != key){
                parent = current;
                if(key < current->data->name){
                        current = current->left;
                } else{
                        current = current->right;
                }
        }

        // if no node was found 
        if(current == NULL){
                cout << "Node was not found!" << endl;
                return NULL;
        }

        deletedRecord = current->data;

        // deleting the node with no children
        if(current->left == NULL && current->right == NULL){
                if(current == root){
                        root = NULL;
                } else if(parent->left == current){
                        parent->left = NULL;
                } else{
                        parent->right = NULL;
                }
                delete current;
                // Node with only one child
        } else if(current->left == NULL || current->right == NULL){
                node *child = (current->left != NULL) ? current->left : current->right;
                if(current == root){
                        root = child;
                } else if(parent->left == current){
                        parent->left = child;
                } else{
                        parent->right = child;
                }
                delete current;
        } else{
                node *successor = current->right; // smallest node in the right subtree
                node *successorParent = current;
                while(successor->left != NULL){
                        successorParent = successor;
                        successor = successor->left;
                }
                 // replace the current data with the successor
                 current->data = successor->data;
                 if(successorParent->left == successor){
                        successorParent->left = successor->right;
                 } else{
                        successorParent->right = successor->right;
                 }
                 delete successor;
        }
        return deletedRecord;
}
record *tree::deleted2(string key){
        node *current = root;
        node *parent = NULL;
        record *deletedRecord = NULL;
        // locate the node that we want to delete and keep track of its parent
        while(current != NULL && current->data->catchphrase != key){
                parent = current;
                if(key < current->data->catchphrase){
                        current = current->left;
                } else{
                        current = current->right;
                }
        }

        // if no node was found 
        if(current == NULL){
                cout << "Node was not found!" << endl;
                return NULL;
        }

        deletedRecord = current->data;

        // deleting the node with no children
        if(current->left == NULL && current->right == NULL){
                if(current == root){
                        root = NULL;
                } else if(parent->left == current){
                        parent->left = NULL;
                } else{
                        parent->right = NULL;
                }
                delete current;
                // Node with only one child
        } else if(current->left == NULL || current->right == NULL){
                node *child = (current->left != NULL) ? current->left : current->right;
                if(current == root){
                        root = child;
                } else if(parent->left == current){
                        parent->left = child;
                } else{
                        parent->right = child;
                }
                delete current;
        } else{
                node *successor = current->right; // smallest node in the right subtree
                node *successorParent = current;
                while(successor->left != NULL){
                        successorParent = successor;
                        successor = successor->left;
                }
                 // replace the current data with the successor
                 current->data = successor->data;
                 if(successorParent->left == successor){
                        successorParent->left = successor->right;
                 } else{
                        successorParent->right = successor->right;
                 }
                 delete successor;
        }
        return deletedRecord;
}













  