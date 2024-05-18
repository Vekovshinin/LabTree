#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <class T>
class Tree {
public:
    //������������ � ����������
    Tree(T); // ����������� ������, ������������ �������� ���� T
    Tree() { left = right = parent = nullptr; } // ����������� �� ���������, �������������� ��������� left, right, parent ��� nullptr.
    ~Tree(); // ���������� ������

    //�������� ������
    T get_data(); // ���������� �������� data.
    void replace(T); // �������� �������� �������� ���� �� ���������� ��������.
    void delete_left();// ������� ����� ���������.
    void delete_right();// ������� ������ ���������.
    void insert_left(T); // ��������� ����� ���� �� ��������� T � ����� ���������.
    void insert_right(T); // ��������� ����� ���� �� ��������� T � ������ ���������.
    void direct_way(Tree<T>*); // ����� ������ � ������ �������.
    void symmetric_way(Tree<T>*); // ����� ������ � ������������ �������.
    void reverse_way(Tree<T>*); // ����� ������ � �������� �������.
    void parse(Tree<T>*, list<T>&); // ����� ������ � ������ �������� � ���������� ������.
    void print_tree(int); // ������� ������ �� ����� � ��������� �������.
    void delete_tree() { delete this; } // ������� ������.

    // ������� ��� ������������ ������ ������
    int getHeight(); // ���������� ������ ������
    int getAmountOfNodes(); // ���������� ���������� ����� � ������
    void obh(Tree<T>* node);
    void printVTree2();

    //�������������� ������
    void insert(T); // ��������� ����� ���� �� ��������� T � ��������������� ����� � ������.
    void erase(T); // ������� ���� � ��������� ��������� �� ������.
    void add_left(Tree<T>* temp) { left = temp; } // ������������� ����� ���������.
    void add_right(Tree<T>* temp) { right = temp; } // ������������� ������ ���������.
    void print_info(); // ������� ���������� � ������� ����
    void print_horizontal(int depth = 0);   // �������������� ����� ������

    // �������� �������
    Tree<T>* eject_left(); // ������� � ���������� ����� ���������.
    Tree<T>* eject_right(); // ������� � ���������� ������ ���������.
    Tree<T>* get_left(); // ���������� ��������� �� ����� ���������.
    Tree<T>* get_right(); // ���������� ��������� �� ������ ���������.
    Tree<T>* get_parent(); // ���������� ��������� �� ������������ ����.
    Tree<T>* copy(); // ������� ����� �������� ������.
    Tree<T>* search(T); // ������� ������ �� ��������� �����
    Tree<T>* find(T); // ������� ���� � ��������� ���������.
    Tree<T>* next(); // ���������� ��������� �� ��������� ����.
    Tree<T>* prev(); // ���������� ��������� �� ���������� ����.
    Tree<T>* find_min(); // ������� ���� � ����������� ���������.
    Tree<T>* find_max(); // ������� ���� � ������������ ���������.
    Tree<T>* balanced(int); // ������� ���������������� ������ �������� ������.
private:
    Tree<T>* left;
    Tree<T>* right;
    Tree<T>* parent;
    T data;
};