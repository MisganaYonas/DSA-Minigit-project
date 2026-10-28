# MiniGit — A Simplified Version Control System in C++

## 1. Project Overview

MiniGit is a lightweight, command-line version control system developed in C++ as part of a Data Structures and Algorithms (DSA) project. It is inspired by Git and demonstrates the fundamental concepts behind tracking changes, storing file contents, maintaining commit history, managing branches, checking out commits, and merging branch histories.

The main goal of MiniGit is to understand how a version control system organizes and manages project history using file handling, hashing, metadata, and commit relationships.

Unlike Git, which is a production-ready version control system with advanced algorithms and extensive functionality, MiniGit is an educational implementation that demonstrates the basic principles of version control through a simplified design.

## 2. Project Objectives

The project aims to:

- Implement a basic file-based version control system using C++.
- Initialize a repository with a dedicated storage directory.
- Track files by storing their contents and associated hashes.
- Record commits with messages, timestamps, and parent commit references.
- Display commit history.
- Create branches and navigate between branches and commits.
- Demonstrate basic merge operations between branches.
- Apply file handling, hashing, and commit-history concepts to a practical software project.

## 3. Features

### Repository Initialization

The initialization feature creates the internal `.minigit/` directory and its required subdirectories. It also creates a `HEAD.txt` file to track the current commit or repository state.

### File Staging

MiniGit allows users to add files to a staging area before committing them. The system reads the file contents, calculates a hash, stores the content as a blob, and records the filename and hash in `staging_area.txt`.

### Commit Creation

The commit feature creates a record containing a commit ID, commit message, timestamp, and parent commit reference. The latest commit is recorded in the HEAD file.

### Commit History

The log feature displays recorded commits, including their metadata, and follows parent references to navigate through the available history.

### Branch Management

The branching feature creates a branch represented by a file containing the commit ID to which that branch points.

### Checkout

The checkout feature allows users to select a branch or a specific commit by updating the repository's internal HEAD reference.

### Merge

The merge feature demonstrates how two branch histories can be combined. It includes simplified fast-forward and merge-commit logic. Full file-content merging and conflict resolution are not currently implemented.

> **Note:** These features represent the project's intended functionality. The completeness of each feature depends on the final integrated implementation and successful testing.

## 4. Technologies Used

- **Programming language:** C++
- **File handling:** `ifstream` and `ofstream`
- **Standard library:** `iostream`, `string`, `fstream`, `filesystem`, and other required standard headers
- **Version control for development:** Git and GitHub
- **Development approach:** Modular implementation and integration of features contributed by multiple team members

## 5. Repository Structure

MiniGit uses a dedicated directory to store its internal repository data.

```text
.minigit/
├── objects/
│   └── <hash>.txt
├── commits/
│   └── <commit-id>.txt
├── branches/
│   └── <branch-name>.txt
├── staging_area.txt
└── HEAD.txt
```

The exact directories created depend on the initialization code and the features enabled in the integrated version.

| Component | Purpose |
|---|---|
| `.minigit/` | Root directory for MiniGit's internal data |
| `objects/` | Stores file contents as blob files identified by hashes |
| `commits/` | Stores commit metadata, including messages and parent references |
| `branches/` | Stores branch pointers as text files |
| `staging_area.txt` | Records staged filenames and their associated hashes |
| `HEAD.txt` | Tracks the current commit or repository reference |

## 6. Supported Commands

MiniGit is designed around a simple command-line interface.

| Command | Purpose |
|---|---|
| `init` | Initializes the MiniGit repository |
| `add <filename>` | Stages a file for a future commit |
| `commit <message>` | Creates a commit with a descriptive message |
| `log` | Displays commit history |
| `branch <branch-name>` | Creates a new branch |
| `checkout <branch-name>` | Checks out a branch |
| `checkout <commit-id>` | Checks out a specific commit |
| `merge <branch-name>` | Attempts to merge a target branch into the current branch |

**Important:** Commands should be considered available only after their corresponding functionality has been integrated into the final executable. Checkout currently focuses on updating internal references; restoring files to the working directory is a planned improvement.

## 7. How to Compile and Run

### Prerequisites

You need a C++ compiler that supports C++17 or later because the project uses `std::filesystem`.

Examples include GCC and a compatible MinGW-w64 installation.

### Compilation

After downloading or cloning the repository, open a terminal in the project directory.

If the final implementation has one `main.cpp` file and separate implementation files, compile all required source files together. For example:

