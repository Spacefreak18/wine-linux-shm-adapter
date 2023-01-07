// +build none

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <stdbool.h>
#include <termios.h>

#ifdef ACPHYSICS
#include "simapi/include/acdata.h"
#define MEM_FILE_LOCATION "acpmf_physics"
#endif

#ifdef ACGRAPHICS
#include "simapi/include/acdata.h"
#define MEM_FILE_LOCATION "acpmf_graphics"
#endif

#ifdef ACSTATIC
#include "simapi/include/acdata.h"
#define MEM_FILE_LOCATION "acpmf_static"
#endif

#ifdef RF2TELEMETRY
#include "simapi/include/rf2data.h"
#define MEM_FILE_LOCATION "rFactor2SMMP_Telemetry"
#endif

#ifdef RF2SCORING
#include "simapi/include/rf2data.h"
#define MEM_FILE_LOCATION "rFactor2SMMP_Scoring"
#endif

#ifdef CREWCHIEF
#include "simapi/include/crewchiefdata.h"
#define MEM_FILE_LOCATION "acpmf_crewchief"
#endif

#define SOCKET_FD 1
#define SEND_FD 0

int main(int argc, char** argv) {


    int fd;
	fd = shm_open(MEM_FILE_LOCATION, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
		return 10;
	}


	void *addr;
#ifdef ACPHYSICS
    ftruncate(fd, sizeof(struct SPageFilePhysics));
	addr = mmap(NULL, sizeof(struct SPageFilePhysics), PROT_WRITE, MAP_SHARED, fd, 0);
#endif
#ifdef ACGRAPHICS
    ftruncate(fd, sizeof(struct SPageFileGraphics));
	addr = mmap(NULL, sizeof(struct SPageFileGraphics), PROT_WRITE, MAP_SHARED, fd, 0);
#endif
#ifdef ACSTATIC
    ftruncate(fd, sizeof(struct SPageFileStatic));
	addr = mmap(NULL, sizeof(struct SPageFileStatic), PROT_WRITE, MAP_SHARED, fd, 0);
#endif
#ifdef RF2TELEMETRY
    ftruncate(fd, sizeof(struct rF2Telemetry));
	addr = mmap(NULL, sizeof(struct rF2Telemetry), PROT_WRITE, MAP_SHARED, fd, 0);
#endif
#ifdef RF2SCORING
    ftruncate(fd, sizeof(struct rF2VehicleScoring));
	addr = mmap(NULL, sizeof(struct rF2VehicleScoring), PROT_WRITE, MAP_SHARED, fd, 0);
#endif
#ifdef CREWCHIEF
    ftruncate(fd, sizeof(struct SPageFileCrewChief));
	addr = mmap(NULL, sizeof(struct SPageFileCrewChief), PROT_WRITE, MAP_SHARED, fd, 0);
#endif


	if (addr == MAP_FAILED)
	{
		perror("mmap");
		return 30;
	}

    int duplicated_stdin = dup(0);
#ifdef ACPHYSICS
    struct SPageFilePhysics* b = malloc(sizeof(struct SPageFilePhysics));
    ftruncate(duplicated_stdin, sizeof(struct SPageFilePhysics));
    read(duplicated_stdin, addr, sizeof(struct SPageFilePhysics));
#endif    
#ifdef ACGRAPHICS
    struct SPageFileGraphics* b = malloc(sizeof(struct SPageFileGraphics));
    ftruncate(duplicated_stdin, sizeof(struct SPageFileGraphics));
    read(duplicated_stdin, addr, sizeof(struct SPageFileGraphics));
#endif    
#ifdef ACSTATIC
    struct SPageFileStatic* b = malloc(sizeof(struct SPageFileStatic));
    ftruncate(duplicated_stdin, sizeof(struct SPageFileStatic));
    read(duplicated_stdin, addr, sizeof(struct SPageFileStatic));
#endif    
#ifdef RF2TELEMETRY
    struct rF2Telemetry* b = malloc(sizeof(struct rF2Telemetry));
    ftruncate(duplicated_stdin, sizeof(struct rF2Telemetry));
    read(duplicated_stdin, addr, sizeof(struct rF2Telemetry));
#endif
#ifdef RF2SCORING
    struct rF2VehicleScoring* b = malloc(sizeof(struct rF2VehicleScoring));
    ftruncate(duplicated_stdin, sizeof(struct rF2VehicleScoring));
    read(duplicated_stdin, addr, sizeof(struct rF2VehicleScoring));
#endif
#ifdef CREWCHIEF
    struct SPageFileCrewChief* b = malloc(sizeof(struct SPageFileCrewChief));
    ftruncate(duplicated_stdin, sizeof(struct SPageFileCrewChief));
    read(duplicated_stdin, addr, sizeof(struct SPageFileCrewChief));
#endif    


    double update_rate = 480;
    int go = 0;

    while (go == 0)
    {

        duplicated_stdin = dup(0);
        lseek(duplicated_stdin, 0, SEEK_SET);

#ifdef ACPHYSICS
        ftruncate(duplicated_stdin, sizeof(struct SPageFilePhysics));
        read(duplicated_stdin, addr, sizeof(struct SPageFilePhysics));
#endif
#ifdef ACGRAPHICS
        ftruncate(duplicated_stdin, sizeof(struct SPageFileGraphics));
        read(duplicated_stdin, addr, sizeof(struct SPageFileGraphics));
#endif
#ifdef ACSTATIC
        ftruncate(duplicated_stdin, sizeof(struct SPageFileStatic));
        read(duplicated_stdin, addr, sizeof(struct SPageFileStatic));
#endif
#ifdef RF2TELEMETRY
        ftruncate(duplicated_stdin, sizeof(struct rF2Telemetry));
        read(duplicated_stdin, addr, sizeof(struct rF2Telemetry));
#endif
#ifdef RF2SCORING
        ftruncate(duplicated_stdin, sizeof(struct rF2VehicleScoring));
        read(duplicated_stdin, addr, sizeof(struct rF2VehicleScoring));
#endif
#ifdef CREWCHIEF
        ftruncate(duplicated_stdin, sizeof(struct SPageFileCrewChief));
        read(duplicated_stdin, addr, sizeof(struct SPageFileCrewChief));
#endif

		usleep((unsigned long)(1000000.0/update_rate));
	}	
    
    close(duplicated_stdin); 
    fd = shm_unlink(MEM_FILE_LOCATION);
	if (fd == -1)
	{
		perror("unlink");
		return 100;
	}
    
    return 0;
}
