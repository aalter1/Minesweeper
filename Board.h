#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include<sstream>
#include "Tile.h"
#include <vector>
#include <random>


class Board{
public:
    Board(){}

    Board(int width, int height, map<string,string> TextureMap, int mines){
        gameState = 1;
        Width = width;
        Height = height;
        textureMap = TextureMap;
        Mines = mines;
        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                tiles.push_back(Tile(j,i, Width, Height));
            }
        }
        restart();
    }

    int getGameState(){
        return gameState;
    }

    void openTile(int x1, int y1){
        if (clicks == 0) {
            clicks++;
            std::uniform_int_distribution<int> x_dist(0, Width- 1);
            std::uniform_int_distribution<int> y_dist(0, Height - 1);
            for (int i = 0; i < Mines; i++) {
                int mine_x = static_cast<int>(x_dist(randomEngine));
                int mine_y = static_cast<int>(y_dist(randomEngine));
                if (getTile(mine_x, mine_y, tiles, Width)->isMineFunc() || (x1 == mine_x && y1 == mine_y)) {
                    i--;
                }
                else {
                    getTile(mine_x, mine_y, tiles, Width)->setMine();
                }
            }
            for (Tile& tile : tiles) {
                tile.countMinesAround(tiles);
            }
        }


        if (gameState == 0 && !getTile(x1,y1,tiles, Width)->getIsFlagged()) {
            if (getTile(x1,y1,tiles, Width)->open(tiles)) {
                gameState = -1;
                setDebug(true); // game over
            }
            else {
                bool allMinesFlagged = true;
                bool allNonMineTilesOpened = true;
                for ( Tile& tile : tiles) {
                    if (tile.isMineFunc()) {
                        if (!tile.getIsFlagged()) {
                            allMinesFlagged = false;
                            break; // No need to check further if any mine is not flagged
                        }
                    } else {
                        if (!tile.isOpenFunc()) {
                            allNonMineTilesOpened = false;
                            break; // No need to check further if any non-mine tile is unopened
                        }
                    }
                }
                if (allMinesFlagged && allNonMineTilesOpened) {
                    gameState = 1; // win
                }
            }
        }
    }

    void drawTo(sf::RenderWindow& window, bool pause, bool pause2) {
        sf::RectangleShape tileShape(sf::Vector2f(31, 31));
        sf::Sprite tileSprite1;
        sf::Texture tileTexture1;
        tileTexture1.loadFromFile(textureMap["hiddenTile"]);
        tileSprite1.setTexture(tileTexture1);
        for (int i = 0; i < Width; i++){
            for (int j = 0; j < Height; j++) {
                tileShape.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                if (pause || pause2) {
                    sf::Sprite tileSprite10;
                    sf::Texture tileTexture10;
                    tileTexture10.loadFromFile(textureMap["revealedTile"]);
                    tileSprite10.setTexture(tileTexture10);
                    tileSprite10.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                    window.draw(tileSprite10);
                    continue;
                }
                else {
                    if (getTile(i, j, tiles, Width)->isOpenFunc() == 1){
                        int minesAround = getTile(i, j, tiles, Width)->getMinesAround();
                        sf::Sprite tileSprite2;
                        sf::Texture tileTexture2;
                        tileTexture2.loadFromFile(textureMap["revealedTile"]);
                        tileSprite2.setTexture(tileTexture2);
                        tileSprite2.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                        window.draw(tileSprite2);
                        if (getTile(i, j, tiles, Width)->isMineFunc()){
                            sf::Sprite tileSprite4;
                            sf::Texture tileTexture4;
                            tileTexture4.loadFromFile(textureMap["mine"]);
                            tileSprite4.setTexture(tileTexture4);
                            tileSprite4.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                            window.draw(tileSprite4);
                        }
                        if (minesAround > 0) {
                            if ( 1 == minesAround) {
                                sf::Sprite numberSprite1;
                                sf::Texture numberTexture1;
                                numberTexture1.loadFromFile(textureMap["1"]);
                                numberSprite1.setTexture(numberTexture1);
                                numberSprite1.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite1);
                            }
                            else if (2 == minesAround) {
                                sf::Sprite numberSprite2;
                                sf::Texture numberTexture2;
                                numberTexture2.loadFromFile(textureMap["2"]);
                                numberSprite2.setTexture(numberTexture2);
                                numberSprite2.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite2);
                            }
                            else if (3 == minesAround) {
                                sf::Sprite numberSprite3;
                                sf::Texture numberTexture3;
                                numberTexture3.loadFromFile(textureMap["3"]);
                                numberSprite3.setTexture(numberTexture3);
                                numberSprite3.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite3);
                            }
                            else if (4 == minesAround) {
                                sf::Sprite numberSprite4;
                                sf::Texture numberTexture4;
                                numberTexture4.loadFromFile(textureMap["4"]);
                                numberSprite4.setTexture(numberTexture4);
                                numberSprite4.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite4);
                            }
                            else if (5 == minesAround) {
                                sf::Sprite numberSprite5;
                                sf::Texture numberTexture5;
                                numberTexture5.loadFromFile(textureMap["5"]);
                                numberSprite5.setTexture(numberTexture5);
                                numberSprite5.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite5);
                            }
                            else if (6 == minesAround) {
                                sf::Sprite numberSprite6;
                                sf::Texture numberTexture6;
                                numberTexture6.loadFromFile(textureMap["6"]);
                                numberSprite6.setTexture(numberTexture6);
                                numberSprite6.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite6);
                            }
                            else if (7 == minesAround) {
                                sf::Sprite numberSprite7;
                                sf::Texture numberTexture7;
                                numberTexture7.loadFromFile(textureMap["7"]);
                                numberSprite7.setTexture(numberTexture7);
                                numberSprite7.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite7);
                            }
                            else if (8 == minesAround) {
                                sf::Sprite numberSprite8;
                                sf::Texture numberTexture8;
                                numberTexture8.loadFromFile(textureMap["8"]);
                                numberSprite8.setTexture(numberTexture8);
                                numberSprite8.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(numberSprite8);
                            }
                        }
                    }
                    else {
                        tileSprite1.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                        window.draw(tileSprite1);
                        if (getTile(i, j, tiles, Width)->getIsFlagged() == 1) {
                            sf::Sprite tileSprite3;
                            sf::Texture tileTexture3;
                            tileTexture3.loadFromFile(textureMap["flag"]);
                            tileSprite3.setTexture(tileTexture3);
                            tileSprite3.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                            window.draw(tileSprite3);
                        }
                        if (Debug) {
                            if (getTile(i, j, tiles, Width)->isMineFunc()){
                                sf::Sprite tileSprite4;
                                sf::Texture tileTexture4;
                                tileTexture4.loadFromFile(textureMap["mine"]);
                                tileSprite4.setTexture(tileTexture4);
                                tileSprite4.setPosition(static_cast<float>(32 * i), static_cast<float>(32 * j));
                                window.draw(tileSprite4);
                            }
                        }
                    }
                }


            }
        }
    }
    void restart(){
        clicks = 0;
        setDebug(false);
        for (Tile& tile : tiles) {
            tile.reset();
        }
        if (gameState != 0){
            gameState = 0;
        }
    }

    void putFlag(int x1, int y1, sf::RenderWindow& window) {
        if (gameState == 0) {
            getTile(x1, y1, tiles, Width)->flag();
        }
    }

    int getFlags(){
        int totalFlags = 0;
        for(Tile& tile : tiles) {
            totalFlags += tile.getIsFlagged();
        }
        return totalFlags;
    }

    void setDebug(bool debug) {
        Debug = debug;
    }

    bool checkWin(int x1, int y1) {
        bool allRemainingTilesAreMines = true;

        for (Tile& tile : tiles) {
            if (!tile.isOpenFunc()) {
                if (!tile.isMineFunc()) {
                    allRemainingTilesAreMines = false;
                    break; // No need to check further if any non-mine tile is unopened
                }
            }
        }

        if (allRemainingTilesAreMines) {
            // Automatically flag all remaining mines
            for (Tile& tile : tiles) {
                if (tile.isMineFunc() && !tile.getIsFlagged()) {
                    tile.flag(); // Flag the mine
                }
            }
            gameState = 1; // Win the game
            return true;
        }
        return false;
    }

private:
    int clicks = 0;
    bool Debug = false;
    std::vector<Tile> tiles;
    sf::Sprite hiddenTile;
    sf::Sprite mineSprite;
    sf::Sprite flagSprite;
    sf::Sprite openTileSprite;
    int Width;
    int Height;
    sf::Texture texture;
    std::map<std::string,std::string> textureMap;
    int Mines;
    std::default_random_engine randomEngine;
    int gameState;
};