#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "TPMS.h"

const SURFACE_TYPE type = PSURFACE; // Change the type of the surface needed to be generated
const float iso_value = 0.1;

int main() {

	clock_t start = clock(), diff;

	SURFACEMESH *bone = readMesh("bone.off");
	float *bounds = (float *)malloc(sizeof(float) * 6);
	findBoundaries(bounds, bone);
	findPeriodies(bounds);

	//printf("min_x = %f, min_y = %f, min_z = %f\n", bounds[0], bounds[1], bounds[2]);
	//printf("max_x = %f, max_y = %f, max_z = %f\n", bounds[3], bounds[4], bounds[5]);

	free(bone);

	float *data = generateDataset(type);
	closeHoles(data);
	SURFACEMESH *surfmesh = marchingCube(data, iso_value);

	free(data);

	diff = clock() - start;

	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec / 1000, msec % 1000);

	char *name = (char *)"test.off";
	normalizeSurfMesh(surfmesh, bounds);
	writeOFF(name, surfmesh);

	free(bounds);
	free(surfmesh->vertex);
	free(surfmesh->face);
	free(surfmesh);

	return 0;
}
