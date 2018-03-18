# Potts model simulation using Metropolis algorithm.

# The following libraries are required:
	run:
		libglew-dev
		libassimp-dev
		libglm-dev
		libglfw3-dev
	build:
		build-essential

# Graphics drivers
In order to run this program you need graphics drivers that support GLSL 1.3+ (130 and higher)
Also OpenGL Context is set to 3.2 but it can be easily downgraded to version supported by your platform. (The context was set to 3.2 in order to support core profile that allows glsl 1.20 + on MacOS)
If you can not obtain suitable drivers, there is another way that will support most platforms.
Simply add a matrix invert (4x4) function in all shaders and switch shader version to 120.


