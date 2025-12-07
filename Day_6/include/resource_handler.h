#ifndef DAY_SIX_RESOURCE_HANDLER_H_
#define DAY_SIX_RESOURCE_HANDLER_H_

#include <vector>
#include <string>
#include <cstdint>
#include <utility>
#include <mutex>

namespace day_six {
    /**
     * @brief day 6 resource holder and processor
     */
    class ResourceHandler {
        public:
            /**
             * @brief Construct a new default Resource Handler object
             */
            ResourceHandler() = default;

            /**
             * @brief Destroy the Resource Handler object
             */
            ~ResourceHandler() = default;

            /**
             * @brief Adds a new line to the map, a new line will contain new x axis positions
             * 
             * @param new_map_line 
             */
            void AddLineToMap(const std::string& new_map_line);

            /**
             * @brief Counts the number of map positions the guard may visit
             * 
             * @return uint64_t 
             */
            uint64_t CountDistinctPositions() const;

            /**
             * @brief Calculates and counts the number of positions loop markers can be located
             * 
             * @return uint64_t 
             */
            uint64_t CountNumberOfLoopObstacles() const;

            /**
             * @brief Handles the position predictions for the guards route
             */
            void PredictPositions();
            
        private:
            /**
             * @brief ENUM to store the different directions a guard can visit
             */
            enum POSSIBLE_DIRECTIONS {
                UP = 0,
                RIGHT,
                DOWN,
                LEFT,
                UNKNOWN
            };

            /**
             * @brief Given the guards location and facing direction, will advise if the guard can move forwards
             * 
             * @param pos_x 
             * @param pos_y 
             * @param direction 
             * @return true 
             * @return false 
             */
            bool CanGuardMove(const long int pos_x, const long int pos_y, const POSSIBLE_DIRECTIONS direction, const std::vector<std::vector<char>>& test_map);

            /**
             * @brief Given the guards location and facing direction, will advise if the guard can exit the map
             * 
             * @param pos_x 
             * @param pos_y 
             * @param direction 
             * @return true 
             * @return false 
             */
            bool CanGuardExit(const long int pos_x, const long int pos_y, const POSSIBLE_DIRECTIONS direction, const std::vector<std::vector<char>>& test_map);

            /**
             * @brief Given the guards current direction, will predict the new direction they shall patroll
             * 
             * @param direction 
             * @return POSSIBLE_DIRECTIONS 
             */
            POSSIBLE_DIRECTIONS RotateGuard(const POSSIBLE_DIRECTIONS direction);

            /**
             * @brief Given the guards current position and direction, will return their next predicted location
             * 
             * @param pos_x 
             * @param pos_y 
             * @param direction 
             * @return std::pair<long int, long int> 
             */
            std::pair<long int, long int> GetNewIndexes(const long int pos_x, const long int pos_y, const POSSIBLE_DIRECTIONS direction);

            /**
             * @brief given a direction, will return a map marker showing the way the guard is facing
             * 
             * @param direction 
             * @return char 
             */
            char GetDirectionIcon(const POSSIBLE_DIRECTIONS direction) const;

            /**
             * @brief Places An obstacle at the current position, tests if it will cause a loop, and if so marks new_obstacle_map_ with that obstacle position
             * 
             * @param pos_x 
             * @param pos_y 
             */
            void PlaceObstacle(const long int pos_x, const long int pos_y);

            /**
             * @brief Stores the map area the guard is patrolling
             */
            std::vector<std::vector<char>> map_;

            /**
             * @brief Stores the map with the locations the guard has been to
             */
            std::vector<std::vector<char>> visited_places_map_;

            /**
             * @brief Stores the map with the locations of possible new obstacles that will create a guard route loop
             */
            std::vector<std::vector<char>> new_obstacle_map_;

            /**
             * @brief class mutex
             */
            std::mutex mutex_;

            /**
             * @brief Icon for locations visited
             */
            const char kPlaceholderVistedMarker = 'X';

            /**
             * @brief Icon for empty map location
             */
            const char kPlaceholderEmptyMarker = '.';

            /**
             * @brief Icon for a map obstacle
             */
            const char kObstacleMarker = '#';

            /**
             * @brief Icon for guard facing up
             */
            const char kFacingUpwardMarker = '^';

            /**
             * @brief Icon for guard facing down
             */
            const char kFacingDownMarker = 'V';

            /**
             * @brief Icon for guard facing left
             */
            const char kFacingLeftMarker = '<';

            /**
             * @brief Icon for guard facing right
             */
            const char kFacingRightMarker = '>';

            /**
             * @brief Icon showing the location of a new obstacle
             * 
             */
            const char kNewObstacleMarker = 'O';

            /**
             * @brief Stores the current known x axis position
             */
            long int current_pos_x = 0;

            /**
             * @brief Stores the current known y axis position
             */
            long int current_pos_y = 0;

            /**
             * @brief Stores the current known direction
             */
            POSSIBLE_DIRECTIONS current_direction = POSSIBLE_DIRECTIONS::UNKNOWN;
    };

} // namespace day_six

#endif