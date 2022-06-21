#include <SFML/Graphics.hpp>
#include <time.h>
/*
0 - нулевая клетка
1 - 1
2 - 2
3 - 3
4 - 4
5 - 5
6 - 6
7 - 7
8 - 8
9 - бомба
10 - начальная не открытая клетка
11 - флажок
*/

using namespace sf;

int main()
{
 
    srand(time(0));

    RenderWindow window(VideoMode(400, 600), "Minesweeper!"); // окно приложения


    int w = 32;  //размер клетки
    int grid[12][12]; //сетка 
    int sgrid[12][12]; //сетка закрытая

    Texture t;
    t.loadFromFile("tiles.png"); //загрузка текстур
    Sprite tiles(t);

    for (int i = 1; i <= 10; i++)    
        for (int j = 1; j <= 10; j++) {   
            sgrid[i][j] = 10;//заполняем клетками

            if (rand() % 5 == 0) //заполнение бомбочек
                grid[i][j] = 9; //"номер" бомбочки
            else
                grid[i][j] = 0; //"номер" пустой клетки
        }

    for (int i = 1; i <= 10; i++)       //формирования числа, путем поверки клеток вокруг и наличия в них бомбочек
        for (int j = 1; j <= 10; j++) {
            int n = 0;

            if (grid[i][j] == 9)                  
                continue;
            if (grid[i + 1][j] == 9) // если бомба(9) есть, то прибавляется единица
                n++; // где n - переменная-счетчик
            if (grid[i][j + 1] == 9)
                n++;
            if (grid[i - 1][j] == 9)
                n++;
            if (grid[i][j - 1] == 9)
                n++;
            if (grid[i + 1][j + 1] == 9)
                n++;
            if (grid[i - 1][j - 1] == 9)
                n++;
            if (grid[i - 1][j + 1] == 9)
                n++;
            if (grid[i + 1][j - 1] == 9)
                n++;

            grid[i][j] = n; //так и образуется цифра
        }
    for (int i = 1; i <= 10; i++)      
        for (int j = 1; j <= 10; j++)

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / w;
        int y = pos.y / w;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)//нажатие на левую кнопку активирует открытие клетки
                if (event.key.code == Mouse::Left)      //путем замены закрытой клетки на открытую
                    sgrid[x][y] = grid[x][y];


            if (event.type == Event::MouseButtonPressed) //то же действия как у лкм, только сркм
                if (event.key.code == Mouse::Middle)
                    sgrid[x][y] = grid[x][y];

            if (event.type == Event::MouseButtonPressed)//нажатие на правую же делает из клетки(10) 
                if (event.key.code == Mouse::Right) //клетку с флажком(11)
                sgrid[x][y] = 11;
        }
        window.clear(Color::Black);
        for (int i = 1; i <= 10; i++)  
            for (int j = 1; j <= 10; j++) { 
                if (sgrid[x][y] == 9) 
                    sgrid[i][j] = grid[i][j];
                //g/o
                tiles.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                tiles.setPosition(i * w, j * w); 

                window.draw(tiles);
            }
      
        if (sgrid[x][y] == 9) //проверка на открытие бомб
            {
            sf::Font font;
            font.loadFromFile("MaredivRegular.ttf"); //в случае наведения на бомбу, пишет you lose
            Text text1("You Lose!", font, 40);
            text1.setFillColor(Color::Magenta);
            text1.setPosition(80.f, 400.f);
            window.draw(text1);
        }
            sf::Font font;
            font.loadFromFile("MaredivRegular.ttf"); //надпись Minesweeper снизу
            Text text1("Minesweeper", font, 40);
            text1.setFillColor(Color::Magenta);
            text1.setPosition(80.f, 450.f);
            window.draw(text1);

 
     
        window.display();

    }

    return 0;
}