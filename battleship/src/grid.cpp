#include "battleship.h"
#include <assert.h>
#include <fstream>

static void save(PegBoard* const grid, std::string name)
{
    auto path = get_config_path() / (name + ".grid");
    auto fp = std::ofstream(path);

    const auto row_size = grid->row_size;

    for (uint8_t row = 0; row < row_size; ++row)
    {
        for (uint8_t col = 0; col < row_size; ++col)
        {
            auto ch = grid->get<char>(Coordinate{row, col});
            fp << (ch ? ch : ' '); // convert '\0' to ' '.
        }
        fp << std::endl;
    }
}

inline char *skip_to_eol(char* source)
{
    
    for (auto ptr = source;;++ptr)
    {
        switch(*ptr)
        {
            case '\r':
            case '\n':
            case '\0':
                return ptr;
        }
    }
    assert(false);
    return nullptr;
}

inline char *skip_past_eol(char* source)
{
    
    for (auto ptr = source;;++ptr)
    {
        switch(*ptr)
        {
        case '\r':
        case '\n':
            break;
        default:
            return ptr;
        }
    }
    assert(false);
    return nullptr;
}

static PegBoard::ptr_t load(std::string name)
{
    auto path = get_config_path() / (name + ".grid");
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> source_buffer(size+1);
    if (!file.read(source_buffer.data(), size))
    {
        throw std::runtime_error("Could not load file.");
    }
    source_buffer[size] = '\0';
    
    auto source = &source_buffer[0];
    unsigned int row_size = skip_to_eol(source) - source;

    auto grid = PegBoard::create(row_size);

    
    auto end = grid->data + (row_size * row_size);
    for (auto data = grid->data; data < end; data += row_size)
    {
        memcpy(data, source, row_size);
        source = skip_past_eol(source + row_size);
    }

    return grid;
}

PegBoard::ptr_t load_aiming_grid()
{
    return load("aiming");
}

PegBoard::ptr_t load_ship_grid()
{
    return load("ship");
}

void save_aiming_grid(PegBoard* const grid)
{
    save(grid, "aiming");
}

void save_ship_grid(PegBoard* const grid)
{
    save(grid, "ship");
}
