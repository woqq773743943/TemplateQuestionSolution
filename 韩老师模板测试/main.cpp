#include <vector>
#include <unordered_map>
#include<iostream>
using namespace std;

class TemplateBase{
public:
	virtual void insert(void *value) = 0; 
};

unordered_map<string, TemplateBase *> hash_table;

template<typename T>
class BPlusTree:public TemplateBase{
public:
	vector<T> contents;
	void insert(void *value){
		insertInner((T*)value);
	}
private:
	void insertInner(T* value){
		contents.push_back(*value);
	}
};

class Handler{
public:
	Handler(int type,string name){
		this->type = type;
		this->name = name;
	};
	bool createBPlusTree(){
		TemplateBase *bPlusTree;
		if (type == 0){
			bPlusTree = new BPlusTree<int>();
		}
		else if (type == 1){
			bPlusTree = new BPlusTree<string>();
		}
		else if (type == 2){
			bPlusTree = new BPlusTree<float>();
		}
		else if (type == 3){
			bPlusTree = new BPlusTree<double>();
		}
		auto result = hash_table.insert(make_pair(name, bPlusTree));
		if (!result.second){
			cout << "ÒÑÓÐ¸ÃÊ÷" << endl;
			return false;
		}
		else
			return true;
	}
	bool insert(void* value){
		TemplateBase *bPlusTree = hash_table[name];
		bPlusTree->insert(value);
	}
private:
	string name;
	int type;
};


void main(){
	Handler *intTree = new Handler(0,"intTree");
	intTree->createBPlusTree();
	Handler *stringTree = new Handler(1, "stringTree");
	stringTree->createBPlusTree();
	
	int a = 1;
	int *pa = &a;
	hash_table["intTree"]->insert(pa);
	string b = "ccg";
	string *pb = &b;
	hash_table["stringTree"]->insert(pb);
	for (auto i : ((BPlusTree<int>*)hash_table["intTree"])->contents){
		cout << i << endl;
	}
}