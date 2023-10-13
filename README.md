
# Vehicle Configuration System

The Vehicle Configuration System is a C++ application that assists dealers in recording and managing vehicle configurations. The system gathers details about vehicles, displays the data, and offers options to save this information to a file.

<p align="center">
  <img src="https://github.com/BrendanGlancy/CISS256/assets/61941978/3d13fe7f-2d95-4e04-a7ec-ee42a16c8968" alt="image"/>
</p>

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building and Running](#building-and-running)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Features

- **Interactive Interface**: The system prompts users for information about vehicles.
- **Data Validation**: Ensures that the data entered by the user adheres to predefined standards.
- **File Operations**: Ability to save the vehicle data to an external file.
- **Modularity**: The codebase is structured to allow easy expansion and maintenance.

## Getting Started

### Prerequisites

Ensure you have the following installed:
- A C++ compiler (e.g., GCC, Clang)
- Make (optional for easier building)

### Building and Running

1. Clone this repository:

```bash
git clone https://github.com/BrendanGlancy/CISS256.git
cd CISS256
```

2. Build the application

```bash
make
```

*If you don't have Make installed, compile using your C++ compiler,* e.g., g++ -o app src/*.cpp

3. Run the application:

```bash
./app
```

## Project Structure

*not yet determined*

## Contributing
1. Fork the repository.
2. Create a new branch for your features or bug fixes.
3. Push your changes to the branch.
4. Create a Pull Request.

Always write a clear log message for your commits. One-line messages are fine for small changes, but bigger changes should look like:

```zsh
$ git commit -m "A brief summary of the commit
> 
> A paragraph describing what changed and its impact."
```

## License 

This project is licensed under the MIT License - see the LICENSE file for details.
