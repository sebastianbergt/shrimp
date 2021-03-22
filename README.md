# shrimp

shrimp is a tiny library allowing for simple arena allocation.
Currently it is not threadsafe!

# Usage
`
#include <arena/arena.h>
#include <array>

struct Packet{
    std::array<std::int32_t, 100> numbers;
}

int main() {
    shrimp::arena::Arena<Packet> my_arena;
    my_arena.initialize(10); // allocates 10 times the space for Packet on heap 

    {
        auto packet = my_arena.create(); // returns a unique_ptr<Packet> with custom deleter.
        if(packet) {    // can return nullptr, which means arena is exhausted.
            packet->numbers[0] = 10;
        } 
    } // packet is going out of scope here and automatically returned to arena.
}
`

# Install Prerequisites

This is used to install catch2 for tests and benchmarks.
`pip3 install conan`

# Build
sh build.sh
