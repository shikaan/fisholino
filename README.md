Fisholino
---

Test game for the `latebit` game engine.

## Dependencies

* cmake (>=3.28.1)
* emscripten (>=3.1.51)


## Native build

```sh
# Configure ./build
cmake -B build

# Build and run the game
cmake --builb build -t run
```

## WASM build

```sh
# In case you started with a native build
rm -rf build/

# Configure ./build with WASM features on
emmake cmake -B build -DWASM=ON

# Build the game
emmake cmake --build build

# Launch the game
python -m http.server --directory ./build/public 1234 & open http://localhost:1234
```