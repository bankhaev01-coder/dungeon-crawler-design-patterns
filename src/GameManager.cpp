#include "GameManager.h"
#include "Battlefield.h"   
#include "Hero.h"          
#include "Enemy.h"
#include "ConsoleObserver.h"
#include <conio.h>
#include <iostream>
#include "Potion.h"
#include <SFML/Config.hpp>
#include "UnitFactory.h"
#include "HeroSpriteFactory.h"
#include "EnemySpriteFactory.h"
#include "PotionSpriteFactory.h"


GameManager::GameManager() : gameOver(false), m_heroHpText(m_font) , m_eventText(m_font)  {
    field = std::make_unique<Battlefield>();
    
    if (!m_font.openFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load font, using default\n";
    }
    
    m_heroHpText.setFont(m_font);
    m_heroHpText.setCharacterSize(24);
    m_heroHpText.setFillColor(sf::Color::White);
    m_heroHpText.setPosition({10.f, 10.f});

    m_eventText.setFont(m_font);
    m_eventText.setCharacterSize(18);
    m_eventText.setFillColor(sf::Color::Yellow);
    m_eventText.setPosition({10.f, 40.f});
}

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

void GameManager::initGame() {
    const int mapWidth = 20;
    const int mapHeight = 15;

    std::vector<int> tiles(mapWidth * mapHeight, 0);

    // Заполнение стенами по краям и полом внутри
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (x == 0 || x == mapWidth-1 || y == 0 || y == mapHeight-1)
                tiles[y * mapWidth + x] = 1; // стена
            else
                tiles[y * mapWidth + x] = 0; // пол
        }
    }

    // Загружаем карту
    if (!field->loadLevel("assets/tileset.png", tiles, mapWidth, mapHeight, 32)) {
        // Если не удалось загрузить текстуру, создаём её
        sf::Image img({64, 32}, sf::Color::White);

        // Рисуем два тайла: 0 — зелёный пол, 1 — серый камень
        for (unsigned int x = 0; x < 32; ++x)
            for (unsigned int y = 0; y < 32; ++y)
                img.setPixel(sf::Vector2u(x, y), sf::Color::Green);
        for (unsigned int x = 32; x < 64; ++x)
            for (unsigned int y = 0; y < 32; ++y)
                img.setPixel(sf::Vector2u(x, y), sf::Color(100, 100, 100));
        if (!img.saveToFile("assets/tileset.png")) {
            std::cerr << "Failed to save generated tileset!" << std::endl;
        }
        // Повторная попытка
        field->loadLevel("assets/tileset.png", tiles, 10, 10, 32);
    }

    // Добавляем юнитов
    HeroSpriteFactory hf;
    EnemySpriteFactory ef;
    PotionSpriteFactory pf;

    field->addUnit(hf.createUnit(2, 2));
    field->addUnit(ef.createUnit(5, 5));
    field->addUnit(ef.createUnit(7, 3));
    field->addUnit(pf.createUnit(3, 6));
    field->addUnit(pf.createUnit(8, 8));

    notify("Level loaded! Use WASD to move/attack.");
}

void GameManager::run() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Dungeon Crawler");
    window.setFramerateLimit(60);

    while (window.isOpen() && !gameOver) {
        // Обработка событий
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                int dx = 0, dy = 0;
                bool action = false;

                switch (key->code) {
                    case sf::Keyboard::Key::W: dy = -1; action = true; break;
                    case sf::Keyboard::Key::S: dy = 1; action = true; break;
                    case sf::Keyboard::Key::A: dx = -1; action = true; break;
                    case sf::Keyboard::Key::D: dx = 1; action = true; break;
                    case sf::Keyboard::Key::Q:
                        gameOver = true;
                        notify("Game quit.");
                        break;
                    default: break;
                }

                if (action) {
                    Hero* hero = field->getHero();
                    if (hero && hero->isAlive()) {
                        int newX = hero->getX() + dx;
                        int newY = hero->getY() + dy;
                        Unit* target = field->getUnitAt(newX, newY);

                        if (target == nullptr) {
                            if (field->isCellFree(newX, newY)) {
                                field->moveUnit(hero, newX, newY);
                                notify("Hero moved.");
                            }
                        } else if (auto* enemy = dynamic_cast<Enemy*>(target)) {
                            int dmg = hero->getAttack();
                            enemy->takeDamage(dmg);
                            notify("Hero attacks Enemy for " + std::to_string(dmg) + " damage!");
                            if (!enemy->isAlive()) {
                                notify("Enemy defeated!");
                            }
                        } else if (auto* potion = dynamic_cast<Potion*>(target)) {
                            potion->use(hero);
                            notify("Hero used potion! HP restored.");
                        }

                        // Ход врагов
                        for (auto* enemy : field->getEnemies()) {
                            if (enemy->isAlive()) {
                                enemy->act(*field);
                            }
                        }
                        field->removeDeadUnits();

                        if (!field->heroAlive()) {
                            notify("Hero died. Game Over.");
                            gameOver = true;
                        } else if (!field->enemiesAlive()) {
                            notify("All enemies defeated! You win!");
                            gameOver = true;
                        }
                    }
                }
            }
        }

        // Обновление UI каждый кадр
        updateUI();

        // Отрисовка
        window.clear(sf::Color::Black);
        field->draw(window);
        window.draw(m_heroHpText);
        window.draw(m_eventText);
        window.display();
    }

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || event->is<sf::Event::KeyPressed>())
                window.close();
        }
        updateUI();
        window.clear(sf::Color::Black);
        field->draw(window);
        window.draw(m_heroHpText);
        window.draw(m_eventText);
        window.display();
    }
}

void GameManager::attach(IObserver* obs) {
    observers.push_back(obs);
}

void GameManager::notify(const std::string& event) {
    m_lastEvent = event;
    for (auto* obs : observers) obs->update(event);
}

void GameManager::updateUI() {
    Hero* hero = field->getHero();
    if (hero) {
        m_heroHpText.setString("Hero HP: " + std::to_string(hero->getHealth()) + 
                               "/" + std::to_string(hero->getMaxHealth()));
    } else {
        m_heroHpText.setString("Hero dead");
    }
    m_eventText.setString(m_lastEvent);
}