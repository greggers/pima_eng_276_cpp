# C++ GPT Example for Pima Community College ENG 276

Example code for using C++ GPT in a simple console application. This example demonstrates how to integrate C++ GPT into a project and use it to generate text based on user input.

# Installation Instructions

Download and install the C++ GPT library from the official repository. 
Follow the installation instructions provided in the documentation to set up the 
library in your development environment.

Developed on Windows 12 with Visual Studio 2026. 

Install VS libcurl and JSON librarys for C++.

1. Install vcpkg package manager if you haven't already:
```powershell
git clone https://github.com/microsoft/vcpkg
cd vcpkg
bootstrap-vcpkg.bat
```

2. Integrate vcpkg with Visual Studio:
```powershell
.\vcpkg.exe integrate install
```

3. Install libcurl
```powershell
.\vcpkg.exe install curl:x64-windows
```

4. Install nlohmann/json
```powershell
.\vcpkg.exe install nlohmann-json:x64-windows
```

# Build the Application

# Licenes
MIT License