#pragma once

#include <array>
#include <assert.h>
#include <memory>
#include <string>
#include <filesystem>
#include <queue>




#define GRID_DIM 10

struct Coordinate {
    const uint8_t row;
    const uint8_t col;

    operator size_t() const { return row*GRID_DIM + col; }
};

enum class Direction{ RIGHT, DOWN };

enum class Type : char {
    NOTHING = ' ',
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

struct PegBoard : public std::array<Type, GRID_DIM * GRID_DIM>
{
    static PegBoard create()
    {
        PegBoard peg_board;
        peg_board.fill(Type::NOTHING);
        return peg_board;
    }
};

template<typename T, unsigned SIZE=GRID_DIM>
struct GridTemplate final
{
    T data[];

    template <typename U>
    void set(Coordinate coord, U value)
    {
        if (coord.row >= GRID_DIM || coord.col >= GRID_DIM)
        {
            assert(false);
            return;
        }
        data[coord.row * GRID_DIM + coord.col] = static_cast<T>(value);
    }

    template <typename U = T>
    U get(Coordinate coord) const
    {
        if (coord.row >= GRID_DIM || coord.col >= GRID_DIM)
        {
            assert(false);
            throw std::runtime_error("Out of bounds");
        }
        return static_cast<U>(data[coord.row * GRID_DIM + coord.col]);
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

typedef GridTemplate<uint64_t> CountGrid;


std::filesystem::path get_config_path();
void clear_config();

PegBoard load_aiming_grid();
PegBoard load_ship_grid();

void save_aiming_grid(const PegBoard& grid);
void save_ship_grid(const PegBoard& grid);

std::vector<Coordinate> get_misses(const PegBoard& grid);
