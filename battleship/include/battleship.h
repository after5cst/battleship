#pragma once

#include <assert.h>
#include <memory>
#include <string>
#include <filesystem>
#include <queue>



enum class Type : char {
    MISS = '-',
    HIT = '*',
    CARRIER = 'A',
    BATTLESHIP = 'B',
    CRUISER = 'C',
    DESTROYER = 'D',
    SUB = 'S'
};


struct Grid final
{
    unsigned int row_size;
    char data[];

    void set(unsigned int row, unsigned int col, Type value)
    {
        if (row >= row_size || col >= row_size)
        {
            assert(false);
            return;
        }
        data[row * row_size + col] = static_cast<char>(value);
    }

    // Lifespan management below.  Other than create() nothing of interest.
    struct Deleter
    {
        void operator()(Grid *p) { free(p); }
    };

    typedef std::unique_ptr<Grid, Deleter> ptr_t;
    
    Grid(const Grid&) = delete;
    Grid(Grid&&) = delete;
    Grid& operator=(const Grid&) = delete;
    Grid& operator=(Grid&&) = delete;
    virtual ~Grid() = default;

    static ptr_t create(int row_size)
    {
        // One extra byte allocated for ease of use.
        const auto grid_area = row_size * row_size;
        auto structure_size = offsetof(struct Grid, data) + (grid_area) + 1;
        auto ptr = ptr_t(reinterpret_cast<Grid*>(malloc(structure_size)));
        ptr->row_size = row_size;
        ptr->data[grid_area] = '\0';
        memset(ptr->data, ' ', grid_area);
        return ptr;
    }
};


#define GRID_SIZE 10


std::filesystem::path get_config_path();
void clear_config( uint8_t row_size=GRID_SIZE);

Grid::ptr_t load_aiming_grid();
Grid::ptr_t load_ship_grid();

void save_aiming_grid(Grid* const grid);
void save_ship_grid(Grid* const grid);
