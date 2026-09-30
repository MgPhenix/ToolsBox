# ToolsBox

A general-purpose C++ toolbox containing various utilities and systems designed to make development easier across different kinds of projects, with a strong focus on **video game development**.

ToolsBox started as a collection of tools I needed for my own projects and gradually grew into a reusable library containing things such as mathematical utilities, event systems, containers, and other development helpers.

The goal is simple: **if a tool is useful in a project, it can belong in the toolbox.**

---

## Features

ToolsBox currently contains a variety of utilities, including:

* **Matrix** classes and operations
* **Vector** types and mathematical operations
* **Event System**
* **Threading utilities**
* **Smart pointer utilities**
* **Object pools**
* **Timers**
* **Logging utilities**
* Various other helpers and utilities

The toolbox is mainly intended for game development, but there is no requirement to use it for games. The components can be used in any C++ project where they are useful.

---

## Platforms

Pre-built versions are available for:

* Windows x64
* Linux x64
* macOS x64

The releases contain the compiled library, headers, examples, and documentation.

Available builds:

* `ToolsBox-Windows-x64.zip`
* `ToolsBox-Linux-x64.zip`
* `ToolsBox-macOS-x64.zip`

---

## Library Format

ToolsBox is distributed as a static library:

* **Windows:** `.lib`
* **Linux:** `.a`
* **macOS:** `.a`

The library is accompanied by the required `include` directory containing the public headers.

A typical installation therefore looks roughly like this:

```text
ToolsBox/
├── include/
│   └── ...
├── lib/
│   └── ToolsBox.lib / ToolsBox.a
└── ...
```

---

## Documentation

The project comes with generated documentation.

After extracting a release, the documentation can be found at:

```text
ToolsBox-Platform-x64/doc/html/index.html
```

Open `index.html` in a web browser to access the full API documentation.

---

## Examples

ToolsBox also includes examples demonstrating how the different systems can be used.

Examples are located at:

```text
ToolsBox-Platform-x64/examples/example-name/main.cpp
```

Each example is intended to demonstrate a specific part of the toolbox and can be used as a reference when integrating ToolsBox into another project.

---

## Building from Source

If you clone the repository directly, the current build process requires a small extra step.

Go to the `bin` directory and run:

```bat
make.bat
```

This will generate the Visual Studio solution.

After running the script, you can either:

* Create your own project using ToolsBox
* Use the existing `Test` project to experiment with the library

> **Note:** The current build system is temporary. The project is planned to move to **CMake** in the future to provide a cleaner and more portable build process.

---

## Using ToolsBox in a Project

Once ToolsBox has been built, you can integrate it into your own C++ project by:

1. Adding the ToolsBox `include` directory to your include paths.
2. Linking against the appropriate ToolsBox library for your platform.
3. Including the headers you need.

For example:

```cpp
#include <ToolsBox/Vector2.h>
#include <ToolsBox/Matrix.h>
```
Or just
```cpp
#include <ToolsBox.h>
```

The exact headers and available APIs are documented in the generated documentation.

---

## Philosophy

ToolsBox is intentionally not tied to a specific engine or project.

It is a collection of reusable components that can be taken individually or used together.

If you find something useful in the project, use it.

If you want to modify it, modify it.

If you want to integrate it into another project, do it.

There are no complicated rules around how the project is intended to be used.

---

## License

ToolsBox does not currently use a formal license.

You are free to:

* Use the project
* Copy the code
* Modify the code
* Fork the repository
* Integrate it into your own projects
* Use it for personal or commercial projects

Basically, **do whatever you want with it.**

---

## AI Usage

AI was **not used to generate the code** of this project, with the following exceptions:

* The `submit` function in `ThreadPool.h`
* This `README.md`

The rest of the source code was written without using AI to generate the implementation.

---

## Project Structure

The repository is roughly organized as follows:

```text
ToolsBox/
├── src/                 # Source code
├── bin/                 # Build scripts and build-related files
├── config/              # Configuration files
├── Natvis/              # Visual Studio debugger visualizers
├── ToolsBox_Release/    # Release-related files
├── .github/
│   └── workflows/       # GitHub Actions workflows
├── CHANGELOG.md
└── README.md
```

---

## Why ToolsBox?

ToolsBox exists mainly because I kept writing the same kinds of utilities for different projects.

Instead of rebuilding things like vectors, matrices, events, timers, or other utilities every time, they can live in one reusable toolbox and evolve alongside my projects.

It is still a growing project, so the contents and architecture may change over time.

---

## Contributing

There are currently no strict contribution rules.

If you want to improve something, fix a bug, add a utility, or experiment with the project, feel free to do so.

Pull requests and forks are welcome.

---

## Author

**MgPhenix**

GitHub: [github.com/MgPhenix](https://github.com/MgPhenix)
