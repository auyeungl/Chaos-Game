// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>


// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    int seed = 0;
    int verticeSel;
    int pointCount;
    int lastVertex = 0;

    cout << "Enter the number of vertices: ";
    cin >> pointCount;
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "not timber game!1!11!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (seed == 0)
                    {
                        seed = event.mouseButton.x * event.mouseButton.y;
                        srand(seed);
                        cout << "seed: " << seed << endl;
                    }
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < pointCount)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        cout << "new vertex" << endl;
                        
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        cout << "first point" << endl;
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            if (pointCount == 3)
            {
                verticeSel = rand() % pointCount;
                points.push_back(Vector2f((vertices[verticeSel].x + points.back().x) / 2, (vertices[verticeSel].y + points.back().y) / 2));
            }
            else
            {
                verticeSel = rand() % pointCount;
                while (verticeSel == lastVertex)
                {
                    verticeSel = rand() % pointCount;

                }
                lastVertex = verticeSel;
                points.push_back(Vector2f((vertices[verticeSel].x + points.back().x) / 2, (vertices[verticeSel].y + points.back().y) / 2));

            }
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        for(int i = 0; i < points.size(); i++)
        {
            CircleShape rect((1));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        window.display();
    }
}