#pragma once

#include "type.h"

#define RGBA_U8(r, g, b, a)                                                    \
    {                                                                          \
        (r) / 255.0f, (g) / 255.0f, (b) / 255.0f, (a) / 255.0f                 \
    }

#define RGBA_F(r, g, b, a)                                                     \
    {                                                                          \
        (r), (g), (b), (a)                                                     \
    }

namespace anyone {

struct Color {
    float r, g, b, a;

    static const Color INDIAN_RED;
    static const Color LIGHT_CORAL;
    static const Color SALMON;
    static const Color DARK_SALMON;
    static const Color LIGHT_SALMON;
    static const Color CRIMSON;
    static const Color RED;
    static const Color FIRE_BRICK;
    static const Color DARK_RED;
    static const Color PINK;
    static const Color LIGHT_PINK;
    static const Color HOT_PINK;
    static const Color DEEP_PINK;
    static const Color MEDIUM_VIOLET_RED;
    static const Color PALE_VIOLET_RED;
    static const Color CORAL;
    static const Color TOMATO;
    static const Color ORANGE_RED;
    static const Color DARK_ORANGE;
    static const Color ORANGE;
    static const Color GOLD;
    static const Color YELLOW;
    static const Color LIGHT_YELLOW;
    static const Color LEMON_CHIFFON;
    static const Color LIGHT_GOLDENROD_YELLOW;
    static const Color PAPAYA_WHIP;
    static const Color MOCCASIN;
    static const Color PEACH_PUFF;
    static const Color PALE_GOLDENROD;
    static const Color KHAKI;
    static const Color DARK_KHAKI;
    static const Color LAVENDER;
    static const Color THISTLE;
    static const Color PLUM;
    static const Color VIOLET;
    static const Color ORCHID;
    static const Color FUCHSIA;
    static const Color MAGENTA;
    static const Color MEDIUM_ORCHID;
    static const Color MEDIUM_PURPLE;
    static const Color REBECCA_PURPLE;
    static const Color BLUE_VIOLET;
    static const Color DARK_VIOLET;
    static const Color DARK_ORCHID;
    static const Color DARK_MAGENTA;
    static const Color PURPLE;
    static const Color INDIGO;
    static const Color SLATE_BLUE;
    static const Color DARK_SLATE_BLUE;
    static const Color MEDIUM_SLATE_BLUE;
    static const Color GREEN_YELLOW;
    static const Color CHARTREUSE;
    static const Color LAWN_GREEN;
    static const Color LIME;
    static const Color LIME_GREEN;
    static const Color PALE_GREEN;
    static const Color LIGHT_GREEN;
    static const Color MEDIUM_SPRING_GREEN;
    static const Color SPRING_GREEN;
    static const Color MEDIUM_SEA_GREEN;
    static const Color SEA_GREEN;
    static const Color FOREST_GREEN;
    static const Color GREEN;
    static const Color DARK_GREEN;
    static const Color YELLOW_GREEN;
    static const Color OLIVE_DRAB;
    static const Color OLIVE;
    static const Color DARK_OLIVE_GREEN;
    static const Color MEDIUM_AQUAMARINE;
    static const Color DARK_SEA_GREEN;
    static const Color LIGHT_SEA_GREEN;
    static const Color DARK_CYAN;
    static const Color TEAL;
    static const Color AQUA;
    static const Color CYAN;
    static const Color LIGHT_CYAN;
    static const Color PALE_TURQUOISE;
    static const Color AQUAMARINE;
    static const Color TURQUOISE;
    static const Color MEDIUM_TURQUOISE;
    static const Color DARK_TURQUOISE;
    static const Color CADET_BLUE;
    static const Color STEEL_BLUE;
    static const Color LIGHT_STEEL_BLUE;
    static const Color POWDER_BLUE;
    static const Color LIGHT_BLUE;
    static const Color SKY_BLUE;
    static const Color LIGHT_SKY_BLUE;
    static const Color DEEP_SKY_BLUE;
    static const Color DODGER_BLUE;
    static const Color CORNFLOWER_BLUE;
    static const Color ROYAL_BLUE;
    static const Color BLUE;
    static const Color MEDIUM_BLUE;
    static const Color DARK_BLUE;
    static const Color NAVY;
    static const Color MIDNIGHT_BLUE;
    static const Color CORNSILK;
    static const Color BLANCHED_ALMOND;
    static const Color BISQUE;
    static const Color NAVAJO_WHITE;
    static const Color WHEAT;
    static const Color BURLY_WOOD;
    static const Color TAN;
    static const Color ROSY_BROWN;
    static const Color SANDY_BROWN;
    static const Color GOLDENROD;
    static const Color DARK_GOLDENROD;
    static const Color PERU;
    static const Color CHOCOLATE;
    static const Color SADDLE_BROWN;
    static const Color SIENNA;
    static const Color BROWN;
    static const Color MAROON;
    static const Color WHITE;
    static const Color SNOW;
    static const Color HONEY_DEW;
    static const Color MINT_CREAM;
    static const Color AZURE;
    static const Color ALICE_BLUE;
    static const Color GHOST_WHITE;
    static const Color WHITE_SMOKE;
    static const Color SEA_SHELL;
    static const Color BEIGE;
    static const Color OLD_LACE;
    static const Color FLORAL_WHITE;
    static const Color IVORY;
    static const Color ANTIQUE_WHITE;
    static const Color LINEN;
    static const Color LAVENDER_BLUSH;
    static const Color MISTY_ROSE;
    static const Color GAINSBORO;
    static const Color LIGHT_GRAY;
    static const Color SILVER;
    static const Color DARK_GRAY;
    static const Color GRAY;
    static const Color DIM_GRAY;
    static const Color LIGHT_SLATE_GRAY;
    static const Color SLATE_GRAY;
    static const Color DARK_SLATE_GRAY;
    static const Color BLACK;
};

} // namespace anyone