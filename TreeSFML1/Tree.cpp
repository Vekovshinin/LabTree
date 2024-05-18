#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <vector>
using namespace std;

#include "tree.h"

#include <SFML/Graphics.hpp>
int main()
{

	system("chcp 1251 >> null");
	//system("color F0");
	cout << "Создание дерева и вывод консоль." << endl;
	cout << "Обход в ширину:" << endl;
	Tree<double> tr, tr1;
	tr.insert(14.5);
	tr.insert(12.1);
	tr.insert(10.8);
	tr.insert(7.4);
	tr.insert(3.4);
	tr.insert(2.9);
	tr.insert(1.1);
	tr.insert(0.2);
	tr.showWidth();
	cout << endl << endl;

	cout << "Удаление элемента и попытка добавления элемента со значением, которое существует в дереве:" << endl;
	if (tr.erase(2.9)) cout << "Уделение успешно." << endl;
	else cout << "Удаление невозможно." << endl;
	tr.insert(7.4);
	cout << "Прямой обход." << endl;
	tr.showStraight();
	cout << endl << endl;
	cout << "Выполнение оператора присваивания" << endl;
	tr1 = tr;
	cout << "Вывод скопированного дерева." << endl;
	cout << "Обход в глубину." << endl;
	tr1.showDepth();
	cout << endl << endl;

	cout << "Отрисовка полученного дерева." << endl;
	cout << "Внимание на окно." << endl;

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Binary Tree");
	window.setFramerateLimit(10);

	sf::CircleShape shape(40.f);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(3.0f);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
	shape.setPosition(500.f, 48.f);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "Ошибка" << endl;
	}

	sf::Text text;
	text.setFont(font);
	text.setString("7.4");
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);

	vector<pair<sf::CircleShape, sf::Text>> vec;
	vec.resize(8);
	vec[0] = make_pair(shape, text);

	shape.setPosition(300.f, 118.f);
	text.setString("2.9");
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);
	vec[1] = make_pair(shape, text);

	shape.setPosition(700.f, 118.f);
	text.setString("12.1");
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);
	vec[2] = make_pair(shape, text);

	shape.setPosition(200.f, 188.f);
	text.setString("1.1");
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);
	vec[3] = make_pair(shape, text);

	shape.setPosition(400.f, 188.f);
	text.setString("3.4");
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);
	vec[4] = make_pair(shape, text);

	shape.setPosition(600.f, 188.f);
	text.setString("10.8");
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);
	vec[5] = make_pair(shape, text);

	shape.setPosition(800.f, 188.f);
	text.setString("14.5");
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);
	vec[6] = make_pair(shape, text);

	shape.setPosition(130.f, 290.f);
	text.setString("0.2");
	text.setPosition(shape.getPosition().x - 3, shape.getPosition().y - 3);
	vec[7] = make_pair(shape, text);

	sf::RectangleShape line(sf::Vector2f(211, 3));
	vector<sf::RectangleShape> vec_lines;
	vec_lines.resize(7);

	vec_lines[0].setSize(sf::Vector2f(211, 3));
	vec_lines[0].setFillColor(sf::Color::Black);
	vec_lines[0].setPosition(vec[0].first.getPosition());
	vec_lines[0].setRotation(160);

	vec_lines[1].setSize(sf::Vector2f(211, 3));
	vec_lines[1].setFillColor(sf::Color::Black);
	vec_lines[1].setPosition(vec[0].first.getPosition());
	vec_lines[1].setRotation(20);

	vec_lines[2].setSize(sf::Vector2f(122, 3));
	vec_lines[2].setFillColor(sf::Color::Black);
	vec_lines[2].setPosition(vec[1].first.getPosition());
	vec_lines[2].setRotation(145);

	vec_lines[3].setSize(sf::Vector2f(122, 3));
	vec_lines[3].setFillColor(sf::Color::Black);
	vec_lines[3].setPosition(vec[1].first.getPosition());
	vec_lines[3].setRotation(35);

	vec_lines[4].setSize(sf::Vector2f(122, 3));
	vec_lines[4].setFillColor(sf::Color::Black);
	vec_lines[4].setPosition(vec[2].first.getPosition());
	vec_lines[4].setRotation(145);

	vec_lines[5].setSize(sf::Vector2f(123, 3));
	vec_lines[5].setFillColor(sf::Color::Black);
	vec_lines[5].setPosition(vec[2].first.getPosition());
	vec_lines[5].setRotation(35);

	vec_lines[6].setSize(sf::Vector2f(122, 3));
	vec_lines[6].setFillColor(sf::Color::Black);
	vec_lines[6].setPosition(vec[3].first.getPosition());
	vec_lines[6].setRotation(125);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		for (size_t i = 0; i < vec_lines.size(); i++)
		{
			window.draw(vec_lines[i]);
		}

		for (int i = 0; i < vec.size(); i++)
		{
			window.draw(vec[i].first);
			window.draw(vec[i].second);
		}


		window.display();
	}



	return 0;
}