#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include<sstream>
#include <map>
#include <vector>

class Tile;

Tile* getTile(unsigned char x1, unsigned char y1, std::vector<Tile>& tiles1, int width);

class Tile {
public:
    Tile(){}

    Tile(unsigned char x1, unsigned char y1, int width, int height){
        minesAround = 0;
        x = x1;
        y = y1;
        Width = width;
        Height = height;
        isFlagged = 0;
        isOpen = false;
    }

    int getIsFlagged(){
        return isFlagged;
    }

    int isOpenFunc(){
        return isOpen;
    }

    bool isMineFunc(){
        return isMine;
    }

    bool open(std::vector<Tile>& tiles1){
        if (!isOpen){
            isOpen = true;
            if (!isMine && minesAround == 0) {
                for (int a = -1; a < 2; a++) {
                    for (int b = -1; b < 2; b++) {
                        if ((a == 0 && b == 0) || (0> a + x || 0 > b + y || Width == a + x || Height == b + y)) {
                            continue;
                        }
                        getTile(a + x, b + y, tiles1, Width)->open(tiles1);
                    }
                }
            }
            return isMine;
        }
        return false;
    }

    int getMinesAround(){
        return minesAround;
    }

    void countMinesAround(std::vector<Tile>& tiles1){
        minesAround = 0;
        if (!isMine) {
            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++) {
                    int newX = x + i;
                    int newY = y + j;
                    if ((i == 0 && j == 0) || newX < 0 || newY < 0 || newX == Width || newY == Height) {
                        continue;
                    }
                    if (getTile(newX, newY, tiles1, Width)->isMineFunc()) {
                        minesAround++;
                    }
                }
            }
        }
    }

    void flag(){
        if (!isOpen) {
            isFlagged = !isFlagged;
        }
    }

    void reset(){
        isFlagged = false;
        isMine = false;
        isOpen = false;
    }

    void setMine(){
        isMine = true;
    }

private:
    int isFlagged;
    int isOpen;
    bool isMine;
    int minesAround;
    int x;
    int y;
    sf::Texture texture;
    sf::Sprite tile;
    int Width;
    int Height;
};

Tile* getTile(unsigned char x1, unsigned char y1, std::vector<Tile> & tiles1, int width){
    return &tiles1[x1 + width * y1];
}