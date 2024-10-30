#pragma once

#include <vector>

struct Life {
public:
    // Constructs the grid of size length and width, live cells are choosen from live_cells.
    Life(int length, int width, std::vector<std::pair<int, int>> const & live_cells);

    // Constructs the grid of size length and width, live cells are choosen randomly.
    Life(int length, int width);

    // Updates the generation of cells until they remain.
    bool update_generation();

    // Clears the screen, prints the generation of cells and waits for a second.
    void print_generation() const;
private:
    // Disables copy constructor for our class.
    Life(Life const & other);

    // Disables assignment operator for our class.
    Life & operator = (Life const & other);

    // Updates the data about the neighbors of each cell.
    void update_info();

    // Updates the state of each cell based on its neighbors.
    void update_grid();

    int length_;
    int width_;
    std::vector<std::vector<int>> grid_;
    std::vector<std::vector<int>> info_;
    int generation_;
    int population_;
};