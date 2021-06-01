#define CATCH_CONFIG_MAIN
#include "../catch2/catch2.hpp"
#include "../Headers/rgb.h"

TEST_CASE("checking hex to decimal constructor")
{
    SECTION("invalid hex codes")
    {
        REQUIRE_THROWS(RGB("ffffff"));
        REQUIRE_THROWS(RGB("#fffff"));
        REQUIRE_THROWS(RGB("#ffffj"));
        REQUIRE_THROWS(RGB("#1234-"));
        REQUIRE_THROWS(RGB("#1ff1"));
        REQUIRE_THROWS(RGB(""));
    }

    SECTION("valid hex codes")
    {
        RGB color0("#000000");
        REQUIRE(color0.red == 0);
        REQUIRE(color0.green == 0);
        REQUIRE(color0.blue == 0);

        RGB color00("#ffffff");
        REQUIRE(color00.red == 255);
        REQUIRE(color00.green == 255);
        REQUIRE(color00.blue == 255);

        RGB color1("#142445");
        REQUIRE(color1.red == 20);
        REQUIRE(color1.green == 36);
        REQUIRE(color1.blue == 69); 


        RGB color2("#3a2722");
        REQUIRE(color2.red == 58);
        REQUIRE(color2.green == 39);
        REQUIRE(color2.blue == 34);

        RGB color3("#d6dff7");
        REQUIRE(color3.red == 214);
        REQUIRE(color3.green == 223);
        REQUIRE(color3.blue == 247);

        RGB color4("#7a8b0e");
        REQUIRE(color4.red == 122);
        REQUIRE(color4.green == 139);
        REQUIRE(color4.blue == 14);

        RGB color5("#f4287e");
        REQUIRE(color5.red == 244);
        REQUIRE(color5.green == 40);
        REQUIRE(color5.blue == 126);

        RGB color6("#3e9272");
        REQUIRE(color6.red == 62);
        REQUIRE(color6.green == 146);
        REQUIRE(color6.blue == 114);

        RGB color7("#0f547f");
        REQUIRE(color7.red == 15);
        REQUIRE(color7.green == 84);
        REQUIRE(color7.blue == 127);

        RGB color8("#f1b1d1");
        REQUIRE(color8.red == 241);
        REQUIRE(color8.green == 177);
        REQUIRE(color8.blue == 209);

        RGB color9("#60e217");
        REQUIRE(color9.red == 96);
        REQUIRE(color9.green == 226);
        REQUIRE(color9.blue == 23);

        RGB color10("#25add0");
        REQUIRE(color10.red == 37);
        REQUIRE(color10.green == 173);
        REQUIRE(color10.blue == 208);
    }
}

TEST_CASE("checking default constructor")
{
    RGB color;
    REQUIRE(color.red == 0);
    REQUIRE(color.green == 0);
    REQUIRE(color.blue == 0);
}

TEST_CASE("checking constructor with parameters")
{
    SECTION("invalid arguments")
    {
        REQUIRE_THROWS(RGB(-5, 10, 20));
        REQUIRE_THROWS(RGB(0, 0, -1));
        REQUIRE_THROWS(RGB(256, 256, 256));
        REQUIRE_THROWS(RGB(255, 255, 256));
    }

    SECTION("valid arguments")
    {
        RGB color1(0, 0, 0);
        REQUIRE(color1.red == 0);
        REQUIRE(color1.green == 0);
        REQUIRE(color1.blue == 0);

        RGB color2(255, 255, 255);
        REQUIRE(color2.red == 255);
        REQUIRE(color2.green == 255);
        REQUIRE(color2.blue == 255);

        RGB color3(0, 100, 200);
        REQUIRE(color3.red == 0);
        REQUIRE(color3.green == 100);
        REQUIRE(color3.blue == 200);
    }
}