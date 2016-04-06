#include "TPMS.h"

const SURFACE_TYPE type = PSURFACE; // Change the type of the surface needed to be generated
const float iso_value = 0.1;

int main() {

	clock_t start = clock(), diff;

  float *data = generateDataset(type);

	SURFACEMESH *surfmesh = marchingCube(data, iso_value);

  free(data);

  diff = clock() - start;

	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec / 1000, msec % 1000);

	char *name = (char *)"test.off";
  writeOFF(name, surfmesh);

	free(surfmesh->vertex);
	free(surfmesh->face);
	free(surfmesh);

	return 0;
}
