#include <SFML/Graphics.hpp>
#include <fstream>
#include "Textbox.h"
#include "Button.h"
#include <chrono>
#include <map>
#include "Board.h"
#include "Tile.h"
using namespace std;


// Function to convert time string to total seconds
int timeStringToSeconds(const std::string& timeStr) {
    std::istringstream ss(timeStr);
    std::string token;
    int minutes, seconds;
    if (std::getline(ss, token, ':')) {
        minutes = std::stoi(token);
    }
    if (std::getline(ss, token, ':')) {
        seconds = std::stoi(token);
    }
    return minutes * 60 + seconds;
}

std::string secondsToTimeString(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    // Convert minutes and seconds to strings with leading zeros if needed
    std::ostringstream ss;
    if (minutes < 10) {
        ss << '0'; // Add leading zero if minutes is less than 10
    }
    ss << minutes << ":";
    if (seconds < 10) {
        ss << '0'; // Add leading zero if seconds is less than 10
    }
    ss << seconds;

    return ss.str();
}

string readLinesFromFile(const std::string& filename, std::vector<std::string>& firstElements, std::vector<std::string>& secondElements, string replacer) {
    // Open the file
    std::ifstream txtFile(filename);

    // Clear previous vectors if needed
    firstElements.clear();
    secondElements.clear();

    // Variables to store all lines concatenated and count lines
    std::string allLines;
    int count = 1;

    std::string singleLine;
    while (std::getline(txtFile, singleLine)) {
        // Use stringstream to split the line by comma
        std::stringstream ss(singleLine);
        std::string firstElement, secondElement;
        std::getline(ss, firstElement, ',');
        std::getline(ss, secondElement);
        string replaceCheck = firstElement + "," + secondElement;
        if (replacer == replaceCheck) {
            secondElement.replace(secondElement.begin(), secondElement.end(), secondElement + "*");
        }

        // Store the first and second elements
        firstElements.push_back(firstElement);
        secondElements.push_back(secondElement);

        // Concatenate the formatted line with two newline characters
        allLines += std::to_string(count) + ".\t" + firstElement + "\t " + secondElement + "\n\n";
        count++;
    }

    // Close the file
    txtFile.close();
    return allLines;
}

