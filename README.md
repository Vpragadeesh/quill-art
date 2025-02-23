# Quill Art
## What is quill-art ?
QuillArt is a free and open-source vector art editor built entirely in C++. Designed for performance and precision, it offers a rich suite of drawing tools, advanced path editing, and seamless SVG support, making it an ideal choice for digital artists and designers.
# Installation
### Prerequisites
Make sure you have the following installed on your system:
- [Git](https://git-scm.com/)
- ```gcc``` or ```clang```

### Steps
1. **Clone the repository**:
   ```bash
   git clone https://github.com/cosmic-striker/quill-art.git
   cd quill-art
   ```
2. **Install the necessary dependencies, if you haven't already** (if you haven't already).
3. **Build the application with the following command**:

   ```sh
   cmake --preset=default
   cmake -B build
   ninja -C build
   ```
5. **For running the application, later on, use the following command**:

   ```build\quill-art.exe```
# Usage
1. Create a new project – Start a fresh canvas to begin your vector artwork.
2. Set up your artboard – Define the canvas size and configure your preferred settings.
3. Draw, edit, and refine – Utilize powerful drawing tools, path editing, and precision controls.
4. Apply colors and effects – Fill shapes, adjust gradients, and enhance your design.
5. Manage layers and objects – Organize your artwork efficiently with layering support.
6. Export your artwork – Save your design in SVG or other supported formats.
### SVG Output:
![My SVG Logo](https://github.com/sanvelu82/quill-art/blob/main/output.svg)

The SVG image represents a well-structured vector artwork, showcasing clean lines, smooth curves, and precisely defined shapes. It may include various design elements such as geometric patterns, gradients, or artistic effects. The scalable nature of SVG ensures that the image retains its quality at any resolution, making it ideal for digital and print applications.

# Acknowledgements
https://github.com/KaganCanSit/Cross-Compatible-FileLock-Windows-and-Linux
https://github.com/ocornut/imgui
https://github.com/libsdl-org/SDL
# License
This project is licensed under the MIT License. You are free to use, modify, and distribute this software under the terms of the [MIT LICENSE]((https://github.com/cosmic-striker/quill-art/blob/main/LICENSE))
