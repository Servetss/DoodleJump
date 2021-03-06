#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <time.h>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <windows.h>

using namespace sf;

struct point
{ int x,y; };



int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(400, 600), "Doodle Game!");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4, t5;

	t1.loadFromFile("E:/fffffffffffffff/Projects/GameSFML/DoodleJump/background.jpg");
	t2.loadFromFile("E:/fffffffffffffff/Projects/GameSFML/DoodleJump/board.png");
	t3.loadFromFile("E:/fffffffffffffff/Projects/GameSFML/DoodleJump/Doodle1.png");
	t4.loadFromFile("E:/fffffffffffffff/Projects/GameSFML/DoodleJump/Doodle2.png");
	t5.loadFromFile("E:/fffffffffffffff/Projects/GameSFML/DoodleJump/Rocket.png");

	Sprite sBackground(t1), sPlate(t2), sPers(t3), sPersB(t4), sRocket(t5);


	point plat[20];
	for (int i = 0; i < 20; i++)
	{
		plat[i].x = 2000;
		plat[i].y = 2000;
	}


	for (int i = 0; i < 10; i++)
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 600;
	}

	Font font;
	Text text("", font, 20);
//	text.setColor(Color::Red);

	int couple[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int x = 100, y = 100, h = 200;
	float dx = 0, dy = 0;
	bool Rotate = false;
	bool Start = true;
	bool Rocket1 = false;
	bool Rocket2 = false;
	int count = 0;
	int rocketSpawn[2] = { 0, 0 };
	int Lenght[2] = {0,0};
	int pos = -1;
	bool GameOver = false;


	if (Start)
	{
		rocketSpawn[1] = rand() % 30;
		rocketSpawn[2] = 0;
		Lenght[1] = 0;
		Lenght[2] = 0;


		Start = false;
	}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Right)) { x += 3; Rotate = true; }
		if (Keyboard::isKeyPressed(Keyboard::Left)) { x -= 3; Rotate = false; }

		app.draw(sBackground);

		dy += 0.2;
		y += dy;
	    if (y > 600) dy = -10;

		
		if (y < h)
		{
			for (int i = 0; i < 20; i++)
			{
						y = h;
						plat[i].y = plat[i].y - dy;


					if (plat[i].y >= 600)
					{
						if (i >= 10)
						{
							plat[i].x = 2000;
							plat[i].y = 2000;
						}

						if (i < 10)
						{
							plat[i].y = 0;
							plat[i].x = rand() % 400;


							if (plat[i].x > 300)
							{
								for (int q = 10; q < 20; q++)
								{
									if (plat[q].x > 400)
									{
										plat[q].y = plat[i].y;
										plat[q].x = plat[i].x - 400;
										break;
									}
								}
							}

							Lenght[2]++;
							if (!Rocket1) pos = i;

						}
					}
				
			}
		}


		for (int i = 0; i < 20 + count; i++)
		{
			if ((x + 87 > plat[i].x) && (x + 0 < plat[i].x + 68) && (y + 100 > plat[i].y) && (y + 100 < plat[i].y + 14) && (dy > 0))
			{
				dy = -10;
				Rocket2 = false;
			}
		}


		if (!Rotate)
		{
			if (x <= -60)
			{
				x = 369;
				sPers.setPosition(x, y);
				app.draw(sPers);
			}
			else
			{
					sPers.setPosition(x, y);
					app.draw(sPers);
			}
		}
		else
		{
			if (x >= 370)
			{
				x = -60;
				sPersB.setPosition(x, y);
				app.draw(sPersB);
			}
			
			else
			{
				sPersB.setPosition(x, y);
				app.draw(sPersB);
			}
		}


		if (Lenght[2] != Lenght[1])
		{
			system("cls");
			std::cout << Lenght[2] << std::endl;
			std::cout << rocketSpawn[2] + rocketSpawn[1] << std::endl;
			std::cout << pos << std::endl;

			std::cout << x << std::endl;

			std::cout << "Y" << std::endl;
			for (int i = 0; i < 20; i++)
				std::cout << "i:"<< i << " = " << plat[i].y << ". ";

			std::cout << std::endl;
			std::cout << "----------------------------------------------------------------------------------------" << std::endl;
			std::cout << "X" << std::endl;
			for (int i = 0; i < 20; i++)
				std::cout << "i:" << i << " = " << plat[i].x << ". ";

			Lenght[1] = Lenght[2];
		}

		if (y > 500)
		{
			std::cout << "Game Over ";
			bool GameOver = true;
		}

		if ((Lenght[2] > 10) && (Lenght[2] >= rocketSpawn[2] + rocketSpawn[1]) && !Rocket1 && !Rocket2)
		{
			Rocket1 = true;
			rocketSpawn[2] = Lenght[2];
			rocketSpawn[1] = 100 + (rand() % 100);
		}


		for (int i = 0; i < 20; i++)
		{
			if (plat[i].y <= 600)
			{
				sPlate.setPosition(plat[i].x, plat[i].y);
				app.draw(sPlate);
			}

				if (Rocket1 && !Rocket2)
				{
					sRocket.setPosition(plat[pos].x, plat[pos].y - 60);
					app.draw(sRocket);

						if ((x + 87 > plat[pos].x) && (x + 0 < plat[pos].x + 68) && (y + 150 > plat[pos].y) && (y + 100 < plat[pos].y + 14))
						{
							dy = -50;
							Rocket1 = false;
							Rocket2 = true;
						}
						else if (plat[pos].y > 599)
							Rocket1 = false;
				}
			
		}

		app.display();
	}

    return 0;
}

