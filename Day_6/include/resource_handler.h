#ifndef DAY_SIX_RESOURCE_HANDLER_H_
#define DAY_SIX_RESOURCE_HANDLER_H_

#include <vector>
#include <string>
#include <cstdint>

namespace day_six {

    class ResourceHandler {
        public:
            ResourceHandler() = default;
            ~ResourceHandler() = default;
            void AddLineToMap(const std::string& new_map_line);
            uint64_t CountDistinctPositions();
            
        private:
            enum POSSIBLE_DIRECTIONS {
                UP,
                LEFT,
                RIGHT,
                DOWN,
                UNKNOWN
            };
            std::vector<std::vector<char>> map_;
            std::vector<std::vector<char>> visited_places_map_;
            void PredictPositions();

            bool CanGuardMove(const size_t pos_x, const size_t pos_y, const POSSIBLE_DIRECTIONS direction);
            bool CanGuardExit(const size_t pos_x, const size_t pos_y, const POSSIBLE_DIRECTIONS direction);
            POSSIBLE_DIRECTIONS RotateGuard(const POSSIBLE_DIRECTIONS current_direction);

            const char kPlaceholderVistedMarker = 'X';
            const char kPlaceholderEmptyMarker = '.';
            const char kObstacleMarker = '#';
            const char kFacingUpwardMarker = '^';
            const char kFacingDownMarker = 'V';
            const char kFacingLeftMarker = '<';
            const char kFacingRightMarker = '>';

            size_t current_pos_x = 0;
            size_t current_pos_y = 0;
            POSSIBLE_DIRECTIONS current_direction = POSSIBLE_DIRECTIONS::UNKNOWN;
    };

} // namespace day_six

#endif