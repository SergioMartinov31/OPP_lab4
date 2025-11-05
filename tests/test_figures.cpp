#include "gtest/gtest.h"
#include "../include/Point.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include <sstream>
#include <cmath>
#include <memory>
#include <typeinfo>

// ------------------ TRAPEZOID ------------------
TEST(TrapezoidTest, AreaAndCenter) {
    Trapezoid<double> t({0,0}, {4,0}, {3,2}, {0,2});
    EXPECT_NEAR(t.surface(), 7.0, 1e-6);

    Point<double> c = t.center();
    EXPECT_NEAR(c.x, 1.75, 1e-6);
    EXPECT_NEAR(c.y, 1.0, 1e-6);
}

TEST(TrapezoidTest, ValidationAndEquality) {
    Trapezoid<int> t({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> same({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> bad({0,0}, {1,0}, {2,0}, {3,0});

    EXPECT_TRUE(t.validate());
    EXPECT_FALSE(bad.validate());
    EXPECT_TRUE(t == same);
    EXPECT_FALSE(t == bad);
}

TEST(TrapezoidTest, CopyAndMove) {
    Trapezoid<int> t1({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> t2 = t1;  // copy
    EXPECT_TRUE(t1 == t2);

    Trapezoid<int> t3 = std::move(t1);  // move
    EXPECT_TRUE(t2 == t3);

    Trapezoid<int> t4;
    t4 = t2;
    EXPECT_TRUE(t2 == t4);

    Trapezoid<int> t5;
    t5 = std::move(t2);
    EXPECT_TRUE(t3 == t5);
}

TEST(TrapezoidTest, OperatorDouble) {
    Trapezoid<double> t({0,0}, {4,0}, {3,2}, {0,2});
    double s = double(t);
    EXPECT_NEAR(s, 7.0, 1e-6);
}

TEST(TrapezoidTest, CrossTypeEquality) {
    Trapezoid<int> t({0,0}, {4,0}, {3,2}, {0,2});
    Rhombus<int> r({0,0}, {1,1}, {2,0}, {1,-1});
    EXPECT_FALSE(t == r);
}

TEST(TrapezoidTest, InputOutput) {
    Trapezoid<double> t;
    std::stringstream ss("0 0  4 0  3 2  0 2");
    ss >> t;
    std::stringstream out;
    out << t;
    EXPECT_NE(out.str().find("(0"), std::string::npos);
}

// ------------------ RHOMBUS ------------------
TEST(RhombusTest, AreaCenterEquality) {
    Rhombus<int> r1({0,0}, {1,1}, {2,0}, {1,-1});
    EXPECT_NEAR(r1.surface(), 2.0, 1e-6);

    Point<int> c = r1.center();
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 0.0, 1e-6);

    Rhombus<int> r2(r1);
    EXPECT_TRUE(r1 == r2);
}

TEST(RhombusTest, CopyMove) {
    Rhombus<int> r1({0,0}, {1,1}, {2,0}, {1,-1});
    Rhombus<int> r2 = r1;
    EXPECT_TRUE(r1 == r2);

    Rhombus<int> r3 = std::move(r1);
    EXPECT_TRUE(r2 == r3);

    Rhombus<int> r4;
    r4 = r2;
    EXPECT_TRUE(r2 == r4);

    Rhombus<int> r5;
    r5 = std::move(r2);
    EXPECT_TRUE(r3 == r5);
}

TEST(RhombusTest, OperatorDouble) {
    Rhombus<double> r({0,0}, {1,1}, {2,0}, {1,-1});
    EXPECT_NEAR(double(r), 2.0, 1e-6);
}

TEST(RhombusTest, Invalid) {
    Rhombus<int> bad({0,0}, {1,1}, {2,2}, {3,3});
    EXPECT_FALSE(bad.validate());
}

// ------------------ PENTAGON ------------------
TEST(PentagonTest, AreaCenter) {
    std::array<Point<double>,5> pts = {
        { {0,0}, {2,0}, {3,1}, {1.5,3}, {0,1} }
    };
    Pentagon<double> p(pts);
    EXPECT_GT(p.surface(), 0.0);

    Point<double> c = p.center();
    EXPECT_NEAR(c.x, (0+2+3+1.5+0)/5.0, 1e-6);
    EXPECT_NEAR(c.y, (0+0+1+3+1)/5.0, 1e-6);
}

TEST(PentagonTest, CopyMove) {
    std::array<Point<int>,5> pts = { { {0,0}, {1,0}, {2,1}, {1,2}, {0,1} } };
    Pentagon<int> p1(pts);
    Pentagon<int> p2 = p1;
    EXPECT_TRUE(p1 == p2);

    Pentagon<int> p3 = std::move(p1);
    EXPECT_TRUE(p2 == p3);

    Pentagon<int> p4;
    p4 = p2;
    EXPECT_TRUE(p2 == p4);

    Pentagon<int> p5;
    p5 = std::move(p2);
    EXPECT_TRUE(p3 == p5);
}

TEST(PentagonTest, OperatorDouble) {
    std::array<Point<double>,5> pts = { { {0,0}, {2,0}, {3,1}, {1.5,3}, {0,1} } };
    Pentagon<double> p(pts);
    EXPECT_GT(double(p), 0.0);
}

TEST(PentagonTest, Invalid) {
    std::array<Point<int>,5> pts = { { {0,0}, {1,0}, {2,0}, {3,0}, {4,0} } };
    Pentagon<int> p(pts);
    EXPECT_FALSE(p.validate());
}

// ------------------ POINT ------------------
TEST(PointTest, DistanceIO) {
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

// ------------------ CROSS-TYPE COMPARISON ------------------
TEST(CrossTypeTest, PentagonTrapezoid) {
    std::array<Point<int>,5> pts = { { {0,0}, {1,0}, {2,1}, {1,2}, {0,1} } };
    Pentagon<int> p(pts);
    Trapezoid<int> t({0,0}, {4,0}, {3,2}, {0,2});
    EXPECT_FALSE(p == t);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
