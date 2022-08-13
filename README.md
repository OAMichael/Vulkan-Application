# My first Vulkan application

### I have managed to implement some features such as camera movement, window management and multiple shaders

## Some requirements
You have to install Vulkan API. Next, glslc is required

## How to build and run

First, you are to build the app by executing the a script:
```console
./compile.sh
```

And then, just run it being in `build` directory:
```console
./MyApp.exe
```

## Control

#### Movement
You can move around using `WASD` keys. If you hold left `Shift` your speed is increased by 3 times in forward and backward and by 1.8 times in right and left directions. On the other hand, if you hold left `Alt` your speed is decreased to 30% in forward and backward and to 18% in right and left directions


#### Other keyboard
- You can enter fullscreen mode whenever you want by tapping `F11` key
- Press `Esc` to close the window
- There is a feature - you can zoom in by pressing left `Ctrl`


#### Camera
You can turn around using a mouse as usual. There is nothing special


#### Other mouse
The window starts with no cursor mode. In such mode you camera movement works as well. You can leave the mode by pressing `LMB` aka **L**eft **M**ouse **B**utton and return back by pressing it again
