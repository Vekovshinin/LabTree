#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <class T>
class Tree {
public:
    //Конструкторы и деструктор
    Tree(T); // конструктор класса, принимающего значения типа T
    Tree() { left = right = parent = nullptr; } // Конструктор по умолчанию, инициализирует указатели left, right, parent как nullptr.
    ~Tree(); // Деструктор класса

    //Основные методы
    T get_data(); // Возвращает значение data.
    void replace(T); // Заменяет значение текущего узла на переданное значение.
    void delete_left();// Удаляет левое поддерево.
    void delete_right();// Удаляет правое поддерево.
    void insert_left(T); // Вставляет новый узел со значением T в левое поддерево.
    void insert_right(T); // Вставляет новый узел со значением T в правое поддерево.
    void direct_way(Tree<T>*); // Обход дерева в прямом порядке.
    void symmetric_way(Tree<T>*); // Обход дерева в симметричном порядке.
    void reverse_way(Tree<T>*); // Обход дерева в обратном порядке.
    void parse(Tree<T>*, list<T>&); // Обход дерева и запись значений в переданный список.
    void print_tree(int); // Выводит дерево на экран в указанном порядке.
    void delete_tree() { delete this; } // Удаляет дерево.

    // функции для вертикальной печати дерева
    int getHeight(); // возвращает высоту дерева
    int getAmountOfNodes(); // возвращает количество узлов в дереве
    void obh(Tree<T>* node);
    void printVTree2();

    //Дополнительные методы
    void insert(T); // Вставляет новый узел со значением T в соответствующее место в дереве.
    void erase(T); // Удаляет узел с указанным значением из дерева.
    void add_left(Tree<T>* temp) { left = temp; } // Устанавливает левое поддерево.
    void add_right(Tree<T>* temp) { right = temp; } // Устанавливает правое поддерево.
    void print_info(); // Выводит информацию о текущем узле
    void print_horizontal(int depth = 0);   // горизонтальный вывод дерева

    // полезные функции
    Tree<T>* eject_left(); // Удаляет и возвращает левое поддерево.
    Tree<T>* eject_right(); // Удаляет и возвращает правое поддерево.
    Tree<T>* get_left(); // Возвращает указатель на левое поддерево.
    Tree<T>* get_right(); // Возвращает указатель на правое поддерево.
    Tree<T>* get_parent(); // Возвращает указатель на родительский узел.
    Tree<T>* copy(); // Создает копию текущего дерева.
    Tree<T>* search(T); // функция поиска по заданному ключу
    Tree<T>* find(T); // Находит узел с указанным значением.
    Tree<T>* next(); // Возвращает указатель на следующий узел.
    Tree<T>* prev(); // Возвращает указатель на предыдущий узел.
    Tree<T>* find_min(); // Находит узел с минимальным значением.
    Tree<T>* find_max(); // Находит узел с максимальным значением.
    Tree<T>* balanced(int); // Создает сбалансированное дерево заданной высоты.
private:
    Tree<T>* left;
    Tree<T>* right;
    Tree<T>* parent;
    T data;
};