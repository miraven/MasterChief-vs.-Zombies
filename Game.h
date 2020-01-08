//
// Created by bswenson3 on 11/9/16.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "RegularGameObject.h"
#include "AnimatedGameObject.h"

class Game {
public:
	//use default screen size
	Game();
	//run the game
	void run();

private:
	void processEvents();
	//update the game objects
	void update(sf::Time deltaT);
	//draw the scene
	void render();
	//handle input from the user
	void handlePlayerInput(sf::Keyboard::Key key, bool isDown);
    // Update Chief animation
	void UpdateChief(GameObject* chief);
	// Reset chief position
	void resetChief();
	// Increment Levels
	void incrementLevel();
	// Render Window
	sf::RenderWindow m_window;
	// Gun sound
	sf::Sound gun_sound;
	sf::SoundBuffer gun_buffer;
	// Death sound
	sf::Sound dead_sound;
	sf::SoundBuffer dead_buffer;
	// Opening music
	sf::Music halo_intro;
    // Game Object vector
	std::vector<GameObject*> g_obj;
    // Start screen object
    RegularGameObject* start_img = new RegularGameObject();
    // End screen object
    RegularGameObject* end_img = new RegularGameObject();


    //TODO::these should be moved to game object
	float m_speed = 1300.0f;
	bool m_left = false;
	bool m_right = false;
	bool m_up = false;
	bool m_down = false;
	bool m_space = false;
	bool m_return = false;
	bool m_escape = false;
	bool start_game = true; // put as true because this is start game screen
	bool end_game = false;  // put as false since not end game screen
    int m_level = 1;
    bool m_hard = false;
    int high_score = 0;
    int cur_score = 0;
    int prev_score = 0;
};

