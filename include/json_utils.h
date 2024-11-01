#pragma once
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>



#include "Map.h"

using json = nlohmann::json;

namespace JsonUtils {
    // Convert CellType to string for better readability in JSON

    const std::string mapsFolder = "assets/maps/";

    inline std::string cellTypeToString(CellType type) {
        switch (type) {
            case WALKABLE: return "WALKABLE";
            case EMPTY: return "EMPTY";
            case OBSTACLE: return "OBSTACLE";
            case NO_RENDER: return "NO_RENDER";
            default: return "WALKABLE";
        }
    }

    // Convert string back to CellType
    inline CellType stringToCellType(const std::string& str) {
        if (str == "EMPTY") return EMPTY;
        if (str == "OBSTACLE") return OBSTACLE;
        if (str == "NO_RENDER") return NO_RENDER;
        return WALKABLE;
    }

    // Save grid to JSON file
    inline bool saveGridToJson(const Map& isometricGrid, const std::string filename)
    {
        const std::string fullPath = mapsFolder + filename;
        std::cout <<  fullPath << std::endl;

        const std::vector<std::vector<GridCell>>& grid = isometricGrid.getGrid();

        try {
            json j;
            j["rows"] = isometricGrid.getWidth();
            j["cols"] = isometricGrid.getHeight();
            j["cellWidth"] = isometricGrid.getCellWidth();
            j["cellHeight"] = isometricGrid.getCellHeight();
            j["viewportwidth"] = isometricGrid.getViewportWidth();
            j["viewportHeight"] = isometricGrid.getViewportHeight();
            
            // Store cells
            json cells = json::array();
            for (const auto& row : grid) {
                json jsonRow = json::array();
                for (const auto& cell : row) {
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
            if (!file.is_open()) {
                return false;
            }
            file << j.dump(4); // Pretty print with indent of 4
            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }

    // Load grid from JSON file
    inline bool loadGridFromJson(IsometricGrid& isometricGrid, const std::string filename)
    {
        const std::string filePath = mapsFolder + filename;
        try {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                return false;
            }

            json j;
            file >> j;

            int rows = j["rows"];
            int cols = j["cols"];
            
            isometricGrid.setCellWidth(j["cellWidth"]);
            isometricGrid.setCellHeight(j["cellHeight"]);
            isometricGrid.setViewportWidth(j["viewportwidth"]);
            isometricGrid.setViewportHeight(j["viewportHeight"]);


            std::vector<std::vector<GridCell>>& grid = isometricGrid.getGrid();

            const auto& cells = j["cells"];
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    const auto& cellJson = cells[i][j];

                    GridCell cell(
                        cellJson["x"],
                        cellJson["y"],
                        stringToCellType(cellJson["type"]),
                        cellJson["occupied"]
                    );
 
                    isometricGrid.setGridCell(i,j, cell);
                }
            }
            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }
}