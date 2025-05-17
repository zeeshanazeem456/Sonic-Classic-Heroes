#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class Menu {
private:
	// Music for whole Menu in a loop
	// Background Sprite
	RenderWindow& window;	// Window jismein game hogi
	Font menuFont;		// Fonts jo ki menu ke liye istemal hongi
	Text* option;		// Total Options ka pointer to an array
	int selectedOption;	// Currently jis option pr hai
	int totalOptions;	// Total Number of options
	Music buttonMusic;	// Jb button click hoga tb ek music bajega wo ismein store hoga
	Text* levelOptions; // New Game ke baad level Options dega
	Text* optionsMenuText;	// Options shown after clicking Options
	Music menuMusic;
	Sprite bgMenu;
	Texture bg;
public:

	// Constructor jo ki window, font aur totalOptions lega
	// Baaki kuch attributes ko mein manually khud set karonga kyu ki wo same hi rahengey for each call
	Menu(RenderWindow& win) : window(win) {

		// Loading menu fonts
		if (!menuFont.loadFromFile("Fonts/MenuSonic.ttf")) {
			cout << "Error: Could not load menu font file, lad!" << endl;
		}
		Text menuText;
		menuText.setFont(menuFont);

		if (!bg.loadFromFile("Data/menuBackground.png")) {
			cout << "Error: Could not load menu font file, lad!" << endl;
		}
		bgMenu.setTexture(bg);
		bgMenu.setScale(2.4, 3.7);

		menuText.setFont(menuFont);


		// Total Options jo ki menu mein available hongey
		this->totalOptions = 5;


		menuMusic.openFromFile("Sound Effects/menu.mp3");
		menuMusic.setVolume(50);
		menuMusic.play();
		menuMusic.setLoop(true);

		// Music for button changing
		if (!buttonMusic.openFromFile("Sound Effects/Global/Menubutton.wav")) {
			cout << "Error: Could not load music file lad.\n";
		}

		// array of options jismein Text store hoga
		option = new Text[totalOptions];
		levelOptions = new Text[5];
		optionsMenuText = new Text[3];


		// Seeting Option 1
		option[0].setFont(menuFont);
		option[0].setString("New Game");
		option[0].setPosition(360, 280);
		option[0].setCharacterSize(65);

		// Setting Option 2
		option[1].setFont(menuFont);
		option[1].setString("Options");
		option[1].setPosition(400, 350);
		option[1].setCharacterSize(65);

		// Setting Option 3
		option[2].setFont(menuFont);
		option[2].setString("Continue");
		option[2].setPosition(380, 420);
		option[2].setCharacterSize(65);

		// Setting Option 4
		option[3].setFont(menuFont);
		option[3].setString("Leader Board");
		option[3].setPosition(280, 490);
		option[3].setCharacterSize(65);

		// Setting Option 5
		option[4].setFont(menuFont);
		option[4].setString("Exit");
		option[4].setPosition(520, 560);
		option[4].setCharacterSize(65);


		for (int i = 0; i < 5; i++) {
			levelOptions[i].setFont(menuFont);
			levelOptions[i].setCharacterSize(65);
		}

		levelOptions[0].setString("Level 1");
		levelOptions[1].setString("Level 2");
		levelOptions[2].setString("Level 3");
		levelOptions[4].setString("Back");
		levelOptions[3].setString("Boss Level");


		levelOptions[0].setPosition(450, 300);
		levelOptions[1].setPosition(450, 400);
		levelOptions[2].setPosition(450, 500);
		levelOptions[4].setPosition(500, 700);
		levelOptions[3].setPosition(360, 600);

		optionsMenuText[0].setFont(menuFont);
		optionsMenuText[1].setFont(menuFont);
		optionsMenuText[2].setFont(menuFont);
		optionsMenuText[0].setCharacterSize(65);
		optionsMenuText[1].setCharacterSize(65);
		optionsMenuText[2].setCharacterSize(65);



		// Selected option ko start pr rakha hai initially
		selectedOption = 0;
	}

	// Ye function option return krega ki konsa option select kiya hai user ne
	int showMenu() {

		selectedOption = 0;
		// Loop jb tk window open hai
		while (window.isOpen()) {
			Event e;
			// Loop jb jb event occurrance ho
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {
					return -1;    // Exit screen agr exit pr user click krey
				}
				// Agr koi keypress howi hai
				if (e.type == Event::KeyPressed) {


					// Jb user enter krey wo option return krdo
					if (e.key.code == Keyboard::Enter) {
						return selectedOption; // Return selected option
					}

					// Checking ki wo UP hai ya DOWN
					if (e.key.code == Keyboard::Down) {
						buttonMusic.play(); // Button Music run hogi
						// +1 isi liye krwa rha kyu ki when pressed down toh wo neechey ayega aur incase jb last option pr +1 hoga toh modulus lekr usko 0 remainder dega
						selectedOption = (selectedOption + 1) % 5; // Neechey jayega
					}
					if (e.key.code == Keyboard::Up) {
						buttonMusic.play(); // Button Music run hogi
						// -1 is liye kyu ki oper hojayega uskey saath + totalOptions isi liye krwa rhe kyu ki jb top (start game) pr UP press hoga toh wo modulus lekr last optiondega jiski wajah se end pr ajayega
						selectedOption = (selectedOption - 1 + 5) % 5; // Oper jayega
					}

				}
			}


			// Ye implement krengey ki jb jis option pr hai wo Green hojaye baaki saarey White rahengey
			for (int i = 0; i < totalOptions; i++) {
				option[i].setFillColor((selectedOption == i) ? Color::Magenta : Color::White);
			}


			// Drawing the things & Display screen ke oper
			window.clear(); // Clear isi liye taaki pechley frames chaley jayey. koi galat na ho due to previous
			//window.draw(backgroundSprite);

			window.draw(bgMenu);
			// baari baari sab options ko draw krega
			for (int i = 0; i < totalOptions; i++) {
				window.draw(option[i]);
			}

			window.display();

		}
	}

	int newGameMenu() {
		selectedOption = 0;
		// Loop jb tk window open hai
		while (window.isOpen()) {
			Event e;
			// Loop jb jb event occurrance ho
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {
					return -1;    // Exit screen agr exit pr user click krey
				}
				// Agr koi keypress howi hai
				if (e.type == Event::KeyPressed) {


					// Jb user enter krey wo option return krdo
					if (e.key.code == Keyboard::Enter) {
						return selectedOption; // Return selected option
					}

					// Checking ki wo UP hai ya DOWN
					if (e.key.code == Keyboard::Down) {
						buttonMusic.play(); // Button Music run hogi
						// +1 isi liye krwa rha kyu ki when pressed down toh wo neechey ayega aur incase jb last option pr +1 hoga toh modulus lekr usko 0 remainder dega
						selectedOption = (selectedOption + 1) % 5; // Neechey jayega
					}
					if (e.key.code == Keyboard::Up) {
						buttonMusic.play(); // Button Music run hogi
						// -1 is liye kyu ki oper hojayega uskey saath + totalOptions isi liye krwa rhe kyu ki jb top (start game) pr UP press hoga toh wo modulus lekr last optiondega jiski wajah se end pr ajayega
						selectedOption = (selectedOption - 1 + 5) % 5; // Oper jayega
					}

				}
			}



			// Ye implement krengey ki jb jis option pr hai wo Green hojaye baaki saarey White rahengey
			for (int i = 0; i < 5; i++) {
				levelOptions[i].setFillColor((selectedOption == i) ? Color::Magenta : Color::White);
			}


			// Drawing the things & Display screen ke oper
			window.clear(); // Clear isi liye taaki pechley frames chaley jayey. koi galat na ho due to previous
			//window.draw(backgroundSprite);


			window.draw(bgMenu);

			// baari baari sab options ko draw krega
			for (int i = 0; i < 5; i++) {
				window.draw(levelOptions[i]);
			}
			window.display();

		}
	}


	int optionsMenu() {

		static int volume = 100;
		selectedOption = 0;
		static bool isMusicOn = true;

		if (isMusicOn == true) {
			optionsMenuText[0].setString("Music: ON");
		}
		else {
			optionsMenuText[0].setString("Music: OFF");
		}

		optionsMenuText[1].setString("Volume: " + to_string(volume));
		optionsMenuText[2].setString("Back");


		optionsMenuText[0].setPosition(600, 400);
		optionsMenuText[1].setPosition(600, 500);
		optionsMenuText[2].setPosition(600, 600);

		// Loop jb tk window open hai
		while (window.isOpen()) {
			Event e;
			// Window mein evenets ko handle krna
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed) {
					window.close();
					break;
				}



				// Agr koi event mein key
				if (e.type == Event::KeyPressed) {

					// Music on/off ki facility
					if (selectedOption == 0 && e.key.code == Keyboard::Enter) {
						isMusicOn = !isMusicOn;
						menuMusic.setVolume(isMusicOn ? volume : 0);	// agr musicOn hai toh volume wali value pr chaley nhi toh 0
						optionsMenuText[0].setString("Music: " + string(isMusicOn ? "ON" : "OFF"));
					}

					// Volume ko oper neechey ka feature
					if (selectedOption == 1) {
						if (e.key.code == Keyboard::Right) {
							buttonMusic.play();
							if (volume < 100) {
								volume = volume + 10;
								optionsMenuText[1].setString("Volume: " + to_string(volume));
								if (isMusicOn) {
									menuMusic.setVolume(volume);
								}
							}

						}
						if (e.key.code == Keyboard::Left) {
							buttonMusic.play();
							if (volume > 0) {
								volume = volume - 10;
								optionsMenuText[1].setString("Volume: " + to_string(volume));
								if (isMusicOn) {
									menuMusic.setVolume(volume);
								}
							}

						}
					}

					// Agr user back option pr click krey toh bs exit krdey is screen se aur automatically pechli screen pr jayega
					if (selectedOption == 2 && e.key.code == Keyboard::Enter) {
						return -1;
					}

					// Changing option feature
					if (e.key.code == Keyboard::Down) {
						buttonMusic.play();
						selectedOption = (selectedOption + 1) % 3;
					}
					if (e.key.code == Keyboard::Up) {
						buttonMusic.play();
						selectedOption = (selectedOption - 1 + 3) % 3;
					}
				}
			}



			// Ye implement krengey ki jb jis option pr hai wo Green hojaye baaki saarey White rahengey
			for (int i = 0; i < 3; i++) {
				optionsMenuText[i].setFillColor((selectedOption == i) ? Color::Magenta : Color::White);
			}


			// Drawing the things & Display screen ke oper
			window.clear(); // Clear isi liye taaki pechley frames chaley jayey. koi galat na ho due to previous
			//window.draw(backgroundSprite);


			window.draw(bgMenu);


			// baari baari sab options ko draw krega
			for (int i = 0; i < 3; i++) {
				window.draw(optionsMenuText[i]);
			}
			window.display();

		}
	}


	void stopMusic() {
		selectedOption = 0;
		menuMusic.setVolume(0);
	}

	// Destructor taaki memory unaalocate krey aur PC ki sehat achi rhe
	~Menu() {
		delete[] option;
		delete[] levelOptions;
		delete[] optionsMenuText;
	}
};