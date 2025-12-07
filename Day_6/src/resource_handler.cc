#include "../include/resource_handler.h"

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <utility>

namespace day_six {
    void ResourceHandler::AddLineToMap(const std::string& new_map_line) {
        std::vector<char> new_line (new_map_line.begin(), new_map_line.end());
        std::vector<char> placeholder_map;

        for(long int i = 0; i < new_line.size(); i++) {
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

        for(long int y = 0; y < visited_places_map_.size(); y++) {
            for(long int x = 0; x < visited_places_map_[y].size(); x++) {
                if(visited_places_map_[y][x] == kPlaceholderVistedMarker) {
                    position_count++;
                }
            }
        }

        return position_count;
    }

    void ResourceHandler::PredictPositions() {
        bool exited_map = false;

        uint counter = 0;
        while(!exited_map) {
            counter++;
            //std::cout << "Loop #" << counter << ", x: " << current_pos_x << ", y: " << current_pos_y << " direction: " << current_direction << std::endl;

            if (CanGuardExit(current_pos_x, current_pos_y, current_direction)) {
                exited_map = true;
            } else if (CanGuardMove(current_pos_x, current_pos_y, current_direction)) {
                // handle moving the position of x & y
                // plot position in placeholder map
                std::pair<long int, long int> new_indexes = GetNewIndexes(current_pos_x, current_pos_y, current_direction);
                if(new_indexes.first == -1 || new_indexes.first == map_[current_pos_y].size() || new_indexes.second == -1 || new_indexes.second == map_.size()) {
                    exited_map = true;
                    std::cout << "ERROR: Guard location unknown, unable to move!" << std::endl;
                } else {
                    // move marker in map, and put as known position in visited map
                    map_[current_pos_y][current_pos_x] = kPlaceholderEmptyMarker;
                    current_pos_x = new_indexes.first;
                    current_pos_y = new_indexes.second;
                    map_[current_pos_y][current_pos_x] = GetDirectionIcon(current_direction);
                    visited_places_map_[current_pos_y][current_pos_x] = kPlaceholderVistedMarker;
                }
            } else {
                current_direction = RotateGuard(current_direction);
            }
        }
    }

    bool ResourceHandler::CanGuardMove(const long int pos_x, const long int pos_y, const ResourceHandler::POSSIBLE_DIRECTIONS direction) {
        std::pair<long int, long int> new_indexes = GetNewIndexes(pos_x, pos_y, direction);

        if(new_indexes.first == -1 || new_indexes.first == map_[pos_y].size() || new_indexes.second == -1 || new_indexes.second == map_.size()) {
            return false;
        }

        if(map_[new_indexes.second][new_indexes.first] == kPlaceholderEmptyMarker) {
            return true;
        }
        return false;
    }

    bool ResourceHandler::CanGuardExit(const long int pos_x, const long int pos_y, const ResourceHandler::POSSIBLE_DIRECTIONS direction) {
        std::pair<long int, long int> new_indexes = GetNewIndexes(pos_x, pos_y, direction);
        if(new_indexes.first == -1 || new_indexes.second == -1) {
            std::cout << "ERROR: Guard already left!" << std::endl;
            return false;
        }

        if(new_indexes.first == map_[pos_y].size() || new_indexes.second == map_.size()) {
            return true;
        }
        return false;
    }
    
    ResourceHandler::POSSIBLE_DIRECTIONS ResourceHandler::RotateGuard(const ResourceHandler::POSSIBLE_DIRECTIONS direction) {
        switch(direction) {
            case POSSIBLE_DIRECTIONS::DOWN: {
                return POSSIBLE_DIRECTIONS::LEFT;
            }
            case POSSIBLE_DIRECTIONS::LEFT: {
                return POSSIBLE_DIRECTIONS::UP;
            }
            case POSSIBLE_DIRECTIONS::RIGHT: {
                return POSSIBLE_DIRECTIONS::DOWN;
            }
            case POSSIBLE_DIRECTIONS::UP: {
                return POSSIBLE_DIRECTIONS::RIGHT;
            }
            default: {
                std::cout << "ERROR: Guard location unknown, unable to move!" << std::endl;
                return POSSIBLE_DIRECTIONS::UNKNOWN;
            }
        }
    }

    std::pair<long int, long int> ResourceHandler::GetNewIndexes(const long int pos_x, const long int pos_y, const ResourceHandler::POSSIBLE_DIRECTIONS direction) {
        long int new_x = pos_x;
        long int new_y = pos_y;
        switch(current_direction) {
            case POSSIBLE_DIRECTIONS::DOWN: {
                new_y++;
                break;
            }
            case POSSIBLE_DIRECTIONS::LEFT: {
                new_x--;
                break;
            }
            case POSSIBLE_DIRECTIONS::RIGHT: {
                new_x++;
                break;
            }
            case POSSIBLE_DIRECTIONS::UP: {
                new_y--;
                break;
            }
            default: {
                std::cout << "Guard direction unknown!" << std::endl;
                new_y = -1;
                new_x = -1;
                break;
            }
        }
        return std::pair<long int, long int>(new_x, new_y);
    }

    char ResourceHandler::GetDirectionIcon(const ResourceHandler::POSSIBLE_DIRECTIONS direction) const {
        switch(current_direction) {
            case POSSIBLE_DIRECTIONS::UP: {
                return kFacingUpwardMarker;
            }
            case POSSIBLE_DIRECTIONS::DOWN: {
                return kFacingDownMarker;
            }
            case POSSIBLE_DIRECTIONS::LEFT: {
                return kFacingLeftMarker;
            }
            case POSSIBLE_DIRECTIONS::RIGHT: {
                return kFacingRightMarker;
            }
            default: {
                std::cout << "ERROR: location unknown, placing marker: " << kPlaceholderEmptyMarker << " on map for current position!" << std::endl;
                return kPlaceholderEmptyMarker;
            }
        }
    }
} // namespace day_six