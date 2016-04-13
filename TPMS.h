#define PI 3.14159265358979323846

#define XDIM 20 // Decide the number of the intervals in one unit on x-dimension
#define YDIM 20 // Decide the number of the intervals in one unit on y-dimension
#define ZDIM 20 // Decide the number of the intervals in one unit on z-dimension

#define MAX_PERIOD 20
#define MAX_PERIOD 40

#define INDEXVECT(i, j, k) ((i) + (((j) * XDIM) * xpd) + (((((k) * XDIM) * xpd) * YDIM) * ypd))

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
void findBoundaries(float *bounds, SURFACEMESH *surfmesh);
SURFACEMESH* readMesh(char *path);
void normalizeSurfMesh(SURFACEMESH *surfmesh, float *bounds);
void findPeriodies(float *bounds);
void closeHoles(float *dataset);
