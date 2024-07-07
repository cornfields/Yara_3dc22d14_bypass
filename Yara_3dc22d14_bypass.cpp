#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <algorithm>

namespace fs = std::filesystem;

void replace_hex(std::vector<uint8_t>& data, const std::vector<uint8_t>& search, const std::vector<uint8_t>& replace, bool& found) {
    auto it = std::search(data.begin(), data.end(), search.begin(), search.end());
    while (it != data.end()) {
        found = true;
        std::copy(replace.begin(), replace.end(), it);
        it = std::search(it + replace.size(), data.end(), search.begin(), search.end());
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::vector<uint8_t> search = { 0x25, 0x73, 0x20, 0x61, 0x73, 0x20, 0x25, 0x73, 0x5c, 0x25, 0x73, 0x3a, 0x20, 0x25, 0x64 };
    std::vector<uint8_t> replace = { 0x25, 0x73, 0x20, 0x2d, 0x73, 0x20, 0x25, 0x73, 0x5c, 0x25, 0x73, 0x3a, 0x20, 0x25, 0x64 };

    std::string path = "."; // Current directory
    std::vector<std::string> modified_files;
    bool hex_found = false;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".bin") {
            std::ifstream file(entry.path(), std::ios::binary);
            std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            bool found_in_file = false;
            replace_hex(data, search, replace, found_in_file);

            if (found_in_file) {
                hex_found = true;
                std::ofstream outfile(entry.path(), std::ios::binary);
                outfile.write(reinterpret_cast<const char*>(data.data()), data.size());
                outfile.close();

                modified_files.push_back(entry.path().string());
            }
        }
    }

    if (hex_found) {
        std::string message = "Modified files:\n";
        for (const auto& filename : modified_files) {
            message += filename + "\n";
        }
        MessageBoxA(NULL, message.c_str(), "Hex Replacement", MB_OK);
    }
    else {
        MessageBoxA(NULL, "Nothing changed", "Hex Replacement", MB_OK);
    }

    return 0;
}
