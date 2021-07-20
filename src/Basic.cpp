#include "Basic.h"
#include "log.h"

bool MouseLeftButtonEvent::mouseDown_;

MouseLeftButtonEvent::~MouseLeftButtonEvent(){
}

bool MouseLeftButtonEvent::event(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(!MouseLeftButtonEvent::mouseDown_)
		{
			MouseLeftButtonEvent::mouseDown_ = true;
			LOG("MOUSE LEFT BUTTON EVENT");
			LeftClick(sf::Mouse::getPosition(window));
			return true;
		}
	}
	else
	{
		MouseLeftButtonEvent::mouseDown_ = false;
	}

	return false;
}

DrawBase::DrawBase(sf::RenderWindow& window) 
	: Drawed(false),
	 window_(window)
{
}

DrawBase::~DrawBase()
{
}

Line::Line(sf::RenderWindow& window) 
	: DrawBase(window)
{
	auto position = sf::Mouse::getPosition(window);

	startPosition.position.x = position.x;
	startPosition.position.y = position.y;
	startPosition.color = sf::Color::Black;

	endPosition.position.x = position.x;
	endPosition.position.y = position.y;
	endPosition.color = sf::Color::Black;
}

void Line::LeftClick(sf::Vector2i pos)
{
	if(!isDrawing)
	{
		startPosition.position.x = pos.x;
		startPosition.position.y = pos.y;
		startPosition.color = sf::Color::Black;

		endPosition.position.x = pos.x;
		endPosition.position.y = pos.y;
		endPosition.color = sf::Color::Black;

		isDrawing = true;
	}
	else
	{
		Drawed = true;
		isDrawing = false;
	}
}

void Line::update()
{
	if(!isDrawing)
	{
		return;
	}

	auto position = sf::Mouse::getPosition(window_);

	endPosition.position.x = position.x;
	endPosition.position.y = position.y;
}

void Line::draw()
{
	sf::Vertex v[2]{ startPosition, endPosition };
	window_.draw(v, 2, sf::Lines);
}

Line::~Line()
{
}