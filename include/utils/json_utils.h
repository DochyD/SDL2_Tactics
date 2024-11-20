#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
// #include <vector>

#include "Map.h"

using json = nlohmann::json;

namespace JsonUtils
{
    // Convert CellType to string for better readability in JSON

    const std::string mapsFolder = "assets/maps/";

    inline std::string cellTypeToString(CellType type)
    {
        switch (type)
        {
        case WALKABLE:
            return "WALKABLE";
        case EMPTY:
            return "EMPTY";
        case OBSTACLE:
            return "OBSTACLE";
        case NO_RENDER:
            return "NO_RENDER";
        default:
            return "WALKABLE";
        }
    }

    // Convert string back to CellType
    inline CellType stringToCellType(const std::string &str)
    {
        if (str == "EMPTY")
            return EMPTY;
        if (str == "OBSTACLE")
            return OBSTACLE;
        if (str == "NO_RENDER")
            return NO_RENDER;
        return WALKABLE;
    }

    // Save grid to json
    inline bool saveGridToJson(const Map &map, const std::string &filename)
    {
        const std::string fullPath = mapsFolder + filename;
        std::clog << "Saving map to: " << fullPath << std::endl;

        try
        {
            json j;
            // Store parameters into json file
            const int mapSize = map.getSize();
            // j["size"] = map.getSize();
            j["playerStartingPosX"] = map.getPlayerStartingPosX();
            j["playerStartingPosY"] = map.getPlayerStartingPosY();
            j["playerBaseHealth"] = map.getPlayerBaseHealth();
            j["windowHeight"] = map.getPlayerBaseHealth();
            j["windowWidth"] = map.getPlayerBaseHealth();

            // Store cells into json
            json cells = json::array();
            for (int row = 0; row < mapSize; row++)
            {
                json jsonRow = json::array();
                for (int col = 0; col < mapSize; col++)
                {
                    const Cell &cell = map.getCell(row, col);
                    json cellJson;
                    cellJson["x"] = cell.x;
                    cellJson["y"] = cell.y;
                    cellJson["type"] = cellTypeToString(cell.cellType);
                    cellJson["occupied"] = cell.occupied;
                    jsonRow.push_back(cellJson);
                }
                cells.push_back(jsonRow);
            }
            j["cells"] = cells;

            // Write to file
            std::ofstream file(fullPath);
            if (!file.is_open())
            {
                std::cerr << "Failed to open file for writing: " << fullPath << std::endl;
                return false;
            }
            file << j.dump(4); // Pretty print with indent of 4
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error saving grid to JSON: " << e.what() << std::endl;
            return false;
        }
    }

    // Load grid from JSON file
    inline bool loadGridFromJson(Map &map, const std::string filename)
    {
        const std::string filePath = mapsFolder + filename;
        try
        {
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                return false;
            }

            json j;
            file >> j;

            map.setPlayerStartingPosX(j["playerStartingPosX"]);
            map.setPlayerStartingPosY(j["playerStartingPosY"]);
            map.setPlayerBaseHealth(j["playerBaseHealth"]);

            const auto &cells = j["cells"];

            const int &mapSize = map.getSize();
            for (int row = 0; row < mapSize; row++)
            {
                for (int col = 0; col < mapSize; col++)
                {
                    const auto &cellJson = cells[row][col];

                    if (cellJson["type"] != "NO_RENDER")
                    {
                        Cell cell(
                            cellJson["x"],
                            cellJson["y"],
                            stringToCellType(cellJson["type"]),
                            cellJson["occupied"]);

                        map.setCell(row, col, cell);
                    }
                }
            }
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "An exception occurred while loading map: " << e.what() << std::endl;
            std::cerr << "Please check the input or configuration and try again." << std::endl;
            return false;
        }
    }
}