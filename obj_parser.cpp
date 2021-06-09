//
// Created by egor on 25.04.2021.
//
#include <vector>
#include <fstream>
#include <iostream>
#include <renderer/primitives.h>

using Renderer::Triangle4d;

std::vector<Triangle4d> ParseObj(const std::string& filename) {
    std::ifstream fin(filename);
    std::string line;
    std::vector<Eigen::Vector4d> vs;
    std::vector<Triangle4d> result;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        std::string type;
        ss >> type;
        if (type == "v") {
            double x, y, z;
            ss >> x >> y >> z;
            vs.emplace_back(x, y, z, 1);
        } else if (type == "f") {
            if (std::rand() % 1000 < 500) continue;
            std::vector<int> idxs;

            std::string token;
            while (ss >> token) {
                std::istringstream tokenStream(token);
                int x;
                tokenStream >> x;
                idxs.push_back(x);
            }
            for (int i = 1; i + 1 < idxs.size(); ++i) {
                Triangle4d tr(vs[idxs[0]],
                              vs[idxs[i]],
                              vs[idxs[i + 1]],
//                              {(sf::Uint8)(std::rand() % 256), (sf::Uint8)(std::rand() % 256), (sf::Uint8)(std::rand() % 256), 255});
                              {200, 200, 200, 255});
                result.emplace_back(tr);
            }
        }
    }
    return result;
}

std::vector<Triangle4d> ParseOff(const std::string& filename) {
    std::ifstream fin(filename);
    std::string line;
    std::vector<Eigen::Vector4d> vs;
    std::vector<Triangle4d> result;

    std::getline(fin, line);
    std::istringstream ss(line);
    int vCnt, polyCnt;
    ss >> vCnt >> polyCnt;
    std::cerr << vCnt << ' ' << polyCnt << std::endl;
    for (int i = 0; i < vCnt; ++i) {
        std::getline(fin, line);
        std::istringstream ss(line);
        double x, y, z;
        ss >> x >> y >> z;
        vs.emplace_back(x, y, z, 1);
    }
    for (int i = 0; i < polyCnt; ++i) {
        std::getline(fin, line);
        std::istringstream ss(line);
        int n;
        ss >> n;
        std::vector<int> indexes(n);
        for (int j = 0; j < n; ++j) {
            ss >> indexes[j];
        }
        for (int j = 1; j + 1 < n; ++j) {
            result.emplace_back(vs[indexes[0]],
                                vs[indexes[j]],
                                vs[indexes[j + 1]],
                              Renderer::Color((sf::Uint8)(std::rand() % 256), (sf::Uint8)(std::rand() % 256), (sf::Uint8)(std::rand() % 256), 255));
        }
    }
    return result;
}