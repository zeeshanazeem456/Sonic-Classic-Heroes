#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Menu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "BossLevel.h"
#include "Health.h"
using namespace sf;
using namespace std;
class GameManager {
protected:
	RenderWindow window;
	bool isPaused;
	int screen_x = 1200;
	int screen_y = 900;
	Menu menu;
	Level1 level_1;
	Level2 level_2;
	Level3 level_3;
	BossLevel bosslevel;
	Health health;
	int characterIndex;
public:
	GameManager():window(VideoMode(1200, 900), "Sonic the Hedgehog-OOP", Style::Close) , menu(window) {
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(60);
	}
	void handleEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	void update(int op) {
		if (op == 0)
			level_1.LevelHandleInput();
		else if (op == 1)
			level_2.LevelHandleInput();
		else if (op == 2)
			level_3.LevelHandleInput();
		else if (op == 3)
			bosslevel.LevelHandleInput();
	}
	void render(int op) {
		
		window.clear();
		if(op == 0)
			level_1.display_level(window);
		if (op == 1) {
			level_2.display_level(window);
		}
		if (op == 2) {
			level_3.display_level(window);
		}
		if (op == 3)
			bosslevel.display_level(window);
		window.display();
	}

	void playGame() {
		int selectedOption = menu.showMenu();
		int NewGameOption = menu.newGameMenu();
		while (true) {
			if (selectedOption == 0) {
				if (NewGameOption != 4) {
					menu.stopMusic();
				}
				if (NewGameOption == 0) {
					menu.stopMusic();
					level_1.startMusic();
					while (window.isOpen()) {
						handleEvents();
						if (level_1.isComplete()) {
							NewGameOption == 1;
							characterIndex = level_1.getCh();
							break;
						}
						update(0);
						render(0);
					}
					level_2.startMusic();
					level_2.setCh(characterIndex);
					while (window.isOpen()) {
						handleEvents();
						if (level_2.isComplete()) {
							NewGameOption == 2;
							characterIndex = level_2.getCh();
							break;
						}
						update(1);
						render(1);
					}
					level_2.startMusic();
					level_3.setCh(characterIndex);
					while (window.isOpen()) {
						handleEvents();
						if (level_3.isComplete()) {
							NewGameOption == 2;
							characterIndex = level_3.getCh();
							break;
						}
						update(2);
						render(2);
					}
					bosslevel.startMusic();
					while (window.isOpen()) {
						handleEvents();
						update(3);
						render(3);
					}
				}
				if (NewGameOption == 1) {
					menu.stopMusic();
					level_2.startMusic();
					while (window.isOpen()) {
						handleEvents();
						update(1);
						render(1);

					}
				}
				else if (NewGameOption == 4) {
					window.close();
					break;
				}
				else if (NewGameOption == 2) {
					menu.stopMusic();
					level_2.startMusic();
					while (window.isOpen()) {
						handleEvents();
						update(2);
						render(2);

					}
				}
				else if (NewGameOption == 3) {
					menu.stopMusic();
					bosslevel.startMusic();
					while (window.isOpen()) {
						handleEvents();
						update(3);
						render(3);
					}
				}
			}
			else if (selectedOption == 1) {
				int s = menu.optionsMenu();
				if (s != -1) {
					menu.stopMusic();
				}
			}
			else if (selectedOption == 2) {
				// Continue option
			}
			else if (selectedOption == 3) {
				// :eaderboard
			}
			else if (selectedOption == 4) {
				window.close();
				break;
			}
		}
	}
};
