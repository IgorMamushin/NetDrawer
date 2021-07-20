#include <vector>
#include <memory>

#include "log.h"
#include "Profile.h"
#include "Basic.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;

const size_t Width = 800;
const size_t Height = 600;

const string Title = "Net drawer";

vector<shared_ptr<DrawBase>> basic;
shared_ptr<DrawBase> drawing; 

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

		if (drawing == nullptr)
		{
			LOG("Build line");
			drawing = make_shared<Line>(window);
		}

		auto leftButtonEvent = dynamic_pointer_cast<MouseLeftButtonEvent>(drawing);

		if(leftButtonEvent != nullptr)
		{
			leftButtonEvent->event(window);
			basic.push_back(drawing);
		}

		if(drawing->Drawed)
		{
			drawing = nullptr;
		}

		window.clear(sf::Color::White);
		for (const auto& item : basic)
		{
			item->update();
		}
		for (const auto& item : basic)
		{
			item->draw();
		}
		window.display();
	}

	return 0;
}