//
// Created by David Prina on 2018-12-04.
//

#include "AnimatedGameObject.h"

// Constructor
AnimatedGameObject::AnimatedGameObject() {

}

bool AnimatedGameObject::load(const std::string& filename) {
    if (m_texture.loadFromFile(filename)) {
        m_filename = filename;
        m_sprite.setTexture(m_texture);
        m_valid = true;
        return true;
    }
    return false;
}

void AnimatedGameObject::draw(sf::RenderWindow& window) {
    if (m_valid)
        window.draw(m_sprite);
}

void AnimatedGameObject::move(sf::Vector2f loc) {
    if (m_valid)
        m_sprite.move(loc);
}

void AnimatedGameObject::setPosition(float x, float y) {
    if (m_valid)
        m_sprite.setPosition(x, y);
}

sf::Vector2f AnimatedGameObject::getPosition() const {
    if (m_valid)
        return m_sprite.getPosition();
    else
        return sf::Vector2f(0, 0);
}

float AnimatedGameObject::getHeight() const {
    return m_sprite.getLocalBounds().height;
}

float AnimatedGameObject::getWidth() const {
    return m_sprite.getLocalBounds().width;
}

void AnimatedGameObject::setScale(float scale) {
    if (m_valid)
        m_sprite.setScale(scale, scale);
}

void AnimatedGameObject::setRect(int left, int top, int width, int height) {
    if (m_valid)
        m_sprite.setTextureRect(sf::IntRect(left,top,width,height));
}

int AnimatedGameObject::getAnimated() {
    return animated;
}

void AnimatedGameObject::setHeightLevel(int level) {
    h_level = level;
}

int AnimatedGameObject::getHeightLevel() {
    return h_level;
}

void AnimatedGameObject::setWidthLevel(int level) {
    w_level = level;
}

int AnimatedGameObject::getWidthLevel() {
    return w_level;
}

void AnimatedGameObject::setCurHeightLevel(int level) {
    cur_h_level = level;
}

int AnimatedGameObject::getCurHeightLevel() {
    return cur_h_level;
}

void AnimatedGameObject::setCurWidthLevel(int level) {
    cur_w_level = level;
}

int AnimatedGameObject::getCurWidthLevel() {
    return cur_w_level;
}

void AnimatedGameObject::setPixDown(int pix) {
    pix_down = pix;
}

int AnimatedGameObject::getPixDown() {
    return pix_down;
}

void AnimatedGameObject::setGameRow(int row) {
    game_row = row;
}

int AnimatedGameObject::getGameRow() {
    return game_row;
}

void AnimatedGameObject::setLife(int health) {
    life = health;
}

int AnimatedGameObject::getLife() {
    return life;
}

void AnimatedGameObject::setGameCol(int col){
    game_col = col;
}

int AnimatedGameObject::getGameCol(){
    return game_col;
}

void AnimatedGameObject::resetPos(){
    setPosition(500.0f + 100.0f * game_col, game_row * 130.0f + 50.0f);
}
