//
// Created by David Prina on 2018-12-04.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"

class RegularGameObject: public GameObject {
public:
    RegularGameObject();
    bool load(const std::string& filename);

    void draw(sf::RenderWindow& window);

    void update(float deltaT) {}

    void setPosition(float x, float y);

    void move(sf::Vector2f);

    sf::Vector2f getPosition() const;

    float getHeight() const;

    float getWidth() const;

    void setScale(float scale);

    void setRect(int left, int top, int width, int height);

    int getAnimated();

    void setHeightLevel(int level);

    int getHeightLevel();

    void setWidthLevel(int level);

    int getWidthLevel();

    void setCurHeightLevel(int level);

    int getCurHeightLevel();

    void setCurWidthLevel(int level);

    int getCurWidthLevel();

    void setPixDown(int pix);

    int getPixDown();

    void setGameRow(int row);

    int getGameRow();

    void setLife(int health);

    int getLife();

    void setGameCol(int col);

    int getGameCol();

    void resetPos ();


private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    std::string m_filename;
    int animated = 0;
    int h_level = 0;
    int cur_h_level = 0;
    int w_level = 0;
    int cur_w_level = 0;
    bool m_valid = false;
    int pix_down = 0;
    int game_row = 3;
    int game_col = 0;
    int life = 3;

};
