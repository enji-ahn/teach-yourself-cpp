#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cstdint>
#include <cassert>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct Position {
	float x;
	float y;

	explicit Position(float const& _x,
					  float const& _y): x(_x), y(_y) {}
};


struct Velocity {
	float x;
	float y;

	Velocity(float const& _x,
			 float const& _y): x(_x), y(_y) {}
};

struct Object : public Position {
	explicit Object(float const& _x,
					float const& _y): Position(_x, _y) {}
};

struct Bullet {
	Position p;
	Velocity v;

	Bullet() : p(0, 0), v(0,0) {}
};

void init_aiming_bullet(float mx, /// target position (x)
						float my, /// target position (y)
						float ex, /// source position (x)
						float ey, /// source position (y)
						float speed,
						float& x, /// bullet position (x)
						float& y, /// bullet position (y)
						float& vx, /// bullet speed vector
						float& vy) /// bullet speed vector
{
	x = ex;
	y = ey;

	float d = ::sqrt((mx-ex)*(mx-ex)+(my-ey)*(my-ey));
	if (d)
	{
		vx = (mx-ex) / d * speed;
		vy = (my-ey) / d * speed;
	}
	else
	{
		vx = 0;
		vy = speed;
	}
}

void move_aiming_bullet(float& x,
						float& y,
						float const& vx,
						float const& vy)
{
	x += vx;
	y += vy;
}

int main(void)
{
	auto ship = Object{100.f, 100.f};
	auto turret = Object{200.f, 200.f};
	auto speed = 3.3f;
	auto bullet = Bullet{};

	init_aiming_bullet(ship.x, ship.y,
					   turret.x, turret.y,
					   speed,
					   bullet.p.x, bullet.p.y,
					   bullet.v.x, bullet.v.y);

	std::cout<<"initial bullet position x : "<<bullet.p.x<<", y : "<<bullet.p.y<<std::endl;
	std::cout<<"initial bullet velocity x : "<<bullet.v.x<<", y : "<<bullet.v.y<<std::endl;


	for (auto i = 0; i < 100; ++i)
	{
		move_aiming_bullet(bullet.p.x, bullet.p.y, bullet.v.x, bullet.v.y);

		std::cout<<"bullet position x : "<<bullet.p.x<<", y : "<<bullet.p.y<<std::endl;
#if 0
		std::cout<<"bullet velocity x : "<<bullet.v.x<<", y : "<<bullet.v.y<<std::endl;
#endif
	}

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return EXIT_SUCCESS;
}

