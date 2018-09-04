// Parameters for KITTI dataset

#pragma once

// The number of superpixel
static int superpixelTotal = 1000;

// The number of iterations
static int outerIterationTotal = 10;
static int innerIterationTotal = 10;

// Weight parameters
static double lambda_pos = 500.0;
static double lambda_depth = 2000.0;
static double lambda_bou = 1000.0;
static double lambda_smo = 400.0;

// Inlier threshold
static double lambda_d = 3.0;

// Penalty values
static double lambda_hinge = 5.0;
static double lambda_occ = 15.0;
static double lambda_pen = 30.0;
