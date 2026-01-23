#include "GameLevel.h"

#include <fstream>
#include <sstream>


void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight) {
    this->Bricks.clear();

    GameLevel level;

    if (std::ifstream fstream(file); fstream) {
        std::vector<std::vector<unsigned int>> tileData;
        unsigned int tileCode;
        std::string line;

        while (std::getline(fstream, line)) {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;

            while (sstream >> tileCode) {
                row.push_back(tileCode);
            }

            tileData.push_back(row);
        }

        if (!tileData.empty()) {
            this->init(tileData, levelWidth, levelHeight);
        }
    }
}

void GameLevel::Draw(SpriteRenderer &renderer) {
    for (GameObject &tile : this->Bricks) {
        if (!tile.destroyed) {
            tile.Draw(renderer);
        }
    }
}

bool GameLevel::isCompleted() {
    for (const GameObject &tile : this->Bricks) {
        if (!tile.isSolid && !tile.destroyed) {
            return false;
        }
    }

    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();

    float unit_width = static_cast<float>(levelWidth) / static_cast<float>(width);
    float unit_height = static_cast<float>(levelHeight) / static_cast<float>(height);


    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (tileData[y][x] == SOLID) {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);

                GameObject object(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                object.isSolid = true;

                this->Bricks.push_back(object);
            }
            else if (tileData[y][x] > SOLID) {
                auto color = glm::vec3(1.0f); // white base color

                switch(tileData[y][x]) {
                    case BREAKABLE_RED: color = glm::vec3(1.0f, 0.0f, 0.0f); break;
                    case BREAKABLE_GREEN: color = glm::vec3(0.0f, 0.7f, 0.0f); break;
                    case BREAKABLE_BLUE: color = glm::vec3(0.2f, 0.6f, 1.0f); break;
                    case BREAKABLE_YELLOW: color = glm::vec3(0.8f, 0.8f, 0.4f); break;
                    default: break;
                }

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);

                this->Bricks.emplace_back(pos, size, ResourceManager::GetTexture("block"), color);
            }
        }
    }
}