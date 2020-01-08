//
// Created by bswenson3 on 11/9/16.
//

#include "Game.h"
#include <random>
#include <iostream>

Game::Game() :
	m_window(sf::VideoMode(1280, 960), "Chief vs. Zombiez")
{
	//load the images/sprites
	//load the player


	/* Game Objects */

	RegularGameObject *r_obj1 = new RegularGameObject();

	r_obj1->load("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/MasterChiefOriginal.png");
	r_obj1->setHeightLevel(1);
	r_obj1->setWidthLevel(1);
	r_obj1->setScale(2.0f);
	r_obj1->setRect(0,0,50,70);
	r_obj1->setPosition(0.0f, 420.0f);

    g_obj.push_back(r_obj1);

    for (int i = 0; i < 100; i++) {
        AnimatedGameObject *a_obj2 = new AnimatedGameObject();

		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0,6);
		std::uniform_int_distribution<std::mt19937::result_type> dist15(0,15);
		int rnd6 = dist6(rng);
		int rnd15 = dist15(rng);

        a_obj2->load("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/zombie-sprite.png");
		a_obj2->setScale(2.0f);
		a_obj2->setRect(128,0,64,60);
		a_obj2->setWidthLevel(7);
		a_obj2->setHeightLevel(1);
		a_obj2->setPosition(500.0f + 100.0f * rnd15, rnd6 * 130.0f + 50.0f);
		a_obj2->setPixDown(128);
		a_obj2->setGameRow(rnd6);
		a_obj2->setGameCol(rnd15);

        g_obj.push_back(a_obj2);
    }

	// Gun sound
	if (!gun_buffer.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/gun_shot.wav")) {
		std::cout << "ERROR: NO SOUND" << std::endl;
	}
	gun_sound.setBuffer(gun_buffer);

	// Death sound
	if (!dead_buffer.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/chief_death.wav")) {
		std::cout << "ERROR: NO SOUND" << std::endl;
	}
	dead_sound.setBuffer(dead_buffer);

	if (!halo_intro.openFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/halo_intro.ogg")) {
		std::cout << "ERROR: NO MUSIC" << std::endl;
	}
	halo_intro.play();

}

void Game::run() {
	sf::Clock clock;

	while (m_window.isOpen()) {
        // Start screen
        while (m_window.isOpen() && start_game && !end_game) {
            // Display screen
            dead_sound.stop();
            processEvents();
            // Update
            if (m_return)
                start_game = false;
            render();
        }

        // Game
        while (m_window.isOpen() &&!start_game && !end_game) { // input && start_game
            sf::Time deltaT = clock.restart();
            processEvents();
            update(deltaT);
            render();
            incrementLevel();
        }

        // End screen
        while (m_window.isOpen() &&end_game && !start_game) {
            // Display screen
            processEvents();
            // Update
            if (m_escape) {
                end_game = false;
                start_game = true; // to restart game
                halo_intro.play();
                resetChief();
                m_level = 1;
                dead_sound.play();
                for (int i = 1; i < 101; i++) {
                    g_obj[i]->setLife(3);
                    g_obj[i]->resetPos();
                }
                /*if (high_score < cur_score) { I moved this to the end screen render section
                    prev_score = high_score;
                    high_score = cur_score;
                }*/
                cur_score = 0;
            }
            render();
        }
    }
}

void Game::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			//handle key down here
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isDown) {
	if (key == sf::Keyboard::Left)
		m_left = isDown;
	if (key == sf::Keyboard::Right)
		m_right = isDown;
	if (key == sf::Keyboard::Up)
		m_up = isDown;
	if (key == sf::Keyboard::Down)
		m_down = isDown;
	if (key == sf::Keyboard::Space)
	    m_space = isDown;
	if (key == sf::Keyboard::Return)
		m_return = isDown;
	if (key == sf::Keyboard::Escape)
		m_escape = isDown;
}

