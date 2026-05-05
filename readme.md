# The Simulation Game

A turn-based ecosystem simulation built in C++ with a terminal-based UI using ncurses.

## Overview

The Simulation Game is a world simulator where various organisms — animals and plants — interact on a 2D grid. Each organism has unique stats (strength, initiative) and behaviors. The simulation proceeds in turns, with actions ordered by initiative, and organisms move, fight, reproduce, or spread based on their species rules.

## Features

- **Turn-based gameplay** — actions are resolved by initiative, then age
- **Rich ecosystem** with 6 animal species and 5 plant species:
  - **Animals:** Wolf, Sheep, Fox, Turtle, Antelope, Human
  - **Plants:** Grass, Sow Thistle, Guarana, Belladonna, Sosnowsky's Hogweed
- **Player-controlled Human** with WASD movement and a special ability (magical strength potion)
- **Fight system** — strength-based combat with special rules (e.g., Fox ignores other animals' special defenses)
- **Reproduction** — animals spawn offspring; plants spread to neighboring cells probabilistically
- **Save & Load** — persist and restore simulation state from a file
- **NCurses terminal UI** with ASCII sprites and an event message log

## Requirements

- **CMake** >= 4.0
- **C++20** compatible compiler (GCC, Clang, or MSVC)
- **ncurses** library (development headers)

### macOS

```bash
brew install ncurses
```

### Ubuntu/Debian

```bash
sudo apt install libncurses5-dev libncursesw5-dev
```

## Build & Run

```bash
# Clone the repository
git clone <repository-url>
cd TheSimulationGame

# Configure and build
cmake -B build -S .
cmake --build build

# Run the simulation
./build/C__1
```

## Controls

| Key     | Action                           |
|---------|----------------------------------|
| `W`     | Move up                          |
| `A`     | Move left                        |
| `S`     | Move down                        |
| `D`     | Move right                       |
| `F`     | Activate special ability         |
| `O`     | Save game                        |
| `X`     | Exit                             |

### Starting a Game

On launch, you can choose to:
- Press `l` to **load** a saved game from `SaveData.txt`
- Press any other key to **start a new game**, then enter the map size and initial organism count

## Organism Stats

### Animals

| Organism  | Sprite | Strength | Initiative | Special Ability                    |
|-----------|--------|----------|------------|------------------------------------|
| Human     | `@`    | 3        | 7          | Strength potion (buffs to 5)       |
| Wolf      | `W`    | 9        | 5          | —                                  |
| Sheep     | `S`    | 4        | 4          | —                                  |
| Fox       | `F`    | 3        | 7          | Ignores other animals' defenses    |
| Turtle    | `T`    | 2        | 1          | Blocks attacks with strength < 5   |
| Antelope  | `A`    | 4        | 4          | Jumps 2 cells                      |

### Plants

| Organism      | Sprite | Strength | Special Effect                           |
|---------------|--------|----------|------------------------------------------|
| Grass         | `_`    | 0        | —                                        |
| Sow Thistle   | `;`    | 0        | Spreads up to 3 times per turn           |
| Guarana       | `+`    | 0        | Increases eater's strength by 3          |
| Belladonna    | `\`    | 99       | Kills any animal that eats it            |
| Hogweed       | `&`    | 10       | Kills all animals in adjacent cells      |

> Plants have initiative of 0 and act last each turn.

## Project Structure

```
TheSimulationGame/
├── CMakeLists.txt          # Build configuration
├── main.cpp                # Entry point, ncurses setup
├── WorldManager.{cpp,h}    # Game loop, world state, save/load
├── Organism.{cpp,h}        # Base organism class
├── Animals.{cpp,h}         # Abstract Animal class
├── Plants.{cpp,h}          # Abstract Plant class
├── Utils.{cpp,h}           # Shared types, enums, helpers
├── Animals/                # Animal implementations
│   ├── Wolf.{cpp,h}
│   ├── Sheep.{cpp,h}
│   ├── Fox.{cpp,h}
│   ├── Turtle.{cpp,h}
│   ├── Antelope.{cpp,h}
│   └── Human.{cpp,h}
└── Plants/                 # Plant implementations
    ├── Grass.{cpp,h}
    ├── SowThistle.{cpp,h}
    ├── Guarana.{cpp,h}
    ├── Belladona.{cpp,h}
    └── Hogweed.{cpp,h}
```

## Architecture

The project follows an object-oriented design:

- **`Organism`** — abstract base class with stats (strength, initiative, age, position) and virtual methods for update, render, and special behavior
- **`Animal`** — extends `Organism`; handles movement and same-species reproduction
- **`Plants`** — extends `Organism`; implements probabilistic spreading to adjacent cells
- **`WorldManager`** — manages the game loop, turn resolution, collision handling, and serialization

Each turn:
1. Organisms are sorted by initiative (descending), then age
2. Each organism takes its action (move, fight, reproduce, spread)
3. Collisions are resolved by strength (stronger wins; equal strength favors attacker)
4. The world is rendered and the message log is updated

## License

This project is for educational purposes.

## Author

Kacper Marciniak
