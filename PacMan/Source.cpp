﻿#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <vector>
#include <math.h>

using namespace sf;

class Food;
class Map; 

class GameSettings {
private:
    std::string windowTitle;
    sf::Color pacmanColor;
    sf::Color squareColor;
    sf::Color smallCircleColor;
    sf::Color biglCircleColor;
    sf::Color blinkyColor;
    sf::Color pinkyColor;
    sf::Color inkyColor;
    sf::Color clydeColor;
    int gridSize;
    int pacmanStartX;
    int pacmanStartY;

public:
    ~GameSettings() {};
    GameSettings() {};
    GameSettings(std::string windowTitle, int gridSize,
        int pacmanStartX, int pacmanStartY,
        sf::Color pacmanColor, sf::Color squareColor, sf::Color smallCircleColor,
        sf::Color biglCircleColor, sf::Color blinkyColor, sf::Color pinkyColor,
        sf::Color inkyColor, sf::Color clydeColor) : windowTitle(windowTitle), gridSize(gridSize),
        pacmanStartX(pacmanStartX), pacmanStartY(pacmanStartY), pacmanColor(pacmanColor), squareColor(squareColor), smallCircleColor(smallCircleColor),
        biglCircleColor(biglCircleColor), blinkyColor(blinkyColor), pinkyColor(pinkyColor), inkyColor(inkyColor), clydeColor(clydeColor) {};
    std::string getWindowTitle() const { return windowTitle; }
    int getGridSize() const { return gridSize; }
    int getPacmanStartX() const { return pacmanStartX; }
    int getPacmanStartY() const { return pacmanStartY; }
    sf::Color getPacmanColor() const { return pacmanColor; }
    sf::Color getSquareColor() const { return squareColor; }
    sf::Color getCircleColor() const { return smallCircleColor; }
    sf::Color getCircle2Color() const { return biglCircleColor; }
    sf::Color getBlinkyColor() const { return blinkyColor; }
    sf::Color getPinkyColor() const { return pinkyColor; }
    sf::Color getInkyColor() const { return inkyColor; }
    sf::Color getClydeColor() const { return clydeColor; }
};

class Pacman {
private:
    int x, y, nextX, nextY, score, nextDirection, lives, points;
    static int maxPoints;
public:
    ~Pacman() {};
    Pacman(int x, int y, int nextX, int nextY, int score, int nextDirection, int lives, int points) : x(x), y(y), nextX(nextX), nextY(nextY), score(score), nextDirection(nextDirection), lives(lives), points(points) {};
    int getX() const { return x; }
    int getY() const { return y; }
    int getPoints() const { return points; }
    int getLives() const { return lives; }
    int getNextDirection() const { return nextDirection; }
    void setX(int a) { x = a; }
    void setY(int a) { y = a; }
    void setNextX(int a) { nextX = a; }
    void setNextY(int a) { nextY = a; }
    void setScore(int a) { score = a; }
    void setLives(int a) { lives = a; }
    void setPoints(int a) { points = a; }
    void setNextDirection(int a) { nextDirection = a; }
    void loseLife() { lives--; }
    void addPoints(int points) { this->points += points; }                                  //оператор this
    static int getMaxPoints(); // объявление статического метода
    static void updateMaxPoints(int newPoints);
    int* getPointsPointer() {
        return &points; // Возвращаем указатель на переменную score
    }
    int& getLivesReference() {
        return lives; // Возвращаем ссылку на переменную lives
    }

    void PacmanMove(Map& map, Food& smallFood, Food& bigFood);

    int WonOrLost(Food smallFood, Food bigFood, Text& Result);
};


int Pacman::maxPoints = 0; // Инициализация статической переменной
// Реализация статического метода
int Pacman::getMaxPoints() {
    return maxPoints;
}

// Реализация статического метода
void Pacman::updateMaxPoints(int newScore) {
    if (newScore > maxPoints)
        maxPoints = newScore;
}

