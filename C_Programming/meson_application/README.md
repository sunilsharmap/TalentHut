In the current directory run the below commands to generate the binary by resolving the external dependencies.

- `meson build`                                 - create the build files in `build` direcotry.
- `meson compile -C build`                      - compile the files.
- `meson install -C build --destdir=binaries`   - install the binaries into the binaries directory(curr_dir/build/binaries).

application.exe will be created with the all necessary dlls.

Run the application.exe `./application.exe`
