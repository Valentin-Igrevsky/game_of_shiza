#include <iostream>
#include <random>
#include "life_backend.h"


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

    void Life::clear() {
        for (size_t i = 0; i < width_ * height_; ++i) {
            cell_states_[i] = false;
        }
    }

    void Life::resize(long long int newWidth, long long int newHeight) {
        long long int deltaX = newWidth - static_cast<long long int>(width_);
        long long int deltaY = newHeight - static_cast<long long int>(height_);

        std::vector<bool>::iterator iter;

        unsigned int pos;

        if (deltaX > 0) {
            for (size_t y = 0; y < height_; ++y) {
                iter = cell_states_.begin() + static_cast<unsigned int>(width_ + newWidth * y);
                cell_states_.insert(iter, deltaX, false);
            }
        } else if (deltaX < 0) {
            for (size_t y = 0; y < height_; ++y) {
                pos = static_cast<unsigned int>((width_ + deltaX) * (y + 1));
                iter = cell_states_.begin() + pos;
                cell_states_.erase(iter, iter - deltaX);
            }
        }

        if (deltaY > 0) {
            cell_states_.insert(cell_states_.cend(), deltaY * newWidth, false);
        } else if (deltaY < 0) {
            cell_states_.erase(cell_states_.begin() + newHeight*newWidth, cell_states_.end());
        }

        width_ = newWidth;
        height_ = newHeight;
    }

    bool Life::fillCoolestStates() {
        if (width_ >= 37 and height_ >= 30) {
            this->clear();
            setCellAlive(8, 0);
            setCellAlive(9, 0);
            setCellAlive(10, 0);
            setCellAlive(11, 0);
            setCellAlive(12, 0);
            setCellAlive(13, 0);
            setCellAlive(14, 0);
            setCellAlive(15, 0);
            setCellAlive(16, 0);
            setCellAlive(17, 0);
            setCellAlive(18, 0);
            setCellAlive(19, 0);
            setCellAlive(20, 0);
            setCellAlive(21, 0);
            setCellAlive(22, 0);
            setCellAlive(23, 0);
            setCellAlive(24, 0);
            setCellAlive(7, 1);
            setCellAlive(25, 1);
            setCellAlive(26, 1);
            setCellAlive(27, 1);
            setCellAlive(28, 1);
            setCellAlive(29, 1);
            setCellAlive(6, 2);
            setCellAlive(10, 2);
            setCellAlive(11, 2);
            setCellAlive(12, 2);
            setCellAlive(13, 2);
            setCellAlive(14, 2);
            setCellAlive(15, 2);
            setCellAlive(16, 2);
            setCellAlive(17, 2);
            setCellAlive(18, 2);
            setCellAlive(19, 2);
            setCellAlive(20, 2);
            setCellAlive(21, 2);
            setCellAlive(22, 2);
            setCellAlive(23, 2);
            setCellAlive(30, 2);
            setCellAlive(31, 2);
            setCellAlive(5, 3);
            setCellAlive(9, 3);
            setCellAlive(24, 3);
            setCellAlive(25, 3);
            setCellAlive(26, 3);
            setCellAlive(32, 3);
            setCellAlive(5, 4);
            setCellAlive(11, 4);
            setCellAlive(12, 4);
            setCellAlive(13, 4);
            setCellAlive(14, 4);
            setCellAlive(15, 4);
            setCellAlive(16, 4);
            setCellAlive(18, 4);
            setCellAlive(28, 4);
            setCellAlive(29, 4);
            setCellAlive(33, 4);
            setCellAlive(4, 5);
            setCellAlive(10, 5);
            setCellAlive(19, 5);
            setCellAlive(24, 5);
            setCellAlive(30, 5);
            setCellAlive(33, 5);
            setCellAlive(4, 6);
            setCellAlive(12, 6);
            setCellAlive(13, 6);
            setCellAlive(14, 6);
            setCellAlive(15, 6);
            setCellAlive(16, 6);
            setCellAlive(17, 6);
            setCellAlive(23, 6);
            setCellAlive(26, 6);
            setCellAlive(27, 6);
            setCellAlive(28, 6);
            setCellAlive(29, 6);
            setCellAlive(33, 6);
            setCellAlive(34, 6);
            setCellAlive(3, 7);
            setCellAlive(8, 7);
            setCellAlive(11, 7);
            setCellAlive(13, 7);
            setCellAlive(14, 7);
            setCellAlive(15, 7);
            setCellAlive(18, 7);
            setCellAlive(25, 7);
            setCellAlive(26, 7);
            setCellAlive(27, 7);
            setCellAlive(29, 7);
            setCellAlive(34, 7);
            setCellAlive(2, 8);
            setCellAlive(10, 8);
            setCellAlive(11, 8);
            setCellAlive(12, 8);
            setCellAlive(13, 8);
            setCellAlive(14, 8);
            setCellAlive(15, 8);
            setCellAlive(16, 8);
            setCellAlive(17, 8);
            setCellAlive(18, 8);
            setCellAlive(19, 8);
            setCellAlive(23, 8);
            setCellAlive(24, 8);
            setCellAlive(25, 8);
            setCellAlive(26, 8);
            setCellAlive(27, 8);
            setCellAlive(28, 8);
            setCellAlive(33, 8);
            setCellAlive(35, 8);
            setCellAlive(1, 9);
            setCellAlive(4, 9);
            setCellAlive(5, 9);
            setCellAlive(6, 9);
            setCellAlive(7, 9);
            setCellAlive(8, 9);
            setCellAlive(34, 9);
            setCellAlive(36, 9);
            setCellAlive(0, 10);
            setCellAlive(3, 10);
            setCellAlive(9, 10);
            setCellAlive(10, 10);
            setCellAlive(11, 10);
            setCellAlive(12, 10);
            setCellAlive(30, 10);
            setCellAlive(31, 10);
            setCellAlive(32, 10);
            setCellAlive(33, 10);
            setCellAlive(36, 10);
            setCellAlive(0, 11);
            setCellAlive(3, 11);
            setCellAlive(6, 11);
            setCellAlive(7, 11);
            setCellAlive(8, 11);
            setCellAlive(18, 11);
            setCellAlive(24, 11);
            setCellAlive(28, 11);
            setCellAlive(29, 11);
            setCellAlive(34, 11);
            setCellAlive(36, 11);
            setCellAlive(0, 12);
            setCellAlive(3, 12);
            setCellAlive(5, 12);
            setCellAlive(6, 12);
            setCellAlive(9, 12);
            setCellAlive(10, 12);
            setCellAlive(15, 12);
            setCellAlive(17, 12);
            setCellAlive(25, 12);
            setCellAlive(32, 12);
            setCellAlive(36, 12);
            setCellAlive(0, 13);
            setCellAlive(6, 13);
            setCellAlive(7, 13);
            setCellAlive(10, 13);
            setCellAlive(11, 13);
            setCellAlive(12, 13);
            setCellAlive(13, 13);
            setCellAlive(17, 13);
            setCellAlive(19, 13);
            setCellAlive(20, 13);
            setCellAlive(25, 13);
            setCellAlive(31, 13);
            setCellAlive(32, 13);
            setCellAlive(35, 13);
            setCellAlive(1, 14);
            setCellAlive(6, 14);
            setCellAlive(7, 14);
            setCellAlive(8, 14);
            setCellAlive(11, 14);
            setCellAlive(14, 14);
            setCellAlive(15, 14);
            setCellAlive(23, 14);
            setCellAlive(24, 14);
            setCellAlive(29, 14);
            setCellAlive(30, 14);
            setCellAlive(31, 14);
            setCellAlive(32, 14);
            setCellAlive(35, 14);
            setCellAlive(2, 15);
            setCellAlive(7, 15);
            setCellAlive(8, 15);
            setCellAlive(9, 15);
            setCellAlive(10, 15);
            setCellAlive(11, 15);
            setCellAlive(16, 15);
            setCellAlive(17, 15);
            setCellAlive(18, 15);
            setCellAlive(19, 15);
            setCellAlive(20, 15);
            setCellAlive(26, 15);
            setCellAlive(27, 15);
            setCellAlive(28, 15);
            setCellAlive(29, 15);
            setCellAlive(30, 15);
            setCellAlive(31, 15);
            setCellAlive(32, 15);
            setCellAlive(34, 15);
            setCellAlive(3, 16);
            setCellAlive(8, 16);
            setCellAlive(11, 16);
            setCellAlive(12, 16);
            setCellAlive(13, 16);
            setCellAlive(16, 16);
            setCellAlive(21, 16);
            setCellAlive(22, 16);
            setCellAlive(23, 16);
            setCellAlive(24, 16);
            setCellAlive(25, 16);
            setCellAlive(26, 16);
            setCellAlive(28, 16);
            setCellAlive(30, 16);
            setCellAlive(31, 16);
            setCellAlive(32, 16);
            setCellAlive(34, 16);
            setCellAlive(3, 17);
            setCellAlive(4, 17);
            setCellAlive(9, 17);
            setCellAlive(11, 17);
            setCellAlive(13, 17);
            setCellAlive(14, 17);
            setCellAlive(15, 17);
            setCellAlive(16, 17);
            setCellAlive(17, 17);
            setCellAlive(21, 17);
            setCellAlive(25, 17);
            setCellAlive(28, 17);
            setCellAlive(30, 17);
            setCellAlive(31, 17);
            setCellAlive(32, 17);
            setCellAlive(34, 17);
            setCellAlive(4, 18);
            setCellAlive(10, 18);
            setCellAlive(11, 18);
            setCellAlive(15, 18);
            setCellAlive(16, 18);
            setCellAlive(17, 18);
            setCellAlive(18, 18);
            setCellAlive(19, 18);
            setCellAlive(20, 18);
            setCellAlive(21, 18);
            setCellAlive(22, 18);
            setCellAlive(23, 18);
            setCellAlive(24, 18);
            setCellAlive(25, 18);
            setCellAlive(26, 18);
            setCellAlive(27, 18);
            setCellAlive(28, 18);
            setCellAlive(29, 18);
            setCellAlive(30, 18);
            setCellAlive(31, 18);
            setCellAlive(32, 18);
            setCellAlive(34, 18);
            setCellAlive(4, 19);
            setCellAlive(5, 19);
            setCellAlive(11, 19);
            setCellAlive(15, 19);
            setCellAlive(19, 19);
            setCellAlive(20, 19);
            setCellAlive(24, 19);
            setCellAlive(25, 19);
            setCellAlive(26, 19);
            setCellAlive(27, 19);
            setCellAlive(28, 19);
            setCellAlive(29, 19);
            setCellAlive(30, 19);
            setCellAlive(31, 19);
            setCellAlive(32, 19);
            setCellAlive(34, 19);
            setCellAlive(5, 20);
            setCellAlive(6, 20);
            setCellAlive(12, 20);
            setCellAlive(13, 20);
            setCellAlive(15, 20);
            setCellAlive(20, 20);
            setCellAlive(24, 20);
            setCellAlive(27, 20);
            setCellAlive(30, 20);
            setCellAlive(31, 20);
            setCellAlive(32, 20);
            setCellAlive(34, 20);
            setCellAlive(6, 21);
            setCellAlive(7, 21);
            setCellAlive(10, 21);
            setCellAlive(14, 21);
            setCellAlive(15, 21);
            setCellAlive(16, 21);
            setCellAlive(20, 21);
            setCellAlive(24, 21);
            setCellAlive(27, 21);
            setCellAlive(29, 21);
            setCellAlive(30, 21);
            setCellAlive(31, 21);
            setCellAlive(34, 21);
            setCellAlive(7, 22);
            setCellAlive(8, 22);
            setCellAlive(11, 22);
            setCellAlive(12, 22);
            setCellAlive(16, 22);
            setCellAlive(17, 22);
            setCellAlive(18, 22);
            setCellAlive(19, 22);
            setCellAlive(20, 22);
            setCellAlive(21, 22);
            setCellAlive(22, 22);
            setCellAlive(23, 22);
            setCellAlive(24, 22);
            setCellAlive(25, 22);
            setCellAlive(26, 22);
            setCellAlive(27, 22);
            setCellAlive(28, 22);
            setCellAlive(29, 22);
            setCellAlive(30, 22);
            setCellAlive(34, 22);
            setCellAlive(9, 23);
            setCellAlive(10, 23);
            setCellAlive(13, 23);
            setCellAlive(14, 23);
            setCellAlive(35, 23);
            setCellAlive(11, 24);
            setCellAlive(12, 24);
            setCellAlive(15, 24);
            setCellAlive(16, 24);
            setCellAlive(17, 24);
            setCellAlive(23, 24);
            setCellAlive(24, 24);
            setCellAlive(25, 24);
            setCellAlive(26, 24);
            setCellAlive(27, 24);
            setCellAlive(28, 24);
            setCellAlive(35, 24);
            setCellAlive(13, 25);
            setCellAlive(14, 25);
            setCellAlive(18, 25);
            setCellAlive(19, 25);
            setCellAlive(20, 25);
            setCellAlive(33, 25);
            setCellAlive(35, 25);
            setCellAlive(15, 26);
            setCellAlive(16, 26);
            setCellAlive(21, 26);
            setCellAlive(22, 26);
            setCellAlive(23, 26);
            setCellAlive(24, 26);
            setCellAlive(25, 26);
            setCellAlive(30, 26);
            setCellAlive(31, 26);
            setCellAlive(32, 26);
            setCellAlive(34, 26);
            setCellAlive(17, 27);
            setCellAlive(18, 27);
            setCellAlive(19, 27);
            setCellAlive(20, 27);
            setCellAlive(26, 27);
            setCellAlive(27, 27);
            setCellAlive(28, 27);
            setCellAlive(29, 27);
            setCellAlive(34, 27);
            setCellAlive(20, 28);
            setCellAlive(21, 28);
            setCellAlive(22, 28);
            setCellAlive(23, 28);
            setCellAlive(24, 28);
            setCellAlive(25, 28);
            setCellAlive(31, 28);
            setCellAlive(32, 28);
            setCellAlive(33, 28);
            setCellAlive(25, 29);
            setCellAlive(26, 29);
            setCellAlive(27, 29);
            setCellAlive(28, 29);
            setCellAlive(29, 29);
            setCellAlive(30, 29);
            setCellAlive(31, 29);
            return true;
        } else {
            return false;
        }
    }

    bool Life::USSR() {
        if (width_ >= 30 && height_ >= 30) {
            this->clear();
            setCellAlive(16, 0);
            setCellAlive(17, 0);
            setCellAlive(17, 1);
            setCellAlive(18, 1);
            setCellAlive(19, 1);
            setCellAlive(18, 2);
            setCellAlive(19, 2);
            setCellAlive(20, 2);
            setCellAlive(20, 3);
            setCellAlive(21, 3);
            setCellAlive(22, 3);
            setCellAlive(21, 4);
            setCellAlive(22, 4);
            setCellAlive(23, 4);
            setCellAlive(10, 5);
            setCellAlive(11, 5);
            setCellAlive(12, 5);
            setCellAlive(13, 5);
            setCellAlive(14, 5);
            setCellAlive(15, 5);
            setCellAlive(22, 5);
            setCellAlive(23, 5);
            setCellAlive(24, 5);
            setCellAlive(9, 6);
            setCellAlive(10, 6);
            setCellAlive(11, 6);
            setCellAlive(12, 6);
            setCellAlive(13, 6);
            setCellAlive(14, 6);
            setCellAlive(23, 6);
            setCellAlive(24, 6);
            setCellAlive(25, 6);
            setCellAlive(8, 7);
            setCellAlive(9, 7);
            setCellAlive(10, 7);
            setCellAlive(11, 7);
            setCellAlive(12, 7);
            setCellAlive(13, 7);
            setCellAlive(23, 7);
            setCellAlive(24, 7);
            setCellAlive(25, 7);
            setCellAlive(26, 7);
            setCellAlive(7, 8);
            setCellAlive(8, 8);
            setCellAlive(9, 8);
            setCellAlive(10, 8);
            setCellAlive(11, 8);
            setCellAlive(12, 8);
            setCellAlive(24, 8);
            setCellAlive(25, 8);
            setCellAlive(26, 8);
            setCellAlive(27, 8);
            setCellAlive(6, 9);
            setCellAlive(7, 9);
            setCellAlive(8, 9);
            setCellAlive(9, 9);
            setCellAlive(10, 9);
            setCellAlive(11, 9);
            setCellAlive(25, 9);
            setCellAlive(26, 9);
            setCellAlive(27, 9);
            setCellAlive(5, 10);
            setCellAlive(6, 10);
            setCellAlive(7, 10);
            setCellAlive(8, 10);
            setCellAlive(9, 10);
            setCellAlive(10, 10);
            setCellAlive(11, 10);
            setCellAlive(12, 10);
            setCellAlive(25, 10);
            setCellAlive(26, 10);
            setCellAlive(27, 10);
            setCellAlive(28, 10);
            setCellAlive(4, 11);
            setCellAlive(5, 11);
            setCellAlive(6, 11);
            setCellAlive(7, 11);
            setCellAlive(8, 11);
            setCellAlive(9, 11);
            setCellAlive(10, 11);
            setCellAlive(11, 11);
            setCellAlive(12, 11);
            setCellAlive(13, 11);
            setCellAlive(25, 11);
            setCellAlive(26, 11);
            setCellAlive(27, 11);
            setCellAlive(28, 11);
            setCellAlive(3, 12);
            setCellAlive(4, 12);
            setCellAlive(5, 12);
            setCellAlive(6, 12);
            setCellAlive(7, 12);
            setCellAlive(8, 12);
            setCellAlive(11, 12);
            setCellAlive(12, 12);
            setCellAlive(13, 12);
            setCellAlive(14, 12);
            setCellAlive(26, 12);
            setCellAlive(27, 12);
            setCellAlive(28, 12);
            setCellAlive(29, 12);
            setCellAlive(4, 13);
            setCellAlive(5, 13);
            setCellAlive(6, 13);
            setCellAlive(7, 13);
            setCellAlive(12, 13);
            setCellAlive(13, 13);
            setCellAlive(14, 13);
            setCellAlive(15, 13);
            setCellAlive(26, 13);
            setCellAlive(27, 13);
            setCellAlive(28, 13);
            setCellAlive(29, 13);
            setCellAlive(5, 14);
            setCellAlive(6, 14);
            setCellAlive(13, 14);
            setCellAlive(14, 14);
            setCellAlive(15, 14);
            setCellAlive(16, 14);
            setCellAlive(26, 14);
            setCellAlive(27, 14);
            setCellAlive(28, 14);
            setCellAlive(29, 14);
            setCellAlive(14, 15);
            setCellAlive(15, 15);
            setCellAlive(16, 15);
            setCellAlive(17, 15);
            setCellAlive(26, 15);
            setCellAlive(27, 15);
            setCellAlive(28, 15);
            setCellAlive(29, 15);
            setCellAlive(15, 16);
            setCellAlive(16, 16);
            setCellAlive(17, 16);
            setCellAlive(18, 16);
            setCellAlive(26, 16);
            setCellAlive(27, 16);
            setCellAlive(28, 16);
            setCellAlive(29, 16);
            setCellAlive(16, 17);
            setCellAlive(17, 17);
            setCellAlive(18, 17);
            setCellAlive(19, 17);
            setCellAlive(25, 17);
            setCellAlive(26, 17);
            setCellAlive(27, 17);
            setCellAlive(28, 17);
            setCellAlive(29, 17);
            setCellAlive(17, 18);
            setCellAlive(18, 18);
            setCellAlive(19, 18);
            setCellAlive(20, 18);
            setCellAlive(25, 18);
            setCellAlive(26, 18);
            setCellAlive(27, 18);
            setCellAlive(28, 18);
            setCellAlive(29, 18);
            setCellAlive(17, 19);
            setCellAlive(18, 19);
            setCellAlive(19, 19);
            setCellAlive(20, 19);
            setCellAlive(21, 19);
            setCellAlive(25, 19);
            setCellAlive(26, 19);
            setCellAlive(27, 19);
            setCellAlive(28, 19);
            setCellAlive(29, 19);
            setCellAlive(18, 20);
            setCellAlive(19, 20);
            setCellAlive(20, 20);
            setCellAlive(21, 20);
            setCellAlive(22, 20);
            setCellAlive(24, 20);
            setCellAlive(25, 20);
            setCellAlive(26, 20);
            setCellAlive(27, 20);
            setCellAlive(28, 20);
            setCellAlive(6, 21);
            setCellAlive(7, 21);
            setCellAlive(8, 21);
            setCellAlive(19, 21);
            setCellAlive(20, 21);
            setCellAlive(21, 21);
            setCellAlive(22, 21);
            setCellAlive(23, 21);
            setCellAlive(24, 21);
            setCellAlive(25, 21);
            setCellAlive(26, 21);
            setCellAlive(27, 21);
            setCellAlive(28, 21);
            setCellAlive(3, 22);
            setCellAlive(4, 22);
            setCellAlive(5, 22);
            setCellAlive(6, 22);
            setCellAlive(7, 22);
            setCellAlive(8, 22);
            setCellAlive(9, 22);
            setCellAlive(10, 22);
            setCellAlive(20, 22);
            setCellAlive(21, 22);
            setCellAlive(22, 22);
            setCellAlive(23, 22);
            setCellAlive(24, 22);
            setCellAlive(25, 22);
            setCellAlive(26, 22);
            setCellAlive(27, 22);
            setCellAlive(28, 22);
            setCellAlive(3, 23);
            setCellAlive(4, 23);
            setCellAlive(5, 23);
            setCellAlive(6, 23);
            setCellAlive(7, 23);
            setCellAlive(8, 23);
            setCellAlive(9, 23);
            setCellAlive(10, 23);
            setCellAlive(11, 23);
            setCellAlive(12, 23);
            setCellAlive(13, 23);
            setCellAlive(20, 23);
            setCellAlive(21, 23);
            setCellAlive(22, 23);
            setCellAlive(23, 23);
            setCellAlive(24, 23);
            setCellAlive(25, 23);
            setCellAlive(26, 23);
            setCellAlive(27, 23);
            setCellAlive(3, 24);
            setCellAlive(4, 24);
            setCellAlive(5, 24);
            setCellAlive(6, 24);
            setCellAlive(10, 24);
            setCellAlive(11, 24);
            setCellAlive(12, 24);
            setCellAlive(13, 24);
            setCellAlive(14, 24);
            setCellAlive(15, 24);
            setCellAlive(16, 24);
            setCellAlive(17, 24);
            setCellAlive(18, 24);
            setCellAlive(19, 24);
            setCellAlive(20, 24);
            setCellAlive(21, 24);
            setCellAlive(22, 24);
            setCellAlive(23, 24);
            setCellAlive(24, 24);
            setCellAlive(25, 24);
            setCellAlive(26, 24);
            setCellAlive(2, 25);
            setCellAlive(3, 25);
            setCellAlive(4, 25);
            setCellAlive(5, 25);
            setCellAlive(6, 25);
            setCellAlive(11, 25);
            setCellAlive(12, 25);
            setCellAlive(13, 25);
            setCellAlive(14, 25);
            setCellAlive(15, 25);
            setCellAlive(16, 25);
            setCellAlive(17, 25);
            setCellAlive(18, 25);
            setCellAlive(19, 25);
            setCellAlive(20, 25);
            setCellAlive(21, 25);
            setCellAlive(22, 25);
            setCellAlive(23, 25);
            setCellAlive(24, 25);
            setCellAlive(25, 25);
            setCellAlive(26, 25);
            setCellAlive(27, 25);
            setCellAlive(1, 26);
            setCellAlive(2, 26);
            setCellAlive(3, 26);
            setCellAlive(4, 26);
            setCellAlive(13, 26);
            setCellAlive(14, 26);
            setCellAlive(15, 26);
            setCellAlive(16, 26);
            setCellAlive(17, 26);
            setCellAlive(18, 26);
            setCellAlive(19, 26);
            setCellAlive(20, 26);
            setCellAlive(21, 26);
            setCellAlive(22, 26);
            setCellAlive(23, 26);
            setCellAlive(24, 26);
            setCellAlive(25, 26);
            setCellAlive(26, 26);
            setCellAlive(27, 26);
            setCellAlive(28, 26);
            setCellAlive(0, 27);
            setCellAlive(1, 27);
            setCellAlive(2, 27);
            setCellAlive(3, 27);
            setCellAlive(16, 27);
            setCellAlive(17, 27);
            setCellAlive(18, 27);
            setCellAlive(19, 27);
            setCellAlive(20, 27);
            setCellAlive(21, 27);
            setCellAlive(25, 27);
            setCellAlive(26, 27);
            setCellAlive(27, 27);
            setCellAlive(28, 27);
            setCellAlive(29, 27);
            setCellAlive(0, 28);
            setCellAlive(1, 28);
            setCellAlive(2, 28);
            setCellAlive(26, 28);
            setCellAlive(27, 28);
            setCellAlive(28, 28);
            setCellAlive(29, 28);
            setCellAlive(0, 29);
            setCellAlive(1, 29);
            setCellAlive(27, 29);
            setCellAlive(28, 29);
            return true;
        } else {
            return false;
        }
    }

    bool Life::ZRUSZ() {
        if (width_ >= 18 && height_ >= 14) {
            this->clear();
            setCellAlive(3, 2);
            setCellAlive(4, 2);
            setCellAlive(5, 2);
            setCellAlive(6, 2);
            setCellAlive(7, 2);
            setCellAlive(8, 2);
            setCellAlive(9, 2);
            setCellAlive(10, 2);
            setCellAlive(11, 2);
            setCellAlive(12, 2);
            setCellAlive(13, 2);
            setCellAlive(14, 2);
            setCellAlive(3, 3);
            setCellAlive(4, 3);
            setCellAlive(8, 3);
            setCellAlive(9, 3);
            setCellAlive(10, 3);
            setCellAlive(11, 3);
            setCellAlive(12, 3);
            setCellAlive(13, 3);
            setCellAlive(14, 3);
            setCellAlive(3, 4);
            setCellAlive(7, 4);
            setCellAlive(8, 4);
            setCellAlive(9, 4);
            setCellAlive(10, 4);
            setCellAlive(11, 4);
            setCellAlive(12, 4);
            setCellAlive(13, 4);
            setCellAlive(7, 5);
            setCellAlive(8, 5);
            setCellAlive(9, 5);
            setCellAlive(10, 5);
            setCellAlive(11, 5);
            setCellAlive(12, 5);
            setCellAlive(6, 6);
            setCellAlive(7, 6);
            setCellAlive(8, 6);
            setCellAlive(9, 6);
            setCellAlive(10, 6);
            setCellAlive(11, 6);
            setCellAlive(12, 6);
            setCellAlive(5, 7);
            setCellAlive(6, 7);
            setCellAlive(7, 7);
            setCellAlive(8, 7);
            setCellAlive(9, 7);
            setCellAlive(10, 7);
            setCellAlive(11, 7);
            setCellAlive(4, 8);
            setCellAlive(5, 8);
            setCellAlive(6, 8);
            setCellAlive(7, 8);
            setCellAlive(8, 8);
            setCellAlive(9, 8);
            setCellAlive(10, 8);
            setCellAlive(15, 8);
            setCellAlive(4, 9);
            setCellAlive(5, 9);
            setCellAlive(6, 9);
            setCellAlive(7, 9);
            setCellAlive(8, 9);
            setCellAlive(9, 9);
            setCellAlive(14, 9);
            setCellAlive(15, 9);
            setCellAlive(3, 10);
            setCellAlive(4, 10);
            setCellAlive(5, 10);
            setCellAlive(6, 10);
            setCellAlive(7, 10);
            setCellAlive(8, 10);
            setCellAlive(9, 10);
            setCellAlive(13, 10);
            setCellAlive(14, 10);
            setCellAlive(2, 11);
            setCellAlive(3, 11);
            setCellAlive(4, 11);
            setCellAlive(5, 11);
            setCellAlive(6, 11);
            setCellAlive(7, 11);
            setCellAlive(8, 11);
            setCellAlive(9, 11);
            setCellAlive(10, 11);
            setCellAlive(11, 11);
            setCellAlive(12, 11);
            setCellAlive(13, 11);
            setCellAlive(14, 11);
            return true;
        } else {
            return false;
        }
    }
}

//void *create_life(size_t width, size_t height) {
//    return new life_backend::Life(width, height);
//}
//
//EXPORT void destroy_life(void *life) {
//    if (life != nullptr) {
////        delete life;
//    }
//}