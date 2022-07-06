#include <iostream>
#include <lyra/lyra.hpp>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>


struct options {
    int verbosity;
    bool help;
    std::filesystem::path workspace;

};

std::vector<std::string> split(const std::string& data, char delimiter) {
    std::stringstream tmp(data);
    std::vector<std::string> seglist;
    std::string segment;

    while(std::getline(tmp, segment, delimiter))
    {
        seglist.push_back(segment);
    }
    return seglist;
}

int main(int argc, char* argv[]) {
    std::filesystem::path base_path = "../../sample";
    base_path = absolute(base_path).lexically_normal();
    std::string configPath = "common.logging.file.path";
    const auto parts = split(configPath, '.');

    auto current = base_path;
    for (const auto& item : parts) {
        auto tmp = current.append(item);
        if (exists(tmp))
            current = tmp;
        else
            break;
    }
    for (const auto& item : std::filesystem::directory_iterator(current.parent_path())) {
        if (item.path().stem() == current.stem()) {
            current = item.path();
        }
    }

    std::cout << current.string() << '\n';

    std::ifstream input(current.string());
    auto file = nlohmann::json().parse(input);
    std::cout << file.dump(2);


    return EXIT_SUCCESS;
}