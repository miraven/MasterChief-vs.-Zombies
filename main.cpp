#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Game.h"

int main()
{
	Game game;
	game.run();

	// Gun sound
	sf::SoundBuffer buffer;
	sf::Sound gun_sound;
	if (!buffer.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/machine-gun-01.wav")) {
		std::cout << "ERROR: NO SOUND" << std::endl;
	}
	gun_sound.setBuffer(buffer);
	gun_sound.play();

	return 0;
}