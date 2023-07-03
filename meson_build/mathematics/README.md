# A meson Project guide

This is an example to demonstrate the meson usage in a project.
This is the guide which shows how to
- building an application with the command line option parsing
- building a library
- linking application to the library
- building and linking the dependency(glib here)
- creating and building the tests

### Commands to build project
All the below commands to be run from the main project library
i.e. mathematics here.
- `meson build` - this will configure the project. This will download the
dependency if to be downloaded. By default the backend used for building
is `ninja`, we can pass other options through `--backend` flag
- `meson compile -C build` - this will compile the dependency and the project
- `meson install -C build --dest binaries` - This will install all the binaries
to the `binaries` directory with bin, lib, share ... etc sub directories.
- `meson test -C build` - this will run all the tests i.e. dependency tests, library tests.

here `build`, `binaries` are the arbitrary directory names.

**Note**: See the meson documentation for more information on the commands.