class Food {
private:
    int count;
    int point;
    char type;
    static int totalFoodCount;
public:
    ~Food() {};
    Food(int count, int point, char type) : count(count), point(point), type(type) { totalFoodCount += count; }
    int getCount() { return count; }
    int getPoint() { return point; }
    char getType() { return type; }
    void decreaseCount() { count--; totalFoodCount--;}
    static int getTotalFoodCount();
    static void setTotalFoodCount(int count);
    friend void Pacman::PacmanMove(Map& map, Food& smallFood, Food& bigFood);
    friend int Pacman::WonOrLost(Food smallFood, Food bigFood, Text& Result);
};
int Food::totalFoodCount = 0; // Инициализация статического поля вне класса
int Food::getTotalFoodCount() { return Food::totalFoodCount; }
void Food:: setTotalFoodCount(int count) { Food::totalFoodCount = count; }

class Map {
private:
    int H, W;
    std::vector<std::string> Mase;
public:
    ~Map() {};
    Map(int H, int W) : H(H), W(W) { Mase.resize(H); }
    int getH() const { return H; }
    int getW() const { return W; }
    char getTile(int y, int x) const { return  Mase[y][x]; }
    void setTile(int y, int x, char tile) { Mase[y][x] = tile; }
    friend void Pacman::PacmanMove(Map& map, Food& smallFood, Food& bigFood);
    void createMap() {
        std::string tempMase[] = {
            "                              ",
            "                              ",
            "                              ",
            " XXXXXXXXXXXXXXXXXXXXXXXXXXXX ",
            " XooooooooooooXXooooooooooooX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XOXXXXoXXXXXoXXoXXXXXoXXXXOX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XooooooooooooooooooooooooooX ",
            " XoXXXXoXXoXXXXXXXXoXXoXXXXoX ",
            " XoXXXXoXXoXXXXXXXXoXXoXXXXoX ",
            " XooooooXXooooXXooooXXooooooX ",
            " XXXXXXoXXXXX XX XXXXXoXXXXXX ",
            "      XoXXXXX XX XXXXXoX      ",
            "      XoXX          XXoX      ",
            "      XoXX XXXXXXXX XXoX      ",
            " XXXXXXoXX X      X XXoXXXXXX ",
            "       o   X      X   o       ",
            " XXXXXXoXX X      X XXoXXXXXX ",
            "      XoXX XXXXXXXX XXoX      ",
            "      XoXX          XXoX      ",
            "      XoXX XXXXXXXX XXoX      ",
            " XXXXXXoXX XXXXXXXX XXoXXXXXX ",
            " XooooooooooooXXooooooooooooX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XoXXXXoXXXXXoXXoXXXXXoXXXXoX ",
            " XOooXXooooooooooooooooXXooOX ",
            " XXXoXXoXXoXXXXXXXXoXXoXXoXXX ",
            " XXXoXXoXXoXXXXXXXXoXXoXXoXXX ",
            " XooooooXXooooXXooooXXooooooX ",
            " XoXXXXXXXXXXoXXoXXXXXXXXXXoX ",
            " XoXXXXXXXXXXoXXoXXXXXXXXXXoX ",
            " XooooooooooooooooooooooooooX ",
            " XXXXXXXXXXXXXXXXXXXXXXXXXXXX ",
            "                              ",
        };
        for (int i = 0; i < H; ++i) {
            Mase[i] = tempMase[i];
        }
    }

