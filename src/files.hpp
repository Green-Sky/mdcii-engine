
// This file is part of the MDCII Game Engine.
// Copyright (C) 2019  Armin Schlegel
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

#pragma once
#include <string>
#include <map>

extern std::map<std::string, std::string> files;

bool check_file(const std::string& filename);
bool check_all_files(std::map<std::string, std::string> files);
std::map<std::string, std::string> create_file_map(const std::string& path, std::map<std::string, std::string> map);
std::string string_to_lower_case(const std::string& str);
std::vector<std::string> get_directory_tree(const std::string& path);
