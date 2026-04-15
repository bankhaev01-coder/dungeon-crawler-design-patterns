#include "GameManager.h"
#include "ConsoleObserver.h"

int main() {
    GameManager& gm = GameManager::getInstance();
    ConsoleObserver obs;
    gm.attach(&obs);
    gm.initGame();
    gm.run();
    return 0;
}