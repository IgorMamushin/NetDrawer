#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "imgui.h"

class MouseLeftButtonEvent
{	
public:
	virtual ~MouseLeftButtonEvent();
	bool event(sf::RenderWindow&, ImGuiIO&);

protected:
	virtual void LeftClick(sf::Vector2i) = 0;

private:
	static bool mouseDown_;
};

class DrawBase
{
public:
	bool Drawed;

	DrawBase(sf::RenderWindow& window);
	virtual ~DrawBase();

	virtual void setColor(sf::Color) = 0;

	virtual void update() = 0;

	virtual void draw() = 0;

protected:
	sf::RenderWindow& window_;
};

class Line : public DrawBase, public MouseLeftButtonEvent
{
private:
	sf::Vertex startPosition;
	sf::Vertex endPosition;
	bool isDrawing;
public:
	Line(sf::RenderWindow&);
	~Line();

	void setColor(sf::Color) override;

	void update() override;

	void draw() override;

	void LeftClick(sf::Vector2i) override;
};
