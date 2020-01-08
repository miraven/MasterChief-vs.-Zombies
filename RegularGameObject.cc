//
// Created by David Prina on 2018-12-04.
//

#include "RegularGameObject.h"

RegularGameObject::RegularGameObject(){

}

bool RegularGameObject::load(const std::string& filename) {
    if (m_texture.loadFromFile(filename)) {
        m_filename = filename;
        m_sprite.setTexture(m_texture);
        m_valid = true;
        return true;
    }
    return false;
}

void RegularGameObject::draw(sf::RenderWindow& window) {
    if (m_valid)
        window.draw(m_sprite);
}

void RegularGameObject::move(sf::Vector2f loc) {
    if (m_valid)
        m_sprite.move(loc);
}

void RegularGameObject::setPosition(float x, float y) {
    if (m_valid)
        m_sprite.setPosition(x, y);
}

sf::Vector2f RegularGameObject::getPosition() const {
    if (m_valid)
        return m_sprite.getPosition();
    else
        return sf::Vector2f(0, 0);
}

float RegularGameObject::getHeight() const {
    return m_sprite.getLocalBounds().height;
}

float RegularGameObject::getWidth() const {
    return m_sprite.getLocalBounds().width;
}

void RegularGameObject::setScale(float scale) {
    if (m_valid)
        m_sprite.setScale(scale, scale);
}

void RegularGameObject::setRect(int left, int top, int width, int height) {
    if (m_valid)
        m_sprite.setTextureRect(sf::IntRect(left,top,width,height));
}

int RegularGameObject::getAnimated() {
    return animated;
}

void RegularGameObject::setHeightLevel(int level) {
    h_level = level;
}

int RegularGameObject::getHeightLevel() {
    return h_level;
}

void RegularGameObject::setWidthLevel(int level) {
    w_level = level;
}

int RegularGameObject::getWidthLevel() {
    return w_level;
}

void RegularGameObject::setCurHeightLevel(int level) {
    cur_h_level = level;
}

int RegularGameObject::getCurHeightLevel() {
    return cur_h_level;
}

void RegularGameObject::setCurWidthLevel(int level) {
    cur_w_level = level;
}

int RegularGameObject::getCurWidthLevel() {
    return cur_w_level;
}

void RegularGameObject::setPixDown(int pix) {
    pix_down = pix;
}

int RegularGameObject::getPixDown() {
    return pix_down;
}

void RegularGameObject::setGameRow(int row) {
    game_row = row;
}

int RegularGameObject::getGameRow() {
    return game_row;
}

void RegularGameObject::setLife(int health) {
    life = health;
}

int RegularGameObject::getLife() {
    return life;
}

void RegularGameObject::setGameCol(int col){
    game_col = col;
}

int RegularGameObject::getGameCol(){
    return game_col;
}

void RegularGameObject::resetPos(){
    setPosition(500.0f + 100.0f * game_col, game_row * 130.0f + 50.0f);
}
