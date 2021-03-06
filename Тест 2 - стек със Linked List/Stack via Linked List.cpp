#include <iostream>
using namespace std;

template<typename T>
struct Node{
	Node * next;
	T data;
	Node() : data(0),next(nullptr){};
	Node(T val) : data(val), next(nullptr){};
	Node(T val, Node * next) : data(val), next(next){};

};


template<typename T>
class Stack{
private:
	Node<T> * head;
public:
	Stack() : head(nullptr) {};
	Stack(const Stack<T> & copy){
		Node<T> * newnode = new Node<T>;
		head = nullptr;
		newnode = copy.head;
		while (newnode){
			this->push(newnode->data);
			newnode = newnode->next;
		}
	}
	void push(T val){
		Node<T> * newnode = new Node<T>(val);
		newnode->next = head;
		head = newnode;
	}
	T pop(){
		Node<T> * newnode = new Node<T>;
		newnode = head;
		head = head->next;
		T val = newnode->data;
		delete newnode;
		return val;
	}
	friend ostream& operator<<(ostream &out, Stack<T> &b){
		Node<T> * newnode = new Node<T>;
		newnode = b.head; // AHAHSHA
		while (newnode){
			out << newnode->data << " ";
			newnode = newnode->next;
		}
		return out;
	}
	 void printReverse(ostream &out){
		Node<T> *newnode = new Node<T>;
		newnode = head;
		int cnt = 1; // UNKNOWN
		
		while (newnode->next){
			cnt++;
			newnode = newnode->next;
		}
		for (int i = cnt; i > 0; i--){
			Node<T>* copyhead = new Node<T>;
			copyhead = head;
			for (int t = 0; t < i - 1; t++)
			{
				copyhead = copyhead->next;
			}
			out << copyhead->data << " ";
		}
		out << endl;
	
	}


};
template <typename T>
void popAndPrint(Stack<T> &stack)
{
	stack.pop();
	cout << stack << endl;
}

int main(int argc, char* argv[])
{
	Stack<int> stack;

	int x;
	while (cin >> x)
	{
		stack.push(x);
	}

	cout << stack.pop() << endl;
	cout << stack.pop() << endl;
	
	cout << stack << endl;
	
	popAndPrint(stack);
	
	cout << stack << endl;
	

	Stack<int> copy;
	copy = stack;
	copy.push(10);

	cout << stack << endl;
	cout << copy << endl;
	
	stack.printReverse(cout);
	
	system("pause");
	return 0;
}
