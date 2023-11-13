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
    int pointCount = 0;
    int lastVertex = 0;
    string input;
    Text text;
    // Create a video mode object
	VideoMode vm(1920, 1080);
    
	// Create and open a window for the game
	RenderWindow window(vm, "not timber game!1!11!", Style::Default);
    window.setFramerateLimit(120);
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
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128 && event.text.unicode != 8)
                {
                    input += static_cast<char>(event.text.unicode);
                }
            
              
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Backspace)
                {
                    if (input.length() > 0)
                    {
                        input.pop_back();
                    }
                }
                if (event.key.scancode == sf::Keyboard::Scan::Enter)
                {
                    try {


                        if (stoi(input) >= 3 && stoi(input) <= 7)
                        {
                            pointCount = stoi(input);
                        }
                    }
                    catch (...)
                    {

                    }
                }
            }

           





            if (event.type == sf::Event::MouseButtonPressed && pointCount != 0)
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
        RectangleShape box(Vector2f(25,25));

        Text vertexPrompt;
        Font comic;
        
        box.setPosition(700, 55);
        try
        {
            if (stoi(input) >= 3 && stoi(input) <= 7)
            {
                box.setFillColor(Color::Green);
            }
            else
            {
                box.setFillColor(Color::Red);
            }
        }
        catch (...)
        {
            box.setFillColor(Color::Red);
        }
        if (!comic.loadFromFile("comic.ttf"))
        {
            //window.close();
        }
        else
        {
            vertexPrompt.setFont(comic);
            if (pointCount == 0)
            {
                vertexPrompt.setString("Input the number of vertices (in range 3-7, enter to confirm): " + input + "_");
                window.draw(box);

            }
            else
            {
                vertexPrompt.setString("Vertex count inputted; chaos gaming with a " + to_string(pointCount) + "-agon :)");
            }
            vertexPrompt.setCharacterSize(24);
            vertexPrompt.setFillColor(Color::White);
            vertexPrompt.setPosition(20, 20);
            window.draw(vertexPrompt);
        }
        
        for(int i = 0; i < points.size(); i++)
        {
            CircleShape rect(.75);
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
        for (int i = 0; i < vertices.size(); i++)
        {
            CircleShape vert((2));
            vert.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            vert.setFillColor(Color::Green);
            window.draw(vert);
        }
        window.display();
    }
}