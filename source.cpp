#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Que.h"
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

int josephus(int n, int k)
{
    Queue q;
    std::vector<sf::CircleShape> circles;
    std::vector<sf::Text> numbers;

    sf::Font font;
    if (!font.loadFromFile("D:\\DataStructre\\Sfml\\Sfml\\Font.otf"))
    {
        cerr << "Error loading font!" << endl;
        return -1;
    }
    sf::Font font2;
    if (!font2.loadFromFile("D:\\DataStructre\\Sfml\\Sfml\\font2.ttf"))
    {
        cerr << "Error loading font!" << endl;
        return -1;
    }

    // Load sound for elimination
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("D:\\DataStructre\\Sfml\\Sfml\\sword-clash-241729.mp3"))
    {
        cerr << "Error loading sound!" << endl;
        return -1;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::SoundBuffer OpenBuff;
    OpenBuff.loadFromFile("D:\\DataStructre\\Sfml\\Sfml\\scary-game-effect-131801.mp3");
    sf::Sound open;
    open.setBuffer(OpenBuff);

    // Load sound for victory
    sf::SoundBuffer finalBuffer;
    if (!finalBuffer.loadFromFile("D:\\DataStructre\\Sfml\\Sfml\\victorymale-version-230553.mp3"))
    {
        cerr << "Error loading final sound!" << endl;
        return -1;
    }
    sf::Sound finalSound;
    finalSound.setBuffer(finalBuffer);

    // Create circles in a circular arrangement
    float radius = 200.0f;  // Radius of the circle for arrangement
    float centerX = 400.0f; // Center of the window
    float centerY = 300.0f;

    for (int i = 0; i < n; ++i)
    {
        q.Push(i + 1);

        // Calculate position for circle
        float angle = 2 * 3.14 * i / n; // Angle for current person
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        // Create a circle shape for each person
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(x, y);
        circles.push_back(circle);

        sf::Text number;
        number.setFont(font);
        number.setString(std::to_string(i + 1));
        number.setCharacterSize(15);
        number.setFillColor(sf::Color::White);
        number.setPosition(x + 5, y + 2); 
        numbers.push_back(number);
    }

    sf::RenderWindow Opening(sf::VideoMode(800, 600), "Opening");
    sf::Text OpenText;
    OpenText.setFont(font2);
    OpenText.setString(" Opening ");
    OpenText.setCharacterSize(40);
    OpenText.setFillColor(sf::Color::Green);
    OpenText.setPosition(80, 150); 
    OpenText.setOutlineColor(sf::Color::Black);
    OpenText.setOutlineThickness(2);

    sf::Text waitText;
    waitText.setFont(font2);
    waitText.setString("Please wait..........");
    waitText.setCharacterSize(30);
    waitText.setFillColor(sf::Color::Blue);
    waitText.setPosition(80, 250);
    waitText.setOutlineColor(sf::Color(255, 255, 0));
    OpenText.setOutlineThickness(2);
    sf::Color background = sf::Color(255, 0, 0);

    while (Opening.isOpen())
    {
        Opening.clear(background);
        Opening.draw(OpenText);
        Opening.draw(waitText);
        Opening.display();
        open.play();
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
        Opening.close();
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Josephus Problem Visualization");

    int c = 0;
    while (q.Size() > 1)
    {
        c++;
        int top = q.front();
        q.pop();
        if (c == k)
        {
            int eliminated = top; // Store the eliminated person's number

            // Change the color of the eliminated circle to red
            circles[eliminated - 1].setFillColor(sf::Color::Red);

            // Play sound on elimination
            sound.play();

            c = 0; // Reset the counter after elimination
        }
        else
        {
            // If not eliminated, push the person back into the queue
            q.Push(top);
        }

        // Render the circles and numbers
        window.clear();
        for (int i = 0; i < circles.size(); ++i)
        {
            window.draw(circles[i]);
            window.draw(numbers[i]);
        }
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Pause for visibility
    }

    // Close the main window
    window.close();

    // Create a new window to display the winner
    sf::RenderWindow winnerWindow(sf::VideoMode(400, 200), "Winner Announcement");

    // Create text for displaying the winner
    sf::Text winnerText;
    winnerText.setFont(font2);
    winnerText.setString("The survivor is: " + std::to_string(q.front()));
    winnerText.setCharacterSize(20);
    winnerText.setPosition(20, 80); // Center the text
    winnerText.setFillColor(sf::Color(57, 255, 20));
    winnerText.setOutlineColor(sf::Color(0, 0, 139)); // Dark Blue
    winnerText.setOutlineThickness(2);
    sf::Color Back = sf::Color(57, 255, 20);

    // Main loop for the winner window
    while (winnerWindow.isOpen())
    {
        winnerWindow.clear(Back);
        winnerWindow.draw(winnerText);
        winnerWindow.display();
        finalSound.play();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        winnerWindow.close();
    }

    return q.front();
}

int main()
{
    int n, k;
    cout << "Enter the number of people (n): ";
    cin >> n;
    cout << "Enter the step count (k): ";
    cin >> k;

    if (k > 0 && n>k)
    {
        int survivor = josephus(n, k);
        cout << "The position of the last remaining person is: " << survivor << std::endl;
    }
    else
    {
        cout << "K must be greater than 0 or less than n \n";
    }

    return 0;
}
  
