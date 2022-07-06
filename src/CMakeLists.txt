add_subdirectory(structure)

add_executable(m2b
    ./main.cpp
)
target_link_libraries(m2b
    PUBLIC lyra
    PUBLIC nlohmann_json::nlohmann_json
)