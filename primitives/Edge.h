/* */

#pragma once

#include "Quad.h"
#include "Disk.h"

class Edge : public Quad
{
public:
    Edge() {}
    Edge(Disk d1, Disk d2)
    {
        // Thin quad (line)
        height = 0.05f;

        // Delta
        float dx = d2.pos.x - d1.pos.x;
        float dy = d2.pos.y - d1.pos.y;

        // Position
        pos.x = dx / 2.0f;
        pos.y = dy / 2.0f;

        // Width
        width = sqrt(dx * dx + dy * dy);

        // Rotation
        angle = (float)atan(d2.pos.y - pos.y);
    }
};