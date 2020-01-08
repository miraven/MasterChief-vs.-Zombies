//
// Created by bswenson3 on 11/9/16.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameObject {
public:
	GameObject();
	virtual bool load(const std::string& filename) = 0;

	virtual void draw(sf::RenderWindow& window) = 0;

	virtual void update(float deltaT) = 0;

	virtual void setPosition(float x, float y) = 0;

	virtual void move(sf::Vector2f) = 0;

	virtual sf::Vector2f getPosition() const = 0;

	virtual float getHeight() const = 0;

	virtual float getWidth() const = 0;

	virtual void setScale(float scale) = 0;

    virtual void setRect(int left, int top, int width, int height) = 0;

    virtual int getAnimated() = 0;

    virtual void setHeightLevel(int level) = 0;

	virtual int getHeightLevel() = 0;

	virtual void setWidthLevel(int level) = 0;

	virtual int getWidthLevel() = 0;

	virtual void setCurHeightLevel(int level) = 0;

	virtual int getCurHeightLevel() = 0;

	virtual void setCurWidthLevel(int level) = 0;

	virtual int getCurWidthLevel() = 0;

	virtual void setPixDown(int pix) = 0;

	virtual int getPixDown() = 0;

	virtual void setGameRow(int row) = 0;

	virtual int getGameRow() = 0;

	virtual void setLife(int health) = 0;

	virtual int getLife() = 0;

	virtual void setGameCol(int col) = 0;

	virtual int getGameCol() = 0;

	virtual void resetPos () = 0;

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::string m_filename;
	int animated = 0;
	int h_level;
	int cur_h_level = 0;
	int w_level;
	int cur_w_level = 0;
	bool m_valid = false;
	int pix_down = 0;
	int game_row = 0;
	int game_col = 0;
	int life = 0;

};

