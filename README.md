<h1 align="center">Fisholino</h1>

<p align="center">
  <img width="50%" src="https://github.com/shikaan/fisholino/assets/17052868/73d9394a-5521-44e0-86d7-3da2591cf822" alt="screenshot">
</p>

<p align="center">
  Test game for the <a href="https://github.com/shikaan/latebit">latebit</a> game engine.
</p>

## Dependencies

* cmake (>=3.28.1)
* emscripten (>=3.1.51)

## Native

```sh
# Configure, build, and run the game
cmake -B build && cmake --builb build -t run
```

## Web

```sh
# In case you started with a native build
rm -rf build/

# Configure and build the game
emmake cmake -B build -DWASM=ON && emmake cmake --build build

# Launch the game
python -m http.server --directory ./build/public 1234 & open http://localhost:1234
```