#include "TileMap.h"
#include <iostream>

bool TileMap::load(const std::string& tilesetPath, const std::vector<int>& tiles,
                   int width, int height, int tileSize) {
    if (!m_tileset.loadFromFile(tilesetPath)) {
        std::cerr << "Failed to load tileset: " << tilesetPath << std::endl;
        return false;
    }

    m_width = width;
    m_height = height;
    m_tiles = tiles;

    // Используем Triangles: 6 вершин на тайл
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(width * height * 6);

    int tilesPerRow = m_tileset.getSize().x / tileSize;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tileNumber = tiles[y * width + x];
            if (tileNumber < 0) continue;

            int tu = tileNumber % tilesPerRow;
            int tv = tileNumber / tilesPerRow;

            // Индекс первого из 6 вершин для этого тайла
            sf::Vertex* triangles = &m_vertices[(y * width + x) * 6];

            // Координаты углов тайла
            float left   = x * tileSize;
            float right  = (x + 1) * tileSize;
            float top    = y * tileSize;
            float bottom = (y + 1) * tileSize;

            // Текстурные координаты углов
            float texLeft   = tu * tileSize;
            float texRight  = (tu + 1) * tileSize;
            float texTop    = tv * tileSize;
            float texBottom = (tv + 1) * tileSize;

            // Первый треугольник (верхний левый, верхний правый, нижний левый)
            triangles[0].position = sf::Vector2f(left, top);
            triangles[1].position = sf::Vector2f(right, top);
            triangles[2].position = sf::Vector2f(left, bottom);
            triangles[0].texCoords = sf::Vector2f(texLeft, texTop);
            triangles[1].texCoords = sf::Vector2f(texRight, texTop);
            triangles[2].texCoords = sf::Vector2f(texLeft, texBottom);

            // Второй треугольник (верхний правый, нижний правый, нижний левый)
            triangles[3].position = sf::Vector2f(right, top);
            triangles[4].position = sf::Vector2f(right, bottom);
            triangles[5].position = sf::Vector2f(left, bottom);
            triangles[3].texCoords = sf::Vector2f(texRight, texTop);
            triangles[4].texCoords = sf::Vector2f(texRight, texBottom);
            triangles[5].texCoords = sf::Vector2f(texLeft, texBottom);
        }
    }
    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

bool TileMap::isSolid(int x, int y) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return true;
    int tile = m_tiles[y * m_width + x];
    return tile == 1; // 1 — стена
}