    void MasePaint(GameSettings& settings, RenderWindow& window, Food& smallFood, Food& bigFood) {
        RectangleShape square(Vector2f(settings.getGridSize(), settings.getGridSize()));
        square.setFillColor(settings.getSquareColor());
        CircleShape smallCircle(3);
        smallCircle.setFillColor(settings.getCircleColor());
        CircleShape biglCircle(6);
        biglCircle.setFillColor(settings.getCircle2Color());
        RectangleShape pacman(Vector2f(settings.getGridSize(), settings.getGridSize()));
        pacman.setFillColor(settings.getPacmanColor());
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
            {
                if (Mase[i][j] == 'X')
                {
                    square.setPosition(j * settings.getGridSize(), i * settings.getGridSize());
                    window.draw(square);
                }
                else if (Mase[i][j] == smallFood.getType())
                {
                    smallCircle.setPosition(j * settings.getGridSize() + 8.5, i * settings.getGridSize() + 8.5f);
                    int pacmanX = static_cast<int>(pacman.getPosition().y / settings.getGridSize());
                    int pacmanCol = static_cast<int>(pacman.getPosition().x / settings.getGridSize());
                    window.draw(smallCircle);
                }
                else if (Mase[i][j] == bigFood.getType())
                {
                    biglCircle.setPosition(j * settings.getGridSize() + 5.5f, i * settings.getGridSize() + 5.5f);
                    window.draw(biglCircle);
                }
                else if (Mase[i][j] == 'P')
                {
                    pacman.setPosition(j * settings.getGridSize(), i * settings.getGridSize());
                    window.draw(pacman);
                }
            }
    }
};


void Pacman::PacmanMove(Map& map, Food& smallFood, Food& bigFood)         //дружественная функция
{
    if (Keyboard::isKeyPressed(Keyboard::Up) && map.Mase[nextY - 1][nextX] != 'X' && !(nextY == 17 && nextX == 0 || nextY == 17 && nextX == map.getW() - 1)) {
        nextDirection = 0;
        nextX = x;
        nextY = y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && map.Mase[nextY + 1][nextX] != 'X' && !(nextY == 17 && nextX == 0 || nextY == 17 && nextX == map.getW() - 1)) {
        nextDirection = 1;
        nextX = x;
        nextY = y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && (map.Mase[nextY][nextX - 1] != 'X')) {
        nextDirection = 2;
        nextX = x;
        nextY = y;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && (map.Mase[nextY][nextX + 1] != 'X')) {
        nextDirection = 3;
        nextX = x;
        nextY = y;
    }

    score++;
    if (score >= 150)
    {
        switch (nextDirection)
        {
        case 0:
            if (map.Mase[nextY - 1][nextX] != 'X' && nextY - 1 >= 0)
                nextY--;
            break;
        case 1:
            if (map.Mase[nextY + 1][nextX] != 'X' && nextY + 1 <= 35)
                nextY++;
            break;
        case 2:
            if (nextY == 17 && nextX == 1)
                nextX = map.W - 2;
            else if (map.Mase[nextY][nextX - 1] != 'X' && nextX - 1 >= 0)
                nextX--;
            break;
        case 3:
            if (nextY == 17 && nextX == map.getW() - 2)
                nextX = 1;
            else if (map.Mase[nextY][nextX + 1] != 'X' && nextX + 1 <= 35)
                nextX++;
            break;
        }
        score = 0;
    }

    if ((map.Mase[nextY][nextX] == ' ' || map.Mase[nextY][nextX] == smallFood.getType() || map.Mase[nextY][nextX] == bigFood.getType()) && nextY != 0 && nextX != 0)
    {
        if (map.Mase[nextY][nextX] == smallFood.getType())
        {
            addPoints(smallFood.point);
            smallFood.decreaseCount();
        }
        if (map.Mase[nextY][nextX] == bigFood.getType())
        {
            addPoints(bigFood.point);
            bigFood.decreaseCount();
        }
        map.setTile(y, x, ' ');
        map.setTile(nextY, nextX, 'P');
        x = nextX;
        y = nextY;
    }
}


int Pacman::WonOrLost(Food smallFood, Food bigFood, Text& Result)
{
    int f = 1;
    if (smallFood.totalFoodCount == 0)
        Result.setString("You won! ");
    else if (!getLives())
        Result.setString("You lost! ");
    else f = 0;
    return f;
}


class Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    Ghost() {};
    ~Ghost() {};
    Ghost(int x, int y, int score, int direction, int lastDirection) : x(x), y(y), score(score), direction(direction), lastDirection(lastDirection) {};
    int getX() const { return x; }
    int getY() const { return y; }
    int getScore() const { return score; }
    int getDirection() const { return direction; }
    int getLastDirection() const { return lastDirection; }
    void setAll(int a, int b, int c, int d, int e) { x = a, y = b, score = c, d = direction, e = lastDirection; }

       // Перегрузка оператора + (сложение)
    Ghost operator+(const Ghost& other) const {
        return Ghost(
            (x + other.x) / 2, // Среднее арифметическое x
            (y + other.y) / 2, // Среднее арифметическое y
             0, //сбрасываем score
            direction,
            lastDirection
         );
    }

    // Перегрузка префиксного оператора ++
    Ghost& operator++() {
       x++;
       return *this;
    }

    // Перегрузка постфиксного оператора ++
    Ghost operator++(int) {
        Ghost temp = *this;
        x++;
        return temp;
    }


    float distance(int x1, int y1, int x2, int y2) {
        return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
    }

    void ghostDraw(sf::Color color, RenderWindow& window, GameSettings settings)
    {
        RectangleShape ghostShape(Vector2f(settings.getGridSize(), settings.getGridSize()));
        ghostShape.setFillColor(color);
        ghostShape.setPosition(getX() * settings.getGridSize(), getY() * settings.getGridSize());
        window.draw(ghostShape);
    }

    void move(Map map, int goalX, int goalY) {
        float distanceUp, distanceDown, distanceLeft, distanceRight;
        double minDistance = INFINITY;
        int change = 0;

        distanceUp = distance(goalX, goalY, x, y - 1);
        distanceDown = distance(goalX, goalY, x, y + 1);
        if (y == 17 && x == 1)
            distanceLeft = distance(goalX, goalY, map.getW() - 1, y);
        else distanceLeft = distance(goalX, goalY, x - 1, y);
        if (y == 17 && x == map.getW() - 1)
            distanceRight = distance(goalX, goalY, 0, y);
        else distanceRight = distance(goalX, goalY, x + 1, y);

        if (distanceRight <= minDistance && map.getTile(y, x + 1) != 'X' && lastDirection != 2) {
            minDistance = distanceRight;
            direction = 3;
        }
        if (distanceUp <= minDistance && map.getTile(y - 1, x) != 'X' && lastDirection != 1 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
            minDistance = distanceUp;
            direction = 0;
        }
        if (distanceLeft <= minDistance && map.getTile(y, x - 1) != 'X' && lastDirection != 3) {
            minDistance = distanceLeft;
            direction = 2;
        }
        if (distanceDown <= minDistance && map.getTile(y + 1, x) != 'X' && lastDirection != 0 && !(y == 17 && x == 0 || y == 17 && x == map.getW() - 1)) {
            minDistance = distanceDown;
            direction = 1;
        }

        score++;
        if (score >= 150)
        {
            change = 1;
            // Двигаемся в выбранном направлении
            switch (direction) {
            case 0: //Движение вверх
                y--;
                break;
            case 1: //Движение вниз
                y++;
                break;
            case 2: //Движение влево
                if (y == 17 && x == 1)
                    x = map.getW() - 2;
                else
                    x--;
                break;
            case 3: //Движение вправо
                if (y == 17 && x == map.getW() - 2)
                    x = 1;
                else
                    x++;
                break;
            default:
                break;
            }
            score = 0;
        }

        if (lastDirection != direction && change)
            lastDirection = direction;
    }
};

class Blinky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Blinky() {};
    Blinky() {};
    Blinky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void BlinkyMove(Pacman pacman, Map map, GameSettings settings, RenderWindow& window) {
        move(map, pacman.getX(), pacman.getY());
        ghostDraw(settings.getBlinkyColor(), window, settings);
    }
};

class Pinky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Pinky() {};
    Pinky() {};
    Pinky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void PinkyMove(Pacman pacman, Map map, GameSettings settings, RenderWindow& window) {
        int a = pacman.getX(), b = pacman.getY();
        switch (pacman.getNextDirection())
        {
        case 0:
            b = b - 4;
            break;
        case 1:
            b = b + 4;
            break;
        case 2:
            a = a - 4;
            break;
        case 3:
            a = a + 4;
            break;
        }
        move(map, a, b);
        ghostDraw(settings.getPinkyColor(), window, settings);
    }
};

