#include "gtest/gtest.h"
#include "../include/Point.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include <sstream>
#include <cmath>

// ------------------ TRAPEZOID ------------------
TEST(TrapezoidTest, AreaAndCenter) {
    Trapezoid<double> t({0,0}, {4,0}, {3,2}, {0,2});
    EXPECT_NEAR(t.surface(), 7.0, 1e-6);

    Point<double> c = t.center();
    EXPECT_NEAR(c.x, 1.75, 1e-6);
    EXPECT_NEAR(c.y, 1.0, 1e-6);
}

TEST(TrapezoidTest, Validation) {
    Trapezoid<int> t({0,0}, {4,0}, {3,2}, {0,2});
    EXPECT_TRUE(t.validate());

    Trapezoid<int> bad({0,0}, {1,0}, {2,0}, {3,0});
    EXPECT_FALSE(bad.validate());
}

TEST(TrapezoidTest, Equality) {
    Trapezoid<int> a({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> b({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> c({0,0}, {2,0}, {2,1}, {0,1});
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

// ------------------ RHOMBUS ------------------
TEST(RhombusTest, AreaCenterAndEquality) {
    Rhombus<int> r1({0,0}, {1,1}, {2,0}, {1,-1});
    EXPECT_NEAR(r1.surface(), 2.0, 1e-6);
    Point<int> c = r1.center();
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 0.0, 1e-6);

    Rhombus<int> r2(r1);
    EXPECT_TRUE(r1 == r2);
}

TEST(RhombusTest, Validation) {
    Rhombus<int> r({0,0}, {1,1}, {2,0}, {1,-1});
    EXPECT_TRUE(r.validate());
}

// ------------------ PENTAGON ------------------
TEST(PentagonTest, AreaPositiveAndCenter) {
    std::array<Point<double>,5> pts = {
        Point<double>(0,0),
        Point<double>(2,0),
        Point<double>(3,1),
        Point<double>(1.5,3),
        Point<double>(0,1)
    };
    Pentagon<double> p(pts);
    EXPECT_GT(p.surface(), 0.0);

    Point<double> c = p.center();
    EXPECT_NEAR(c.x, (0+2+3+1.5+0)/5.0, 1e-6);
    EXPECT_NEAR(c.y, (0+0+1+3+1)/5.0, 1e-6);
}

TEST(PentagonTest, CopyAndMove) {
    std::array<Point<int>,5> pts = {
        Point<int>(0,0),
        Point<int>(1,0),
        Point<int>(2,1),
        Point<int>(1,2),
        Point<int>(0,1)
    };

    Pentagon<int> p1(pts);
    Pentagon<int> p2(p1);
    EXPECT_TRUE(p1 == p2);

    Pentagon<int> p3(std::move(p1));
    EXPECT_TRUE(p2 == p3);

    Pentagon<int> p4;
    p4 = p2;
    EXPECT_TRUE(p2 == p4);

    Pentagon<int> p5;
    p5 = std::move(p2);
    EXPECT_TRUE(p3 == p5);
}

// ------------------ POINT ------------------
TEST(PointTest, DistanceAndIO) {
    Point<double> p1(0,0), p2(3,4);
    EXPECT_NEAR(p1.distanceTo(p2), 5.0, 1e-6);

    std::stringstream ss;
    ss << p1;
    EXPECT_NE(ss.str().find("0"), std::string::npos);

    Point<double> p3;
    std::stringstream in("1.5 2.5");
    in >> p3;
    EXPECT_NEAR(p3.x, 1.5, 1e-6);
    EXPECT_NEAR(p3.y, 2.5, 1e-6);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}