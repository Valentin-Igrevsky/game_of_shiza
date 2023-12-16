#include "gtest/gtest.h"
#include "life_backend.h"

TEST(life_backend, Constructor) {
    ASSERT_THROW(life_backend::Life(1,1), life_backend::LifeException);
    ASSERT_THROW(life_backend::Life(3,1), life_backend::LifeException);
    ASSERT_THROW(life_backend::Life(1,3), life_backend::LifeException);

    life_backend::Life a(3,4);
    ASSERT_EQ(a.getWidth(), 3);
    ASSERT_EQ(a.getHeight(), 4);
    ASSERT_EQ(a.getCellStates(), std::vector<bool>({0,0,0,0,0,0,0,0,0,0,0,0}));
}

TEST(life_backend, setCellStates) {
    life_backend::Life a(3,4);
    a.setCellAlive(0, 0);
    a.setCellAlive(1, 0);
    a.setCellAlive(0, 1);
    a.setCellAlive(2, 3);
    ASSERT_EQ(a.getCellStates(), std::vector<bool>({1,1,0,1,0,0,0,0,0,0,0,1}));

    a.setCellDead(1, 0);
    a.setCellDead(2, 3);
    ASSERT_EQ(a.getCellStates(), std::vector<bool>({1,0,0,1,0,0,0,0,0,0,0,0}));

    ASSERT_THROW(a.setCellAlive(-1, 0), life_backend::LifeException);
    ASSERT_THROW(a.setCellDead(3, 3), life_backend::LifeException);
}

TEST(life_backend, ostream) {
    life_backend::Life a(3,4);
    a.setCellAlive(0, 0);
    a.setCellAlive(1, 0);
    a.setCellAlive(0, 1);
    a.setCellAlive(2, 3);
    std::stringstream ss;
    ss << a;
    ASSERT_STREQ(ss.str().c_str(), "* * .\n* . .\n. . .\n. . *\n");
}

TEST(life_backend, updateCellStates) {
    life_backend::Life a(3,4);
    a.setCellAlive(0, 0);
    a.setCellAlive(1, 0);
    a.setCellAlive(0, 1);
    a.setCellAlive(2, 3);
    a.updateCellStates();
    ASSERT_EQ(a.getCellStates(), std::vector<bool>({1,1,0,1,1,1,0,0,0,1,1,1}));
}

TEST(life_backend, getAliveNeighbourCount) {
    life_backend::Life a(3, 4);
    a.setCellAlive(0, 0);
    a.setCellAlive(1, 0);
    a.setCellAlive(0, 1);
    a.setCellAlive(2, 3);
    ASSERT_EQ(a.getAliveNeighbourCount(0,0), 3);
    ASSERT_EQ(a.getAliveNeighbourCount(1,2), 2);
    ASSERT_EQ(a.getAliveNeighbourCount(0,3), 3);
}

void print(std::vector<bool> &vec) {
    for(auto && i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

TEST(life_backend, resize) {
    life_backend::Life a(2, 2);

    a.resize(5, 5);
    EXPECT_EQ(a.getWidth(), 5);
    EXPECT_EQ(a.getHeight(), 5);

    a.resize(7, 7);
    EXPECT_EQ(a.getWidth(), 7);
    EXPECT_EQ(a.getHeight(), 7);

    a.resize(3, 3);
    EXPECT_EQ(a.getWidth(), 3);
    EXPECT_EQ(a.getHeight(), 3);
}

