#pragma once

#include <functional>

namespace lel::graphic
{
  enum class CircleLocation
  {
    RIGHT_UP_OCTANT, // 1st octant
    UP_RIGHT_OCTANT, // 2nd octant
    UP_LEFT_OCTANT, // 3rd octant
    LEFT_UP_OCTANT, // 4th octant
    LEFT_DOWN_OCTANT, // 5th octant
    DOWN_LEFT_OCTANT, // 6th octant
    DOWN_RIGHT_OCTANT, // 7th octant
    RIGHT_DOWN_OCTANT, // 8th octant
    STRAIGHT_LEFT,
    STRAIGHT_RIGHT,
    STRAIGHT_UP,
    STRAIGHT_DOWN,
  };

  // Pseudo-code from
  // https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Bresenham
  template <typename Fct>
  void drawLine(int x1, int y1, int x2, int y2, Fct&& draw)
  {
    int dx = x2 - x1;
    int dy;

    if (dx != 0)
    {
      if (dx > 0)
      {
        dy = y2 - y1;
        if (dy != 0)
        {
          if (dy > 0)
          {
            // 1st octant
            if (dx >= dy)
            {
              int e = dx;
              dx *= 2;
              dy *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::RIGHT_UP_OCTANT);
                ++x1;
                if (x1 == x2)
                  break;
                e -= dy;
                if (e < 0)
                {
                  ++y1;
                  e += dx;
                }
              }
            }
            // 2nd octant
            else
            {
              int e = dy;
              dx *= 2;
              dy *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::UP_RIGHT_OCTANT);
                ++y1;
                if (y1 == y2)
                  break;
                e -= dx;
                if (e < 0)
                {
                  ++x1;
                  e += dy;
                }
              }
            }
          }
          else // dy < 0
          {
            // 8th octant
            if (dx >= -dy)
            {
              int e = dx;
              dx *= 2;
              dy *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::RIGHT_DOWN_OCTANT);
                ++x1;
                if (x1 == x2)
                  break;
                e += dy;
                if (e < 0)
                {
                  --y1;
                  e += dx;
                }
              }
            }
            // 7th octant
            else
            {
              int e = dy;
              dx *= 2;
              dy *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::DOWN_RIGHT_OCTANT);
                --y1;
                if (y1 == y2)
                  break;
                e += dx;
                if (e > 0)
                {
                  ++x1;
                  e += dy;
                }
              }
            }
          }
        }
        // Straight line to the right
        else
        {
          std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_RIGHT);
          while (x1 != x2)
          {
            ++x1;
            std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_RIGHT);
          }
        }
      }
      else
      {
        dy = y2 - y1;
        if (dy != 0)
        {
          if (dy > 0)
          {
            // 4th octant
            if (-dx >= dy)
            {
              int e = dx;
              dx *= 2;
              dy *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::LEFT_UP_OCTANT);
                --x1;
                if (x1 == x2)
                  break;
                e += dy;
                if (e >= 0)
                {
                  ++y1;
                  e += dx;
                }
              }
            }
            // 3rd octant
            else
            {
              int e = dy;
              dy *= 2;
              dx *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::UP_LEFT_OCTANT);
                ++y1;
                if (y1 == y2)
                  break;
                e += dx;
                if (e <= 0)
                {
                  --x1;
                  e += dy;
                }
              }
            }
          }
          else
          {
            // 5th octant
            if (dx <= dy)
            {
              int e = dx;
              dx *= 2;
              dy *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::LEFT_DOWN_OCTANT);
                --x1;
                if (x1 == x2)
                  break;
                e -= dy;
                if (e >= 0)
                {
                  --y1;
                  e += dx;
                }
              }
            }
            // 6th octant
            else
            {
              int e = dy;
              dy *= 2;
              dx *= 2;
              for (;;)
              {
                std::forward<Fct>(draw)(x1, y1, CircleLocation::DOWN_LEFT_OCTANT);
                --y1;
                if (y1 == y2)
                  break;
                e -= dx;
                if (e >= 0)
                {
                  --x1;
                  e += dy;
                }
              }
            }
          }
        }
        else
        {
          std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_LEFT);
          while (x1 != x2)
          {
            --x1;
            std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_LEFT);
          }
        }
      }
    }
    else
    {
      dy = y2 - y1;
      if (dy != 0)
      {
        if (dy > 0)
        {
          std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_UP);
          while (y1 != y2)
          {
            ++y1;
            std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_UP);
          }
        }
        else
        {
          std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_DOWN);
          while (y1 != y2)
          {
            --y1;
            std::forward<Fct>(draw)(x1, y1, CircleLocation::STRAIGHT_DOWN);
          }
        }
      }
    }
  }
} /* !lel::graphic */
