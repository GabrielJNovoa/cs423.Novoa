#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
//sfml
#ifndef GLAD_GL_IMPLEMENTATION
#define GLAD_GL_IMPLEMENTATION
#endif
#include <gl/GL.h>
#include <SFML/Graphics.hpp>
//stl
#include <vector>
#include <chrono>
#include <fstream>
#include <iostream>
//other
#include "GameObject.h"
#include "GameWorld.h"
#include "PhysicsObject.h"
#include "GraphicsObject.h"
#include "InputObject.h"
#include "Player.hpp"
#include "WallBlock.hpp"

//https://www.gamedev.net/forums/topic/690860-60-fps-game-loop-using-stdchrono/

using frame = std::chrono::duration<int32_t, std::ratio<1, 60>>;
using ms = std::chrono::duration<float, std::milli>;

int main()
{
    std::ofstream test("textures\\test.txt");
    test << "test";
    test.close();

    sf::ContextSettings settings;

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;

    sf::Window window(sf::VideoMode(640, 480), "Game!", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);
    std::cout << "openGL version: " << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << "\n";

    //openGL start-----------------------------------------------------------------------------------------------------------
    window.setActive(true);    

    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glViewport(0, 0, static_cast<GLsizei>(window.getSize().x), static_cast<GLsizei>(window.getSize().y));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    

    //openGL end-------------------------------------------------------------------------------------------------------------

    sf::Clock clock;
    std::chrono::time_point<std::chrono::steady_clock> fpsTimer(std::chrono::steady_clock::now());
    frame FPS{};
    
    //physics chunk size of 10, so no hitbox can be larger than 5.
    GameWorld world(&window, 1000,100);
    world.setWindow(&window);
    world.loadTexture("C:\\Users\\Gnovo\\OneDrive\\Desktop\\cs423 repository\\cs423.Novoa\\cs423.Novoa\\Game\\Game\\textures\\wall.png");

    Player* player = new Player;
    player->setWindow(&window);

    std::vector<WallBlock*> walls;

    for (int i = 0; i < 8 + 8 + 1 + 12; i++) {
        walls.push_back(new WallBlock);
    }

    walls[0]->setPosition(0 * 40, 0 * 40, -1 * 40);
    walls[1]->setPosition(1 * 40, 0 * 40, -1 * 40);
    walls[2]->setPosition(2 * 40, 0 * 40, -1 * 40);
    walls[3]->setPosition(0 * 40, 1 * 40, -1 * 40);
    walls[4]->setPosition(0 * 40, 2 * 40, -1 * 40);
    walls[5]->setPosition(2 * 40, 1 * 40, -1 * 40);
    walls[6]->setPosition(1 * 40, 2 * 40, -1 * 40);
    walls[7]->setPosition(2 * 40, 2 * 40, -1 * 40);

    walls[8]->setPosition(0 * 40, 0 * 40, 1 * 40);
    walls[9]->setPosition(1 * 40, 0 * 40, 1 * 40);
    walls[10]->setPosition(2 * 40, 0 * 40, 1 * 40);
    walls[11]->setPosition(0 * 40, 1 * 40, 1 * 40);
    walls[12]->setPosition(0 * 40, 2 * 40, 1 * 40);
    walls[13]->setPosition(2 * 40, 1 * 40, 1 * 40);
    walls[14]->setPosition(1 * 40, 2 * 40, 1 * 40);
    walls[15]->setPosition(2 * 40, 2 * 40, 1 * 40);

    walls[16]->setPosition(1 * 40, 1 * 40, 0 * 40);

    walls[17]->setPosition(-1 * 40, 0 * 40, 0 * 40);
    walls[18]->setPosition(-1 * 40, 1 * 40, 0 * 40);
    walls[19]->setPosition(-1 * 40, 2 * 40, 0 * 40);
    walls[20]->setPosition(0 * 40, -1 * 40, 0 * 40);
    walls[21]->setPosition(1 * 40, -1 * 40, 0 * 40);
    walls[22]->setPosition(2 * 40, -1 * 40, 0 * 40);
    walls[23]->setPosition(3 * 40, 0 * 40, 0 * 40);
    walls[24]->setPosition(3 * 40, 1 * 40, 0 * 40);
    walls[25]->setPosition(3 * 40, 2 * 40, 0 * 40);
    walls[26]->setPosition(0 * 40, 3 * 40, 0 * 40);
    walls[27]->setPosition(1 * 40, 3 * 40, 0 * 40);
    walls[28]->setPosition(2 * 40, 3 * 40, 0 * 40);


    world.addGameObject(player);
    world.addInputObject(player);
    world.addPhysicsObject(player);
    world.setCamera(player);

    for (auto i : walls) {
        world.addGameObject(i);
        world.addGraphicsObject(i);
        world.addPhysicsObject(i);
    }

    while (window.isOpen()) {

        window.setActive(true);
        glClear(GL_DEPTH_BUFFER_BIT);

        world.processEvents();

        FPS = std::chrono::duration_cast<frame>(std::chrono::steady_clock::now() - fpsTimer);
        if (FPS.count() >= 1) {
            fpsTimer = std::chrono::steady_clock::now();
            world.tick(window);
            //std::cout << "LastFrame: " << duration_cast<ms>(FPS).count() << "ms  |  FPS: " << FPS.count() * 60 << "\n";
        }

        window.setActive(false);

        window.display();
    }

    return 0;
}