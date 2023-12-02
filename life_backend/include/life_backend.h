#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#define EXPORT __attribute__((visibility("default")))

namespace life_backend {
    class LifeException : public std::runtime_error {
    public:
        explicit LifeException(const std::string &message);
    };

    class Life {
    public:
        explicit Life(size_t width, size_t height);

        size_t getWidth() const;

        size_t getHeight() const;

        std::vector<bool> getCellStates() const;

        void setCellDead(size_t x, size_t y);

        void setCellAlive(size_t x, size_t y);

        bool getCellState(size_t x, size_t y) const;

        size_t getAliveNeighbourCount(size_t x, size_t y) const;

        void updateCellStates();

        friend std::ostream &operator<<(std::ostream &os, const Life &life);

        void fillRandomStates();

        void clear();

        void resize(long long int newWidth, long long int newHeight);

        bool fillCoolestStates();

        bool USSR();

        bool ZRUSZ();

    private:
        void setCellStates(size_t x, size_t y, bool state);

        void refactor(int64_t &x, int64_t &y) const;

        void isCorrectCoordinates(size_t x, size_t y) const;

        size_t width_;
        size_t height_;
        std::vector<bool> cell_states_;
    };
}

//extern "C" {
//    EXPORT void *create_life(size_t width, size_t height);
//    EXPORT void destroy_life(void *life);
//}