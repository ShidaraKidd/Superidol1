#include <SFML/Graphics.hpp>
#include <time.h>
/*
0 - ������� ������
1 - 1
2 - 2
3 - 3
4 - 4
5 - 5
6 - 6
7 - 7
8 - 8
9 - �����
10 - ��������� �� �������� ������
11 - ������
*/

using namespace sf;

int main()
{
 
    srand(time(0));

    RenderWindow window(VideoMode(400, 600), "Minesweeper!"); // ���� ����������


    int w = 32;  //������ ������
    int grid[12][12]; //����� 
    int sgrid[12][12]; //����� ��������

    Texture t;
    t.loadFromFile("tiles.png"); //�������� �������
    Sprite tiles(t);

    for (int i = 1; i <= 10; i++)    
        for (int j = 1; j <= 10; j++) {   
            sgrid[i][j] = 10;//��������� ��������

            if (rand() % 5 == 0) //���������� ��������
                grid[i][j] = 9; //"�����" ��������
            else
                grid[i][j] = 0; //"�����" ������ ������
        }

    for (int i = 1; i <= 10; i++)       //������������ �����, ����� ������� ������ ������ � ������� � ��� ��������
        for (int j = 1; j <= 10; j++) {
            int n = 0;

            if (grid[i][j] == 9)                  
                continue;
            if (grid[i + 1][j] == 9) // ���� �����(9) ����, �� ������������ �������
                n++; // ��� n - ����������-�������
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

            grid[i][j] = n; //��� � ���������� �����
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

            if (event.type == Event::MouseButtonPressed)//������� �� ����� ������ ���������� �������� ������
                if (event.key.code == Mouse::Left)      //����� ������ �������� ������ �� ��������
                    sgrid[x][y] = grid[x][y];


            if (event.type == Event::MouseButtonPressed) //�� �� �������� ��� � ���, ������ ����
                if (event.key.code == Mouse::Middle)
                    sgrid[x][y] = grid[x][y];

            if (event.type == Event::MouseButtonPressed)//������� �� ������ �� ������ �� ������(10) 
                if (event.key.code == Mouse::Right) //������ � �������(11)
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
      
        if (sgrid[x][y] == 9) //�������� �� �������� ����
            {
            sf::Font font;
            font.loadFromFile("MaredivRegular.ttf"); //� ������ ��������� �� �����, ����� you lose
            Text text1("You Lose!", font, 40);
            text1.setFillColor(Color::Magenta);
            text1.setPosition(80.f, 400.f);
            window.draw(text1);
        }
            sf::Font font;
            font.loadFromFile("MaredivRegular.ttf"); //������� Minesweeper �����
            Text text1("Minesweeper", font, 40);
            text1.setFillColor(Color::Magenta);
            text1.setPosition(80.f, 450.f);
            window.draw(text1);

 
     
        window.display();

    }

    return 0;
}