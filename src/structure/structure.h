#pragma once
#include "lyra/lyra.hpp"

struct structure_command {
    bool help;
    structure_command(lyra::cli& cli) {
        cli.add_argument(lyra::command("structure"))
    }
};