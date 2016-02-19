#include "TPMS.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int xdim = 200; // Decide the number of the intervals in one unit on x-dimension
int ydim = 200; // Decide the number of the intervals in one unit on y-dimension
int zdim = 200; // Decide the number of the intervals in one unit on z-dimension

int xpd = 1; // Change the period of x-dimension
int ypd = 1; // Change the period of y-dimension
int zpd = 1; // Change the period of z-dimension

float length = 1;

typedef enum {
	PSURFACE, DSURFACE, GSURFACE, IWPSURFACE
} Surface;

Surface surf = PSURFACE; // Change the type of the surface needed to be generated

int IndexVect(int i, int j, int k) {
	return i + j * xdim + k * xdim * ydim;
}

SurfaceMesh* SurfaceMesh_marchingCube(float* dataset, float isovalue) {
	int tempt_x, tempt_y, tempt_z;
	int i, j, k, ii;
	int v_num, t_num;
	float den1, den2, ratio;
	FLTVECT *vertex;
	INT3VECT *triangle, *mc_edge;
	int cellVerts[12];
	unsigned char cellIndex;
	unsigned char *mc_sign;
	SurfaceMesh *surfmesh;

	vertex = (FLTVECT*)malloc(sizeof(FLTVECT) * xdim * ydim * zdim);
	triangle = (INT3VECT*)malloc(sizeof(INT3VECT) * xdim * ydim * zdim);
	v_num = 0;
	t_num = 0;

	mc_edge = (INT3VECT*)malloc(sizeof(INT3VECT) * xdim * ydim * zdim);
	mc_sign = (unsigned char*)malloc(sizeof(unsigned char)*xdim * ydim * zdim);

	//float max = -100, min = 100;

	for (k = 0; k < zdim; k++)
		for (j = 0; j < ydim; j++)
			for (i = 0; i < xdim; i++) {

				/*
				if (dataset[IndexVect(i, j, k)] > max)
				max = dataset[IndexVect(i, j, k)];
				if (dataset[IndexVect(i, j, k)] < min)
				min = dataset[IndexVect(i, j, k)];
				*/

				if (dataset[IndexVect(i, j, k)] > isovalue - 0.0001 &&
					dataset[IndexVect(i, j, k)] < isovalue + 0.0001)
					dataset[IndexVect(i, j, k)] = isovalue + 0.0001;

				if (dataset[IndexVect(i, j, k)] >= isovalue)
					mc_sign[IndexVect(i, j, k)] = 1;
				else
					mc_sign[IndexVect(i, j, k)] = 255;

				mc_edge[IndexVect(i, j, k)].a = -1;
				mc_edge[IndexVect(i, j, k)].b = -1;
				mc_edge[IndexVect(i, j, k)].c = -1;
			}

	//printf("max: %f && min: %f", max, min);

	for (tempt_z = 0; tempt_z < zdim - 1; tempt_z++)
		for (tempt_y = 0; tempt_y < ydim - 1; tempt_y++)
			for (tempt_x = 0; tempt_x < xdim - 1; tempt_x++) {

				for (ii = 0; ii < 12; ii++)
					cellVerts[ii] = -1;

				cellIndex = 0;
				if (mc_sign[IndexVect(tempt_x, tempt_y, tempt_z)] == 255) cellIndex |= 1;
				if (mc_sign[IndexVect(tempt_x, tempt_y + 1, tempt_z)] == 255) cellIndex |= 2;
				if (mc_sign[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z)] == 255) cellIndex |= 4;
				if (mc_sign[IndexVect(tempt_x + 1, tempt_y, tempt_z)] == 255) cellIndex |= 8;
				if (mc_sign[IndexVect(tempt_x, tempt_y, tempt_z + 1)] == 255) cellIndex |= 16;
				if (mc_sign[IndexVect(tempt_x, tempt_y + 1, tempt_z + 1)] == 255) cellIndex |= 32;
				if (mc_sign[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z + 1)] == 255) cellIndex |= 64;
				if (mc_sign[IndexVect(tempt_x + 1, tempt_y, tempt_z + 1)] == 255) cellIndex |= 128;

				if (edgeTable[cellIndex] & 1) {
					if (mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].b == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y, tempt_z)];
						den2 = dataset[IndexVect(tempt_x, tempt_y + 1, tempt_z)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x;
						vertex[v_num].y = (float)tempt_y + ratio;
						vertex[v_num].z = (float)tempt_z;
						cellVerts[0] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].b = v_num;
						v_num++;
					}
					else
						cellVerts[0] = mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].b;
				}

				if (edgeTable[cellIndex] & 2) {
					if (mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z)].a == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y + 1, tempt_z)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + ratio;
						vertex[v_num].y = (float)tempt_y + 1;
						vertex[v_num].z = (float)tempt_z;
						cellVerts[1] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z)].a = v_num;
						v_num++;
					}
					else
						cellVerts[1] = mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z)].a;
				}
				if (edgeTable[cellIndex] & 4) {
					if (mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z)].b == -1) {

						den1 = dataset[IndexVect(tempt_x + 1, tempt_y, tempt_z)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + 1;
						vertex[v_num].y = (float)tempt_y + ratio;
						vertex[v_num].z = (float)tempt_z;
						cellVerts[2] = v_num;
						mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z)].b = v_num;
						v_num++;
					}
					else
						cellVerts[2] = mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z)].b;
				}
				if (edgeTable[cellIndex] & 8) {
					if (mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].a == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y, tempt_z)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y, tempt_z)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + ratio;
						vertex[v_num].y = (float)tempt_y;
						vertex[v_num].z = (float)tempt_z;
						cellVerts[3] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].a = v_num;
						v_num++;
					}
					else
						cellVerts[3] = mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].a;
				}
				if (edgeTable[cellIndex] & 16) {
					if (mc_edge[IndexVect(tempt_x, tempt_y, tempt_z + 1)].b == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y, tempt_z + 1)];
						den2 = dataset[IndexVect(tempt_x, tempt_y + 1, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x;
						vertex[v_num].y = (float)tempt_y + ratio;
						vertex[v_num].z = (float)tempt_z + 1;
						cellVerts[4] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y, tempt_z + 1)].b = v_num;
						v_num++;
					}
					else
						cellVerts[4] = mc_edge[IndexVect(tempt_x, tempt_y, tempt_z + 1)].b;
				}
				if (edgeTable[cellIndex] & 32) {
					if (mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z + 1)].a == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y + 1, tempt_z + 1)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + ratio;
						vertex[v_num].y = (float)tempt_y + 1;
						vertex[v_num].z = (float)tempt_z + 1;
						cellVerts[5] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z + 1)].a = v_num;
						v_num++;
					}
					else
						cellVerts[5] = mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z + 1)].a;
				}
				if (edgeTable[cellIndex] & 64) {
					if (mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z + 1)].b == -1) {

						den1 = dataset[IndexVect(tempt_x + 1, tempt_y, tempt_z + 1)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + 1;
						vertex[v_num].y = (float)tempt_y + ratio;
						vertex[v_num].z = (float)tempt_z + 1;
						cellVerts[6] = v_num;
						mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z + 1)].b = v_num;
						v_num++;
					}
					else
						cellVerts[6] = mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z + 1)].b;
				}
				if (edgeTable[cellIndex] & 128) {
					if (mc_edge[IndexVect(tempt_x, tempt_y, tempt_z + 1)].a == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y, tempt_z + 1)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + ratio;
						vertex[v_num].y = (float)tempt_y;
						vertex[v_num].z = (float)tempt_z + 1;
						cellVerts[7] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y, tempt_z + 1)].a = v_num;
						v_num++;
					}
					else
						cellVerts[7] = mc_edge[IndexVect(tempt_x, tempt_y, tempt_z + 1)].a;
				}
				if (edgeTable[cellIndex] & 256) {
					if (mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].c == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y, tempt_z)];
						den2 = dataset[IndexVect(tempt_x, tempt_y, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x;
						vertex[v_num].y = (float)tempt_y;
						vertex[v_num].z = (float)tempt_z + ratio;
						cellVerts[8] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].c = v_num;
						v_num++;
					}
					else
						cellVerts[8] = mc_edge[IndexVect(tempt_x, tempt_y, tempt_z)].c;
				}
				if (edgeTable[cellIndex] & 512) {
					if (mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z)].c == -1) {

						den1 = dataset[IndexVect(tempt_x, tempt_y + 1, tempt_z)];
						den2 = dataset[IndexVect(tempt_x, tempt_y + 1, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x;
						vertex[v_num].y = (float)tempt_y + 1;
						vertex[v_num].z = (float)tempt_z + ratio;
						cellVerts[9] = v_num;
						mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z)].c = v_num;
						v_num++;
					}
					else
						cellVerts[9] = mc_edge[IndexVect(tempt_x, tempt_y + 1, tempt_z)].c;
				}
				if (edgeTable[cellIndex] & 1024) {
					if (mc_edge[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z)].c == -1) {

						den1 = dataset[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + 1;
						vertex[v_num].y = (float)tempt_y + 1;
						vertex[v_num].z = (float)tempt_z + ratio;
						cellVerts[10] = v_num;
						mc_edge[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z)].c = v_num;
						v_num++;
					}
					else
						cellVerts[10] = mc_edge[IndexVect(tempt_x + 1, tempt_y + 1, tempt_z)].c;
				}
				if (edgeTable[cellIndex] & 2048) {
					if (mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z)].c == -1) {

						den1 = dataset[IndexVect(tempt_x + 1, tempt_y, tempt_z)];
						den2 = dataset[IndexVect(tempt_x + 1, tempt_y, tempt_z + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)tempt_x + 1;
						vertex[v_num].y = (float)tempt_y;
						vertex[v_num].z = (float)tempt_z + ratio;
						cellVerts[11] = v_num;
						mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z)].c = v_num;
						v_num++;
					}
					else
						cellVerts[11] = mc_edge[IndexVect(tempt_x + 1, tempt_y, tempt_z)].c;
				}

				ii = 0;
				while (triTable[cellIndex][ii] != -1) {
					triangle[t_num].a = cellVerts[triTable[cellIndex][ii++]];
					triangle[t_num].b = cellVerts[triTable[cellIndex][ii++]];
					triangle[t_num].c = cellVerts[triTable[cellIndex][ii++]];
					t_num++;
				}
			}

	// Allocate memory
	surfmesh = (SurfaceMesh *)malloc(sizeof(FLTVECT) * v_num + sizeof(INT3VECT) * t_num + sizeof(int) * 2);

	surfmesh->nv = v_num;
	surfmesh->nf = t_num;
	surfmesh->vertex = vertex;
	surfmesh->face = triangle;

	free(mc_edge);
	free(mc_sign);

	// Return created SurfaceMesh
	return surfmesh;

}

