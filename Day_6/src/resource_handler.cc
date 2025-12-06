#include "../include/resource_handler.h"

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

namespace day_six {
    void ResourceHandler::AddLineToMap(const std::string& new_map_line) {
        std::vector<char> new_line (new_map_line.begin(), new_map_line.end());
        std::vector<char> placeholder_map;

        for(size_t i = 0; i < new_line.size(); i++) {
            const char s = new_line[i];
            if(s == kFacingUpwardMarker || s == kFacingDownMarker || s == kFacingLeftMarker || s == kFacingRightMarker) {
                if (current_direction == POSSIBLE_DIRECTIONS::UNKNOWN) {
                    placeholder_map.push_back(kPlaceholderVistedMarker);
                    current_pos_x = i;
                    current_pos_y = map_.size();
                    if(s == kFacingUpwardMarker) {
                        current_direction = POSSIBLE_DIRECTIONS::UP;
                    } else if (s == kFacingDownMarker) {
                        current_direction = POSSIBLE_DIRECTIONS::DOWN;
                    } else if (s == kFacingLeftMarker) {
                        current_direction = POSSIBLE_DIRECTIONS::LEFT;
                    } else if (s == kFacingRightMarker) {
                        current_direction = POSSIBLE_DIRECTIONS::RIGHT;
                    }
                } else {
                    std::cout << "WARN: Found a second guard!, unable to track more than the first found guards position." << std::endl;
                }
            } else if (s == kObstacleMarker) {
                placeholder_map.push_back(kObstacleMarker);
            } else {
                placeholder_map.push_back(kPlaceholderEmptyMarker);
            }
        }

        map_.push_back(new_line);
        visited_places_map_.push_back(placeholder_map);
    }

    uint64_t ResourceHandler::CountDistinctPositions() {
        PredictPositions();
        uint64_t position_count = 0;

        for(size_t y = 0; y < visited_places_map_.size(); y++) {
            for(size_t x = 0; x < visited_places_map_[y].size(); x++) {
                if(visited_places_map_[y][x] == kPlaceholderVistedMarker) {
                    position_count++;
                }
            }
        }

        return position_count;
    }

    void ResourceHandler::PredictPositions() {
        bool exited_map = false;

        while(!exited_map) {
            if (CanGuardExit(current_pos_x, current_pos_y, current_direction)) {
                exited_map = true;
            } else if (CanGuardMove(current_pos_x, current_pos_y, current_direction)) {
                // handle moving the position of x & y
                // plot position in placeholder map
                switch(current_direction) {
                    case POSSIBLE_DIRECTIONS::DOWN: {
                        current_pos_y = current_pos_y + 1;
                        break;
                    }
                    case POSSIBLE_DIRECTIONS::LEFT: {
                        current_pos_x = current_pos_x - 1;
                        break;
                    }
                    case POSSIBLE_DIRECTIONS::RIGHT: {
                        current_pos_x = current_pos_x + 1;
                        break;
                    }
                    case POSSIBLE_DIRECTIONS::UP {
                        current_pos_y = current_pos_y - 1;
                        break;
                    }
                }
                visited_places_map_[current_pos_y][current_pos_x] = kPlaceholderVistedMarker;
            } else {
                current_direction = RotateGuard(current_direction);
            }
        }
    }

    bool ResourceHandler::CanGuardMove(const size_t pos_x, const size_t pos_y, const ResourceHandler::POSSIBLE_DIRECTIONS direction) {
        try {
            switch(current_direction) {
                case POSSIBLE_DIRECTIONS::DOWN: {
                    
                }
                case POSSIBLE_DIRECTIONS::LEFT: {
                    
                    break;
                }
                case POSSIBLE_DIRECTIONS::RIGHT: {
                    
                    break;
                }
                case POSSIBLE_DIRECTIONS::UP {
                    
                    break;
                }
            }
        } catch(...) {
            // index out of bounds, cannot move!
            return false;
        }
    }

    bool ResourceHandler::CanGuardExit(const size_t pos_x, const size_t pos_y, const ResourceHandler::POSSIBLE_DIRECTIONS direction) {

    }
    
    ResourceHandler::POSSIBLE_DIRECTIONS ResourceHandler::RotateGuard(const ResourceHandler::POSSIBLE_DIRECTIONS current_direction) {

    }
}