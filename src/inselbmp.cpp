
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

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>

#include <fstream>

#include "bsh_leser.hpp"
#include "bildspeicher_pal8.hpp"
#include "insel.hpp"
#include "bebauung.hpp"
#include "grafiken.hpp"


  
#define XRASTER 32
#define YRASTER 16
#define ELEVATION 20


int main(int argc, char **argv)
{
  if (argc < 2)
    exit(EXIT_FAILURE);
  
  std::ifstream f;
  f.open(argv[1]);
  
  Block inselX = Block(f);
  Block inselhaus = Block(f);
  
  f.close();
  
  Bebauung bebauung("bebauung.txt");
  Grafiken stadtfld_grafiken("grafiken.txt");
  
  Insel insel = Insel(&inselX, &inselhaus, bebauung);
  uint8_t width = insel.breite;
  uint8_t height = insel.hoehe;
  
  Bsh_leser bsh_leser("gfx/stadtfld.bsh");
  
  Bildspeicher_pal8 bs((width + height) * XRASTER, (width + height) * YRASTER, 0);
  
  int x, y;
  for (y = 0; y < height; y++)
  {
    for (x = 0; x < width; x++)
    {
      feld_t feld;
      insel.grafik_bebauung(feld, x, y, 0, stadtfld_grafiken);
      if (feld.index != -1)
      {
	Bsh_bild& bsh = bsh_leser.gib_bsh_bild(feld.index);
	bs.zeichne_bsh_bild_oz(bsh, (x - y + height) * XRASTER, (x + y) * YRASTER + 2 * YRASTER - feld.grundhoehe * ELEVATION);
      }
    }
  }
  
  
  bs.exportiere_bmp(argv[2]);
  
}