int main() {

	int x, y, z;

	xdim *= xpd;
	ydim *= ypd;
	zdim *= zpd;

	float denx = length / xdim;
	float deny = length / ydim;
	float denz = length / zdim;

	clock_t start = clock(), diff;

	float *array = (float *)malloc(sizeof(float) * xdim * ydim * zdim);

	char* name = (char*)malloc(sizeof(char) * 9);

	for (x = 0; x < zdim; x++)
		for (y = 0; y < ydim; y++)
			for (z = 0; z < xdim; z++) {

				float a = x * denx / length * 2 * PI * xpd;
				float b = y * deny / length * 2 * PI * ypd;
				float c = z * denz / length * 2 * PI * zpd;

				switch (surf) {
				case PSURFACE:
					name = "P_3_0.1.off";
					array[IndexVect(z, y, x)] = cos(a) + cos(b) + cos(c);
					break;
				case DSURFACE:
					name = "D_3_0.1.off";
					array[IndexVect(z, y, x)] = sin(a) * sin(b) * sin(c) + sin(a) * cos(b) * cos(c) + cos(a) * sin(b) * cos(c) + cos(a) * cos(b) * sin(c);
					break;
				case GSURFACE:
					name = "G_1_0.1.off";
					array[IndexVect(z, y, x)] = cos(a) * sin(b) + cos(b) * sin(c) + cos(c) * sin(a);
					//+ cos(a) * sin(c) + cos(b) * sin(a) + cos(c) * sin(b);
					break;
				case IWPSURFACE:
					name = "I-WP_1_0.1.off";
					array[IndexVect(z, y, x)] = 2 * (cos(a) * cos(b) + cos(b) * cos(c) + cos(c) * cos(a)) - cos(2 * a) - cos(2 * b) - cos(2 * c);
					break;
				}
			}

	SurfaceMesh *surfmesh = SurfaceMesh_marchingCube(array, 0.1);

	diff = clock() - start;

	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec / 1000, msec % 1000);

	printf("Number of triangle: %d\n", surfmesh->nf);

	name = "test.off";
	FILE *fp;
	fp = fopen(name, "w+");

	fprintf(fp, "OFF\n");
	fprintf(fp, "%d %d 0\n", surfmesh->nv, surfmesh->nf);

	int n;
	for (n = 0; n < surfmesh->nv; n++)
		fprintf(fp, "%f %f %f\n", surfmesh->vertex[n].x, surfmesh->vertex[n].y, surfmesh->vertex[n].z);

	for (n = 0; n < surfmesh->nf; n++)
		fprintf(fp, "3 %d %d %d\n", surfmesh->face[n].a, surfmesh->face[n].b, surfmesh->face[n].c);

	fclose(fp);

	free(surfmesh->vertex);
	free(surfmesh->face);
	free(surfmesh);

	return 0;
}