class Inky : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Inky() {};
    Inky() {};
    Inky(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void InkyMove(Pacman pacman, Map map, Ghost blinky, GameSettings settings, RenderWindow& window) {
        int a = pacman.getX(), b = pacman.getY();
        switch (pacman.getNextDirection())
        {
        case 0:
            b = b - 2;
            break;
        case 1:
            b = b + 2;
            break;
        case 2:
            a = a - 2;
            break;
        case 3:
            a = a + 2;
            break;
        }
        a = blinky.getX() + 2 * (a - blinky.getX());
        b = blinky.getY() + 2 * (b - blinky.getY());
        move(map, a, b);
        ghostDraw(settings.getInkyColor(), window, settings);
    }
};

class Clyde : public Ghost {
private:
    int x, y, score, direction, lastDirection;
public:
    ~Clyde() {};
    Clyde() {};
    Clyde(int x, int y, int score, int direction, int lastDirection) : Ghost(x, y, score, direction, lastDirection) {};
    void ClydeMove(Pacman pacman, Map map, GameSettings settings, RenderWindow& window) {
        int a, b;
        float mainDistance = distance(pacman.getX(), pacman.getY(), x, y);
        if (mainDistance > 8)
        {
            a = pacman.getX();
            b = pacman.getY();
        }
        else
        {
            a = 0;
            b = map.getH();
        }
        move(map, a, b);
        ghostDraw(settings.getClydeColor(), window, settings);
    }

    int Lose(Pacman& pacman, Blinky& blinky, Pinky& pinky, Inky& inky)
    {
        int result = 0;
        if (pacman.getX() == blinky.getX() && pacman.getY() == blinky.getY()) {
            pacman.loseLife();
            result = 1;
        }
        else if (pacman.getX() == pinky.getX() && pacman.getY() == pinky.getY()) {
            pacman.loseLife();
            result = 1;
        }
        else if (pacman.getX() == inky.getX() && pacman.getY() == inky.getY()) {
            pacman.loseLife();
            result = 1;
        }
        else if (pacman.getX() == getX() && pacman.getY() == getY()) {
            pacman.loseLife();
            result = 1;
        }
        switch (pacman.getNextDirection()) {
        case 0:
            if (pacman.getX() == blinky.getX() && pacman.getY() - 1 == blinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() == pinky.getX() && pacman.getY() - 1 == pinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() == inky.getX() && pacman.getY() - 1 == inky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() == getX() && pacman.getY() - 1 == getY()) {
                pacman.loseLife();
                result = 1;
            }
            break;
        case 1:
            if (pacman.getX() == blinky.getX() && pacman.getY() + 1 == blinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() == pinky.getX() && pacman.getY() + 1 == pinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() == inky.getX() && pacman.getY() + 1 == inky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() == getX() && pacman.getY() + 1 == getY()) {
                pacman.loseLife();
                result = 1;
            }
            break;
        case 2:
            if (pacman.getX() - 1 == blinky.getX() && pacman.getY() == blinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() - 1 == pinky.getX() && pacman.getY() == pinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() - 1 == inky.getX() && pacman.getY() == inky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() - 1 == getX() && pacman.getY() == getY()) {
                pacman.loseLife();
                result = 1;
            }
            break;
        case 3:
            if (pacman.getX() + 1 == blinky.getX() && pacman.getY() == blinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() + 1 == pinky.getX() && pacman.getY() == pinky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() + 1 == inky.getX() && pacman.getY() == inky.getY()) {
                pacman.loseLife();
                result = 1;
            }
            else if (pacman.getX() + 1 == getX() && pacman.getY() == getY()) {
                pacman.loseLife();
                result = 1;
            }
            break;
        }
        return result;
    }
};

