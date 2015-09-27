
// This file is part of the MDCII Game Engine.
// Copyright (C) 2015  Benedikt Freisen
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

#ifndef INSEL_HPP
#define INSEL_HPP

#include <inttypes.h>
#include "block.hpp"
#include "grafikinfo.hpp"

typedef struct
{
  uint16_t bebauung;
  uint8_t x_pos;
  uint8_t y_pos;
  uint32_t rot : 2;
  uint32_t ani : 4;
  uint32_t a : 8;
  uint32_t spieler : 3;
  uint32_t zufall : 5;
  uint32_t spieler_ : 3;
  uint32_t c : 7;
} inselfeld_t;

typedef struct
{
  int16_t index;
  uint8_t grundhoehe;
} feld_t;

class Insel
{
  inselfeld_t *schicht1;
  inselfeld_t *schicht2;
public:
  uint8_t breite;
  uint8_t hoehe;
  uint16_t xpos;
  uint16_t ypos;
  void insel_rastern(inselfeld_t* a, uint32_t laenge, inselfeld_t* b, uint8_t breite, uint8_t hoehe);
  std::string basisname(uint8_t breite, uint8_t num, uint8_t sued);
  Block *inselX;
  Insel(Block *inselX, Block *inselhaus);
  void grafik_boden(feld_t *ziel, uint8_t x, uint8_t y, uint8_t r);
  void grafik_bebauung(feld_t *ziel, uint8_t x, uint8_t y, uint8_t r);
  void bewege_wasser();
};

#endif