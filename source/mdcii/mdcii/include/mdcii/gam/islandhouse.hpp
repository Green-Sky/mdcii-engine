// This file is part of the MDCII Game Engine.
// Copyright (C) 2020  Armin Schlegel
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef _ISLANDHOUSE_HPP
#define _ISLANDHOUSE_HPP

#include <experimental/optional>
#include <inttypes.h>
#include <map>
#include <string>
#include <utility>
#include <vector>

struct IslandHouseData
{
    uint16_t id; // tile gaphic ID, see haeuser.cod for referene
    uint8_t posx; // position on island
    uint8_t posy; // position on island
    uint32_t orientation : 2; // orientation
    uint32_t animationCount : 4; // animation step for tile
    uint32_t islandNumber : 8; // the island the field is part of
    uint32_t cityNumber : 3; // the city the field is part of
    uint32_t randomNumber : 5; // random number, what for?
    uint32_t playerNumber : 4; // the player that occupies this field
};

class IslandHouse
{
public:
    IslandHouse()
    {
    }
    explicit IslandHouse(uint8_t* data, uint32_t length, const char* name, uint16_t width, uint16_t height);
    explicit IslandHouse(const std::string& name, uint16_t width, uint16_t height);
    void Finalize();
    std::shared_ptr<IslandHouseData[]> GetIslandHouse();
    IslandHouseData Get(uint16_t x, uint16_t y);
    uint32_t Size();

private:
    std::string name;
    uint32_t elements;
    uint32_t rawElements;
    uint16_t width;
    uint16_t height;
    std::shared_ptr<IslandHouseData[]> rawIslandHouse;
    std::shared_ptr<IslandHouseData[]> islandHouse;
};

#endif // _ISLANDHOUSE_HPP