```bash
g++ -std=c++17 main.cpp init_add.cpp minigit.cpp.cpp Branching_and_Checkout.cpp merge.cpp -o minigit
```

The filenames in this command are examples based on the repository's current file organization. Adjust them to match the actual files and ensure that only one `main()` function is compiled.

### Running on Windows

```bash
minigit.exe
```

### Running on Linux or macOS

```bash
./minigit
```

Once the program starts, enter a supported command at the MiniGit prompt.

**Before compiling:** Ensure that helper functions are declared and defined consistently across files, the required headers are included, and no duplicate `main()` functions remain.

## 8. Data Structures and Concepts

MiniGit demonstrates several fundamental programming concepts:

- **Strings:** Store filenames, commit IDs, branch names, commit messages, and metadata.
- **File-based records:** Text files represent blobs, commits, branches, staging information, and HEAD.
- **Hashing:** Converts file contents into identifiers used to name stored blob files.
- **Parent references:** Connect commits to earlier commits and represent commit history.
- **Branch pointers:** Represent branches as references to particular commits.
- **Commit graph:** Parent references form a simplified history graph, including two-parent merge commits.
- **File streams:** Read and write repository data using C++ file-handling facilities.

## 9. Design Decisions

MiniGit uses a file-based storage architecture rather than a database to keep the implementation simple and make the repository's internal state easy to inspect.

Each commit is stored separately, while branch pointers and HEAD are represented by text files. This allows the project to demonstrate how version control systems maintain references between commits.

The system uses simplified hashing and commit identifiers to focus on the underlying concepts rather than reproducing Git's complete storage and security mechanisms.

The command-line interface keeps the system lightweight and allows users to interact with repository operations through simple commands.

## 10. Limitations

The current design has several limitations:

- **Simplified hashing:** The hash functions used for file contents or commit identifiers may produce collisions and are not necessarily cryptographically secure.
- **Limited checkout behavior:** Updating HEAD does not automatically restore the corresponding file contents.
- **Incomplete merge functionality:** Branch merging does not yet perform a complete file-by-file merge.
- **No conflict resolution:** Conflicting changes are not detected and resolved as in Git.
- **Limited change detection:** The staging and commit process does not provide a complete comparison between working files and previous versions.
- **Basic error handling:** Invalid commands, missing files, and inconsistent repository states may not be handled comprehensively.
- **Integration requirements:** The program requires a consistent set of shared functions and a single entry point to compile and operate as one application.

## 11. Future Improvements

Potential improvements include:

1. Implementing reliable commit and blob identifiers using a well-established hashing algorithm.
2. Restoring files when checking out branches or commits.
3. Adding file comparison and change detection.
4. Implementing proper common-ancestor traversal for merge operations.
5. Supporting merge conflict detection and resolution.
6. Adding branch listing, deletion, and renaming commands.
7. Improving error handling and input validation.
8. Adding automated unit and integration tests.
9. Organizing the source code into reusable header and implementation files.
10. Improving commit-history visualization and repository status reporting.

## 12. Demo Video

A short demonstration video accompanies this project to showcase MiniGit in action. The video illustrates how users interact with the command-line interface and demonstrates the version control features implemented by the team.

The demonstration covers the following operations, depending on the functionality available in the final integrated version:

- Initializing the MiniGit repository
- Adding and staging files
- Creating commits and viewing commit history
- Creating branches and checking out branches or commits
- Demonstrating the merge functionality

**Watch the Demo:** https://drive.google.com/file/d/1fV3g2q8mSafSFM2ik9fvWTEybWTfkn-1/view?usp=sharing

The video provides a practical overview of the system's workflow and complements the source code and documentation in this repository.

## 13. Team Collaboration

The project was developed collaboratively, with different team members responsible for separate components of the version control system.

The main areas of work were:

- **Repository initialization and file staging**
- **Commit creation and commit history**
- **Branching and checkout**
- **Merge functionality**

Git and GitHub were used to manage development branches and combine the individual contributions into a shared repository.

## 14. Conclusion

MiniGit provides a practical introduction to the fundamental concepts behind version control systems. By implementing repository initialization, file staging, commits, commit history, branching, checkout, and simplified merging, the project demonstrates how files, metadata, hashes, and parent references can be used to manage changes over time.

Although MiniGit does not reproduce all the capabilities of Git, it establishes a foundation for understanding version control architecture and provides opportunities for further development in file restoration, merge algorithms, conflict resolution, and testing.
