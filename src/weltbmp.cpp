
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
#include <iostream>

#include "bsh_leser.hpp"
#include "bildspeicher_pal8.hpp"
#include "insel.hpp"
#include "welt.hpp"
#include "grafiken.hpp"
#include "files.hpp"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#define XRASTER 16
#define YRASTER 8
#define ELEVATION 10


int main(int argc, char** argv)
{
  if (argc < 3)
    exit(EXIT_FAILURE);

  std::ifstream f;
  f.open(argv[1], std::ios_base::in | std::ios_base::binary);

  Welt welt = Welt(f);

  f.close();
  auto files = Files::create_instance(".");
  Bsh_leser bsh_leser(files->instance()->get_file("mgfx_stadtfld_bsh"));
  Grafiken stadtfld_grafiken(files->instance()->get_file("grafiken_txt"));

  Bildspeicher_pal8 bs((Welt::KARTENBREITE + Welt::KARTENHOEHE) * XRASTER, (Welt::KARTENBREITE + Welt::KARTENHOEHE) * YRASTER, 0);

  for (int y = 0; y < Welt::KARTENHOEHE; y++)
  {
    for (int x = 0; x < Welt::KARTENBREITE; x++)
    {
      Insel* insel = welt.insel_an_pos(x, y);
      feld_t feld;
      if (insel != NULL)
	insel->grafik_bebauung(feld, x - insel->xpos, y - insel->ypos, 0, stadtfld_grafiken);
      else
      {
	feld.index = stadtfld_grafiken.grafik_zu(1201) + (y + x * 3) % 12;
	feld.grundhoehe = 0;
      }
      /*feld_t feld2;
      insel->grafik_boden(&feld2, x, y, 0);*/
      if (feld.index != -1)
      {
	Bsh_bild& bsh = bsh_leser.gib_bsh_bild(feld.index);
	uint16_t x_auf_karte = x /*- insel->breite / 2*/;
	uint16_t y_auf_karte = y /*- insel->hoehe / 2*/;
	bs.zeichne_bsh_bild_oz(
	    bsh, (x_auf_karte - y_auf_karte + Welt::KARTENHOEHE) * XRASTER, (x_auf_karte + y_auf_karte) * YRASTER + 2 * YRASTER - feld.grundhoehe * ELEVATION);
      }
      /*else
	std::cout << insel->schicht2[y * insel->breite + x].bebauung << " ";*/
    }
  }

  bs.exportiere_bmp(argv[2]);
}
