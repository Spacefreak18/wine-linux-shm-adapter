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
#endif
#ifdef ACGRAPHICS
#include "simapi/acdata.h"
typedef struct SPageFileGraphics SharedMemory;
#endif
#ifdef ACSTATIC
#include "simapi/acdata.h"
typedef struct SPageFileStatic SharedMemory;
#endif
#ifdef RF2TELEMETRY
#include "simapi/rf2data.h"
typedef struct rF2Telemetry SharedMemory;
#endif
#ifdef RF2SCORING
#include "simapi/rf2data.h"
typedef struct rF2VehicleScoring SharedMemory;
#endif
#ifdef CREWCHIEF
#include "simapi/crewchiefdata.h"
typedef struct SPageFileCrewChief SharedMemory;
#endif

int main(int argc, char** argv) {
    char *access_mode;
    DWORD access = 0;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE maph;

    if (argc < 4) {
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

    //maph = OpenFileMapping(access, 1, TEXT(argv[1]));
    maph = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, access, 0, sizeof(SharedMemory), TEXT(argv[1]));
    
    if (maph == NULL) {
        fprintf(stderr, "failed to open mapping %s: %s\n", argv[1], strerror(GetLastError()));
        return 1;
    }
 

    /*
    unsigned char* mapfb;
    mapfb = (unsigned char*)MapViewOfFile(maph, FILE_MAP_READ, 0, 0, sizeof(SharedMemory));
    SharedMemory* b = malloc(sizeof(SharedMemory));
    b = (SharedMemory*)mapfb;

    fprintf(stderr, "buf contains: %d\n", b->mNumVehicles);
    fprintf(stderr, "buf contains: %d\n", b->mVehicles[0].mLapNumber);
    fprintf(stderr, "buf contains: %lf\n", b->mVehicles[0].mLocalVel.x);
    fprintf(stderr, "buf contains: %lf\n", b->mVehicles[0].mLocalVel.y);
    fprintf(stderr, "buf contains: %lf\n", b->mVehicles[0].mLocalVel.z);
    fprintf(stderr, "buf contains: %d\n", b->mVehicles[0].mGear);
    fprintf(stderr, "buf contains: %lf\n", b->mVehicles[0].mEngineRPM);
    FILE *outfile;
     
    outfile = fopen ("/home/racedev/telemetry.dat", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }
 
    fwrite (b, sizeof(SharedMemory), 1, outfile);
     
    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");
 
    fclose (outfile);
    */

    SetStdHandle(STD_INPUT_HANDLE, maph);
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.hStdInput = maph;
    si.dwFlags |= STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    if (!CreateProcess(argv[3], NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "failed to launch second helper process: %s\n", strerror(GetLastError()));
    }

    for (;;)
    {
        _sleep(1);
    }
}
