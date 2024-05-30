#include "game.h"
#include "mainwindow.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

Game::Game() : playerHealth(100), playerXP(0), location("Pyroklas Castle"), mainWindow(nullptr) {
    initializeGame();
}

void Game::initializeGame() {
    inventory["WaterBombs"] = 3;
    inventory["FireExtinguishers"] = 3;
    locations = {"Pyroklas Castle", "Amber Lair", "Fire Pits", "Hot Caves", "Boiling Waters", "Treasure Coast", "Volcanic Mountains"};

    dragonAttacks["Pyroklas Castle"] = {
        "A small dragon is causing havoc in the marketplace!",
        "As you're walking around you feel strange heat coming from the sewer grade, as you walk closer A FLAME SLUG attacks you!",
        "As you're patrolling around you hear strange noises coming from the basement of nearby house. You decide to enter and check what's happening. All of a sudden THE FIRE RAT jumps you from around the corner!"
    };

    dragonAttacks["Volcanic Mountains"] = {
        "You walk into the volcanic mountains. You can barely take a breath due to heavy air. In the distance you see him, the Ember Lord approaches you! You can hardly contain yourself! All of your journey has come to this very moment, legendary battle commences!"
    };

    dragonAttacks["Amber Lair"] = {
        "You enter the amber lair, air feels strange here. As you're trying to assess the situation THE FIRE SLIME attacks you!",
        "As you go deeper and deeper into a cave you hear childlike cry for help. You rush to save poor child from oppression! As you go to the source of the cries you notice it wasn't human, it's A FLAME MIMIC luring you into its grasp!",
        "You try to get some quick rest but, a dragon ambushes you from the cliffs!"
    };

    dragonAttacks["Fire Pits"] = {
        "You walk around the pit trying not to get burned by the fire. As you try to avoid lava suddenly it starts attacking you. It's A FIRE SLIME!",
        "While you come across a pit filled with hot lava you feel strong presence around you. Lava dragon flies to you and starts a battle!",
        "As you go around the area you trip and fall over! It's a trap set by A FLAME GOBLIN, as you hit the ground you tense up for the fight!"
    };

    dragonAttacks["Hot Caves"] = {
        "You enter hot caves, temperature is really different from that outside. You're trying to adapt to the temperature but as you try, THE SCORCHED SPIDER begins his attack!",
        "As you roam around the cave you see a very bright glow, almost treasure-like. You come closer to examine the light source, you note it's a trap! A FLAME GOBLIN emerges from the shadows and starts attacking!",
        "You try to go deeper into the cave but you notice a strange figure in the corner of your eye. It's A BURNED KOBOLD running straight for you!"
    };

    dragonAttacks["Boiling Waters"] = {
        "You approach water in the area. It's boiling hot! As you're focusing on the water THE FIRE LIZARD emerges and attacks you!",
        "While you're patrolling the area you hear terrifying screech. THE BOILING DRAGON notices you and closes the distance!",
        "You walk around the boiling pond in hope of finding something useful. Then as you lower your guard THE GIANT FLAME TURTLE blocks your way and begins to charge you!"
    };

    dragonAttacks["Treasure Coast"] = {
        "You see a ruined shipwreck, you try entering it in order to find old treasures. As you find a chest hidden in the ship something creeps behind you. It's A BURNING SKELETON!",
        "While going around you find yourself in an abandoned pirate city. You enter old abandoned tavern in hope there's still some loot. Before you blink your eyes HUGE FLAMING DRAGON blocks your way! You put on your best stance and enter the battle!",
        "You're in the middle of the old port city. You cannot see a single living soul in the area. As you try leaving with a disappointed look something grabs your ankle! It's a FIRE ZOMBIE OF A PIRATE! You slice the hand that grabbed you and brace for the fight!"
    };

    NPC["Pyroklas Castle"] = {
        "A merchant offers you food supplies! +1 water bomb",
        "You see two people brawling in the middle of the street, you decide to separate them, one of the men thanks you for your help and wishes you a safe trip.",
        "You see a strange individual walking around, you decide to follow him but he disappears around the corner...",
        "You walk around the town square, sight of the fountain gives you a boost of confidence, you feel like nothing can stop you now! +10XP",
        "You meet a little girl, you can tell she's been crying, you decide to give her some candy. As soon as you take some out of your bag her expression changes, she takes sweets from you and happily goes on her way. +10XP"
    };

    NPC["Amber Lair"] = {
        "You enter deeper parts of the cave. As you walk by, you see a bright glimmer in the corner of your eye. You decide to check it out. It's your lucky day! It's a hidden stash with water bombs! +3 water bombs",
        "You meet an old hermit who offers to trade some of his supplies for water bombs. You agree and he gives you a map to a hidden treasure. You go to the place marked on the map. +2 water bombs",
    };

    NPC["Fire Pits"] = {
        "You stumble upon a group of adventurers around a campfire. They share stories and give you a spare fire extinguisher they found. +1 fire extinguisher",
        "You find a hidden alcove with a cache of old supplies. Among them, you find a few water bombs. +2 water bombs",
    };

    NPC["Hot Caves"] = {
        "You come across a wounded traveler. After helping him, he thanks you by giving you a pouch of water bombs he was carrying. +2 water bombs",
        "You find an ancient inscription on the wall. Deciphering it, you uncover the location of a hidden chamber filled with valuable supplies. +3 water bombs",
    };

    NPC["Boiling Waters"] = {
        "You encounter a merchant sailing through the boiling waters. He sells you a powerful artifact in exchange for some of your supplies. +1 water bomb",
        "You discover a hidden underwater cave. Inside, you find a stash of water bombs left by previous adventurers. +2 water bombs",
    };

    NPC["Treasure Coast"] = {
        "You meet a pirate who offers to share some of his loot if you help him find a hidden treasure. After a short adventure, he gives you a portion of his findings. +3 water bombs",
        "You find an old treasure chest buried in the sand. Inside, you discover a variety of useful items, including water bombs. +2 fire extinguishers",
    };

    srand(static_cast<unsigned int>(time(nullptr)));

    currentLocation = "Pyroklas Castle";
    if (mainWindow) {
        mainWindow->logMessage("Location: " + QString::fromStdString(currentLocation));
        mainWindow->changeBackground(":/images/castle.jpg");
        mainWindow->updateLocationLabel(QString::fromStdString(currentLocation));
    }
}

