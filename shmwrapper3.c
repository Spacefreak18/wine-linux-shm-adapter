// +build none

#include <windows.h>
#include <stdio.h>

#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


#ifdef ACPHYSICS
#include "simapi/include/acdata.h"
typedef struct SPageFilePhysics SharedMemory;
LPCSTR SHARED_MEM_FILE = AC_PHYSICS_FILE;
#endif
#ifdef ACGRAPHICS
#include "simapi/include/acdata.h"
typedef struct SPageFileGraphics SharedMemory;
LPCSTR SHARED_MEM_FILE = AC_GRAPHICS_FILE;
#endif
#ifdef ACSTATIC
#include "simapi/include/acdata.h"
typedef struct SPageFileStatic SharedMemory;
LPCSTR SHARED_MEM_FILE = AC_STATIC_FILE;
#endif
#ifdef ACCREWCHIEF
#include "simapi/include/acdata.h"
typedef struct SPageFileCrewChief SharedMemory;
LPCSTR SHARED_MEM_FILE = CREWCHIEF_FILE;
#endif
#ifdef RF2TELEMETRY
#include "simapi/include/rf2data.h"
typedef struct rF2Telemetry SharedMemory;
LPCSTR SHARED_MEM_FILE = "$rFactor2SMMP_Telemetry$";
#endif

int main(int argc, char** argv) {
    char *access_mode;
    DWORD access = 0;
    DWORD cnWritten = 0;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE maph;

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

    HANDLE hFile = CreateFile( TEXT(argv[1]), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

    /*
    printf("Opened again %s, %i", TEXT(argv[1]), hFile);
    printf("Opened again %s, %i", TEXT(SHARED_MEM_FILE), hFile);
    */
    maph = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, sizeof(SharedMemory), TEXT(SHARED_MEM_FILE));
    /*
    unsigned char* mapfb;
    mapfb = (unsigned char*)MapViewOfFile(maph, FILE_MAP_READ, 0, 0, sizeof(SharedMemory));
    SharedMemory* b = malloc(sizeof(SharedMemory));
    b = (SharedMemory*)mapfb;
    
    fprintf(stderr, "buf contains: %i\n", b->packetId);
    fprintf(stderr, "buf contains: %f\n", b->fuel);
    fprintf(stderr, "buf contains: %i\n", b->gear);
    fprintf(stderr, "buf contains: %f\n", b->speedKmh);
    */

    if (maph == NULL) {
        fprintf(stderr, "failed to open mapping %s: %s\n", argv[1], strerror(GetLastError()));
        return 1;
    }
    

    for (;;)
    {
        _sleep(1);
    }
}
