# PongGame

![Screenshot 2021-05-30 193221](https://user-images.githubusercontent.com/52585921/120123607-cd0a2900-c17d-11eb-9280-39e54e44f40c.jpg)

The game was created using Immediate Mode in OpenGL for learning purposes. Slight glitch when colliding with some corner due to not implementing a great collision system, but that was beyond the scope of this project. Might update the project in order to use stuff like the Core Profile in order to take advantage of the GPU for calculations.

The project does not use any Shaders, Uniforms, or Textures. All draw calls are done through glBegin() and glEnd(). Therefore might cause a bottleneck because everything is drawn everyframe instead of passing something like an MVP and doing the moving on the GPU side.
