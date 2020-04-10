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

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "files.hpp"
#include "palette.hpp"

Palette* Palette::_instance = 0;

Palette* Palette::instance()
{
  return _instance;
}

Palette* Palette::create_instance(const std::string& palette_file_path)
{
  static CGuard g;
  if (!_instance)
  {
    _instance = new Palette(palette_file_path);
    _instance->transparentColor = _instance->findTransparentColorIndex();
  }
  return _instance;
}

void Palette::init(const std::string& palette_file_path)
{
  path = palette_file_path;
  std::ifstream input(path, std::ios::binary);
  std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input), {});

  for (int i = 20; i < buffer.size() - 4; i = i + 4)
  {
    PaletteColor color(static_cast<uint8_t>(buffer[i]), static_cast<uint8_t>(buffer[i + 1]), static_cast<uint8_t>(buffer[i + 2]));
    palette.push_back(color);
  }
}

PaletteColor Palette::getColor(int index)
{
  return palette.at(index);
}

int Palette::getTransparentColor()
{
  return transparentColor;
}

int Palette::findTransparentColorIndex()
{
  for (int i = palette.size(); i >= 0; i--)
  {
    // this is hard coded to magenta: 0xFF, 0x00, 0xFF
    if (palette[i].getRed() == 0xFF && palette[i].getGreen() == 0x00 && palette[i].getBlue() == 0xFF)
    {
      return i;
    }
  }
  return -1;
}

size_t Palette::size()
{
  return palette.size();
}