//use time since last update to get smooth movement
void Game::update(sf::Time deltaT) {


    //Look a vector class!
    sf::Vector2f movement(0.0f, 0.0f);
    sf::Vector2f zmovement(-20.0f, 0.0f);
    if (m_hard) {
        zmovement.x = -40.0f;
    }
    float delay = 0.15f;

    if (m_up) {
        if (g_obj[0]->getGameRow() > 0) {
            movement.y -= m_speed;
            g_obj[0]->setGameRow(g_obj[0]->getGameRow() - 1);
        }
    }
    if (m_down) {
        if (g_obj[0]->getGameRow() < 6) {
            movement.y += m_speed;
            g_obj[0]->setGameRow(g_obj[0]->getGameRow() + 1);
        }
    }
    if (m_space) {
        UpdateChief(g_obj[0]);
        gun_sound.play();
        delay = 0.1f;
        int ind = -1;
        float min_pos = MAXFLOAT;
        for (int i = 1; i < 1 + 20 * m_level; i++) {

            if (g_obj[i]->getGameRow() == g_obj[0]->getGameRow() && g_obj[i]->getPosition().x < min_pos && g_obj[i]->getLife() && g_obj[i]->getPosition().x < 1250.0f) {
                ind = i;
                min_pos = g_obj[i]->getPosition().x;
            }
        }
        if (ind != -1) {
            g_obj[ind]->setLife(g_obj[ind]->getLife() - 1);
            cur_score += 10;
            if (!g_obj[ind]->getLife()) {
                cur_score += 90;
            }
        }
    }


    for (int i = 0; i < 1 + 20 * m_level; i++) {

        int h_lev = g_obj[i]->getCurHeightLevel();
        int w_lev = g_obj[i]->getCurWidthLevel();

        if (g_obj[i]->getAnimated() && g_obj[i]->getLife()) {

            if (w_lev == g_obj[i]->getWidthLevel() - 1) {
                g_obj[i]->setCurWidthLevel(0);
                if (h_lev == g_obj[i]->getHeightLevel() - 1) {
                    g_obj[i]->setCurHeightLevel(0);
                } else {
                    g_obj[i]->setCurHeightLevel(h_lev + 1);
                }
            } else {
                g_obj[i]->setCurWidthLevel(w_lev + 1);
            }

            g_obj[i]->setRect(g_obj[i]->getWidth() * w_lev,g_obj[i]->getPixDown() + g_obj[i]->getHeight() * h_lev,g_obj[i]->getWidth(),g_obj[i]->getHeight());
            g_obj[i]->move(zmovement * deltaT.asSeconds());
            if (g_obj[i]->getPosition().x < 100.0f) {
                g_obj[0]->setLife(g_obj[0]->getLife() - 1);
                g_obj[i]->setLife(0);
            }

        } else if (!g_obj[i]->getAnimated()){
            g_obj[i]->move(movement * 0.1f);
        }
    }

    sf::Clock wait;

    while(wait.getElapsedTime().asSeconds() < delay);

}

