#include "../include/Life.h"
#include <iostream>
#include <random>


namespace life_backend {
    LifeException::LifeException(const std::string &message) : std::runtime_error(message) {}

    Life::Life(size_t width, size_t height) : width_(width), height_(height) {
        if (width_ < 3 || height_ < 3) {
            throw LifeException("Wrong width and height");
        }
        cell_states_.resize(height_ * width_);
    }

    size_t Life::getWidth() const {
        return width_;
    }

    size_t Life::getHeight() const {
        return height_;
    }

    std::vector<bool> Life::getCellStates() const {
        return cell_states_;
    }

    void Life::setCellStates(size_t x, size_t y, bool state) {
        isCorrectCoordinates(x, y);
        cell_states_[y * width_ + x] = state;
    }

    void Life::refactor(int64_t &x, int64_t &y) const {
        if (x == -1) x = x + width_;
        else if (x == width_) x = 0;
        if (y == -1) y = y + height_;
        else if (y == height_) y = 0;
    }

    void Life::isCorrectCoordinates(size_t x, size_t y) const {
        if (x >= width_ || y >= height_) {
            throw LifeException("Wrong cell coordinates:"
                                " x = " + std::to_string(x) +
                                "; y = " + std::to_string(y) + ";");
        }
    }

    void Life::setCellDead(size_t x, size_t y) {
        setCellStates(x, y, false);
    }

    void Life::setCellAlive(size_t x, size_t y) {
        setCellStates(x, y, true);
    }

    bool Life::getCellState(size_t x, size_t y) const {
        isCorrectCoordinates(x, y);
        return cell_states_[y * width_ + x];
    }

    size_t Life::getAliveNeighbourCount(size_t x, size_t y) const {
        isCorrectCoordinates(x, y);
        size_t count = 0;
        int64_t cx;
        int64_t cy;
        for (int64_t i = -1; i < 2; ++i) {
            for (int64_t j = -1; j < 2; ++j) {
                cx = i + x;
                cy = j + y;
                refactor(cx, cy);
                if (cx == x && cy == y) continue;
                else count += getCellState(cx, cy);
            }
        }
        return count;
    }

    void Life::updateCellStates() {
        Life new_life(width_, height_);\
    size_t count;
        for (size_t x = 0; x < width_; ++x) {
            for (size_t y = 0; y < height_; ++y) {
                count = getAliveNeighbourCount(x, y);
                if (getCellState(x, y)) {
                    if (count >= 2 && count <= 3) new_life.setCellAlive(x, y);
                } else if (count == 3) new_life.setCellAlive(x, y);
            }
        }
        std::swap(*this, new_life);
    }

    std::ostream &operator<<(std::ostream &os, const Life &life) {
        for (size_t y = 0; y < life.height_; ++y) {
            for (size_t x = 0; x < life.width_; ++x) {
//                os << (life.getCellState(x, y) ? '\xDB' : '\xB0');
                os << (life.getCellState(x, y) ? '*' : '.');
                if (x != life.getWidth() - 1) {
                    os << ' ';
                }
            }
            os << std::endl;
        }
        return os;
    }

    void Life::fillRandomStates() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        for (size_t i = 0; i < width_ * height_; ++i) {
            cell_states_[i] = (dis(gen));
        }
    }
}

void *create_life(size_t width, size_t height) {
    return new life_backend::Life(width, height);
}

EXPORT void destroy_life(void *life) {
    if (life != nullptr) {
        delete life;
    }
}