#include "gtest/gtest.h"

#include "../include/Point.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Array.h"

#include <sstream>
#include <cmath>
#include <memory>
#include <array>

// ================== TRAPEZOID ==================
TEST(TrapezoidTest, AreaAndCenter) {
    Trapezoid<double> t({0,0}, {4,0}, {3,2}, {0,2});

    EXPECT_NEAR(double(t), 7.0, 1e-6);

    auto c = t.center();
    EXPECT_NEAR(c.x(), 1.75, 1e-6);
    EXPECT_NEAR(c.y(), 1.0, 1e-6);
}

TEST(TrapezoidTest, Equality) {
    Trapezoid<int> t({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> same({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> bad({0,0}, {1,0}, {2,0}, {3,0});

    EXPECT_TRUE(t == same);
    EXPECT_FALSE(t == bad);
}

TEST(TrapezoidTest, CopyAndMove) {
    Trapezoid<int> t1({0,0}, {4,0}, {3,2}, {0,2});
    Trapezoid<int> t2 = t1;
    EXPECT_TRUE(t1 == t2);

    Trapezoid<int> t3 = std::move(t1);
    EXPECT_TRUE(t2 == t3);

    Trapezoid<int> t4;
    t4 = t2;
    EXPECT_TRUE(t2 == t4);

    Trapezoid<int> t5;
    t5 = std::move(t2);
    EXPECT_TRUE(t3 == t5);
}

TEST(TrapezoidTest, InputOutput) {
    Trapezoid<double> t;
    std::stringstream ss("0 0 4 0 3 2 0 2");
    ss >> t;

    std::stringstream out;
    out << t;

    EXPECT_NE(out.str().find("("), std::string::npos);
}

// ================== RHOMBUS ==================
TEST(RhombusTest, AreaCenterEquality) {
    Rhombus<int> r({0,0}, {1,1}, {2,0}, {1,-1});

    EXPECT_NEAR(double(r), 2.0, 1e-6);

    auto c = r.center();
    EXPECT_NEAR(c.x(), 1.0, 1e-6);
    EXPECT_NEAR(c.y(), 0.0, 1e-6);

    Rhombus<int> copy(r);
    EXPECT_TRUE(r == copy);
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

TEST(RhombusTest, Invalid) {
    Rhombus<int> bad({0,0}, {1,1}, {2,2}, {3,3});
    EXPECT_FALSE(double(bad) > 0);
}

// ================== PENTAGON ==================
TEST(PentagonTest, AreaCenter) {
    std::array<Point<double>,5> pts = {{
        {0,0}, {2,0}, {3,1}, {1.5,3}, {0,1}
    }};

    Pentagon<double> p(pts);

    EXPECT_GT(double(p), 0.0);

    auto c = p.center();
    EXPECT_NEAR(c.x(), (0+2+3+1.5+0)/5.0, 1e-6);
    EXPECT_NEAR(c.y(), (0+0+1+3+1)/5.0, 1e-6);
}

TEST(PentagonTest, CopyMove) {
    std::array<Point<int>,5> pts = {{
        {0,0}, {1,0}, {2,1}, {1,2}, {0,1}
    }};

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

TEST(PentagonTest, Invalid) {
    std::array<Point<int>,5> pts = {{
        {0,0}, {1,0}, {2,0}, {3,0}, {4,0}
    }};
    Pentagon<int> p(pts);

    EXPECT_FALSE(double(p) > 0);
}

// ================== POINT ==================
TEST(PointTest, DistanceIO) {
    Point<double> p1(0,0), p2(3,4);
    EXPECT_NEAR(p1.distanceTo(p2), 5.0, 1e-6);

    std::stringstream ss;
    ss << p1;
    EXPECT_NE(ss.str().find("0"), std::string::npos);

    Point<double> p3;
    std::stringstream in("1.5 2.5");
    in >> p3;

    EXPECT_NEAR(p3.x(), 1.5, 1e-6);
    EXPECT_NEAR(p3.y(), 2.5, 1e-6);
}

// ================== CROSS TYPE ==================
TEST(CrossTypeTest, PentagonTrapezoid) {
    std::array<Point<int>,5> pts = {{
        {0,0}, {1,0}, {2,1}, {1,2}, {0,1}
    }};
    Pentagon<int> p(pts);
    Trapezoid<int> t({0,0}, {4,0}, {3,2}, {0,2});

    EXPECT_FALSE(p == t);
}

// ================== ARRAY ==================
TEST(ArrayTest, NonPolymorphicContainer) {
    Array<Trapezoid<int>> arr;

    arr.add(Trapezoid<int>({0,0}, {4,0}, {3,2}, {0,2}));
    arr.add(Trapezoid<int>({1,1}, {5,1}, {4,3}, {2,3}));

    EXPECT_EQ(arr.getSize(), 2);

    double total = 0;
    for (size_t i = 0; i < arr.getSize(); ++i)
        total += double(arr[i]);

    EXPECT_NEAR(total, 13.0, 1e-6);
}

TEST(ArrayTest, Polymorphism) {
    Array<std::shared_ptr<Figure<int>>> arr;

    arr.add(std::make_shared<Trapezoid<int>>(
        Point<int>(0,0), Point<int>(4,0), Point<int>(3,2), Point<int>(0,2)
    ));
    arr.add(std::make_shared<Rhombus<int>>(
        Point<int>(0,0), Point<int>(1,1), Point<int>(2,0), Point<int>(1,-1)
    ));
    std::array<Point<int>,5> pts = {{
        {0,0}, {1,0}, {2,1}, {1,2}, {0,1}
    }};
    arr.add(std::make_shared<Pentagon<int>>(pts));

    EXPECT_NE(dynamic_cast<Trapezoid<int>*>(arr[0].get()), nullptr);
    EXPECT_NE(dynamic_cast<Rhombus<int>*>(arr[1].get()), nullptr);
    EXPECT_NE(dynamic_cast<Pentagon<int>*>(arr[2].get()), nullptr);
}

// ================== MAIN ==================
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
