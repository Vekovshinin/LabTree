#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <vector>
using namespace std;




template <typename T>
class Tree
{
private:
	class Node				//вложенный класс - ячейка памяти
	{
	public:
		Node(T data = T(), Node* pLeft = nullptr, Node* pRight = nullptr)		//используется параметр по умолчанию, то есть если мы не передаем указатель, то он автоматически присваивается nullptr
		{									//для поля data также используется параметр по умолчанию, выглядит он как вызов конструктора по умолчанию
			this->data = data;
			this->pLeft = pLeft;
			this->pRight = pRight;
		}
		Node* pLeft;		//хранит указатель на следующий элемент слева
		Node* pRight;		//хранит указатель на следующий элемент справа
		T data;				//хранит наши данные
	};
	int _size;			//количество элементов в списке.
	Node* head;			//указатель на первый элемент в списке
public:
	Tree();								//Конструктор
	~Tree();							//Деструктор
	void insert(T data);				//добавляет элемент в конец списка
	int size() { return this->_size; }		//так как инкапсуляция не дает нам доступ к количеству элементов в списке, то нам необходимо происать геттер
	bool erase(const T& data);				//Удаление элемента
	void clear();						//удаляет все элементы списка (логика как у pop_front, деструктор основан на этой штуке)
	Tree<T>* find(T data);

	void showWidth();						//обход в ширину
	void showStraight();					//прямой обход
	void showDepth();						//обход в глубину
	void showDepthBackward();				//обход в глубину в другую сторону (элементы идут по возрастанию)
	Tree<T>& operator=(const Tree<T>& other);

	Tree<T>* get_data();
	Tree<T>* get_left(); // Возвращает указатель на левое поддерево.
	Tree<T>* get_right(); // Возвращает указатель на правое поддерево.

	// методы обхода дерева
	void direct_way(Tree<T>*); // Обход дерева в прямом порядке.
	void symmetric_way(Tree<T>*); // Обход дерева в симметричном порядке.
	void reverse_way(Tree<T>*); // Обход дерева в обратном порядке.

	// функции для балансировки дерева
	int getHeight(Node* node);
	int getBalanceFactor(Node* node);
	typename Node* rotateLeft(Node* node);
	typename Node* rotateRight(Node* node);
	typename Node* balance(Node* node);

private:
	void HelperDepth(Node* node);
	void HelperDepthBackward(Node* node);
	void HelperClear(Node* node);
	int helpDepth;


};

template<typename T>
Tree<T>::Tree()
{
	this->_size = 0;
	head = nullptr;
	helpDepth = 0;
}

template<typename T>
Tree<T>::~Tree()
{
	this->clear();
}

template<typename T>
void Tree<T>::insert(T data)
{
	if (head == nullptr)
		head = new Node(data);
	else
	{
		Node* temp = this->head;
		while (true)
		{
			if (data < temp->data)
			{
				if (temp->pLeft == nullptr)
				{
					temp->pLeft = new Node(data);
					break;
				}
				else
					temp = temp->pLeft;
			}
			else if (data > temp->data)
				if (temp->pRight == nullptr)
				{
					temp->pRight = new Node(data);
					break;
				}
				else
					temp = temp->pRight;

			else return;
		}
	}
	++_size;
	head = balance(head); //вызов балансировки
}

template<typename T>
bool Tree<T>::erase(const T& data)
{
	Node* prev = head;
	Node* iter = head;
	while (true)
	{
		if (data == iter->data)
		{
			break;
		}
		else if (data < iter->data)
		{
			if (iter->pLeft == nullptr) return false;
			prev = iter;
			iter = iter->pLeft;
		}
		else
		{
			if (iter->pRight == nullptr) return false;
			prev = iter;
			iter = iter->pRight;
		}
	}
	if (iter->pLeft == nullptr && iter->pRight == nullptr)
	{
		if (iter == head)
		{
			delete iter;
			head == nullptr;
		}
		else
		{
			if (prev->pLeft == iter)
				prev->pLeft = nullptr;
			else
				prev->pRight = nullptr;
			delete iter;
		}
	}
	else if (iter->pLeft == nullptr || iter->pRight == nullptr)
	{
		if (iter == head)
		{
			if (iter->pLeft != nullptr)
				head = head->pLeft;
			else
				head = head->pRight;
		}
		else
		{
			if (iter->pLeft != nullptr)
			{
				if (prev->pLeft == iter)
					prev->pLeft = iter->pLeft;
				else
					prev->pRight = iter->pLeft;
			}
			else
			{
				if (prev->pLeft == iter)
					prev->pLeft = iter->pRight;
				else
					prev->pRight = iter->pRight;
			}
		}
		delete iter;
	}
	else
	{
		Node* temp = iter;
		prev = iter;
		iter = iter->pRight;
		while (iter->pLeft != nullptr)
		{
			temp = iter;
			iter = iter->pLeft;
		}
		prev->data = iter->data;
		delete iter;
		temp->pLeft = nullptr;
	}
	--this->_size;
	return true;
}

template<typename T>
void Tree<T>::showWidth()
{
	if (this->head == nullptr) return;
	int j = 0;
	Node* temp;
	queue<Node*> que;
	que.push(this->head);
	while (!que.empty())
	{
		temp = que.front();
		cout << ++j << ". " << temp->data << endl;
		que.pop();
		if (temp->pLeft != nullptr)
			que.push(temp->pLeft);
		if (temp->pRight != nullptr)
			que.push(temp->pRight);
	}
}

