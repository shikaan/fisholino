<h1 align="center">Fisholino</h1>

<p align="center">
  <img width="50%" src="https://github.com/shikaan/fisholino/assets/17052868/735aa453-9a50-45c0-923d-57162355d753" alt="screenshot">
</p>

<p align="center">
  Test game for the <a href="https://github.com/shikaan/latebit">latebit</a> game engine.
</p>

## Dependencies

* cmake (>=3.28.1)
* emscripten (>=3.1.51)

> [!IMPORTANT]  
> On MacOS you may see an `dyld[XXX]: Library not loaded: 'libunwind.1.dylib'` error.
> That's because on some systems, that library is called `libunwind.1.0.dylib`.
>
> In such cases, you can either symlink `libunwind.1.0.dylib` to `libunwind.1.dylib`
> or just copy it in the [./lib](`lib`) folder with the `libunwind.1.dylib` name.

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

## Assets

* font: [FFF forward](https://www.1001fonts.com/fff-forward-font.html)
* music: **I am unable to attribute, I had it in a random hard drive. If it's yours or you know who it belongs to, reach out** 
