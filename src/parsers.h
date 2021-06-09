//
// Created by egor on 09.06.2021.
//

#ifndef COURSEPROJECT_PARSERS_H
#define COURSEPROJECT_PARSERS_H

#include <vector>
#include <fstream>
#include <iostream>
#include <renderer/primitives.h>

std::vector<Renderer::Triangle4d> ParseObj(const std::string& filename);

std::vector<Renderer::Triangle4d> ParseOff(const std::string& filename);

#endif //COURSEPROJECT_PARSERS_H
