#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>

bool is_game = true;

float GetRandomNumber(std::mt19937& random_generator, float from, float to) {
    std::uniform_real_distribution<float> dis(from, to);
    return dis(random_generator);
}
std::mt19937 random_generator(1337);


class Cross
{
public:
    sf::Sprite sprite;
    Cross(std::string file_name,int pos_x, int pos_y)
    {
        sf::Texture *texture;
        texture = new sf::Texture;
        if(!texture->loadFromFile(file_name))
        {
            std::cout << "Nie mozna otworzyc pliku";
        }

        sprite.setTexture(*texture);
        sprite.setScale(0.5714285714285714,0.5714285714285714);
        sprite.setPosition(pos_x,pos_y);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

};

class Circle
{
public:

    sf::Sprite sprite;
    Circle(std::string file_name,int pos_x, int pos_y)
    {
        sf::Texture *texture;
        texture = new sf::Texture;
        if(!texture->loadFromFile(file_name))
        {
            std::cout << "Nie mozna otworzyc pliku";
        }

        sprite.setTexture(*texture);
        sprite.setScale(0.5,0.5);
        sprite.setPosition(pos_x,pos_y);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

};

class Wall
{
public:
    sf::RectangleShape sprite;
    Wall(int pos_x, int pos_y, int width, int height)
    {
        sprite = sf::RectangleShape(sf::Vector2f(width, height));
        sprite.setFillColor(sf::Color(0,0,0));
        sprite.setPosition(pos_x,pos_y);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

    void col(int r,int g, int b)
    {
        sprite.setFillColor(sf::Color(r,g,b));
    }

    void angle(float val)
    {
        sprite.rotate(val);
    }
};

void winner(int free_place[],sf::RenderWindow &window)
{

        if(free_place[0] == free_place[1] && free_place[0] == free_place[2] && free_place[0]!=0)
        {
            Wall wall1(10,100,620,20);
            wall1.col(50, 147, 168);
            wall1.draw(window);
            is_game = false;
        }

        if (free_place[3] == free_place[4] && free_place[3] == free_place[5] && free_place[3]!=0)
        {
            Wall wall1(10,320,620,20);
            wall1.col(50, 147, 168);
            wall1.draw(window);
            is_game = false;
        }

        if(free_place[6] == free_place[7] && free_place[6] == free_place[8] && free_place[6]!=0)
        {
            Wall wall1(10,540,620,20);
            wall1.col(50, 147, 168);
            wall1.draw(window);
            is_game = false;
        }

        if(free_place[0] == free_place[3] && free_place[0] == free_place[6] && free_place[0]!=0)
        {
            Wall wall1(95,10,20,620);
            wall1.col(50, 147, 168);
            wall1.draw(window);
            is_game = false;
        }

        if(free_place[1] == free_place[4] && free_place[1] == free_place[7] && free_place[1]!=0)
        {
            Wall wall1(315,10,20,620);
            wall1.col(50, 147, 168);
            wall1.draw(window);
            is_game = false;
        }

        if(free_place[2] == free_place[5] && free_place[2] == free_place[8] && free_place[2]!=0)
        {
            Wall wall1(535,10,20,620);
            wall1.col(50, 147, 168);
            wall1.draw(window);
            is_game = false;
        }

        if(free_place[0] == free_place[4] && free_place[0] == free_place[8] && free_place[0]!=0)
        {
            Wall wall1(20,10,860,20);
            wall1.col(50, 147, 168);
            wall1.angle(44.7);
            wall1.draw(window);
            is_game = false;
        }

        if(free_place[6] == free_place[4] && free_place[6] == free_place[2] && free_place[6]!=0)
        {
            Wall wall1(5,620,870,20);
            wall1.col(50, 147, 168);
            wall1.angle(-44.7);
            wall1.draw(window);
            is_game = false;
        }



}

int main() {

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(640, 640), "Tic Tac Toe");

    Wall wall1(200,0,20,700);
    Wall wall2(420,0,20,700);
    Wall wall3(0,200,700,20);
    Wall wall4(0,420,700,20);

    std::vector<std::pair<int,int>> slots = {{0,0},{220,0},{440,0},
                                             {0,220},{220,220},{440,220},
                                             {0,440},{220,440},{440,440}};

    int free_place[] = {0,0,0,
                        0,0,0,
                        0,0,0};

    std::vector<Cross> cross_vec;
    std::vector<Circle> circle_vec;



    bool is_cross_player = true;

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && is_game == true)
            {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_cross_player == true)
                {



                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));


                    int i = 0;


                    for ( const std::pair<int,int>  &slot : slots )
                    {

                        if(slot.first <= mouse_position.x && slot.second <= mouse_position.y && (slot.first + 200) >= mouse_position.x && (slot.second + 200) >= mouse_position.y && free_place[i] == 0)
                        {
                            Cross cross("C:/Users/filof/OneDrive/Pulpit/Qt/Project3/tic_tac_toe/x.png", slot.first + 5 ,slot.second + 5);
                            cross_vec.emplace_back(cross);
                            free_place[i] = 1;
                            is_cross_player = false;

                        }
                        i++;

                    }






                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && is_cross_player == false)
                {
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    int i = 0;

                    for ( const std::pair<int,int>  &slot : slots )
                    {

                        if(slot.first <= mouse_position.x && slot.second <= mouse_position.y && (slot.first + 200) >= mouse_position.x && (slot.second + 200) >= mouse_position.y && free_place[i] == 0)
                        {
                            Circle circle("C:/Users/filof/OneDrive/Pulpit/Qt/Project3/tic_tac_toe/o.png",slot.first + 5,slot.second + 5);

                            circle_vec.emplace_back(circle);
                            free_place[i] = 2;

                            is_cross_player = true;

                        }
                        i++;

                    }


                }

            }

        }



        window.clear(sf::Color(188, 194, 126));
        wall1.draw(window);
        wall2.draw(window);
        wall3.draw(window);
        wall4.draw(window);






        for(auto& i:cross_vec)
        {
            i.draw(window);
        }

        for(auto& i:circle_vec)
        {
            i.draw(window);
        }



        winner(free_place,window);


        window.display();

    }

    return 0;
}
