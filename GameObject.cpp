//
// Created by bswenson3 on 11/9/16.
//

#include "GameObject.h"

GameObject::GameObject() {

}

bool GameObject::load(const std::string& filename) {
	if (m_texture.loadFromFile(filename)) {
		m_filename = filename;
		m_sprite.setTexture(m_texture);
		m_valid = true;
		return true;
	}
	return false;
}

void GameObject::draw(sf::RenderWindow& window) {
	if (m_valid)
		window.draw(m_sprite);
}

void GameObject::move(sf::Vector2f loc) {
	if (m_valid)
		m_sprite.move(loc);
}

void GameObject::setPosition(float x, float y) {
	if (m_valid)
		m_sprite.setPosition(x, y);
}

sf::Vector2f GameObject::getPosition() const {
	if (m_valid)
		return m_sprite.getPosition();
	else
		return sf::Vector2f(0, 0);
}

float GameObject::getHeight() const {
	return m_sprite.getLocalBounds().height;
}

float GameObject::getWidth() const {
	return m_sprite.getLocalBounds().width;
}

void GameObject::setScale(float scale) {
	if (m_valid)
		m_sprite.setScale(scale, scale);
}

void GameObject::setRect(int left, int top, int width, int height) {
    if (m_valid)
        m_sprite.setTextureRect(sf::IntRect(left,top,width,height));
}

int GameObject::getAnimated() {
	return animated;
}

void GameObject::setHeightLevel(int level) {
	h_level = level;
}

int GameObject::getHeightLevel() {
	return h_level;
}

void GameObject::setWidthLevel(int level) {
	w_level = level;
}

int GameObject::getWidthLevel() {
	return w_level;
}

void GameObject::setCurHeightLevel(int level) {
	cur_h_level = level;
}

int GameObject::getCurHeightLevel() {
	return cur_h_level;
}

void GameObject::setCurWidthLevel(int level) {
	cur_w_level = level;
}

int GameObject::getCurWidthLevel() {
	return cur_w_level;
}

void GameObject::setPixDown(int pix) {
	pix_down = pix;
}

int GameObject::getPixDown() {
	return pix_down;
}

void GameObject::setGameRow(int row) {
	game_row = row;
}

int GameObject::getGameRow() {
	return game_row;
}

void GameObject::setLife(int health) {
	life = health;
}

int GameObject::getLife() {
	return life;
}

void GameObject::setGameCol(int col){
	game_col = col;
}

int GameObject::getGameCol(){
	return game_col;
}

void GameObject::resetPos(){
	setPosition(500.0f + 100.0f * game_col, game_row * 130.0f + 50.0f);
}
