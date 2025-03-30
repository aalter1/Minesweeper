#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include<sstream>

using namespace std;

class Textbox {
public:
    Textbox() {}

    Textbox(int size, sf::Color color, int width, int height) {
        x = width;
        y = height;
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        textbox.setString("|");
    }

    void setFont(sf::Font &font) {
        textbox.setFont(font);
    }


    string getText() {
        return text.str();
    }

    void setPosition() {
        sf::FloatRect textRect = textbox.getLocalBounds();
        textbox.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        textbox.setPosition(sf::Vector2f(x, y));
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(textbox);
    }

    void typedOn(sf::Event input) {
        int charTyped = input.text.unicode;
        if ((65 <= charTyped && charTyped <= 90) || (97 <= charTyped && charTyped <= 122) || (charTyped == 8))  {
            if(text.str().length() <= limit) {
                inputLogic(charTyped);
            }
            else if(text.str().length() > limit && charTyped == 8) {
                deleteLastChar();
            }
        }
    }
private:
    int x;
    int y;
    sf::Text textbox;
    ostringstream text;
    int limit = 9;

    void inputLogic(int charTyped) {
        if (charTyped != 8 && charTyped != 13) {
            if (text.str().empty() || text.str().back() == ' ') {
                text << static_cast<char>(toupper(charTyped));
            } else {
                text << static_cast<char>(tolower(charTyped));
            }
            textbox.setStyle(sf::Text::Bold); // Set the style to Bold
        } else if (charTyped == 8) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }
        textbox.setString(text.str() + "|");
    }

    void deleteLastChar() {
        string t = text.str();
        string newT = "";
        for(int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        text.str("");
        text << newT;

        textbox.setString(text.str());
    }

};

class TextElement{
public:
    TextElement() {

    }
    TextElement(int size, bool Bold, bool Underlined, sf::Color color, string Text) {
        textElement.setCharacterSize(size);
        textElement.setFillColor(color);
        text = Text;
        bold = Bold;
        underlined = Underlined;
    }

    void setPosition(float x, float y) {
        sf::FloatRect textRect = textElement.getLocalBounds();
        textElement.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        textElement.setPosition(sf::Vector2f(x, y));
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(textElement);
    }

    void setFont(sf::Font &font) {
        textElement.setFont(font);
    }


    void setString() {
        if (bold && underlined) {
            textElement.setString(text);
            textElement.setStyle(sf::Text::Bold | sf::Text::Underlined);
        } else if (bold) {
            textElement.setString(text);
            textElement.setStyle(sf::Text::Bold);
        } else if (underlined) {
            textElement.setString(text);
            textElement.setStyle(sf::Text::Underlined);
        } else {
            textElement.setString(text);
            textElement.setStyle(sf::Text::Regular);
        }
    }

    void setStringLeader() {
        if (bold && underlined) {
            textElement.setString(text);
            textElement.setStyle(sf::Text::Bold | sf::Text::Underlined);
        } else if (bold) {
            textElement.setString(text);
            textElement.setStyle(sf::Text::Bold);
        } else if (underlined) {
            textElement.setString(text);
            textElement.setStyle(sf::Text::Underlined);
        } else {
            // Add new lines between each entry
            std::string newText;
            std::istringstream iss(text);
            std::string line;
            while (std::getline(iss, line)) {
                newText += line + "\n";
            }
            textElement.setString(newText);
            textElement.setStyle(sf::Text::Regular);
        }
    }
private:
    sf::Text textElement;
    string text;
    bool bold;
    bool underlined;
};


