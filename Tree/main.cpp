#include <iostream>
#include "treeFunction.cpp"
#include "tree.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Ru");
	system("chcp 1251 > null");

	Tree<int>* tree = new Tree<int>(10);
	tree->insert_left(7);
	tree->insert_right(15);
	tree->get_left()->insert_left(5);
	tree->get_left()->insert_right(9);
	tree->get_right()->insert_left(12);
	tree->get_right()->insert_right(17);
	cout << "горизонтальный вывод" << endl;
	tree->print_horizontal();
	cout << endl << endl;
	cout << "вертикальный вывод" << endl;
	tree->printVTree2();

	cout << endl << endl;
	Tree<int>* result = tree->find_max();
	cout << "максимальный элемент: ";
	result->print_horizontal();

	Tree<double>* tree1 = new Tree<double>(10.2);
	tree1->insert_left(7.1);
	tree1->insert_right(15.9);
	tree1->get_left()->insert_left(5.4);
	tree1->get_left()->insert_right(9.3);
	tree1->get_right()->insert_left(12.6);
	tree1->get_right()->insert_right(17.8);

	cout << "горизонтальный вывод" << endl;
	tree1->print_horizontal();
	cout << endl << endl;
	cout << "вертикальный вывод  ( только интовые выводит:(  )" << endl;
	tree1->printVTree2();

	cout << endl << endl;
	Tree<double>* result1 = tree1->find_max();
	cout << "максимальный элемент: ";
	result1->print_horizontal();

	return 0;
}