void Game::setMainWindow(MainWindow *window) {
    mainWindow = window;
    if (mainWindow) {
        mainWindow->changeBackground(":/images/castle.jpg");
        mainWindow->updateLocationLabel(QString::fromStdString(currentLocation));
    }
}

int Game::getPlayerHealth() const {
    return playerHealth;
}

int Game::getPlayerXP() const {
    return playerXP;
}

std::string Game::getLocation() const {
    return location;
}

std::vector<std::string> Game::getLocations() const {
    return locations;
}

std::map<std::string, int> Game::getInventory() const {
    return inventory;
}

std::string Game::getCurrentLocation() const {
    return currentLocation;
}

void Game::setPlayerXP(int xp) {
    playerXP = xp;
}

void Game::moveLocation(const std::string &newLocation) {
    if (std::find(locations.begin(), locations.end(), newLocation) != locations.end()) {
        currentLocation = newLocation;
        if (mainWindow) {
            mainWindow->logMessage("You have moved to " + QString::fromStdString(newLocation) + " +10 XP");
            if (newLocation == "Pyroklas Castle") {
                mainWindow->changeBackground(":/images/castle.jpg");
            }
            if (newLocation == "Volcanic Mountains") {
                mainWindow->changeBackground(":/images/wulkan.jpg");
            }
            if (newLocation == "Fire Pits") {
                mainWindow->changeBackground(":/images/pit.jpg");
            }
            if (newLocation == "Hot Caves") {
                mainWindow->changeBackground(":/images/cave.jpg");
            }
            if (newLocation == "Boiling Waters") {
                mainWindow->changeBackground(":/images/waters.jpg");
            }
            if (newLocation == "Treasure Coast") {
                mainWindow->changeBackground(":/images/cove.jpg");
            }
            if (newLocation == "Amber Lair") {
                mainWindow->changeBackground(":/images/amber.jpg");
            }
        }

        if (newLocation == "Volcanic Mountains") {
            encounterDragon();  // Always trigger dragon encounter in Volcanic Mountains
        } else {
            // Randomly generate events
            int eventChance = rand() % 100;  // Generate number from 0 to 99
            if (eventChance < 60) {  // 50% chance for an event
                encounterDragon();
            } else {
                encounterNPC();
            }
        }
    }
}

