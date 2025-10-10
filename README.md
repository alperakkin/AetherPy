# AetherPy - Minimal C-Python Embedded Game Engine (macOS only)

AetherPy is a minimal game engine example that allows running Python scripts embedded inside C.
Python-side `GameObject` instances are safely represented in C and can be accessed and manipulated from Python scripts.

> **Note:** This project is currently only tested and supported on macOS.

---

## Features

- Python 3.11/3.12 embedding support (recommended via pyenv)
- Simple `GameObject` class with `CreateGameObject` function
- Call `setup()` and `update()` functions from Python scripts
- Safe and segfault-free C-Python interaction

---


## Installation and Running

1. Install and activate the desired Python version via pyenv:

```bash
pyenv install 3.12.11
pyenv local 3.12.11
```

2. Build the project:

```bash
make clean
make
```

3. Run the game:

```bash
./game
```

Expected output:

```
[Python] player: GameObject(name='Player')
```

---

## Example Python Script (`player.py`)

```python
from engine import CreateGameObject

player = None

def setup():
    global player
    player = CreateGameObject("Player")

def update():
    print(f"[Python] player: {player}")
```

---

## Notes

- `PyImport_AppendInittab` **must be called before** `Py_Initialize()`.
- Use `PyType_GenericNew` to safely create Python objects in C.
- To access `player.x`, `y`, `z` from Python scripts, add `tp_members` in `PyGameObjectType`.
- On macOS, the linker flag `-undefined dynamic_lookup` is required.
- Currently, this project is only tested on macOS and may not work on Linux or Windows without modifications.