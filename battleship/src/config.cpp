#include "battleship.h"

static std::filesystem::path get_system_data_path();

void clear_config(uint8_t row_size)
{
    auto path = get_config_path();
    std::filesystem::remove_all(path);
    std::filesystem::create_directories(path);

    auto empty_grid = Grid::create(row_size);
    save_aiming_grid(empty_grid.get());
    save_ship_grid(empty_grid.get());
}

std::filesystem::path get_config_path()
{
    auto path = get_system_data_path() / "battleship";
    if (!(std::filesystem::is_directory(path) || 
          std::filesystem::create_directory(path)))
    {
        throw std::runtime_error("Could not find or create config path");
    }
    return path;
}

#ifdef _MSC_VER
// Modified from https://stackoverflow.com/a/62314965/2525388
#include <windows.h>
#include <shlobj_core.h>

static std::filesystem::path get_system_data_path()
{
    std::filesystem::path path;
    PWSTR path_tmp;

    /* Attempt to get user's AppData folder
     *
     * Microsoft Docs:
     * https://docs.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
     * https://docs.microsoft.com/en-us/windows/win32/shell/knownfolderid
     */
    auto get_folder_path_ret = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path_tmp);

    /* Error check */
    if (get_folder_path_ret != S_OK) {
        CoTaskMemFree(path_tmp);
        throw std::runtime_error("Could not find AppData folder");
    }

    /* Convert the Windows path type to a C++ path */
    path = path_tmp;

    /* Free memory :) */
    CoTaskMemFree(path_tmp);

    return path;
}
#elif defined __linux__
    #error "TODO: implement get_system_data_path() on linux"
#else
    #error "TODO: implement get_system_data_path() on unknown OS"
#endif
