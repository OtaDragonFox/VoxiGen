#pragma once
#include"../types.h"

bool IsOverlapping(vec2 in_tl_corner, vec2 in_br_corner, vec2 in_location){
    if(in_tl_corner.x < in_location.x && in_br_corner.x > in_location.x)
    {
        if(in_tl_corner.y > in_location.y && in_location.y > in_br_corner.y)
        {
            return true;
        }
    } 
    return false;
}