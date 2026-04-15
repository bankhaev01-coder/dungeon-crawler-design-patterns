#pragma once
#include <vector>
#include <memory>
#include <string>
#include "IObserver.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Battlefield;

class GameManager {
private:
    GameManager();
    std::unique_ptr<Battlefield> field;
    std::vector<IObserver*> observers;
    bool gameOver;
    
    sf::Font m_font;
    sf::Text m_heroHpText;
    sf::Text m_eventText;
    std::string m_lastEvent;
    void updateUI();

public:
    static GameManager& getInstance();
    void initGame();
    void run();
    void attach(IObserver* obs);
    void notify(const std::string& event);
    Battlefield* getField() { return field.get(); }
    void setGameOver(bool val) { gameOver = val; }
};