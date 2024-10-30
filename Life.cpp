#include "Life.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

// Constructs the grid of size length and width, live cells are choosen from live_cells.
Life::Life(int length, int width, std::vector<std::pair<int, int>> const & live_cells) : length_(length), width_(width) {
    grid_.resize(length_, std::vector<int> (width_, 0));
    for (std::pair<int, int> const & live_cell : live_cells) {
        grid_[live_cell.first][live_cell.second] = 1;
    }
    info_.resize(length_, std::vector<int> (width_, 0));
    generation_ = 1;
    population_ = 0;
    for (int i = 0; i != length_; ++i) {
        for (int j = 0; j != width_; ++j) {
            population_ += grid_[i][j];
        }
    }
}

// Constructs the grid of size length and width, live cells are choosen randomly.
Life::Life(int length, int width) : length_(length), width_(width) {
    grid_.resize(length_, std::vector<int> (width_, 0));
    for (int i = 0; i != length_; ++i) {
        for (int j = 0; j != width_; ++j) {
            grid_[i][j] = rand() % 2;
        }
    }
    info_.resize(length_, std::vector<int> (width_, 0));
    generation_ = 1;
    population_ = 0;
    for (int i = 0; i != length_; ++i) {
        for (int j = 0; j != width_; ++j) {
            population_ += grid_[i][j];
        }
    }
}

// Updates the generation of cells until they remain.
bool Life::update_generation() {
    if (population_ == 0) {
        return false;
    }
    update_info();
    update_grid();
    return true;
}

// Clears the screen, prints the generation of cells and waits for a second.
void Life::print_generation() const {
    system("cls");
    std::cout << "Generation: " << generation_ << '\n';
    std::cout << "Population: " << population_ << '\n';
    for (int i = 0; i != length_; ++i) {
        for (int j = 0; j != width_; ++j) {
            if (grid_[i][j] == 0) {
                std::cout << ' ';
            } else {
                std::cout << '*';
            }
        }
        std::cout << '\n';
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Helps iterate through all neighbors of a cell.
std::vector<std::pair<int, int>> shifts = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}  
};

// Checks whether the coordinates of the cell are valid.
bool check_cell(int x, int y, int length, int width) {
    return x >= 0 and x < length and y >= 0 and y < width;
}

// Updates the data about the neighbors of each cell.
void Life::update_info() {
    for (int i = 0; i != length_; ++i) {
        for (int j = 0; j != width_; ++j) {
            info_[i][j] = 0;
            for (std::pair<int, int> const & shift : shifts) {
                if (check_cell(i + shift.first, j + shift.second, length_, width_)) {
                    info_[i][j] += grid_[i + shift.first][j + shift.second];
                }
            }
        }
    }
}

// Updates the state of each cell based on its neighbors.
void Life::update_grid() {
    ++generation_;
    for (int i = 0; i != length_; ++i) {
        for (int j = 0; j != width_; ++j) {
            if (grid_[i][j] == 0) {
                if (info_[i][j] == 3) {
                    grid_[i][j] = 1;
                    ++population_;
                }
            } else {
                if (info_[i][j] < 2 or info_[i][j] > 3) {
                    grid_[i][j] = 0;
                    --population_;
                }
            }
        }
    }
}