void Game::encounterDragon() {
    if (dragonAttacks.find(currentLocation) != dragonAttacks.end()) {
        // Randomly select an attack
        const std::vector<std::string> &attacks = dragonAttacks[currentLocation];
        int randomIndex = rand() % attacks.size();
        std::string selectedAttack = attacks[randomIndex];

        if (mainWindow) {
            mainWindow->logMessage(QString::fromStdString(selectedAttack));
        }

        if (currentLocation == "Volcanic Mountains") {
            if (playerXP >= 300 && inventory["WaterBombs"] >= 5) {
                inventory["WaterBombs"] -= 5;
                playerXP += 50;
                if (mainWindow) {
                    mainWindow->logMessage("You used 5 Water Bombs! The Ember Lord is defeated. XP +50.");
                    mainWindow->displayGameOver2();
                }
            } else {
                playerHealth = 0;
                if (mainWindow) {
                    mainWindow->displayGameOver1();
                }
            }
        } else {
            if (inventory["WaterBombs"] > 0) {
                inventory["WaterBombs"]--;
                playerXP += 10;
                if (mainWindow) {
                    mainWindow->logMessage("You used a Water Bomb! Enemy repelled. XP +10.");
                }
                if (inventory["WaterBombs"] == 0 && inventory["FireExtinguishers"] > 0) {
                    inventory["FireExtinguishers"]--;
                    playerXP += 10;
                    if (mainWindow) {
                        mainWindow->logMessage("You have no more Water Bombs but you used a Fire Extinguisher! Enemy extinguished. XP +10.");
                    }
                }
            } else {
                playerHealth -= 20;
                if (mainWindow) {
                    mainWindow->logMessage("You have no Water Bombs or Fire Extinguishers! You took 20 damage and got XP +10 for successfully escaping. Health: " + QString::number(playerHealth));
                }
                if (playerHealth <= 0) {
                    if (mainWindow) {
                        mainWindow->displayGameOver();
                    }
                }
            }
        }
    }
}

void Game::encounterNPC() {
    if (NPC.find(currentLocation) != NPC.end()) {
        // Randomly select an NPC event
        const std::vector<std::string> &events = NPC[currentLocation];
        int randomIndex = rand() % events.size();
        std::string selectedEvent = events[randomIndex];

        if (!selectedEvent.empty()) {
            if (mainWindow) {
                mainWindow->logMessage(QString::fromStdString(selectedEvent));
            }

            // Update inventory or XP based on event content
            size_t pos;
            if ((pos = selectedEvent.find("+")) != std::string::npos) {
                std::string bonus = selectedEvent.substr(pos + 1);
                int count = 0;

                if (bonus.find("water bomb") != std::string::npos) {
                    count = std::stoi(bonus);
                    inventory["WaterBombs"] += count;
                    mainWindow->logMessage("Water Bombs added: " + QString::number(count));
                } else if (bonus.find("fire extinguisher") != std::string::npos) {
                    count = std::stoi(bonus);
                    inventory["FireExtinguishers"] += count;
                    mainWindow->logMessage("Fire Extinguishers added: " + QString::number(count));
                } else if (bonus.find("XP") != std::string::npos) {
                    count = std::stoi(bonus);
                    playerXP += count;
                    mainWindow->logMessage("XP added: " + QString::number(count));
                }
            }
        } else {
            if (mainWindow) {
                mainWindow->logMessage("Nothing interesting happens.");
            }
        }
    } else {
        if (mainWindow) {
            mainWindow->logMessage("There are no events in this location.");
        }
    }
}

bool Game::saveGame(const std::string &fileName) const {
    std::ofstream outFile(fileName);
    if (outFile) {
        outFile << playerHealth << std::endl;
        outFile << playerXP << std::endl;
        outFile << inventory.size() << std::endl;
        for (const auto &item : inventory) {
            outFile << item.first << " " << item.second << std::endl;
        }
        outFile.close();
        return true;
    } else {
        return false;
    }
}

void Game::loadGame(const std::string &fileName) {
    std::ifstream loadFile(fileName);
    if (loadFile.is_open()) {
        loadFile >> playerHealth >> playerXP;

        int inventorySize;
        loadFile >> inventorySize;

        inventory.clear();
        std::string itemName;
        int itemCount;
        for (int i = 0; i < inventorySize; ++i) {
            loadFile >> itemName >> itemCount;
            inventory[itemName] = itemCount;
        }
        loadFile.close();
    }
}

void Game::resetGame() {
    playerHealth = 100; // Reset player health
    playerXP = 0; // Reset player XP
    inventory.clear(); // Clear inventory
    currentLocation = "Pyroklas Castle"; // Reset location to Pyroklas Castle
    inventory["WaterBombs"] = 0; // Initialize inventory items
    inventory["FireExtinguishers"] = 0;

    if (mainWindow) {
        mainWindow->changeBackground(":/images/castle.jpg");
        mainWindow->updateLocationLabel(QString::fromStdString(currentLocation));
        mainWindow->updateUI(); // Ensure the UI is updated with the new game state
    }
}
