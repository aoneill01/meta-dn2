#include <Gamebuino-Meta.h>
#include "BreakableTiles.h"
#include "Constants.h"

bool BreakableTiles::triggerBlockAt(int x, int y) {
    if (count >= BREAKABLE_TILES_MAX_COUNT) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (tiles[i].x == x && tiles[i].y == y) return false;
    }

    tiles[count].x = x;
    tiles[count].y = y;
    tiles[count].countdown = BREAKABLE_TILES_COUNTDOWN;

    count++;

    return true;
}

void BreakableTiles::clear() {
    count = 0;
    fragments.clear();
}

void BreakableTiles::handleTick(Level& level) {
    for (int i = 0; i < count; i++) {
        tiles[i].countdown--;
        if (tiles[i].countdown == 0) {
            fragments.add(tiles[i].x, tiles[i].y);
            level.setTile(tiles[i].x, tiles[i].y, EMPTY_TILE);

            for (int j = i; j < count - 1; j++) {
                tiles[j] = tiles[j + 1];
            }
            i--;
            count--;
            continue;
        }
        else if (tiles[i].countdown < 10) {
            level.setTile(tiles[i].x, tiles[i].y, BREAK3_TILE);
        }
        else if (tiles[i].countdown < 20) {
            level.setTile(tiles[i].x, tiles[i].y, BREAK2_TILE);
        }
        else {
            level.setTile(tiles[i].x, tiles[i].y, BREAK1_TILE);
        }
    }

    fragments.handleTick(level);
}

FragmentSprite::FragmentSprite(SQ15x16 x, SQ15x16 y) {
    this->x = x;
    this->y = y;
    velX = ((SQ15x16)random(-16, 16)) / 16;
    velY = 0;
}

SQ15x16 _gravity = 0.32;
SQ15x16 _maxFragmentVelY = 8;

bool FragmentSprite::handleTick(Level &level) {
    TileSet collidedTiles;
    tickCountdown--;

    x += velX;
    if (level.collisionsAt(getX() + 1, getY() + 2, 3, 4, collidedTiles)) {
        int backOne = velX > 0 ? -1 : 1;
        
        do {
            x += backOne;
        } 
        while(level.collisionsAt(getX() + 1, getY() + 2, 3, 4, collidedTiles));

        velX = -velX;
    }

    velY += _gravity;
    if (velY > _maxFragmentVelY) velY = _maxFragmentVelY;
    y += velY;
    if (level.collisionsAt(getX() + 1, getY() + 2, 3, 4, collidedTiles)) {
        int backOne = velY > 0 ? -1 : 1;
        
        do {
            y += backOne;
        }
        while(level.collisionsAt(getX() + 1, getY() + 2, 3, 4, collidedTiles));

        velY = -velY / 2;
    }

    return tickCountdown == 0;
}

int FragmentSprite::getX() {
  return x.getInteger();
}

int FragmentSprite::getY() {
  return y.getInteger();
}

void FragmentSprites::add(int x, int y) {
    while (count + 4 > FRAGMENT_SPRITES_MAX_COUNT) {
        for (int i = 1; i < count; i++) {
            sprites[i - 1] = sprites[i];
        }
        count--;
    }

    sprites[count] = FragmentSprite(x * LEVEL_TILE_SIZE + 2, y * LEVEL_TILE_SIZE);
    count++;
    sprites[count] = FragmentSprite(x * LEVEL_TILE_SIZE + 10, y * LEVEL_TILE_SIZE);
    count++;
    sprites[count] = FragmentSprite(x * LEVEL_TILE_SIZE + 2, y * LEVEL_TILE_SIZE + 8);
    count++;
    sprites[count] = FragmentSprite(x * LEVEL_TILE_SIZE + 10, y * LEVEL_TILE_SIZE + 8);
    count++;
}

void FragmentSprites::clear() {
    count = 0;
}

int FragmentSprites::getCount() {
    return count;
}

FragmentSprite FragmentSprites::getSprite(int index) {
    return sprites[index];
}

void FragmentSprites::handleTick(Level &level) {
    for (int i = 0; i < count; i++) {
        if (sprites[i].handleTick(level)) {
            for (int j = i + 1; j < count; j++) {
                sprites[j - 1] = sprites[j];
            }
            i--;
            count--;
        }
    }
}