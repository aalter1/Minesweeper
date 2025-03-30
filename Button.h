#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include<sstream>
#include <chrono>


class Button {
public:
    Button() {}

    Button(string filename, float numCol, float numRow){
        Filename = filename;
        width = numCol;
        height = numRow;
    }

    void setTexture() {
        texture.loadFromFile(Filename);
        button.setTexture(texture);
    }



    void setPosition() {
        sf::FloatRect textRect = button.getLocalBounds();
        button.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        button.setPosition(sf::Vector2f(width, height));
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(button);
    }

    bool isMouseOver(sf::RenderWindow &window) {
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        }
        return false;
    }

private:
    sf::Texture texture;
    sf::Sprite button;
    string Filename;
    float width;
    float height;
};


class Digits{
public:
    Digits(){}

    Digits(string filename, float numCol, float numRow){
        Filename = filename;
        width = numCol;
        height = numRow;
    }

    void setTexture() {
        texture.loadFromFile(Filename);
        counter.setTexture(texture);
    }

    void setPosition() {
        sf::FloatRect textRect = counter.getLocalBounds();
        counter.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        counter.setPosition(sf::Vector2f(width, height));
    }

    void setDigit(int digit) {
        sf::IntRect textureRect(digit * DigitWidth, 0, DigitWidth, DigitHeight);
        counter.setTextureRect(textureRect);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(counter);
    }

private:
    int DigitWidth = 21;
    int DigitHeight = 32;
    sf::Texture texture;
    sf::Sprite counter;
    string Filename;
    float width;
    float height;

};