class Game {
public:
    Game() {};
    ~Game() {};
    void resetGame(Map& map, Food& smallFood, Food& bigFood, Pacman& pacman, Ghost** ghostArray, GameSettings& settings, Text& Result) {
        // сброс карты

        map.createMap();

        // сброс еды
        smallFood.setTotalFoodCount(-1);
        smallFood = Food(242, 5, 'o');
        bigFood = Food(4, 10, 'O');
    

        // сброс Pacman
        pacman.setX(settings.getPacmanStartX());
        pacman.setY(settings.getPacmanStartY());
        pacman.setNextX(settings.getPacmanStartX());
        pacman.setNextY(settings.getPacmanStartY());
        pacman.setNextDirection(3);
        int* pointsPtr = pacman.getPointsPointer();
        *pointsPtr = 0;                                              // Изменяем значение points через указатель
        int& livesRef = pacman.getLivesReference();
        livesRef = 30;                                              // Изменяем значение lives через ссылку
        pacman.setScore(0);

        // сброс призраков
        Blinky& blinky = *static_cast<Blinky*>(ghostArray[0]);
        Pinky& pinky = *static_cast<Pinky*>(ghostArray[1]);
        Inky& inky = *static_cast<Inky*>(ghostArray[2]);
        Clyde& clyde = *static_cast<Clyde*>(ghostArray[3]);
        blinky.setAll(11, 14, 0, 3, 3);
        pinky.setAll(13, 14, 0, 3, 3);
        inky.setAll(15, 14, 0, 3, 3);
        clyde.setAll(17, 14, 0, 3, 3);
        map.setTile(pacman.getY(), pacman.getX(), ' ');
        map.setTile(settings.getPacmanStartY(), settings.getPacmanStartX(), 'P');
        Result.setString(" ");
    }
};

