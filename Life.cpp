#include "Life.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

// Constructs the grid of size grid_length and grid_width, live cells are chosen from live_cells.
Life::Life(int grid_length, int grid_width, std::vector<std::pair<int, int>> const & live_cells) : length(grid_length), width(grid_width) {
    grid.resize(length, std::vector<int> (width, 0));
    for (std::pair<int, int> const & live_cell : live_cells) {
        grid[live_cell.first][live_cell.second] = 1;
    }
    info.resize(length, std::vector<int> (width, 0));
    generation = 1;
    population = 0;
    for (int i = 0; i != length; ++i) {
        for (int j = 0; j != width; ++j) {
            population += grid[i][j];
        }
    }
}

// Constructs the grid of size grid_length and grid_width, live cells are chosen randomly.
Life::Life(int grid_length, int grid_width) : length(grid_length), width(grid_width) {
    grid.resize(length, std::vector<int> (width, 0));
    for (int i = 0; i != length; ++i) {
        for (int j = 0; j != width; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
    info.resize(length, std::vector<int> (width, 0));
    generation = 1;
    population = 0;
    for (int i = 0; i != length; ++i) {
        for (int j = 0; j != width; ++j) {
            population += grid[i][j];
        }
    }
}

// Updates the generation of cells until they remain.
bool Life::update_generation() {
    if (population == 0) {
        return false;
    }
    update_info();
    update_grid();
    return true;
}

// Clears the screen, prints the generation of cells and waits for a second.
void Life::print_generation() const {
    system("cls");
    std::cout << "Generation: " << generation << '\n';
    std::cout << "Population: " << population << '\n';
    for (int i = 0; i != length; ++i) {
        for (int j = 0; j != width; ++j) {
            if (grid[i][j] == 0) {
                std::cout << ' ';
            } else {
                std::cout << '*';
            }
        }
        std::cout << '\n';
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Updates the data about the neighbors of each cell.
void Life::update_info() {
    for (int i = 0; i != length; ++i) {
        for (int j = 0; j != width; ++j) {
            info[i][j] = 0;
            for (std::pair<int, int> const & shift : shifts) {
                if (check_cell(i + shift.first, j + shift.second)) {
                    info[i][j] += grid[i + shift.first][j + shift.second];
                }
            }
        }
    }
}

// Checks whether the coordinates of the cell are valid.
bool Life::check_cell(int x, int y) const {
    return x >= 0 and x < length and y >= 0 and y < width;
}

// Updates the state of each cell based on its neighbors.
void Life::update_grid() {
    ++generation;
    for (int i = 0; i != length; ++i) {
        for (int j = 0; j != width; ++j) {
            if (grid[i][j] == 0) {
                if (info[i][j] == 3) {
                    grid[i][j] = 1;
                    ++population;
                }
            } else {
                if (info[i][j] < 2 or info[i][j] > 3) {
                    grid[i][j] = 0;
                    --population;
                }
            }
        }
    }
}
