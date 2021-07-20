#include <vector>
#include <iostream>

#include "log.h"
#include "Profile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;

const size_t Width = 800;
const size_t Height = 600;

const string Title = "Net drawer";

struct Line
{
	sf::Vertex line[2];
};

bool isDrawing = false;

vector<Line> lines;

void Logic(sf::RenderWindow& window)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		auto position = sf::Mouse::getPosition(window);
		if (!isDrawing)
		{
			Line line;
			line.line[0].position.x = position.x;
			line.line[0].position.y = position.y;
			line.line[0].color = sf::Color::Black;

			line.line[1].position.x = position.x;
			line.line[1].position.y = position.y;
			line.line[1].color = sf::Color::Black;

			lines.push_back(line);
			LOG("Add new line");
			isDrawing = true;
		}
		else
		{
			lines[lines.size() - 1].line[1].position.x = position.x;
			lines[lines.size() - 1].line[1].position.y = position.y;
		}
	}
	else
	{
		isDrawing = false;
	}

	window.clear(sf::Color::White);

#ifndef RELEASE
	for (const auto& item : lines)
	{
		window.draw(item.line, 2, sf::Lines);
		
	}
#endif
	window.display();
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5;

	sf::RenderWindow window(sf::VideoMode(Width, Height), Title, sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Logic(window);
	}

	return 0;
}