int main()
{
    Game game;
    //динамический массив объектов класса GameSettings 
    GameSettings* settingsArray;
    settingsArray = new GameSettings[2];
    settingsArray[0] = GameSettings("Pac-Man 1", 25, 14, 26, sf::Color::Yellow, sf::Color::Blue, sf::Color::White, sf::Color::White, sf::Color::Red, sf::Color(255, 185, 193),
        sf::Color::Cyan, sf::Color(255, 165, 0));
    settingsArray[1] = GameSettings("Pac-Man 2", 25, 14, 8, sf::Color(255, 255, 153), sf::Color(100, 149, 247), sf::Color(255, 245, 238),
        sf::Color(255, 228, 225), sf::Color(220, 20, 60), sf::Color(255, 105, 180), sf::Color(176, 234, 240), sf::Color(255, 140, 0)
    );
    srand(time(NULL));
    GameSettings settings = settingsArray[rand() % 2];

    Pacman pacman(settings.getPacmanStartX(), settings.getPacmanStartY(), settings.getPacmanStartX(), settings.getPacmanStartY(), 0, 3, 1, 0);

    Ghost** ghostArray = new Ghost * [4];
    Map map(35, 30);
    map.createMap();
    Food smallFood(242, 5, 'o');
    Food bigFood(4, 10, 'O');

    //Mассив динамических объектов класса Ghost
    ghostArray[0] = new Blinky(11, 14, 0, 3, 3);
    ghostArray[1] = new Pinky(13, 14, 0, 3, 3);
    ghostArray[2] = new Inky(15, 14, 0, 3, 3);
    ghostArray[3] = new Clyde(17, 14, 0, 3, 3);
    Blinky& blinky = *static_cast<Blinky*>(ghostArray[0]);
    Pinky& pinky = *static_cast<Pinky*>(ghostArray[1]);
    Inky& inky = *static_cast<Inky*>(ghostArray[2]);
    Clyde& clyde = *static_cast<Clyde*>(ghostArray[3]);
    sf::Font font;
    if (!font.loadFromFile("Unformital Medium.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text pointsText;
    pointsText.setFont(font);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(2 * settings.getGridSize(), 1 * settings.getGridSize());
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(40);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(22 * settings.getGridSize(), 1 * settings.getGridSize());
    sf::Text Result;
    Result.setFont(font);
    Result.setCharacterSize(80);
    Result.setFillColor(sf::Color::White);
    Result.setPosition(5 * settings.getGridSize(), 10 * settings.getGridSize());
    sf::Text Record;
    Record.setFont(font);
    Record.setCharacterSize(40);
    Record.setFillColor(sf::Color::White);
    Record.setPosition(11 * settings.getGridSize(), 1 * settings.getGridSize());
    RenderWindow window(VideoMode(settings.getGridSize() * map.getW(), settings.getGridSize() * map.getH()), settings.getWindowTitle());


    // Операция сложения призраков:
    Ghost combinedGhost = blinky + pinky; // Combined Ghost: x = 7, y = 7
    // Combined Ghost: x = 7, y = 7

    // Префиксный инкремент (сдвиг Blinky вправо):
    ++blinky;
    // Blinky (после ++blinky): x = 6, y = 5
    // Blinky после инкремента: x = 6, y = 5

    // Постфиксный инкремент (сдвиг Pinky вправо):
    Ghost tempPinky = pinky++;
    // tempPinky: x = 13, y = 14
     // Pinky после инкремента:  x = 14, y = 14
     // Координаты pinky после pinky++: x=14, y=14
     // Координаты tempPinky после pinky++: x=13, y=14


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                game.resetGame(map, smallFood, bigFood, pacman, ghostArray, settings, Result);
            }
        }
        window.clear(Color::Black);
        map.MasePaint(settings, window, smallFood, bigFood);
        if (pacman.WonOrLost(smallFood, bigFood, Result))
        {
            blinky.ghostDraw(settings.getBlinkyColor(), window, settings);
            combinedGhost.ghostDraw(Color::White, window, settings);
           pinky.ghostDraw(settings.getPinkyColor(), window, settings);
           inky.ghostDraw(settings.getInkyColor(), window, settings);
          clyde.ghostDraw(settings.getClydeColor(), window, settings);
            sf::FloatRect textBounds = Result.getLocalBounds();
            sf::Vector2u windowSize = window.getSize();
            Result.setPosition((windowSize.x - textBounds.width) / 2, (windowSize.y - textBounds.height) / 2 - 50);
            window.draw(Result);
            pacman.updateMaxPoints(pacman.getPoints());
        }
        else
        {
            pacman.PacmanMove(map, smallFood, bigFood);
            combinedGhost = blinky + pinky;
            combinedGhost.ghostDraw(Color::White, window, settings);
            blinky.BlinkyMove(pacman, map, settings, window);
           pinky.PinkyMove(pacman, map, settings, window);
            inky.InkyMove(pacman, map, blinky, settings, window);
           clyde.ClydeMove(pacman, map, settings, window);
            if (clyde.Lose(pacman, blinky, pinky, inky))
            {
                if (pacman.getLives())
                {
                    blinky.setAll(11, 14, 0, 3, 3);
                    pinky.setAll(13, 14, 0, 3, 3);
                    inky.setAll(15, 14, 0, 3, 3);
                    clyde.setAll(17, 14, 0, 3, 3);
                    map.setTile(pacman.getY(), pacman.getX(), ' ');
                    map.setTile(settings.getPacmanStartY(), settings.getPacmanStartX(), 'P');
                    pacman.setX(settings.getPacmanStartX());
                    pacman.setY(settings.getPacmanStartY());
                    pacman.setNextX(settings.getPacmanStartX());
                    pacman.setNextY(settings.getPacmanStartY());
                    pacman.setScore(0);
                    pacman.setNextDirection(3);
                }
            }
        }
        pointsText.setString("Score " + std::to_string(smallFood.getTotalFoodCount()));
        livesText.setString("Lives " + std::to_string(pacman.getLives()));
        Record.setString("Record " + std::to_string(pacman.getMaxPoints()));
        window.draw(pointsText);
        window.draw(livesText);
        window.draw(Record);
        window.display();
    }
    delete[] settingsArray;
    for (int i = 0; i < 4; ++i)
        delete ghostArray[i];
    delete[] ghostArray;
    return 0;
}