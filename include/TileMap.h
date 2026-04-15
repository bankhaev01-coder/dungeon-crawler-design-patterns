#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    int m_width, m_height;
    std::vector<int> m_tiles;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    bool load(const std::string& tilesetPath, const std::vector<int>& tiles,
              int width, int height, int tileSize = 32);
    bool isSolid(int x, int y) const;
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
};