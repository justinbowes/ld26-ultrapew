//
//  blackbody_srgb.c
//  p1
//
//  Created by Justin Bowes on 2013-01-30.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "science/blackbody_srgb.h"

static float r_0_6700(float k) {
	return 1.0;
}

static float r_6700_10000(float k) {
	return 6380.0 / k;
}

static float r_10000(float k) {
	return 0.313 * k / (k - 5100.0);
}

static float g_0_1100(float k) {
	return 0.000005 * k;
}

static float g_1100_4000(float k) {
	return 0.000204 * k - 0.164;
}

static float g_4000_6700(float k) {
	return -2956.0 / k + 1.39;
}

static float g_6700_10000(float k) {
	return 5030.0 / k + 0.196;
}

static float g_10000(float k) {
	return 0.436 * k / (k - 3820.0) - 0.0006;
}

static float b_0_2086(float k) {
	return 0.0;
}

static float b_2086_4000(float k) {
	return 0.00018 * k - 0.378;
}

static float b_4000_6700(float k) {
	return 0.000245 * k - 0.64;
}

static float b_6700(float k) {
	return 1.0;
}

static float i_0_15000(float k) {
	return (k == 0.f) ? 0.f : 179.3 * pow(k, (-3509.0 / (k + 0.001)));
}

static float i_15000(float k) {
	return 0.00313 * k - 28.04;
}

xvec4 blackbody_rgbi(float k) {
	if (k <= 1100.0) return xvec4_set(r_0_6700(k), g_0_1100(k), b_0_2086(k), i_0_15000(k));
	if (k <= 2086.0) return xvec4_set(r_0_6700(k), g_1100_4000(k), b_0_2086(k), i_0_15000(k));
	if (k <= 4000.0) return xvec4_set(r_0_6700(k), g_1100_4000(k), b_2086_4000(k), i_0_15000(k));
	if (k <= 6700.0) return xvec4_set(r_0_6700(k), g_4000_6700(k), b_4000_6700(k), i_0_15000(k));
	if (k <= 10000.0) return xvec4_set(r_6700_10000(k), g_6700_10000(k), b_6700(k), i_0_15000(k));
	if (k <= 15000.0) return xvec4_set(r_10000(k), g_10000(k), b_6700(k), i_0_15000(k));
	return xvec4_set(r_10000(k), g_10000(k), b_6700(k), i_15000(k));
}