#pragma once

#include <vector>

struct Life {
public:
    // Constructs the grid of size grid_length and grid_width, live cells are chosen from live_cells.
    Life(int grid_length, int grid_width, std::vector<std::pair<int, int>> const & live_cells);

    // Constructs the grid of size grid_length and grid_width, live cells are chosen randomly.
    Life(int grid_length, int grid_width);

    // Updates the generation of cells while they remain.
    bool update_generation();

    // Clears the screen, prints the generation of cells and waits for a second.
    void print_generation() const;
private:
    // Disables copy constructor for our class.
    Life(Life const & other);

    // Disables assignment operator for our class.
    Life & operator = (Life const & other);

    // Updates the data about neighbors of each cell.
    void update_info();

    // Checks whether the coordinates of the cell are valid.
    bool check_cell(int x, int y) const;

    // Updates the state of each cell based on its neighbors.
    void update_grid();

    int const length;
    int const width;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> info;
    int generation;
    int population;
    inline static std::vector<std::pair<int, int>> const shifts = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };
};
