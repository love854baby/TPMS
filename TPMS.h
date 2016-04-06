#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

#define xdim 200 // Decide the number of the intervals in one unit on x-dimension
#define ydim 200 // Decide the number of the intervals in one unit on y-dimension
#define zdim 200 // Decide the number of the intervals in one unit on z-dimension

#define xpd 2 // Change the period of x-dimension
#define ypd 2 // Change the period of y-dimension
#define zpd 2 // Change the period of z-dimension

#define Index(i, j, k) ((i) + ((j) * xdim) + (((k) * xdim) * ydim))
#define IndexVect(i, j, k) ((i) + (((j) * xdim) * xpd) + (((((k) * xdim) * xpd) * ydim) * ypd))

typedef enum {
	PSURFACE, DSURFACE, GSURFACE, IWPSURFACE
} SURFACE_TYPE;

/** @brief Other data structure FLTVECT (float) */
typedef struct {
	float x; /**< @brief x-coordinate */
	float y; /**< @brief y-coordinate */
	float z; /**< @brief z-coordinate */
} FLTVECT;

/** @brief Other data structure INT3VECT (int) */
typedef struct {
	int a; /**< @brief first integer */
	int b; /**< @brief second integer */
	int c; /**< @brief third integer */
} INT3VECT;

/** @brief Other data structure SurfaceMesh (for surface meshes) */
typedef struct {
	int nv; /**< @brief number of vertices */
	int nf; /**< @brief number of triangles */
	FLTVECT* vertex; /**< @brief pointer to the vertices */
	INT3VECT* face; /**< @brief pointer to the triangles */
} SURFACEMESH;

float* generateDataset(SURFACE_TYPE type);
void writeOFF(char *name, SURFACEMESH *surfmesh);
SURFACEMESH* marchingCube(float* dataset, float isovalue);
