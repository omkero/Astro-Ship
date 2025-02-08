#include "detections.hpp"

bool Detections::isColiding(SDL_Rect primary_rect, SDL_Rect target_rect) {
    // Check if there is no overlap (non-collision)
    if (primary_rect.x + primary_rect.w <= target_rect.x ||  // primary is left of target
        target_rect.x + target_rect.w <= primary_rect.x ||  // target is left of primary
        primary_rect.y + primary_rect.h <= target_rect.y || // primary is above target
        target_rect.y + target_rect.h <= primary_rect.y) {  // target is above primary
        return false; // No collision
    }
    return true; // There is a collision
}