template<typename T>
void Tree<T>::showStraight()
{
	if (this->head == nullptr) return;
	int j = 0;
	Node* temp;
	stack<Node*> st;
	st.push(this->head);
	while (!st.empty())
	{
		temp = st.top();
		cout << ++j << ". " << temp->data << endl;
		st.pop();
		if (temp->pRight != nullptr)
			st.push(temp->pRight);
		if (temp->pLeft != nullptr)
			st.push(temp->pLeft);
	}
}

template<typename T>
inline void Tree<T>::HelperDepth(Node* node)
{
	if (node == nullptr) return;
	HelperDepth(node->pLeft);
	cout << ++helpDepth << ". " << node->data << endl;
	HelperDepth(node->pRight);
}

template<typename T>
void Tree<T>::showDepth()
{
	if (this->head != nullptr)
	{
		this->helpDepth = 0;
		this->HelperDepth(this->head);
	}
}

template<typename T>
void Tree<T>::HelperDepthBackward(Node* node)
{
	if (node == nullptr) return;
	HelperDepthBackward(node->pRight);
	cout << ++helpDepth << ". " << node->data << endl;
	HelperDepthBackward(node->pLeft);
}

template<typename T>
void Tree<T>::showDepthBackward()
{
	if (this->head != nullptr)
	{
		this->helpDepth = 0;
		this->HelperDepthBackward(this->head);
	}
}

template<typename T>
inline void Tree<T>::HelperClear(Node* node)
{
	if (node == nullptr) return;
	HelperClear(node->pLeft);
	HelperClear(node->pRight);
	node->pLeft == nullptr;
	node->pRight = nullptr;
	delete node;
}

template<typename T>
void Tree<T>::clear()
{
	if (head != nullptr)
	{
		this->HelperClear(this->head);
		this->_size = 0;
		this->head = nullptr;
	}
}

template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other)
{
	this->clear();
	if (other.head == nullptr) return *this;
	Node* temp;
	stack<Node*> st;
	st.push(other.head);
	while (!st.empty())
	{
		temp = st.top();
		this->insert(temp->data);
		st.pop();
		if (temp->pRight != nullptr)
			st.push(temp->pRight);
		if (temp->pLeft != nullptr)
			st.push(temp->pLeft);
	}
	return *this;
}

template<typename T>
inline Tree<T>* Tree<T>::find(T data)
{
	if (this == nullptr || this->data = data)
	{
		return this;
	}
	else if (data > this->data)
	{
		return this->pRight->find(data);
	}
	else
	{
		return this->left->find(data);
	}
}

template<typename T>
int Tree<T>::getHeight(Node* node)
{
	if (node == nullptr)
		return 0;
	return max(getHeight(node->pLeft), getHeight(node->pRight)) + 1;
}

template<typename T>
int Tree<T>::getBalanceFactor(Node* node)
{
	if (node == nullptr)
		return 0;
	return getHeight(node->pLeft) - getHeight(node->pRight);
}

template<typename T>
typename Tree<T>::Node* Tree<T>::rotateLeft(Node* node)
{
	Node* newRoot = node->pRight;
	node->pRight = newRoot->pLeft;
	newRoot->pLeft = node;
	return newRoot;
}

template<typename T>
typename Tree<T>::Node* Tree<T>::rotateRight(Node* node)
{
	Node* newRoot = node->pLeft;
	node->pLeft = newRoot->pRight;
	newRoot->pRight = node;
	return newRoot;
}

template<typename T>
typename Tree<T>::Node* Tree<T>::balance(Node* node)
{
	if (node == nullptr)
		return nullptr;

	int balanceFactor = getBalanceFactor(node);

	if (balanceFactor > 1) //если левое поддерево выше
	{
		if (getBalanceFactor(node->pLeft) < 0) //условтие балансировки
			node->pLeft = rotateLeft(node->pLeft);
		return rotateRight(node);
	}
	else if (balanceFactor < -1) //правое поддерево выше
	{
		if (getBalanceFactor(node->pRight) > 0)
			node->pRight = rotateRight(node->pRight);
		return rotateLeft(node);
	}

	return node;
}

// функции для получения элементов из дерева
template <class T>
Tree<T>* Tree<T>::get_data() {
	return data;
}

template <class T>
Tree<T>* Tree<T>::get_left() {
	return left;
}

template <class T>
Tree<T>* Tree<T>::get_right() {
	return right;
}

// функции обхода дерева
template <class T>
void Tree<T>::direct_way(Tree<T>* current) {
	if (current == nullptr) {
		return;
	}
	else {
		cout << current->get_data() << " ";
		direct_way(current->get_left());
		direct_way(current->get_right());
	}
}

template <class T>
void Tree<T>::symmetric_way(Tree<T>* tree) {
	if (tree != nullptr) {
		symmetric_way(tree->left);
		cout << tree->data << " ";
		symmetric_way(tree->right);
	}
}

template <class T>
void Tree<T>::reverse_way(Tree<T>* tree) {
	if (tree != nullptr) {
		reverse_way(tree->left);
		reverse_way(tree->right);
		cout << tree->data << " ";
	}
}

