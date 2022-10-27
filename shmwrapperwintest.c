// +build none

#include <windows.h>
#include <stdio.h>

#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#ifdef ACPHYSICS
#include "simapi/acdata.h"
typedef struct SPageFilePhysics SharedMemory;
LPCSTR SHARED_MEM_FILE = AC_PHYSICS_FILE;
#endif
#ifdef ACGRAPHICS
#include "simapi/acdata.h"
typedef struct SPageFileGraphics SharedMemory;
LPCSTR SHARED_MEM_FILE = AC_GRAPHICS_FILE;
#endif
#ifdef ACSTATIC
#include "simapi/acdata.h"
typedef struct SPageFileStatic SharedMemory;
LPCSTR SHARED_MEM_FILE = AC_STATIC_FILE;
#endif
#ifdef CREWCHIEF
#include "simapi/crewchiefdata.h"
typedef struct SPageFileCrewChief SharedMemory;
LPCSTR SHARED_MEM_FILE = CREWCHIEF_FILE;
#endif

int main(int argc, char** argv) {
    char *access_mode;
    DWORD access = 0;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE maph;
/*
    if (argc < 3) {
        fprintf(stderr, "not enough arguments\n");
        return 1;
    }
    access_mode = argv[2];
    while (*access_mode) {
        switch(*access_mode) {
            case 'r': access |= FILE_MAP_READ; break;
            case 'w': access |= FILE_MAP_WRITE; break;
        }
        access_mode++;
    }
*/
    //maph = OpenFileMapping(PAGE_READONLY, TRUE, TEXT(argv[1]));
    maph = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READONLY, 0, sizeof(SharedMemory), TEXT(SHARED_MEM_FILE));
    //maph = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, access, 0, sizeof(SharedMemory), TEXT(SHARED_MEM_FILE));
    
    if (maph == NULL) {
        fprintf(stderr, "failed to open mapping %s: %s\n", TEXT(SHARED_MEM_FILE), strerror(GetLastError()));
        //fprintf(stderr, "failed to open mapping %s: %s\n", TEXT(SHARED_MEM_FILE), strerror(GetLastError()));
        return 1;
    }
   
    //fprintf("You got here %i", maph);


    unsigned char* mapfb;
    mapfb = (unsigned char*)MapViewOfFile(maph, FILE_MAP_READ, 0, 0, sizeof(SharedMemory));
    SharedMemory* b = malloc(sizeof(SharedMemory));
    b = (SharedMemory*)mapfb;
    
    //fprintf(stderr, "buf contains: %i\n", b->packetId);
    //fprintf(stderr, "buf contains: %f\n", b->fuel);
    //fprintf(stderr, "buf contains: %i\n", b->gear);
    //fprintf(stderr, "buf contains: %f\n", b->speedKmh);
    //fprintf(stderr, "buf contains: %i\n", b->maxRpm);
    //fprintf(stderr, "buf contains: %i\n", b->numVehicles);
    

}
