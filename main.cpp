#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

//Funcion del Juego Pong
void Pong() {
    //Creacion de la ventana
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong Game");

    //CONSTRUCCION DE VENTANA
    //Creación de las lineas centrales
    std::vector<sf::RectangleShape> centralLines(18);
    float yPositions = 0;
    for (int i = 0; i < 18; i++) {
        centralLines[i].setSize(sf::Vector2f(10, 30));
        centralLines[i].setPosition(635, yPositions);
        yPositions += 40;
        centralLines[i].setFillColor(sf::Color::White);
    }
    //Creacion de Paletas
    //Izquierda
    sf::RectangleShape leftPalette(sf::Vector2f(12, 150));
    leftPalette.setPosition(5, 285);
    leftPalette.setFillColor(sf::Color::White);
    //Derecha
    sf::RectangleShape rightPalette(sf::Vector2f(12, 150));
    rightPalette.setPosition(1263, 285);
    rightPalette.setFillColor(sf::Color::White);

    //Creacion de Marcadores (Score)
    //Cargar Fuente del Texto
    sf::Font arial;
    if (!arial.loadFromFile("../arial.ttf")) {
        std::cout << "Error al cargar la fuente\n";
    }
    //Creacion de Texto de Marcadores
    //Izquierda
    sf::Text leftText;
    leftText.setFont(arial);
    leftText.setString("0");
    leftText.setPosition(317.5, 5);
    leftText.setCharacterSize(35);
    leftText.setFillColor(sf::Color::White);
    //Derecha
    sf::Text rightText;
    rightText.setFont(arial);
    rightText.setString("0");
    rightText.setPosition(952.5, 5);
    rightText.setCharacterSize(35);
    rightText.setFillColor(sf::Color::White);

    //Creacion de Pelota
    sf::CircleShape ball(15);
    ball.setPosition(625, 350);
    ball.setFillColor(sf::Color::White);

    //Creación de Variables para While
    sf::Event event{};
    sf::Vector2f ballMovement(0.5f, 0.5f);
    sf::Vector2f leftPaletteMovement(15.f, 15.f);
    sf::Vector2f rightPaletteMovement(15.f, 15.f);
    int leftMarcador = 0;
    int rightMarcador = 0;

    //While de Salida
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::W){
                    if(leftPalette.getPosition().y > 0) {
                        leftPalette.move(0, -leftPaletteMovement.y);
                    }
                }
                if(event.key.code == sf::Keyboard::S){
                    if(leftPalette.getPosition().y + leftPalette.getSize().y < window.getSize().y) {
                        leftPalette.move(0, leftPaletteMovement.y);
                    }
                }
                if(event.key.code == sf::Keyboard::Up){
                    if(rightPalette.getPosition().y > 0) {
                        rightPalette.move(0, -rightPaletteMovement.y);
                    }
                }
                if(event.key.code == sf::Keyboard::Down){
                    if(rightPalette.getPosition().y + rightPalette.getSize().y < window.getSize().y) {
                        rightPalette.move(0, rightPaletteMovement.y);
                    }
                }
            }
        }

        //If's para realizar el movimiento de la pelota y colisiones
        ball.move(ballMovement);
        if (ball.getPosition().x + ball.getLocalBounds().width >= window.getSize().x) {
            leftMarcador++;
            leftText.setString(std::to_string(leftMarcador));
            ball.setPosition(625, 350);
            ballMovement.x = -ballMovement.x;
        }
        if (ball.getPosition().x <= 0) {
            rightMarcador++;
            rightText.setString(std::to_string(rightMarcador));
            ball.setPosition(625, 350);
            ballMovement.x = -ballMovement.x;
        }
        if (ball.getPosition().y + ball.getLocalBounds().height >= window.getSize().y || ball.getPosition().y <= 0) {
            ballMovement.y = -ballMovement.y;
        }
        if (ball.getGlobalBounds().intersects(leftPalette.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(rightPalette.getGlobalBounds())) {
            ballMovement.x = -ballMovement.x;
        }


        //Limpiamos pantalla, dibujamos y desplegamos
        window.clear(sf::Color::Black);
        for (int i = 0; i < 18; i++) {
            window.draw(centralLines[i]);
        }
        window.draw(leftPalette);
        window.draw(rightPalette);
        window.draw(leftText);
        window.draw(rightText);
        window.draw(ball);
        window.display();
    }
}

int main(){
    Pong();
    return 0;
}