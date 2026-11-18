# Live Object Similarity Detector in C

#### Video Demo:https://youtu.be/7P4OzM_kS0g

#### Description

This project is a live visual similarity detector written in C. It uses the Structural Similarity Index (SSIM) to compare visual structure between objects shown to a camera. Instead of relying only on pixel-by-pixel differences, SSIM compares image characteristics such as luminance, contrast, and structure

The program is designed to use a live camera feed as its visual input. It analyzes the captured view and uses SSIM to estimate how closely the objects or images being compared resemble one another. It  gave me a way to work with C beyond basic image transformations, including organizing image-processing code across multiple files and thinking about how a similarity score can guide a useful result.

A key design choice was to build on an image-filtering structure and extend it with a similarity-based approach. A conventional filter changes an image’s appearance like the cs50 project we had; this project uses image analysis to compare visual structure. SSIM provides a score that can represent similarity, while the live camera makes the comparison interactive. Results can depend on camera position, lighting, focus, and how consistently objects are presented, so the comparison works best when the camera view is reasonably steady.

#### Files

- **`filter.c`** contains the program’s main flow. It handles the selected operation and coordinates the image-processing work.
- **`helper.c`** contains supporting image-processing or similarity functions used by the main program.
- **`helpers.h`** declares shared functions and definitions used by the C source files.
- **`bmp.h`** contains definitions related to bitmap image data and headers.
- **`Makefile`** provides the build instructions for compiling the project.
- **`tryingout.c`** contains experimental or test code developed while exploring the project. If it is not part of the final build, it is kept separate from the main program.
- **`.vscode/`** contains editor configuration files used during development.

ffmpeg -f avfoundation -list_devices true -i "" to find video devices
ffmpeg -hide_banner -loglevel error -nostats -f avfoundation -framerate 30 -video_size 640x480 -i 0 -pix_fmt bgr24 -f rawvideo - | ./stream_filter | ffplay -hide_banner -nostats -loglevel error -f rawvideo -pixel_format bgr24 -video_size 640x480 -i -
to run
