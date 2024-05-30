#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>
#include <string>

class MainWindow;

class Game {
public:
    Game();
    void reset();
    void initializeGame();
    void setMainWindow(MainWindow *window);
    int getPlayerHealth() const;
    int getPlayerXP() const;
    std::string getLocation() const;
    std::vector<std::string> getLocations() const;
    std::map<std::string, int> getInventory() const;
    std::string getCurrentLocation() const;
    void setPlayerXP(int xp);
    void moveLocation(const std::string &newLocation);
    void encounterDragon();
    void encounterNPC();
    bool saveGame(const std::string &fileName) const;
    void loadGame(const std::string &fileName);
    void resetGame();

private:
    MainWindow *mainWindow;
    std::string playerName;
    int playerHealth;
    int playerXP;
    std::string location;
    std::string currentLocation;
    std::map<std::string, int> inventory;
    std::vector<std::string> locations;
    std::map<std::string, std::vector<std::string>> dragonAttacks;
    std::map<std::string, std::vector<std::string>> NPC;
};

#endif // GAME_H
