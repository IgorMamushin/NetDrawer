#include <vector>
#include <memory>

#include "log.h"
#include "Profile.h"

#include "imgui.h"
#include "imgui-sfml.h"

#include "Basic.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;

const size_t Width = 800;
const size_t Height = 600;

const string Title = "Net drawer";

int main()
{
	vector<shared_ptr<DrawBase>> basic;
	shared_ptr<DrawBase> drawing;

	sf::Color bgColor;
	float color[3] = {0.f, 0.f, 0.f};

	sf::ContextSettings settings;
	settings.antialiasingLevel = 5;

	sf::RenderWindow window(sf::VideoMode(Width, Height), Title, sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		ImGuiIO& io = ImGui::GetIO();

		ImGui::Begin("Select color");
		if (ImGui::ColorEdit3("Background color", color))
		{
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}
		ImGui::End();

		if (drawing == nullptr)
		{
			LOG("Build line");
			drawing = make_shared<Line>(window);
		}

		auto leftButtonEvent = dynamic_pointer_cast<MouseLeftButtonEvent>(drawing);

		if (leftButtonEvent != nullptr)
		{
			leftButtonEvent->event(window, io);
			basic.push_back(drawing);
		}

		drawing->setColor(bgColor);

		window.clear(sf::Color::White);
		if (drawing->Drawed)
		{
			drawing = nullptr;
		}

		for (const auto &item : basic)
		{
			item->update();
		}
		for (const auto &item : basic)
		{
			item->draw();
		}


		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}