int main()
{

    // Set Welcome Window, Read info from config.cfg
    ifstream windowFile("files/config.cfg");
    string oldWidth;
    string oldHeight;
    string Smines;
    getline(windowFile, oldWidth);
    getline(windowFile, oldHeight);
    getline(windowFile, Smines);
    int rowCount = stoi(oldHeight);
    int colCount = stoi(oldWidth);
    int mines = stoi(Smines);
    int height = (rowCount * 32) + 100;
    int width = colCount * 32;

    //textures for tiles
    map<string, string> textureMap;
    textureMap.emplace("mine", "files/images/mine.png");
    textureMap.emplace("hiddenTile", "files/images/tile_hidden.png");
    textureMap.emplace("revealedTile", "files/images/tile_revealed.png");
    textureMap.emplace("flag", "files/images/flag.png");
    textureMap.emplace("1", "files/images/number_1.png");
    textureMap.emplace("2", "files/images/number_2.png");
    textureMap.emplace("3", "files/images/number_3.png");
    textureMap.emplace("4", "files/images/number_4.png");
    textureMap.emplace("5", "files/images/number_5.png");
    textureMap.emplace("6", "files/images/number_6.png");
    textureMap.emplace("7", "files/images/number_7.png");
    textureMap.emplace("8", "files/images/number_8.png");
    textureMap.emplace("9", "files/images/number_9.png");

    //Initialize game board
    bool debugger = false;
    Board board(colCount, rowCount, textureMap, mines);

    //Set textbox and textElements of welcome window
    sf::RenderWindow window1(sf::VideoMode(width, height), "Welcome Window");
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    Textbox textbox(18, sf::Color::Yellow, width / 2, (height / 2) - 45);
    textbox.setFont(font);
    textbox.setPosition();
    TextElement textElement1(24, true, true, sf::Color::White, "WELCOME TO MINESWEEPER");
    textElement1.setFont(font);
    textElement1.setString();
    textElement1.setPosition(width / 2, (height / 2) - 150);
    TextElement textElement2(20, true, false, sf::Color::White, "Enter your name:");
    textElement2.setFont(font);
    textElement2.setString();
    textElement2.setPosition(width / 2, (height / 2) - 75);

    //Set buttons and digits for Game Window
    Button happyFace("files/images/face_happy.png", ((colCount / 2.0) * 32) - 32, 32 * (rowCount + 0.5));
    happyFace.setPosition();
    happyFace.setTexture();
    //Set buttons and digits for Game Window
    Button loseFace("files/images/face_lose.png", ((colCount / 2.0) * 32) - 32, 32 * (rowCount + 0.5));
    loseFace.setPosition();
    loseFace.setTexture();
    //Set buttons and digits for Game Window
    Button winFace("files/images/face_win.png", ((colCount / 2.0) * 32) - 32, 32 * (rowCount + 0.5));
    winFace.setPosition();
    winFace.setTexture();
    Button debug("files/images/debug.png", (colCount * 32) - 304, 32 * (rowCount + 0.5));
    debug.setPosition();
    debug.setTexture();
    Button pause("files/images/pause.png", (colCount * 32) - 240, 32 * (rowCount + 0.5));
    pause.setPosition();
    pause.setTexture();
    Button play("files/images/play.png", (colCount * 32) - 240, 32 * (rowCount + 0.5));
    play.setPosition();
    play.setTexture();
    Button leaderboard("files/images/leaderboard.png", (colCount * 32) - 176, 32 * (rowCount + 0.5));
    leaderboard.setPosition();
    leaderboard.setTexture();
    Digits digitSeconds1("files/images/digits.png", (colCount * 32) - 54, 32 * (rowCount + 0.5) + 16);
    digitSeconds1.setPosition();
    digitSeconds1.setTexture();
    Digits digitSeconds2("files/images/digits.png", (colCount * 32) - 33, 32 * (rowCount + 0.5) + 16);
    digitSeconds2.setPosition();
    digitSeconds2.setTexture();
    Digits digitMinutes1("files/images/digits.png", (colCount * 32) - 97, 32 * (rowCount + 0.5) + 16);
    digitMinutes1.setPosition();
    digitMinutes1.setTexture();
    Digits digitMinutes2("files/images/digits.png", (colCount * 32) - 76, 32 * (rowCount + 0.5) + 16);
    digitMinutes2.setPosition();
    digitMinutes2.setTexture();
    Digits mineCounter1("files/images/digits.png", 33, 32 * (rowCount + 0.5) + 16);
    mineCounter1.setPosition();
    mineCounter1.setTexture();
    mineCounter1.setDigit(mines / 100);
    Digits mineCounter2("files/images/digits.png", 54, 32 * (rowCount + 0.5) + 16);
    mineCounter2.setPosition();
    mineCounter2.setTexture();
    mineCounter2.setDigit(mines / 10);
    Digits mineCounter3("files/images/digits.png", 75, 32 * (rowCount + 0.5) + 16);
    mineCounter3.setPosition();
    mineCounter3.setTexture();
    mineCounter3.setDigit(mines % 10);

    //set text for leaderboard
    TextElement leaderboardWord(20, true, true, sf::Color::White, "LEADERBOARD");
    leaderboardWord.setFont(font);
    leaderboardWord.setString();
    leaderboardWord.setPosition((colCount * 16)/2, (((rowCount * 16) + 50)/2) - 120);


    std::vector<std::string> firstElements;
    std::vector<std::string> secondElements;


    TextElement textLeaderboard(18, true, false, sf::Color::White, readLinesFromFile("files/leaderboard.txt", firstElements, secondElements, "none"));
    textLeaderboard.setFont(font);
    textLeaderboard.setStringLeader();
    textLeaderboard.setPosition((colCount * 16) / 2, (((rowCount * 16) + 50) / 2) + 20);



    // GAME LOOP for Welcome Window
    bool openSecondWindow = false;
    bool openThirdWindow = false;
    bool update = false;
    std::vector<int> totalSeconds;
    for (const auto& timeStr : firstElements) {
        totalSeconds.push_back(timeStringToSeconds(timeStr));
    }
    while (window1.isOpen())
    {
        sf::Event event;
        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window1.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if (textbox.getText().length() > 0)
                {
                    window1.close(); // Close the welcome window
                    openSecondWindow = true;
                }
            }
            if (event.type == sf::Event::TextEntered)
            {
                textbox.typedOn(event);
                textbox.setPosition();
            }
        }

        // Update and draw welcome window
        window1.clear(sf::Color::Blue);
        textbox.drawTo(window1);
        textElement1.drawTo(window1);
        textElement2.drawTo(window1);
        window1.display();

        if (openSecondWindow)
            break; // Exit the loop to open the second window
    }

    // Open the second window only if the Enter key was pressed
    if (openSecondWindow)
    {
        sf::RenderWindow window2(sf::VideoMode(width, height), "Game Window");

        // GAME LOOP for Second Window and timer implementation
        bool gameStarted = false;
        auto startTime = chrono::high_resolution_clock::now();
        auto pauseTime = chrono::high_resolution_clock::now();
        auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime).count();
        auto leaderStartTime = chrono::high_resolution_clock::now();
        auto leaderboard_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - leaderStartTime).count();
        bool paused1 = false;
        bool paused2 = false;

        //other conditions
        bool win = false;
        bool lose = false;
        bool negative = false;
        int totFlagLeft = mines;
        auto leaderboardOpenTime = std::chrono::high_resolution_clock::now();
        auto leaderboardEndTime = std::chrono::high_resolution_clock::now();
        int counter = 0;
        string addAsterisk;


        while (window2.isOpen())
        {
            sf::Event event;
            while (window2.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window2.close();
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i pos = sf::Mouse::getPosition(window2);
                    int x = pos.x / 32;
                    int y = pos.y / 32;
                    if (!paused1 && !paused2 && pos.x < width && pos.y < rowCount * 32) {
                        board.openTile(x,y);
                        if(board.checkWin(x, y)) {
                            totFlagLeft = 0;
                        }

                    }
                      if (pause.isMouseOver(window2))
                    {
                          if (board.getGameState() == 0) {
                              paused1 = !paused1;

                              if (paused1) {
                                  pauseTime = chrono::high_resolution_clock::now();
                              }
                              else {
                                  auto unPausedTime = chrono::high_resolution_clock::now();
                                  elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
                              }
                          }
                    }
                    else if (debug.isMouseOver(window2))
                    {
                        debugger = !debugger;
                        board.setDebug(debugger);
                    }
                    else if (happyFace.isMouseOver(window2))
                    {
                        paused1 = false;
                        paused2 = false;
                        negative = false;
                        counter = 0;
                        totFlagLeft = mines;
                        board.restart();
                        startTime = chrono::high_resolution_clock ::now();
                        elapsed_paused_time = 0;
                        leaderboard_time = 0;
                    }
                    else if (leaderboard.isMouseOver(window2))
                    {
                        openThirdWindow = true;
                        paused2 = true;
                        if (!paused1) {
                            leaderStartTime = chrono::high_resolution_clock::now();
                        }
                        }
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window2);
                    int x = pos.x / 32;
                    int y = pos.y / 32;
                    if (!paused1 && !paused2) {
                        board.putFlag(x,y, window2);
                        negative = false;
                        totFlagLeft = mines - board.getFlags();
                        if (totFlagLeft < 0) {
                            totFlagLeft = -totFlagLeft;
                            negative = true;
                        }
                        if (board.checkWin(x, y)) {
                            totFlagLeft = 0;
                        }
                    }
                }
            }

            // Update and draw the second window
            window2.clear(sf::Color::White);



            //timer
            // Update timer only if the leaderboard window is not open
            int getTime = 0;
            if (!paused1 && !paused2 && board.getGameState() == 0) {
                // Timer logic
                auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - startTime);
                int totalTime = game_duration.count();
                int minutes;
                int seconds;

                totalTime = totalTime - elapsed_paused_time;
                totalTime = totalTime - leaderboard_time;
                minutes = totalTime / 60;
                seconds = totalTime % 60;

                int minutes0 = minutes / 10 % 10;
                int minutes1 = minutes % 10;
                int seconds0 = seconds / 10 % 10;
                int seconds1 = seconds % 10;

                digitMinutes1.setDigit(minutes0);
                digitMinutes2.setDigit(minutes1);
                digitSeconds1.setDigit(seconds0);
                digitSeconds2.setDigit(seconds1);
            }
            if (board.getGameState() != 0) {
                if (counter == 0) {
                    auto game_duration2 = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - startTime);
                    getTime = game_duration2.count();
                    counter++;
                    int newMinutes = getTime / 60;
                    int newSeconds = getTime % 60;
                    string newMinutes0 = std:: to_string(newMinutes / 10 % 10);
                    string newMinutes1 = std:: to_string(newMinutes % 10);
                    string newSeconds0 = std:: to_string(newSeconds / 10 % 10);
                    string newSeconds1 = std:: to_string(newSeconds % 10);
                    string gameEndTime =  newMinutes0 + newMinutes1 + ":" + newSeconds0 + newSeconds1;
                    // Convert leaderboard times from string format to total seconds

                    // Check if the player's time is better than any existing time
                    bool updateTime = false;
                    for (int i = 0; i < totalSeconds.size(); i++) {
                        if (getTime < totalSeconds[i] && board.getGameState() == 1) {
                            // If the player's time is better, update the leaderboard
                            totalSeconds.insert(totalSeconds.begin() + i, getTime);
                            secondElements.insert(secondElements.begin() + i, " " + textbox.getText());
                            totalSeconds.pop_back(); // Remove the last element (worst time)
                            secondElements.pop_back();
                            addAsterisk = secondsToTimeString(getTime) + ", " + textbox.getText();
                            updateTime = true;
                            break; // Exit loop since we've updated the leaderboard
                        }
                    }

                    // If the leaderboard was updated, rewrite it to the file
                    if (updateTime) {
                        update = true;
                        std::ofstream leaderboardFile("files/leaderboard.txt");
                        if (leaderboardFile.is_open()) {
                            // Rewrite the leaderboard with updated times and names
                            for (int i = 0; i < totalSeconds.size(); i++) {
                                leaderboardFile << secondsToTimeString(totalSeconds[i]) << "," << secondElements[i] << std::endl;
                            }
                            leaderboardFile.close();
                        }
                    }
                }
            }
            //mines
            if (negative) {
                mineCounter1.setDigit(10);
            }
            else {
                mineCounter1.setDigit(totFlagLeft / 100);
            }
            mineCounter2.setDigit(totFlagLeft / 10);
            mineCounter3.setDigit(totFlagLeft % 10);



            //draw
            board.drawTo(window2, paused1, paused2);
            mineCounter1.drawTo(window2);
            mineCounter2.drawTo(window2);
            mineCounter3.drawTo(window2);
            digitSeconds1.drawTo(window2);
            digitSeconds2.drawTo(window2);
            digitMinutes1.drawTo(window2);
            digitMinutes2.drawTo(window2);
            happyFace.drawTo(window2);
            debug.drawTo(window2);
            pause.drawTo(window2);
            if (paused1) {
                play.drawTo(window2);
            }
            if (board.getGameState() == 1){
                winFace.drawTo(window2);
            }
            if (board.getGameState() == -1){
                loseFace.drawTo(window2);
            }
            leaderboard.drawTo(window2);
            window2.display();


            if (openThirdWindow) {
                // Open the third window to display the updated leaderboard
                sf::RenderWindow window3(sf::VideoMode(colCount * 16, (rowCount * 16) + 50), "Leaderboard");
                while (window3.isOpen()) {
                    sf::Event event;
                    while (window3.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window3.close();
                            paused2 = false;
                            openThirdWindow = false;
                            if (!paused1) {
                                auto leaderEndTime = chrono::high_resolution_clock::now();
                                leaderboard_time += chrono::duration_cast<chrono::seconds>(leaderEndTime - leaderStartTime).count();
                            }
                        }
                    }
                    window3.clear(sf::Color::Blue);
                    leaderboardWord.drawTo(window3);
                    if (!update) {
                        textLeaderboard.drawTo(window3);
                    }
                    else {
                        std::vector<std::string> newFirstElements;
                        std::vector<std::string> newSecondElements;
                        TextElement newTextLeaderboard(18, true, false, sf::Color::White, readLinesFromFile("files/leaderboard.txt", newFirstElements, newSecondElements, addAsterisk));
                        newTextLeaderboard.setFont(font);
                        newTextLeaderboard.setStringLeader();
                        newTextLeaderboard.setPosition((colCount * 16) / 2, (((rowCount * 16) + 50) / 2) + 20);
                        newTextLeaderboard.drawTo(window3);
                    }
                    window3.display();
                }
            }
        }
    }
    return 0;
}