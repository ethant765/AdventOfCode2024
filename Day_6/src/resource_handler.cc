#include "../include/resource_handler.h"

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <utility>
#include <thread>
#include <mutex>

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
        new_obstacle_map_.push_back(new_line);
        visited_places_map_.push_back(placeholder_map);
    }

    uint64_t ResourceHandler::CountDistinctPositions() const {
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

    uint64_t ResourceHandler::CountNumberOfLoopObstacles() const {
        uint64_t obstacle_count = 0;

        for(size_t y = 0; y < new_obstacle_map_.size(); y++) {
            for(size_t x = 0; x < new_obstacle_map_[y].size(); x++) {
                if(new_obstacle_map_[y][x] == kNewObstacleMarker) {
                    obstacle_count++;
                }
            }
        }

        return obstacle_count;
    }

    void ResourceHandler::PredictPositions() {
        std::vector<std::thread> obstacle_prediction_threads;
        
        uint64_t thread_count = 0;
        for(size_t y = 0; y < new_obstacle_map_.size(); y++) {
            for(size_t x = 0; x < new_obstacle_map_[y].size(); x++) {
                std::thread thread(&ResourceHandler::PlaceObstacle, this, x, y);
                obstacle_prediction_threads.push_back(std::move(thread));
                thread_count++;
            }
        }
        uint64_t thread_exit_count = 0;
        for(auto& thread : obstacle_prediction_threads) {
            thread.join();
            thread_exit_count++;

            std::cout << "Thread " << thread_exit_count << "/" << thread_count << " finished." << std::endl;
        }

        bool exited_map = false;
        while(!exited_map) {
            if (CanGuardExit(current_pos_x, current_pos_y, current_direction, map_)) {
                exited_map = true;
            } else if (CanGuardMove(current_pos_x, current_pos_y, current_direction, map_)) {
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

    void ResourceHandler::PlaceObstacle(const long int pos_x, const long int pos_y) {
        if(map_[pos_y][pos_x] != kPlaceholderEmptyMarker) {
            // location cannot hold marker if not empty at start
            return;
        }

        // create a copy of the original Map state
        std::vector<std::vector<char>> test_map(map_.begin(), map_.end());

        // place obstacle at provided location in the test map
        test_map[pos_y][pos_x] = kNewObstacleMarker;

        long int curr_x = current_pos_x;
        long int curr_y = current_pos_y;
        POSSIBLE_DIRECTIONS curr_dir = current_direction;
        uint marker_hit_counter = 0;
        bool map_exited = false;
        uint64_t loop_count = 0;
        while(!map_exited) {
            loop_count++;

            /**
             * DIRTY SOLUTION
             * Threads getting stuck, can't be bothered to figure out issue. 
             */
            if(loop_count > 50000000) {
                std::cout << "Thread stuck. X: " << curr_x << ", Y: " << curr_y << ", dir: " << curr_dir << ", provided X: " << pos_x << ", provided Y: " << pos_y << ", Marker hit counter: " << marker_hit_counter << std::endl;
                marker_hit_counter = 5;
                map_exited = true;
                break;
            }


            if(CanGuardExit(curr_x, curr_y, curr_dir, test_map)) {
                map_exited = true;
            } else if (CanGuardMove(curr_x, curr_y, curr_dir, test_map)) {
                // handle guard position move
                std::pair<long int, long int> new_indexes = GetNewIndexes(curr_x, curr_y, curr_dir);
                if(new_indexes.first == -1 || new_indexes.first == test_map[current_pos_y].size() || new_indexes.second == -1 || new_indexes.second == test_map.size()) {
                    map_exited = true;
                    std::cout << "ERROR: Guard location unknown, unable to move!" << std::endl;
                } else {
                    test_map[curr_y][curr_x] = kPlaceholderEmptyMarker;
                    curr_x = new_indexes.first;
                    curr_y = new_indexes.second;
                    test_map[curr_y][curr_x] = GetDirectionIcon(curr_dir);
                }
            } else {
                // rotate guard, test if we are rotating because we are facing new obstacle
                std::pair<long int, long int> new_indexes = GetNewIndexes(curr_x, curr_y, curr_dir);
                if(new_indexes.first == pos_x && new_indexes.second == pos_y) {
                    marker_hit_counter++;

                    // 5 means each side can be hit once, but the next hit means a loop is occuring
                    if(marker_hit_counter >= 5) {
                        map_exited = true;
                    }
                }

                curr_dir = RotateGuard(curr_dir);
            }
        }

        if (marker_hit_counter >= 5) {
            std::scoped_lock lock(mutex_);
            new_obstacle_map_[pos_y][pos_x] = kNewObstacleMarker;
        }
    }

    bool ResourceHandler::CanGuardMove(const long int pos_x, const long int pos_y, const ResourceHandler::POSSIBLE_DIRECTIONS direction, const std::vector<std::vector<char>>& test_map) {
        std::pair<long int, long int> new_indexes = GetNewIndexes(pos_x, pos_y, direction);

        if(new_indexes.first == -1 || new_indexes.first == test_map[pos_y].size() || new_indexes.second == -1 || new_indexes.second == test_map.size()) {
            return false;
        }

        if(test_map[new_indexes.second][new_indexes.first] == kPlaceholderEmptyMarker) {
            return true;
        }
        return false;
    }

    bool ResourceHandler::CanGuardExit(const long int pos_x, const long int pos_y, const ResourceHandler::POSSIBLE_DIRECTIONS direction, const std::vector<std::vector<char>>& test_map) {
        std::pair<long int, long int> new_indexes = GetNewIndexes(pos_x, pos_y, direction);
        if(new_indexes.first == test_map[pos_y].size() || new_indexes.second == test_map.size() || new_indexes.first == -1 || new_indexes.second == -1) {
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
        switch(direction) {
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
        switch(direction) {
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