#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "TPMS.h"

int edgeTable[256] = {
	0x0, 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
	0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
	0x190, 0x99, 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
	0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
	0x230, 0x339, 0x33, 0x13a, 0x636, 0x73f, 0x435, 0x53c,
	0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
	0x3a0, 0x2a9, 0x1a3, 0xaa, 0x7a6, 0x6af, 0x5a5, 0x4ac,
	0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
	0x460, 0x569, 0x663, 0x76a, 0x66, 0x16f, 0x265, 0x36c,
	0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
	0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff, 0x3f5, 0x2fc,
	0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
	0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55, 0x15c,
	0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
	0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc,
	0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
	0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
	0xcc, 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
	0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
	0x15c, 0x55, 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
	0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
	0x2fc, 0x3f5, 0xff, 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
	0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
	0x36c, 0x265, 0x16f, 0x66, 0x76a, 0x663, 0x569, 0x460,
	0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
	0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa, 0x1a3, 0x2a9, 0x3a0,
	0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
	0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33, 0x339, 0x230,
	0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
	0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99, 0x190,
	0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
	0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0
};


int triTable[256][16] = {
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
	{ 8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1 },
	{ 3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1 },
	{ 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
	{ 4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1 },
	{ 9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1 },
	{ 10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1 },
	{ 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
	{ 5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1 },
	{ 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1 },
	{ 2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
	{ 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1 },
	{ 11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1 },
	{ 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1 },
	{ 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1 },
	{ 11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1 },
	{ 2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1 },
	{ 6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
	{ 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1 },
	{ 6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
	{ 6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1 },
	{ 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1 },
	{ 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1 },
	{ 3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
	{ 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1 },
	{ 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1 },
	{ 8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
	{ 5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1 },
	{ 0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1 },
	{ 6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1 },
	{ 10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
	{ 1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1 },
	{ 0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1 },
	{ 3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
	{ 6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1 },
	{ 9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1 },
	{ 8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1 },
	{ 3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1 },
	{ 10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1 },
	{ 10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
	{ 2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1 },
	{ 7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
	{ 2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1 },
	{ 1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1 },
	{ 11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1 },
	{ 8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1 },
	{ 0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1 },
	{ 7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1 },
	{ 7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1 },
	{ 10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1 },
	{ 0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1 },
	{ 7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1 },
	{ 6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1 },
	{ 4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1 },
	{ 10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1 },
	{ 8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1 },
	{ 1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1 },
	{ 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1 },
	{ 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1 },
	{ 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1 },
	{ 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1 },
	{ 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1 },
	{ 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1 },
	{ 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1 },
	{ 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1 },
	{ 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1 },
	{ 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1 },
	{ 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1 },
	{ 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1 },
	{ 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1 },
	{ 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1 },
	{ 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1 },
	{ 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1 },
	{ 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1 },
	{ 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1 },
	{ 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1 },
	{ 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1 },
	{ 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1 },
	{ 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1 },
	{ 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1 },
	{ 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1 },
	{ 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1 },
	{ 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1 },
	{ 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1 },
	{ 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1 },
	{ 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1 },
	{ 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1 },
	{ 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1 },
	{ 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1 },
	{ 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1 },
	{ 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1 },
	{ 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1 },
	{ 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1 },
	{ 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1 },
	{ 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1 },
	{ 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1 },
	{ 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1 },
	{ 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1 },
	{ 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1 },
	{ 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1 },
	{ 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1 },
	{ 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
	{ 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1 },
	{ 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1 },
	{ 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1 },
	{ 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1 },
	{ 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1 },
	{ 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1 },
	{ 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
	{ 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1 },
	{ 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
};

int xpd, ypd, zpd;

SURFACEMESH* marchingCube(float* dataset, float isovalue) {
	INT3VECT *mc_edge = (INT3VECT*)malloc(sizeof(INT3VECT) * XDIM * xpd * YDIM * ypd * ZDIM * zpd);
	unsigned char *mc_sign = (unsigned char*)malloc(sizeof(unsigned char) * XDIM * xpd * YDIM * ypd * ZDIM * zpd);

	//float max = -100, min = 100;

	int i, j, k;

	for (k = 0; k < ZDIM * zpd; k++)
		for (j = 0; j < YDIM * ypd; j++)
			for (i = 0; i < XDIM * xpd; i++) {

				/*
				if (dataset[INDEXVECT(i, j, k)] > max)
				max = dataset[INDEXVECT(i, j, k)];
				if (dataset[INDEXVECT(i, j, k)] < min)
				min = dataset[INDEXVECT(i, j, k)];
				*/

				if (dataset[INDEXVECT(i, j, k)] > isovalue - 0.0001 && dataset[INDEXVECT(i, j, k)] < isovalue + 0.0001)
					dataset[INDEXVECT(i, j, k)] = isovalue + 0.0001;

				if (dataset[INDEXVECT(i, j, k)] >= isovalue)
					mc_sign[INDEXVECT(i, j, k)] = 1;
				else
					mc_sign[INDEXVECT(i, j, k)] = 255;

				mc_edge[INDEXVECT(i, j, k)].a = -1;
				mc_edge[INDEXVECT(i, j, k)].b = -1;
				mc_edge[INDEXVECT(i, j, k)].c = -1;
			}

	//printf("max: %f && min: %f", max, min);

	float den1, den2, ratio;
	int cellVerts[12], m;
	unsigned char cellIndex;
	FLTVECT *vertex = (FLTVECT*)malloc(sizeof(FLTVECT) * XDIM * xpd * YDIM * ypd * ZDIM * zpd);
	INT3VECT *triangle = (INT3VECT*)malloc(sizeof(INT3VECT) * XDIM * xpd * YDIM * ypd * ZDIM * zpd);
	int v_num = 0;
	int t_num = 0;

	for (k = 0; k < ZDIM * zpd - 1; k++)
		for (j = 0; j < YDIM * ypd - 1; j++)
			for (i = 0; i < XDIM * xpd - 1; i++) {

				for (m = 0; m < 12; m++)
					cellVerts[m] = -1;

				cellIndex = 0;
				if (mc_sign[INDEXVECT(i, j, k)] == 255) cellIndex |= 1;
				if (mc_sign[INDEXVECT(i, j + 1, k)] == 255) cellIndex |= 2;
				if (mc_sign[INDEXVECT(i + 1, j + 1, k)] == 255) cellIndex |= 4;
				if (mc_sign[INDEXVECT(i + 1, j, k)] == 255) cellIndex |= 8;
				if (mc_sign[INDEXVECT(i, j, k + 1)] == 255) cellIndex |= 16;
				if (mc_sign[INDEXVECT(i, j + 1, k + 1)] == 255) cellIndex |= 32;
				if (mc_sign[INDEXVECT(i + 1, j + 1, k + 1)] == 255) cellIndex |= 64;
				if (mc_sign[INDEXVECT(i + 1, j, k + 1)] == 255) cellIndex |= 128;

				if (edgeTable[cellIndex] & 1) {
					if (mc_edge[INDEXVECT(i, j, k)].b == -1) {

						den1 = dataset[INDEXVECT(i, j, k)];
						den2 = dataset[INDEXVECT(i, j + 1, k)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i;
						vertex[v_num].y = (float)j + ratio;
						vertex[v_num].z = (float)k;
						cellVerts[0] = v_num;
						mc_edge[INDEXVECT(i, j, k)].b = v_num;
						v_num++;
					}
					else
						cellVerts[0] = mc_edge[INDEXVECT(i, j, k)].b;
				}

				if (edgeTable[cellIndex] & 2) {
					if (mc_edge[INDEXVECT(i, j + 1, k)].a == -1) {

						den1 = dataset[INDEXVECT(i, j + 1, k)];
						den2 = dataset[INDEXVECT(i + 1, j + 1, k)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + ratio;
						vertex[v_num].y = (float)j + 1;
						vertex[v_num].z = (float)k;
						cellVerts[1] = v_num;
						mc_edge[INDEXVECT(i, j + 1, k)].a = v_num;
						v_num++;
					}
					else
						cellVerts[1] = mc_edge[INDEXVECT(i, j + 1, k)].a;
				}

				if (edgeTable[cellIndex] & 4) {
					if (mc_edge[INDEXVECT(i + 1, j, k)].b == -1) {

						den1 = dataset[INDEXVECT(i + 1, j, k)];
						den2 = dataset[INDEXVECT(i + 1, j + 1, k)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + 1;
						vertex[v_num].y = (float)j + ratio;
						vertex[v_num].z = (float)k;
						cellVerts[2] = v_num;
						mc_edge[INDEXVECT(i + 1, j, k)].b = v_num;
						v_num++;
					}
					else
						cellVerts[2] = mc_edge[INDEXVECT(i + 1, j, k)].b;
				}

				if (edgeTable[cellIndex] & 8) {
					if (mc_edge[INDEXVECT(i, j, k)].a == -1) {

						den1 = dataset[INDEXVECT(i, j, k)];
						den2 = dataset[INDEXVECT(i + 1, j, k)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + ratio;
						vertex[v_num].y = (float)j;
						vertex[v_num].z = (float)k;
						cellVerts[3] = v_num;
						mc_edge[INDEXVECT(i, j, k)].a = v_num;
						v_num++;
					}
					else
						cellVerts[3] = mc_edge[INDEXVECT(i, j, k)].a;
				}

				if (edgeTable[cellIndex] & 16) {
					if (mc_edge[INDEXVECT(i, j, k + 1)].b == -1) {

						den1 = dataset[INDEXVECT(i, j, k + 1)];
						den2 = dataset[INDEXVECT(i, j + 1, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i;
						vertex[v_num].y = (float)j + ratio;
						vertex[v_num].z = (float)k + 1;
						cellVerts[4] = v_num;
						mc_edge[INDEXVECT(i, j, k + 1)].b = v_num;
						v_num++;
					}
					else
						cellVerts[4] = mc_edge[INDEXVECT(i, j, k + 1)].b;
				}

				if (edgeTable[cellIndex] & 32) {
					if (mc_edge[INDEXVECT(i, j + 1, k + 1)].a == -1) {

						den1 = dataset[INDEXVECT(i, j + 1, k + 1)];
						den2 = dataset[INDEXVECT(i + 1, j + 1, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + ratio;
						vertex[v_num].y = (float)j + 1;
						vertex[v_num].z = (float)k + 1;
						cellVerts[5] = v_num;
						mc_edge[INDEXVECT(i, j + 1, k + 1)].a = v_num;
						v_num++;
					}
					else
						cellVerts[5] = mc_edge[INDEXVECT(i, j + 1, k + 1)].a;
				}

				if (edgeTable[cellIndex] & 64) {
					if (mc_edge[INDEXVECT(i + 1, j, k + 1)].b == -1) {

						den1 = dataset[INDEXVECT(i + 1, j, k + 1)];
						den2 = dataset[INDEXVECT(i + 1, j + 1, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + 1;
						vertex[v_num].y = (float)j + ratio;
						vertex[v_num].z = (float)k + 1;
						cellVerts[6] = v_num;
						mc_edge[INDEXVECT(i + 1, j, k + 1)].b = v_num;
						v_num++;
					}
					else
						cellVerts[6] = mc_edge[INDEXVECT(i + 1, j, k + 1)].b;
				}

				if (edgeTable[cellIndex] & 128) {
					if (mc_edge[INDEXVECT(i, j, k + 1)].a == -1) {

						den1 = dataset[INDEXVECT(i, j, k + 1)];
						den2 = dataset[INDEXVECT(i + 1, j, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + ratio;
						vertex[v_num].y = (float)j;
						vertex[v_num].z = (float)k + 1;
						cellVerts[7] = v_num;
						mc_edge[INDEXVECT(i, j, k + 1)].a = v_num;
						v_num++;
					}
					else
						cellVerts[7] = mc_edge[INDEXVECT(i, j, k + 1)].a;
				}

				if (edgeTable[cellIndex] & 256) {
					if (mc_edge[INDEXVECT(i, j, k)].c == -1) {

						den1 = dataset[INDEXVECT(i, j, k)];
						den2 = dataset[INDEXVECT(i, j, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i;
						vertex[v_num].y = (float)j;
						vertex[v_num].z = (float)k + ratio;
						cellVerts[8] = v_num;
						mc_edge[INDEXVECT(i, j, k)].c = v_num;
						v_num++;
					}
					else
						cellVerts[8] = mc_edge[INDEXVECT(i, j, k)].c;
				}

				if (edgeTable[cellIndex] & 512) {
					if (mc_edge[INDEXVECT(i, j + 1, k)].c == -1) {

						den1 = dataset[INDEXVECT(i, j + 1, k)];
						den2 = dataset[INDEXVECT(i, j + 1, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i;
						vertex[v_num].y = (float)j + 1;
						vertex[v_num].z = (float)k + ratio;
						cellVerts[9] = v_num;
						mc_edge[INDEXVECT(i, j + 1, k)].c = v_num;
						v_num++;
					}
					else
						cellVerts[9] = mc_edge[INDEXVECT(i, j + 1, k)].c;
				}

				if (edgeTable[cellIndex] & 1024) {
					if (mc_edge[INDEXVECT(i + 1, j + 1, k)].c == -1) {

						den1 = dataset[INDEXVECT(i + 1, j + 1, k)];
						den2 = dataset[INDEXVECT(i + 1, j + 1, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + 1;
						vertex[v_num].y = (float)j + 1;
						vertex[v_num].z = (float)k + ratio;
						cellVerts[10] = v_num;
						mc_edge[INDEXVECT(i + 1, j + 1, k)].c = v_num;
						v_num++;
					}
					else
						cellVerts[10] = mc_edge[INDEXVECT(i + 1, j + 1, k)].c;
				}

				if (edgeTable[cellIndex] & 2048) {
					if (mc_edge[INDEXVECT(i + 1, j, k)].c == -1) {

						den1 = dataset[INDEXVECT(i + 1, j, k)];
						den2 = dataset[INDEXVECT(i + 1, j, k + 1)];
						if (den1 != den2)
							ratio = (isovalue - den1) / (den2 - den1);
						else
							ratio = 0;

						vertex[v_num].x = (float)i + 1;
						vertex[v_num].y = (float)j;
						vertex[v_num].z = (float)k + ratio;
						cellVerts[11] = v_num;
						mc_edge[INDEXVECT(i + 1, j, k)].c = v_num;
						v_num++;
					}
					else
						cellVerts[11] = mc_edge[INDEXVECT(i + 1, j, k)].c;
				}

				m = 0;
				while (triTable[cellIndex][m] != -1) {
					triangle[t_num].a = cellVerts[triTable[cellIndex][m++]];
					triangle[t_num].b = cellVerts[triTable[cellIndex][m++]];
					triangle[t_num].c = cellVerts[triTable[cellIndex][m++]];
					t_num++;
				}
			}

	// Allocate memory
	SURFACEMESH *surfmesh = (SURFACEMESH *)malloc(sizeof(SURFACEMESH));

	surfmesh->nv = v_num;
	surfmesh->nf = t_num;
	surfmesh->vertex = vertex;
	surfmesh->face = triangle;

	free(mc_edge);
	free(mc_sign);

	return surfmesh;
}

void findPeriodies(float *bounds) {
	float length_x = bounds[3] - bounds[0];
	float length_y = bounds[4] - bounds[1];
	float length_z = bounds[5] - bounds[2];
	float max_length = fmax(length_x, fmax(length_y, length_z));
	float interval = max_length / MAX_PERIOD;
	xpd = ceil(length_x / interval);
	ypd = ceil(length_y / interval);
	zpd = ceil(length_z / interval);
	bounds[3] = bounds[0] + xpd * interval;
	bounds[4] = bounds[1] + ypd * interval;
	bounds[5] = bounds[2] + zpd * interval;
}

void normalizeSurfMesh(SURFACEMESH *surfmesh, float *bounds) {
	float *surf_bounds = (float *)malloc(sizeof(float) * 6);
	findBoundaries(surf_bounds, surfmesh);

	int n;
	float ratio_x, ratio_y, ratio_z;
	for (n = 0; n < surfmesh->nv; n++) {
		ratio_x = (surfmesh->vertex[n].x - surf_bounds[0]) / (surf_bounds[3] - surf_bounds[0]);
		ratio_y = (surfmesh->vertex[n].y - surf_bounds[1]) / (surf_bounds[4] - surf_bounds[1]);
		ratio_z = (surfmesh->vertex[n].z - surf_bounds[2]) / (surf_bounds[5] - surf_bounds[2]);
		surfmesh->vertex[n].x = bounds[0] + ratio_x * (bounds[3] - bounds[0]);
		surfmesh->vertex[n].y = bounds[1] + ratio_y * (bounds[4] - bounds[1]);
		surfmesh->vertex[n].z = bounds[2] + ratio_z * (bounds[5] - bounds[2]);
	}

	free(surf_bounds);
}

float* generateDataset(SURFACE_TYPE type) {
	int i, j, k;
	float *data = (float *)malloc(sizeof(float) * XDIM * xpd * YDIM * ypd * ZDIM * zpd);

	for (k = 0; k < ZDIM * zpd; k++)
		for (j = 0; j < YDIM * ypd; j++)
			for (i = 0; i < XDIM * xpd; i++) {

				float a = 2 * PI / XDIM * i;
				float b = 2 * PI / YDIM * j;
				float c = 2 * PI / ZDIM * k;

				switch (type) {
				case PSURFACE:
					data[INDEXVECT(i, j, k)] = cos(a) + cos(b) + cos(c);
					break;
				case DSURFACE:
					data[INDEXVECT(i, j, k)] = sin(a) * sin(b) * sin(c) + sin(a) * cos(b) * cos(c) + cos(a) * sin(b) * cos(c) + cos(a) * cos(b) * sin(c);
					break;
				case GSURFACE:
					data[INDEXVECT(i, j, k)] = cos(a) * sin(b) + cos(b) * sin(c) + cos(c) * sin(a);
					//+ cos(a) * sin(c) + cos(b) * sin(a) + cos(c) * sin(b);
					break;
				case IWPSURFACE:
					data[INDEXVECT(i, j, k)] = 2 * (cos(a) * cos(b) + cos(b) * cos(c) + cos(c) * cos(a)) - cos(2 * a) - cos(2 * b) - cos(2 * c);
					break;
				}
			}

	return data;
}

void writeOFF(char *name, SURFACEMESH *surfmesh) {
	FILE *fp;
	if((fp = fopen(name, "w+")) == NULL) {
		perror("Open OFF File Failed!");
		exit(1);
	}

	fprintf(fp, "OFF\n");
	fprintf(fp, "%d %d 0\n", surfmesh->nv, surfmesh->nf);

	int n;
	for (n = 0; n < surfmesh->nv; n++)
		fprintf(fp, "%f %f %f\n", surfmesh->vertex[n].x, surfmesh->vertex[n].y, surfmesh->vertex[n].z);

	for (n = 0; n < surfmesh->nf; n++)
		fprintf(fp, "3 %d %d %d\n", surfmesh->face[n].a, surfmesh->face[n].b, surfmesh->face[n].c);

	fclose(fp);
}

SURFACEMESH* readMesh(char *path) {
  int num, n, m;
  int a, b, c, d;
  float x, y, z;
  SURFACEMESH *surfmesh;
  char line[256];
  FILE *fin;


  if ((fin=fopen(path, "r"))==NULL){
    perror("Read Mesh File Failed!\n");
    exit(0);
  }

  /* OFF format */
  while (fgets(line,256,fin) != NULL) {
    if (line[0]=='O' && line[1]=='F' && line[2]=='F')
      break;
  }

  fscanf(fin,"%d %d %d\n",&m,&n,&num);

  surfmesh = (SURFACEMESH *)malloc(sizeof(SURFACEMESH));
  surfmesh->nv = m;
  surfmesh->nf = n;
  surfmesh->vertex = (FLTVECT *)malloc(sizeof(FLTVECT)*surfmesh->nv);
  surfmesh->face = (INT3VECT *)malloc(sizeof(INT3VECT)*surfmesh->nf);

  for (n = 0; n < surfmesh->nv; n++) {
    fscanf(fin,"%f %f %f\n",&x,&y,&z);
    surfmesh->vertex[n].x = x;
    surfmesh->vertex[n].y = y;
    surfmesh->vertex[n].z = z;
  }

  for (n = 0; n < surfmesh->nf; n++) {
    fscanf(fin,"%d %d %d %d\n",&a,&b,&c,&d);
    surfmesh->face[n].a = b;
    surfmesh->face[n].b = c;
    surfmesh->face[n].c = d;
  }

  fclose(fin);

  return surfmesh;
}

// min_x, min_y, min_z, max_x, max_y, max_z
void findBoundaries(float *bounds, SURFACEMESH *surfmesh) {
	int n;
	for(n = 0; n < 6; n++) {
		if(n < 3)
			bounds[n] = FLT_MAX;
		else
			bounds[n] = FLT_MIN;
	}

	FLTVECT *node;
	for (n = 0; n < surfmesh->nv; n++) {
		node = (surfmesh->vertex) + n;
		if(node->x < bounds[0])
			bounds[0] = node->x;
		if(node->y < bounds[1])
			bounds[1] = node->y;
		if(node->z < bounds[2])
			bounds[2] = node->z;
		if(node->x > bounds[3])
			bounds[3] = node->x;
		if(node->y > bounds[4])
			bounds[4] = node->y;
		if(node->z > bounds[5])
			bounds[5] = node->z;
  }
}
