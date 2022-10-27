# Wine->Linux Shared Memory Adapter

Wrapper programs to map shared memory from a wine process into a Linux process.

This is basically forked from [wineshm-go](https://github.com/LeonB/wineshm-go), but I don't know and don't want anything to do with GO, and I had to change some lines to get it to work. Hopefully, the intention of this project is to be more generic and extensible.

## Compilation

### Prerequisits

This project is used by my Monocoque project which is a device manager for Simulators. It depends on [simapi](https://github.com/spacefreak18/simapi) for the headers for the various simulators that are supported. When pulling lastest if the submodule does not download run:
```
git submodule sync --recursive
git submodule update --init --recursive
```
Then to compile wrapper for various shared memory files...
### Assetto Corsa
#### Assetto Corsa Physics
```
make CFLAGS=-DACPHYSICS
```
#### Assetto Corsa Static
```
make CFLAGS=-DACSTATIC
```
Yes, unfortunately you'll have to do a seaparte compile and run those two instances of the wrapper for each memory mapped file.

## Usage Example

```
protontricks --no-runtime --background-wineserver -c "wine /home/racedev/git/wine-linux-shm-adapter/assets/shmwrapper1.exe 'acpmf_physics' r /home/racedev/git/wine-linux-shm-adapter/assets/shmwrapper2.bin" 244210
```

## ToDo
 - This thing leaks more memory than my Grandma, i need to find a way to exit the child process gracefully so I can free memory
 - Support more sims/programs

