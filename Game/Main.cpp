//Libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>

//Global Variables, funtions, and classes



//main
int main()
{
	//Make
	sf::RenderWindow window(sf::VideoMode(800,600), "SFML Game");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	bool play = true;
	sf::Event event;

	//Font
	sf::Font font;
	if(font.loadFromFile("Data/calibri.ttf") == false)
	{
		return 1;
	}

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(40);
	score.setColor(sf::Color::White);
	score.setPosition(350, 10);
	score.setString("0 : 0");


	//Sounds
	sf::SoundBuffer buff_hit;
	sf::Sound hit;
	hit.setBuffer(buff_hit);
	if(buff_hit.loadFromFile("Data/hit.wav") == false)
	{
		return 1;
	}



	//States
	
	bool up_key = false;
	bool down_key = false;
	bool w_key = false;
	bool s_key = false;



	//Variables
	
	int y_velocity_pad1;
	int y_velocity_pad2;
	int x_velocity_ball = -3;
	int y_velocity_ball = -3;
	int pad1_score = 0;
	int pad2_score = 0;



	//Paddles
	sf::RectangleShape pad_1;
	pad_1.setSize(sf::Vector2f(50,100));
	pad_1.setPosition(50,200);
	pad_1.setFillColor(sf::Color::White);
	//
	sf::RectangleShape pad_2;
	pad_2.setSize(sf::Vector2f(50,100));
	pad_2.setPosition(700,200);
	pad_2.setFillColor(sf::Color::White);
	//Ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(20,20));
	ball.setPosition(350,230);
	ball.setFillColor(sf::Color::White);

	//Game Loop
	while(play == true)
	{
	
//Events
		while(window.pollEvent(event))
		{
			//Key pressing
			
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			{
				up_key = true;
			}

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				down_key = true;
			}

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
			{
				w_key = true;
			}

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				s_key = true;
			}

			//Key releasing

			if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
			{
				up_key = false;
			}

			if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
			{
				down_key = false;
			}

			if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W)
			{
				w_key = false;
			}

			if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
			{
				s_key = false;
			}

			//Exit
			if(event.type == sf::Event::Closed)
			{
				play = false;
			}
		}
	
			
//Logic

		//Pad 1
		if (up_key == true)
		{
			y_velocity_pad1 = -5;
		}
		if (down_key == true)
		{
			y_velocity_pad1 = 5;
		}
		if (up_key == true && down_key == true)
		{
			y_velocity_pad1 = 0;
		}
		if (up_key == false && down_key == false)
		{
			y_velocity_pad1 = 0;
		}

		//Pad 2
		if (w_key == true)
		{
			y_velocity_pad2 = -5;
		}
		if (s_key == true)
		{
			y_velocity_pad2 = 5;
		}
		if (w_key == true && s_key == true)
		{
			y_velocity_pad2 = 0;
		}
		if (w_key == false && s_key == false)
		{
			y_velocity_pad2 = 0;
		}

		//Movement

			//Pads
			
			pad_1.move(0, y_velocity_pad2);
			pad_2.move(0, y_velocity_pad1);

			//Ball

			ball.move(x_velocity_ball, y_velocity_ball);


		//Boundries
		

		if(pad_1.getPosition().y < 0)
		{
			pad_1.setPosition(50, 0);
		}
		if(pad_1.getPosition().y > 500)
		{
			pad_1.setPosition(50, 500);
		}

		if(pad_2.getPosition().y < 0)
		{
			pad_2.setPosition(700, 0);
		}
		if(pad_2.getPosition().y > 500)
		{
			pad_2.setPosition(700, 500);
		}

		//Ball

		if(ball.getPosition().y < 0)
		{
			y_velocity_ball = -y_velocity_ball;
		}
		if(ball.getPosition().y > 585)
		{
			y_velocity_ball = -y_velocity_ball;
		}

		if(ball.getPosition().x < -50)
		{
			pad2_score ++;
			ball.setPosition(300,200);
			y_velocity_ball = y_velocity_ball ++;
			x_velocity_ball = x_velocity_ball --;
			std::cout << y_velocity_ball << "  " << x_velocity_ball << "  ";
		}
		if(ball.getPosition().x > 800)
		{
			pad1_score ++;
			ball.setPosition(300,200);
			y_velocity_ball = y_velocity_ball ++;
			x_velocity_ball = x_velocity_ball --;
			std::cout << y_velocity_ball << "  " << x_velocity_ball << "  ";
		}

		//Colision
		if(ball.getGlobalBounds().intersects(pad_1.getGlobalBounds()) == true)
		{
			x_velocity_ball = -x_velocity_ball;
			hit.play();
		}
		if(ball.getGlobalBounds().intersects(pad_2.getGlobalBounds()) == true)
		{
			x_velocity_ball = -x_velocity_ball;
			hit.play();
		}


//Rendering
		
		window.clear();
		
		//Shapes
		window.draw(pad_1);
		window.draw(pad_2);
		window.draw(ball);


		//Score
		std::stringstream text;
		text << pad1_score << " : " << pad2_score;
		score.setString(text.str());
		window.draw(score);

		//Window
		window.display();

	}

	//End
	window.close();
	return 0;
}

// Jamie's first GAME!!!!