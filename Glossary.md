## Graphics APIs
- **OpenGl**: cross-platform
- **Vulkan**: cross-platform low-level
- **Direct3D**: Microsoft Window low-level
- **Metal**: MACOS low-level
- **WebGL**: cross-platform is based on OpenGL ES

### Context For OpenGL
- **wgl**: microsoft window interface to OpenGL
- cgl/**nsgl**: MACOS interface to OpenGL
- **glx**: Unix interface to OpenGL
- **egl**: interface to OpenGL ES/ OpenGV

### Other Implementations
- **mesa3d**: implementation of OpenGL/ OpenGL ES/ Vulkan and others

## debug with visual studio
```
devenv /debugexe sdk\launcher.exe
```