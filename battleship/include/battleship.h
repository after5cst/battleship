#pragma once

#include <assert.h>
#include <memory>
#include <string>
#include <filesystem>
#include <queue>



struct Coordinate {
    const uint8_t row;
    const uint8_t col;
};

enum class Direction{ RIGHT, DOWN };

enum class Type : char {
    MISS = '-',
    HIT = '*',
    CARRIER = 'A',
    BATTLESHIP = 'B',
    CRUISER = 'C',
    DESTROYER = 'D',
    SUB = 'S'
};


// template <typename T>
// struct Array
// {
//     unsigned int count;
//     T data[];

//     // Lifespan management below.  Other than create() nothing of interest.
//     struct Deleter
//     {
//         void operator()(Array *p) { free(p); }
//     };

//     typedef std::unique_ptr<Array, Deleter> ptr_t;
    
//     Array(const Array&) = delete;
//     Array(Array&&) = delete;
//     Array& operator=(const Array&) = delete;
//     Array& operator=(Array&&) = delete;
//     virtual ~Array() = default;

//     static ptr_t create(int count)
//     {
//         // One extra byte allocated for ease of use.
//         auto structure_size = offsetof(struct Array, data) + count;
//         auto ptr = ptr_t(reinterpret_cast<PegBoard*>(malloc(structure_size)));
//         ptr->count = count;
//         memset(ptr->data, 0, grid_area);
//         return ptr;
//     }
// };


template<typename T>
struct GridTemplate final
{
    unsigned int row_size;
    T data[];

    template <typename U>
    void set(Coordinate coord, U value)
    {
        if (coord.row >= row_size || coord.col >= row_size)
        {
            assert(false);
            return;
        }
        data[coord.row * row_size + coord.col] = static_cast<T>(value);
    }

    template <typename U = T>
    U get(Coordinate coord) const
    {
        if (coord.row >= row_size || coord.col >= row_size)
        {
            assert(false);
            throw std::runtime_error("Out of bounds");
        }
        return static_cast<U>(data[coord.row * row_size + coord.col]);
    }

    // Lifespan management below.  Other than create() nothing of interest.
    struct Deleter
    {
        void operator()(GridTemplate *p) { free(p); }
    };

    typedef std::unique_ptr<GridTemplate, Deleter> ptr_t;
    
    GridTemplate(const GridTemplate&) = delete;
    GridTemplate(GridTemplate&&) = delete;
    GridTemplate& operator=(const GridTemplate&) = delete;
    GridTemplate& operator=(GridTemplate&&) = delete;
    virtual ~GridTemplate() = default;

    static ptr_t create(int row_size)
    {
        // One extra byte allocated for ease of use.
        const auto grid_area = row_size * row_size * sizeof(T);
        auto structure_size = offsetof(struct GridTemplate, data) + (grid_area) + 1;
        auto ptr = ptr_t(reinterpret_cast<GridTemplate*>(malloc(structure_size)));
        memset(reinterpret_cast<uint8_t*>(ptr.get()), 0, structure_size);
        ptr->row_size = row_size;
        return ptr;
    }
};

typedef GridTemplate<Type> PegBoard;
typedef GridTemplate<uint64_t> CountGrid;

#define GRID_SIZE 10


std::filesystem::path get_config_path();
void clear_config( uint8_t row_size=GRID_SIZE);

PegBoard::ptr_t load_aiming_grid();
PegBoard::ptr_t load_ship_grid();

void save_aiming_grid(PegBoard* const grid);
void save_ship_grid(PegBoard* const grid);

std::vector<Coordinate> get_misses(const PegBoard& grid);