void Game::render() {



	m_window.clear();

	// Start game
	if (start_game && !end_game){
		start_img->load("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/CvZ_start.jpg");
		start_img->draw(m_window);
		sf::Font font_start;
		font_start.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/arial.ttf");
		sf::Text text_start("Press Enter to begin",font_start,32);
		text_start.setPosition(500.0f, 800.0f);
		m_window.draw(text_start);
	}
	// Only if on game
	if (!start_game && !end_game) {
		for (int i = 0; i < 1 + 20 * m_level; i++) {
			if (g_obj[i]->getLife()) {
				g_obj[i]->draw(m_window);
			}
		}
        if (g_obj[0]->getLife() <= 0) {
            //end_game = true;
            //dead_sound.play();
            sf::Font font_end;
            font_end.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/arial.ttf");
            sf::Text text_end("You died. You suck. Get Better.",font_end,32);
            text_end.setPosition(480.0f, 400.0f);
            m_window.draw(text_end);
            m_window.display();

            sf::Clock wait;
            while(wait.getElapsedTime().asSeconds() < 5.0f);
            end_game = true;
            halo_intro.stop();
            dead_sound.play();
        }

        // Lives and Current Score
        sf::Font font_g;
        font_g.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/arial.ttf");

        std::string t_lives = std::to_string(g_obj[0]->getLife());
        std::string t_score = std::to_string(cur_score);
        sf::Text text_lives("Lives: ",font_g,24);
        sf::Text actual_lives(t_lives,font_g,24);
        sf::Text text_score("Score: ", font_g, 24);
        sf::Text actual_score(t_score,font_g,24);
        text_lives.setPosition(800.0f, 0.0f);
        text_score.setPosition(1000.0f, 0.0f);
        actual_lives.setPosition(900.0f, 0.0f);
        actual_score.setPosition(1100.0f, 0.0f);
        m_window.draw(actual_lives);
        m_window.draw(actual_score);
        m_window.draw(text_lives);
        m_window.draw(text_score);
	}

	if (!start_game && end_game){

        if (high_score < cur_score) {
            prev_score = high_score;
            high_score = cur_score;
        }
		end_img->load("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/CvZ_end.jpg");
		end_img->setPosition(210.0f, 100.0f);
		end_img->draw(m_window);
		sf::Font font_end;
		font_end.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/arial.ttf");
		sf::Text text_end("Press Escape to restart",font_end,32);
		text_end.setPosition(480.0f, 800.0f);
		m_window.draw(text_end);

        // High score and Previous High Score
        sf::Font font_x;
        font_x.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/arial.ttf");

        std::string t_hiscore = std::to_string(high_score);
        std::string t_prevscore = std::to_string(prev_score);
        sf::Text text_hiscore("High Score: ",font_x,24);
        sf::Text actual_hiscore(t_hiscore,font_x,24);
        sf::Text text_prevscore("Previous High Score: ", font_x, 24);
        sf::Text actual_prevscore(t_prevscore,font_x,24);

        text_hiscore.setPosition(400.0f, 700.0f);
        actual_hiscore.setPosition(550.0f, 700.0f);
        text_prevscore.setPosition(700.0f, 700.0f);
        actual_prevscore.setPosition(950.0f, 700.0f);


        m_window.draw(text_hiscore);
        m_window.draw(actual_hiscore);
        m_window.draw(text_prevscore);
        m_window.draw(actual_prevscore);
	}
	// End game draw

	m_window.display();


}

void Game::UpdateChief(GameObject* chief) {
    chief->setRect(55,0,50,70); // set fire frame
    render();
	//chief->draw(m_window); // draw for 0.05f seconds
    sf::Clock wait;
    while(wait.getElapsedTime().asSeconds() < 0.05f);
    chief->setRect(0,0,50,70); // set back to original frame
    render();
}

void Game::incrementLevel() {
	bool increment = true;

	for (int i = 1; i < 1 + 20 * m_level; i++) {
		if (g_obj[i]->getLife() > 0) {
			increment = false;
			break;
		}
	}

	if (increment) {
		for (int i = 1; i < 1 + 20 * m_level; i++) {
			g_obj[i]->setLife(3);
			g_obj[i]->resetPos();
		}
		if (m_hard) {
			end_game = true;
			sf::Font font_level_up;
			font_level_up.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/arial.ttf");
			sf::Text text_level_up("Congratulations!\nYou Win!", font_level_up, 32);
			text_level_up.setPosition(480.0f, 400.0f);
			m_window.draw(text_level_up);
			m_window.display();
		} else {
			if (m_level == 5) {
				m_hard = true;
			} else {
				m_level++;
			}
			sf::Font font_level_up;
			font_level_up.loadFromFile("/Users/ravenlt/Desktop/Georgia Tech/ECE 2036/Zombiez/Lab5/arial.ttf");
			sf::Text text_level_up("Next Level! Get Ready!", font_level_up, 32);
			text_level_up.setPosition(480.0f, 400.0f);
			m_window.draw(text_level_up);
			m_window.display();
		}
		sf::Clock wait;

		while(wait.getElapsedTime().asSeconds() < 5.0f);

	}
}

void Game::resetChief() {
    g_obj[0]->setPosition(0.0f, 420.0f);
    g_obj[0]->setLife(3);

}