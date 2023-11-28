#pragma once
#define NOMINMAX
#include <Windows.h>
#include "GameWorld.hpp"
#include <iostream>
#include <chrono>
#include <cstdint>
#include <fstream>

#include <SFML/Graphics.hpp>

#define GLAD_GL_IMPLEMENTATION
#include <gl/GL.h>

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

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

    sf::Texture texture1;
    if (!texture1.loadFromFile("C:\\Users\\Gnovo\\OneDrive\\Desktop\\cs423 repository\\cs423.Novoa\\cs423.Novoa\\Game\\Game\\textures\\testTexture1.jpg")) {
        return -1;
    }
    sf::Texture texture2;
    if (!texture2.loadFromFile("C:\\Users\\Gnovo\\OneDrive\\Desktop\\cs423 repository\\cs423.Novoa\\cs423.Novoa\\Game\\Game\\textures\\testTexture2.jpg")) {
        return -1;
    }

    glEnable(GL_TEXTURE_2D);

    static const GLfloat cube[] = {
        -20, -20, -20,  0, 0,
        -20,  20, -20,  1, 0,
        -20, -20,  20,  0, 1,
        -20, -20,  20,  0, 1,
        -20,  20, -20,  1, 0,
        -20,  20,  20,  1, 1,

         20, -20, -20,  0, 0,
         20,  20, -20,  1, 0,
         20, -20,  20,  0, 1,
         20, -20,  20,  0, 1,
         20,  20, -20,  1, 0,
         20,  20,  20,  1, 1,

        -20, -20, -20,  0, 0,
         20, -20, -20,  1, 0,
        -20, -20,  20,  0, 1,
        -20, -20,  20,  0, 1,
         20, -20, -20,  1, 0,
         20, -20,  20,  1, 1,

        -20,  20, -20,  0, 0,
         20,  20, -20,  1, 0,
        -20,  20,  20,  0, 1,
        -20,  20,  20,  0, 1,
         20,  20, -20,  1, 0,
         20,  20,  20,  1, 1,

        -20, -20, -20,  0, 0,
         20, -20, -20,  1, 0,
        -20,  20, -20,  0, 1,
        -20,  20, -20,  0, 1,
         20, -20, -20,  1, 0,
         20,  20, -20,  1, 1, //cube 1 end

        -10, -10, -10,  0, 0,
        -10,  10, -10,  1, 0,
        -10, -10,  10,  0, 1,
        -10, -10,  10,  0, 1,
        -10,  10, -10,  1, 0,
        -10,  10,  10,  1, 1,

         10, -10, -10,  0, 0,
         10,  10, -10,  1, 0,
         10, -10,  10,  0, 1,
         10, -10,  10,  0, 1,
         10,  10, -10,  1, 0,
         10,  10,  10,  1, 1,

        -10, -10, -10,  0, 0,
         10, -10, -10,  1, 0,
        -10, -10,  10,  0, 1,
        -10, -10,  10,  0, 1,
         10, -10, -10,  1, 0,
         10, -10,  10,  1, 1,

        -10,  10, -10,  0, 0,
         10,  10, -10,  1, 0,
        -10,  10,  10,  0, 1,
        -10,  10,  10,  0, 1,
         10,  10, -10,  1, 0,
         10,  10,  10,  1, 1,

        -10, -10, -10,  0, 0,
         10, -10, -10,  1, 0,
        -10,  10, -10,  0, 1,
        -10,  10, -10,  0, 1,
         10, -10, -10,  1, 0,
         10,  10, -10,  1, 1,

        -10, -10,  10,  0, 0,
         10, -10,  10,  1, 0,
        -10,  10,  10,  0, 1,
        -10,  10,  10,  0, 1,
         10, -10,  10,  1, 0,
         10,  10,  10,  1, 1
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
    glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    //openGL end-------------------------------------------------------------------------------------------------------------


    GameWorld world;

    sf::Clock clock;
    std::chrono::time_point<std::chrono::steady_clock> fpsTimer(std::chrono::steady_clock::now());
    frame FPS{};

    while (window.isOpen()) {
        world.processEvents(window);

        FPS = std::chrono::duration_cast<frame>(std::chrono::steady_clock::now() - fpsTimer);
        if (FPS.count() >= 1) {
            fpsTimer = std::chrono::steady_clock::now();
            world.tick(window);
            //std::cout << "LastFrame: " << duration_cast<ms>(FPS).count() << "ms  |  FPS: " << FPS.count() * 60 << "\n";
        }

        //openGL start-----------------------------------------------------------------------------------------------------------
        window.setActive(true);
        glClear(GL_DEPTH_BUFFER_BIT);

        sf::Vector2i pos;
        pos = sf::Mouse::getPosition(window);

        float x = static_cast<float>(pos.x) * 200.f / static_cast<float>(window.getSize().x) - 100;
        float y = -static_cast<float>(pos.y) * 200.f / static_cast<float>(window.getSize().y) + 100;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(x, y, -100.f);
        glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
        glRotatef(clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
        glRotatef(clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);

        sf::Texture::bind(&texture1);
        glDrawArrays(GL_TRIANGLES, 0, 30);
        sf::Texture::bind(&texture2);
        glDrawArrays(GL_TRIANGLES, 30, 36);
        window.setActive(false);

        window.display();
        //openGL end-------------------------------------------------------------------------------------------------------------
    }

    return 0;
}