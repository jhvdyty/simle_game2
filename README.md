simle_game2
A simple 2D OpenGL-based game prototype written in C++. This project features basic character movement, textured rendering with normal mapping, and collision with a ground platform using modern OpenGL (3.3 Core Profile), GLFW, and GLAD.

Features
Basic player movement using keyboard input

Dynamic background color and frame timing

Texture blending (brick wall with normal map)

Ground collision object

Simple input handling (W, S, ESC)

Clean and minimal game loop

Project Structure
graphql
Copy
Edit
simle_game2/
├── OpenGL/
│   ├── main.cpp             # Entry point and game loop
│   ├── shader.h             # Shader loading utility
│   ├── stb_image.h          # Image loading (textures)
│   ├── character.h          # Player entity logic and rendering
│   └── collide.h            # Static ground/platform object
├── texture/
│   ├── brickwall.jpg        # Main texture
│   └── brickwall_normal.jpg # Normal map for lighting effects
├── vertex.glsl              # Vertex shader for player
├── fragment.glsl            # Fragment shader for player
├── vertex_full.glsl         # Vertex shader for ground object
└── fragment_full.glsl       # Fragment shader for ground object
🕹 Controls
W: Increase texture mix value

S: Decrease texture mix value

ESC: Exit the game

🛠 Requirements
Make sure you have the following libraries:

GLFW – window and input

GLAD – OpenGL loader

stb_image – image loading

OpenGL 3.3+

C++17 compatible compiler

How to Build and Run
On Linux/macOS
Clone the repo

bash
Copy
Edit
git clone https://github.com/yourusername/simle_game2.git
cd simle_game2
Install dependencies (if not installed)

bash
Copy
Edit
sudo apt install libglfw3-dev libglm-dev
Compile

bash
Copy
Edit
g++ OpenGL/main.cpp -IOpenGL -lglfw -ldl -lGL -o simle_game2
Run

bash
Copy
Edit
./simle_game2
You may need to adjust include/library paths based on your platform.

Screenshots
Add gameplay screenshots here if available.

License
This project is open-source. Use it for learning or experimentation. Attribution is appreciated but not required.
