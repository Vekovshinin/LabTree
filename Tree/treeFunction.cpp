#include <iostream>
#include "tree.h"
#include <vector>
#include <list>
#include <cmath>
#include <queue>
#include <fstream>

using namespace std;

// конструкторы и деструкторы
template <class T>
Tree<T>::Tree(T data) {
    this->data = data;
    left = right = parent = nullptr;
}

template <class T>
Tree<T>::~Tree() {
    delete_left();
    delete_right();
}

// функции для получения элементов из дерева
template <class T>
T Tree<T>::get_data() {
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

template <class T>
Tree<T>* Tree<T>::get_parent() {
    return parent;
}

template <class T>
Tree<T>* Tree<T>::prev() {
    if (left != nullptr) {
        Tree<T>* temp = left;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp;
    }
    else {
        Tree<T>* temp = this;
        while (temp->parent != nullptr && temp->parent->left == temp) {
            temp = temp->parent;
        }
        return temp->parent;
    }
}

template <class T>
Tree<T>* Tree<T>::next() {
    Tree<T>* current = this;
    if (current->right != nullptr) {
        return current->right->find_min();
    }
    Tree<T>* temp = current->parent;
    while (temp != nullptr && current == temp->right) {
        current = temp;
        temp = temp->parent;
    }
    return temp;
}

// функции добавления элементов в дерево
template <class T>
void Tree<T>::insert(T data) {
    Tree<T>* current = this;
    while (current != nullptr) {
        if (data > current->data) {
            if (current->right != nullptr) {
                current = current->right;
            }
            else {
                current->insert_right(data);
                return;
            }
        }
        else if (data < current->data) {
            if (current->left != nullptr) {
                current = current->left;
            }
            else {
                current->insert_left(data);
                return;
            }
        }
        else return;
    }
}

template <class T>
void Tree<T>::insert_right(T data) {
    Tree<T>* new_node = new Tree(data);
    if (this->right != nullptr) {
        this->right->parent = new_node;
        new_node->right = this->right;
    }
    this->right = new_node;
    new_node->parent = this;
}

template <class T>
void Tree<T>::insert_left(T data) {
    left = new Tree<T>(data);
    left->parent = this;
}

// функции на удаление элементов
template <class T>
void Tree<T>::erase(T data) {
    Tree<T>* to_erase = this->find(data);
    Tree<T>* te_parent = to_erase->parent;
    if (to_erase->left == nullptr && to_erase->right == nullptr) {
        if (te_parent->left == to_erase) {
            te_parent->left == nullptr;
            delete to_erase;
        }
        else {
            te_parent->right = nullptr;
            delete to_erase;
        }
    }
    else if ((to_erase->left != nullptr && to_erase->right == nullptr) || ((to_erase->left == nullptr && to_erase->right != nullptr))) {
        if (to_erase->left == nullptr) {
            if (to_erase == te_parent->left) {
                te_parent->left == to_erase->right;
            }
            else {
                te_parent->right == to_erase->right;
            }
            to_erase->right->parent = te_parent;
        }
        else {
            if (te_parent->left == to_erase) {
                te_parent->left = to_erase->left;
            }
            else {
                te_parent->right = to_erase->left;
            }
            to_erase->left->parent = te_parent;
        }
    }
    else {
        Tree<T>* next = to_erase->next();
        to_erase->data = next->data;
        if (next == next->parent->left) {
            next->parent->left = next->right;
            if (next->right != nullptr) {
                next->right->parent = next->parent;
            }
        }
        else {
            next->parent->right = next->right;
            if (next->right != nullptr) {
                next->right->parent = next->parent;
            }
        }
        delete next;
    }
}

template <class T>
void Tree<T>::delete_left() {
    if (left != NULL) {
        left->delete_left();
        left->delete_right();
        delete left;
    }
}

template <class T>
void Tree<T>::delete_right() {
    if (right != NULL) {
        right->delete_left();
        right->delete_right();
        delete right;
    }
}

template <class T>
Tree<T>* Tree<T>::eject_left() {
    Tree<T>* temp = left;
    left = nullptr;
    if (temp != nullptr) {
        temp->parent = nullptr;
    }
    return temp;
}

template <class T>
Tree<T>* Tree<T>::eject_right() {
    Tree<T>* temp = right;
    right = nullptr;
    if (temp != nullptr) {
        temp->parent = nullptr;
    }
    return temp;
}
// функции поиска элементов в дереве 
template <class T>
Tree<T>* Tree<T>::search(T key) {
    if (data == key) {
        return this;
    }
    if (left != nullptr) {
        Tree<T>* result = left->search(key);
        if (result != nullptr) {
            return result;
        }
    }
    if (right != nullptr) {
        Tree<T>* result = right->search(key);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}

template <class T>
Tree<T>* Tree<T>::find(T data) {
    if (this == nullptr || this->data == data) {
        return this;
    }
    else if (data > this->data) {
        return this->right->find(data);
    }
    else {
        return this->left->find(data);
    }
}

template <class T>
Tree<T>* Tree<T>::find_max() {
    if (this->right == nullptr) {
        return this;
    }
    return this->right->find_max();
}

template <class T>
Tree<T>* Tree<T>::find_min() {
    Tree<T>* min_node = this;
    while (min_node->left != nullptr) {
        min_node = min_node->left;
    }
    return min_node;
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

//функции вывода
// 1) Горизонтальный вывод
template <class T>
void Tree<T>::print_horizontal(int depth) {
    if (right != nullptr) {
        right->print_horizontal(depth + 1);
    }
    for (int i = 0; i < depth; ++i) {
        cout << "   ";
    }
    cout << data << endl;
    if (left != nullptr) {
        left->print_horizontal(depth + 1);
    }
}

template <class T>
void Tree<T>::print_tree(int level) {
    if (this != NULL) {
        this->left->print_tree(level + 1);
        for (int i = 1; i < level; i++) cout << " ";
        cout << this->get_data() << endl;
        this->right->print_tree(level + 1);
    }
}

template <class T>
void Tree<T>::print_info() {
    cout << "                           Корень: " << data << endl << endl;
    if (parent != nullptr) {
        cout << "                   Родительский корень:  " << parent->data << endl;
    }
    if (left != nullptr) {
        cout << "Левый потомок: " << "      " << left->data << "               ";
    }
    if (right != nullptr) {
        cout << "Правый потомок: " << right->data << endl;
    }
}

// 2) Вертикальный вывод и нужные для них функции

template <class T>
int Tree<T>::getHeight() {
    int h1 = 0, h2 = 0, hadd = 0;
    if (this == NULL)return 0;
    if (this->left != NULL) h1 = this->left->getHeight();
    if (this->right != NULL) h2 = this->right->getHeight();
    if (h1 >= h2) return h1 + 1;
    else return h2 + 1;
}

template<class T>
int Tree<T>::getAmountOfNodes() {
    if (this == NULL)return 0;
    if ((this->left == NULL) && (this->right == NULL)) return
        1;
    int l = 0;
    int r = 0;
    if (this->left != NULL) l = this->left->getAmountOfNodes();
    if (this->right != NULL) r = this->right->getAmountOfNodes();
    return (l + r + 1);
}

template <class T>
/* Построчный обход дерева и запись элементов в файл */
void Tree<T>::obh(Tree<T>* node) {
    ofstream f("print.txt");
    /* Кол-во элементов в дереве */
    int amount = node->getAmountOfNodes();
    queue<Tree<T>*> q; // Очередь указателей
    q.push(node);
    // Для начала поместим в очередь корень
    while (!q.empty()) {
        Tree<T>* temp = q.front();
        q.pop();
        f << temp->data << endl;
        /* Если есть левый наследник, то помещаем
        его в очередь для дальнейшей обработки */
        if (temp->left)
            q.push(temp->left);
        /* Если есть правый наследник, то помещаем
        его в очередь для дальнейшей обработки */
        if (temp->right)
            q.push(temp->right);
    }
    f.close();
}

template <class T>
void Tree<T>::printVTree2() {
    obh(this); // Обход дерева и заполнение файла
    ifstream f("print.txt");
    int amount = 0; // Кол-во элементов в дереве
    while (!f.eof()) {
        char str[255];
        f.getline(str, 255);
        amount++;
    }
    f.close();
    amount--; // Кол-во элементов в дереве
    ifstream f1("print.txt");
    int* mas = new int[amount];
    for (int i = 0; i < amount; i++) {
        // Считывание элементов в массив
        char str[255];
        f1.getline(str, 255);
        mas[i] = atoi(str);
    }
    f1.close();
    int height = this->getHeight();
    int count = 0; // Счетчик для вывода
    int* spaces = new int[height];
    // Массив нужных пробелов
    spaces[0] = 0; // При глубине 1 будет 0 пробелов
    for (int i = 1; i < height; i++)
        // Вычисление пробелов
        spaces[i] = spaces[i - 1] * 2 + 1;
    int amount_p = 0; // Кол-во напечатанных элементов
    if (height == 1) {
        cout << mas[0] << endl;
    }
    else {
        /* l – индекс для вывода пробелов |
        вывод всех строк, кроме последней */
        for (int i = 0, l = height - 1; i < height - 1; i++, l--) {
            for (int j = 0, k = 0; j < pow(2, i); j++, k++) {
                if (k == 0) // Вывод первого числа в строке
                    /* Печатаем пробелы */
                    for (int u = 0; u < spaces[l]; u++)
                        cout << " ";
                else {
                    for (int u = 0; u < spaces[l + 1]; u++)
                        cout << " ";
                }
                cout << mas[count++];
                amount_p++;
            }
            cout << endl;
        }
        /* Будет храниться последняя строка */
        int* last_str = new int[pow(2, height - 1)];
        for (int i = 0; i < pow(2, height - 1); i++)
            last_str[i] = 2000000000;
        // amount – это amount_p (кол-во оставшихся элементов) 
        int sch1 = 0;
        // счетчик для последнего массива
        /* Второй счетчик для последнего массива */
        int sch2 = spaces[height - 2] + 1;
        /* Строим массив так, как
        встают элементы в дереве */
        for (int i = amount_p; i < amount; i += 2) {
            if (i <= amount - 1) //если еще есть элементы
            {
                last_str[sch1] = mas[i];
                sch1 += 2;
            }
            if (i + 1 <= amount - 1) {
                last_str[sch2] = mas[i + 1];
                sch2 += 2;
            }
            if (sch1 >= pow(2, height - 1) || sch2 >= pow(2,
                height - 1)) { //Заполняем вторую половину массива
                sch1 = 1;
                sch2 = spaces[height - 2] + 2;
            }
        }
        /* Исправляем неправильное построение массива */
        for (int i = 0; i < pow(2, height - 1); i++)
            if (last_str[i] != 2000000000)
                last_str[i] = mas[amount_p++];
        /* Печатаем последнюю строку */
        for (int i = 0; i < pow(2, height - 1); i++)
            if (last_str[i] != 2000000000)
                cout << last_str[i] << " ";
            else cout << " ";
        delete[] last_str;
        cout << endl;
    }
    delete[] mas;
    delete[] spaces;
}

// прочие функции
template <class T>
void Tree<T>::replace(T data) {
    Tree<T>* search_tree = new Tree<T>();
    list<T> list_1;
    parse(this, list_1);
    for (auto data : list_1) {
        search_tree->insert(data);
    }

    Tree<T>* current = search_tree->find(data);
    if (current == nullptr) return;

    cout << "Затем: " << endl;
    if (current->left == nullptr && current->right == nullptr) {
        current->data = "L";
        search_tree->print_tree(2);
        return;
    }
}

template <class T>
Tree<T>* Tree<T>::balanced(int count) {
    if (count <= 0) {
        return nullptr;
    }
    T data;
    cout << "Введите данные для сбалансированного дерева: "; cin >> data;
    Tree<T>* temp = new Tree<T>(data);
    temp->add_left(balanced(count / 2));
    temp->add_right(balanced(count - count / 2 - 1));
    return temp;
}

template <class T>
void Tree<T>::parse(Tree<T>* current, list<T>& lst) {
    if (current == nullptr) {
        return;
    }
    else {
        lst.push_back(current->get_data());
        parse(current->get_left(), lst);
        parse(current->get_right(), lst);
    }
}

template <class T>
Tree<T>* Tree<T>::copy() {
    Tree<T>* new_tree = new Tree<T>(data);
    if (left != nullptr) {
        new_tree->left = left->copy();
        new_tree->left->parent = new_tree;
    }
    if (right != nullptr) {
        new_tree->right = right->copy();
        new_tree->right->parent = new_tree;
    }
    return new_tree;
}

