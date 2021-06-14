#define CATCH_CONFIG_MAIN
#include "../catch2/catch2.hpp"
#include "../Headers/commandLine.h"

TEST_CASE("check operator []")
{   
    SECTION("NEW")
    {
        CommandLine cmd("     neW        1000 1000         #ffffff"); 
        REQUIRE(cmd[0] == "NEW");
        REQUIRE(cmd[1] == "1000");
        REQUIRE(cmd[2] == "1000");
        REQUIRE(cmd[3] == "#ffffff");
        REQUIRE(cmd.getSize() == 4);
        REQUIRE_THROWS(cmd[4]);
    }

    SECTION("OPEN")
    {
        CommandLine cmd("      opEn \"Images/cube.ppm\"    ");
        REQUIRE(cmd[0] == "OPEN");
        REQUIRE(cmd[1] == "Images/cube.ppm");
        REQUIRE(cmd.getSize() == 2);
        REQUIRE_THROWS(cmd[2]);
    }

    SECTION("CLOSE")
    {
        CommandLine cmd("clOsE");
        REQUIRE(cmd[0] == "CLOSE");
        REQUIRE(cmd.getSize() == 1);
        REQUIRE_THROWS(cmd[1]);
    }

    SECTION("SAVE")
    {
        CommandLine cmd("sAVE");
        REQUIRE(cmd[0] == "SAVE");
        REQUIRE(cmd.getSize() == 1);
        REQUIRE_THROWS(cmd[1]);
    }

    SECTION("SAVEAS")
    {
        CommandLine cmd("      saveAs \"Images/cube.ppm\"    ");
        REQUIRE(cmd[0] == "SAVEAS");
        REQUIRE(cmd[1] == "Images/cube.ppm");
        REQUIRE(cmd.getSize() == 2);
        REQUIRE_THROWS(cmd[2]);
    }

    SECTION("EXIT")
    {
        CommandLine cmd("exit");
        REQUIRE(cmd[0] == "EXIT");
        REQUIRE(cmd.getSize() == 1);
        REQUIRE_THROWS(cmd[1]);
    }

    SECTION("HELP")
    {
        CommandLine cmd("HeLP");
        REQUIRE(cmd[0] == "HELP");
        REQUIRE(cmd.getSize() == 1);
        REQUIRE_THROWS(cmd[1]);
    }

    SECTION("DITHER")
    {
        CommandLine cmd("       dITHer");
        REQUIRE(cmd[0] == "DITHER");
        REQUIRE(cmd.getSize() == 1);
        REQUIRE_THROWS(cmd[1]);
    }

    SECTION("RESIZE")
    {
        CommandLine cmd1("        resize      100   100");
        REQUIRE(cmd1[0] == "RESIZE");
        REQUIRE(cmd1[1] == "100");
        REQUIRE(cmd1[2] == "100");
        REQUIRE(cmd1.getSize() == 3);
        REQUIRE_THROWS(cmd1[3]);

        CommandLine cmd2("    resize      100                   ");
        REQUIRE(cmd2[0] == "RESIZE");
        REQUIRE(cmd2[1] == "100");
        REQUIRE(cmd2.getSize() == 2);
        REQUIRE_THROWS(cmd2[2]);
    }

    SECTION("CROP")
    {
        CommandLine cmd("     crop        1000 1000 20 20"); 
        REQUIRE(cmd[0] == "CROP");
        REQUIRE(cmd[1] == "1000");
        REQUIRE(cmd[2] == "1000");
        REQUIRE(cmd[3] == "20");
        REQUIRE(cmd[4] == "20");
        REQUIRE(cmd.getSize() == 5);
        REQUIRE_THROWS(cmd[5]);
    }
}