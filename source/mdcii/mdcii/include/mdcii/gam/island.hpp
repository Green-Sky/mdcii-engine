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

#ifndef _ISLAND_HPP
#define _ISLAND_HPP

#include <inttypes.h>
#include <string>
#include <vector>

#include "productionlist.hpp"
#include "warehouse.hpp"

struct IslandHouseData
{
  uint16_t id;                 // tile gaphic ID, see haeuser.cod for referene
  uint8_t posx;                // position on island
  uint8_t posy;                // position on island
  uint32_t orientation : 2;    // orientation
  uint32_t animationCount : 4; // animation step for tile
  uint32_t islandNumber : 8;   // the island the field is part of
  uint32_t cityNumber : 3;     // the city the field is part of
  uint32_t randomNumber : 5;   // random number, what for?
  uint32_t playerNumber : 4;   // the player that occupies this field
};

class IslandHouse
{
public:
  IslandHouse()
  {
  }
  explicit IslandHouse(uint8_t* data, uint32_t length, const char* name);

private:
  std::string name;
  std::vector<IslandHouseData> islandHouse;
};


struct OreMountainData // Erzberg
{
  uint8_t ware;        // which good lays here?
  uint8_t posx;        // position on island x
  uint8_t posy;        // position on island y
  uint8_t playerflags; // which player knows this secret? (DANGER: PLAYER_MAX)
  uint8_t kind;        // which kind?
  uint8_t empty;       // empty
  uint16_t stock;      // how much of this good lays here?
};

enum class Fertility : uint32_t
{
  Random = 0x0000,
  None = 0x1181,
  TobaccoOnly = 0x1183,
  WineOnly = 0x11A1,
  SugarOnly = 0x1189,
  CocoaOnly = 0x11C1,
  WoolOnly = 0x1191,
  SpicesOnly = 0x1185,
  TobaccoAndSpices = 0x1187,
  TobaccoAndSugar = 0x118B,
  SpicesAndSugar = 0x118D,
  WoolAndWine = 0x11B1,
  WoolAndCocoa = 0x11D1,
  WineAndCocoa = 0x11E1
};

enum class IslandOriginal : uint8_t
{
  Modified = 0,
  Original = 1
};

struct Island5Data // Insel5
{
  uint8_t inselnr;
  uint8_t felderx;
  uint8_t feldery;
  uint8_t strtduerrflg : 1;
  uint8_t nofixflg : 1;
  uint8_t vulkanflg : 1;
  uint16_t posx;
  uint16_t posy;
  uint16_t hirschreviercnt;
  uint16_t speedcnt;
  uint8_t stadtplayernr[11];
  uint8_t vulkancnt;
  uint8_t schatzflg;
  uint8_t rohstanz;
  uint8_t eisencnt;
  uint8_t playerflags;
  OreMountainData eisenberg[4];
  OreMountainData vulkanberg[4];
  Fertility fertility;
  uint16_t filenr;
  uint16_t sizenr;
  uint8_t klimanr;
  IslandOriginal orginalFlag; // flag that indicates if the island is `original` (empty INSELHAUS chunk) or `modified` (filled INSELHAUS chunk).
  uint8_t duerrproz;
  uint8_t rotier;
  uint32_t seeplayerflags;
  uint32_t duerrcnt;
  uint32_t leer3;
};

class Island5
{
public:
  Island5()
  {
  }
  explicit Island5(uint8_t* data, uint32_t length, const std::string& name);
  void setIslandHouse(std::shared_ptr<Chunk> c);
  void setWarehouse2(std::shared_ptr<Chunk> c);
  void setProductionList(std::shared_ptr<Chunk> c);

private:
  std::string name;
  Island5Data island5;
  IslandHouse islandHouse; // INSELHAUS
  // std::shared_ptr<Deer2> deer;                 // HIRSCH2
  ProductionList productionList; // PRODLIST2
  // std::shared_ptr<Shipyard> shipyard;          // WERFT
  // std::shared_ptr<Military> military;          // MILITAR
  // std::shared_ptr<Settlers> settlers;          // SIEDLER
  // std::shared_ptr<RawGrow2> rawGrow2;          // ROHWACHS2
  // std::shared_ptr<City4> city4;                // STADT4
  Warehouse2 warehouse2; // KONTOR2
  // std::shared_ptr<Market2>;                    // MARKT2
};

struct Island3Data // Insel3
{
  uint8_t inselnr;    // ID for this island (per game)
  uint8_t breite;     // width
  uint8_t hoehe;      // height
  uint8_t a;          // TODO: unknown
  uint16_t x_pos;     // position of island x
  uint16_t y_pos;     // position of island y
  uint16_t b;         // TODO: unknown
  uint16_t c;         // TODO: unknown
  uint8_t bytes1[28]; // TODO: unknown
};

class Island3
{
public:
  explicit Island3(uint8_t* data, uint32_t length, const std::string& name);
  Island3Data island3;

private:
  std::string name;
};


#endif // _ISLAND_HPP