#ifndef _sf_fft_size_h	
#define _sf_fft_size_h

#define SF_FFTR_SIZE 334

const struct {	
    int size; 
    float cost;
} SF_FFTR[SF_FFTR_SIZE] = {
    {1,0},	
    {2,0},	
    {5,0},
    {6,0},
    {10,0},
    {11,0},
    {15,0},
    {17,0},
    {18,0},
    {19,0},
    {20,0},
    {22,0},
    {24,0},
    {28,0},
    {31,0},
    {34,0},
    {37,0},
    {38,0},
    {47,0},
    {49,0},
    {50,0},
    {54,0},
    {55,0},
    {59,0},
    {63,0},
    {64,0},
    {66,0},
    {87,0},
    {99,0},
    {107,0},
    {192,0.01},
    {215,0.01},
    {216,0.01},
    {249,0.01},
    {250,0.01},
    {270,0.01},
    {499,0.03},
    {500,0.03},
    {511,0.03},
    {512,0.03},
    {639,0.04},
    {640,0.04},
    {767,0.05},
    {768,0.05},
    {800,0.05},
    {863,0.05},
    {899,0.05},
    {900,0.06},
    {960,0.06},
    {972,0.06},
    {1023,0.06},
    {1024,0.07},
    {1079,0.07},
    {1080,0.07},
    {1151,0.08},
    {1152,0.08},
    {1200,0.08},
    {1279,0.08},
    {1280,0.08},
    {1295,0.08},
    {1296,0.08},
    {1319,0.02},
    {1320,0.01},
    {1343,0.05},
    {1344,0.08},
    {1349,0.06},
    {1350,0.07},
    {1439,0.09},
    {1440,0.09},
    {1457,0.1},
    {1458,0.1},
    {1535,0.09},
    {1536,0.1},
    {1599,0.11},
    {1600,0.11},
    {1619,0.11},
    {1620,0.1},
    {1727,0.12},
    {1728,0.11},
    {1799,0.13},
    {1800,0.12},
    {1919,0.12},
    {1920,0.13},
    {1943,0.13},
    {1944,0.13},
    {1999,0.15},
    {2000,0.14},
    {2047,0.13},
    {2048,0.12},
    {2159,0.15},
    {2160,0.15},
    {2199,0.11},
    {2200,0.07},
    {2249,0.17},
    {2250,0.16},
    {2303,0.16},
    {2304,0.15},
    {2399,0.17},
    {2400,0.16},
    {2429,0.17},
    {2430,0.17},
    {2499,0.19},
    {2500,0.19},
    {2559,0.15},
    {2560,0.17},
    {2591,0.17},
    {2592,0.18},
    {2659,0.08},
    {2660,0.07},
    {2661,0.11},
    {2662,0.09},
    {2663,0.1},
    {2664,0.13},
    {2667,0.2},
    {2687,0.18},
    {2688,0.17},
    {2699,0.21},
    {2700,0.2},
    {2879,0.19},
    {2880,0.19},
    {2915,0.2},
    {2916,0.2},
    {2999,0.21},
    {3000,0.2},
    {3071,0.2},
    {3072,0.2},
    {3199,0.22},
    {3200,0.23},
    {3239,0.22},
    {3240,0.22},
    {3455,0.22},
    {3456,0.23},
    {3535,0.17},
    {3536,0.26},
    {3599,0.27},
    {3600,0.26},
    {3749,0.25},
    {3750,0.25},
    {3839,0.26},
    {3840,0.26},
    {3869,0.25},
    {3871,0.19},
    {3872,0.24},
    {3887,0.21},
    {3888,0.24},
    {3999,0.29},
    {4000,0.3},
    {4049,0.31},
    {4050,0.3},
    {4095,0.26},
    {4096,0.28},
    {4199,0.34},
    {4200,0.34},
    {4319,0.3},
    {4320,0.29},
    {4373,0.3},
    {4374,0.31},
    {4499,0.33},
    {4500,0.33},
    {4607,0.3},
    {4608,0.3},
    {4774,0.25},
    {4799,0.34},
    {4800,0.33},
    {4859,0.34},
    {4860,0.34},
    {4999,0.39},
    {5000,0.38},
    {5119,0.35},
    {5120,0.34},
    {5183,0.35},
    {5184,0.34},
    {5375,0.45},
    {5376,0.46},
    {5399,0.39},
    {5400,0.38},
    {5459,0.45},
    {5759,0.39},
    {5760,0.38},
    {5831,0.4},
    {5832,0.4},
    {5999,0.44},
    {6000,0.46},
    {6143,0.4},
    {6144,0.4},
    {6249,0.5},
    {6250,0.5},
    {6399,0.46},
    {6400,0.45},
    {6479,0.46},
    {6480,0.47},
    {6749,0.51},
    {6750,0.51},
    {6911,0.47},
    {6912,0.47},
    {7199,0.52},
    {7200,0.46},
    {7259,0.43},
    {7260,0},
    {7289,0.53},
    {7290,0.51},
    {7499,0.59},
    {7500,0.58},
    {7679,0.45},
    {7680,0.4},
    {7775,0.53},
    {7776,0.54},
    {7849,0.58},
    {7999,0.6},
    {8000,0.6},
    {8007,0.64},
    {8008,0.71},
    {8099,0.57},
    {8100,0.6},
    {8191,0.52},
    {8192,0.54},
    {8279,0},
    {8280,0.2},
    {8639,0.61},
    {8640,0.58},
    {8747,0.66},
    {8748,0.65},
    {8819,0.79},
    {8820,0.76},
    {8999,0.7},
    {9000,0.7},
    {9215,0.65},
    {9216,0.65},
    {9416,0.53},
    {9599,0.7},
    {9600,0.7},
    {9719,0.71},
    {9720,0.73},
    {9843,0.77},
    {9996,0.07},
    {9999,0.79},
    {10000,0.8},
    {10239,0.7},
    {10240,0.7},
    {10367,0.74},
    {10368,0.75},
    {10752,0.96},
    {10799,0.82},
    {10800,0.82},
    {10981,0.79},
    {10982,0.41},
    {11069,0.77},
    {11070,0.84},
    {11249,0.92},
    {11250,0.91},
    {11263,0.79},
    {11264,0.91},
    {11499,0.76},
    {11500,0.97},
    {11519,0.83},
    {11520,0.82},
    {11663,0.83},
    {11664,0.86},
    {11999,0.9},
    {12000,0.88},
    {12149,0.83},
    {12150,0.9},
    {12287,0.89},
    {12288,0.88},
    {12499,0},
    {12500,0.11},
    {12799,0.94},
    {12800,0.91},
    {12959,0.97},
    {12960,0.94},
    {13121,0.94},
    {13122,0.93},
    {13132,0.73},
    {13499,1.01},
    {13500,1.01},
    {13607,1.28},
    {13608,1.26},
    {13823,0.96},
    {13824,0.98},
    {14399,1.18},
    {14400,1.14},
    {14579,1.09},
    {14580,1.07},
    {14999,1.17},
    {15000,1.23},
    {15359,1.11},
    {15360,1.12},
    {15427,0.73},
    {15503,0.73},
    {15504,1.07},
    {15551,1.13},
    {15552,1.14},
    {15659,1.04},
    {15660,1.01},
    {15999,1.22},
    {16000,1.21},
    {16072,1.44},
    {16127,1.56},
    {16199,1.22},
    {16200,1.2},
    {16383,1.16},
    {16384,1.18},
    {16523,1.57},
    {16820,1.46},
    {17167,1.35},
    {17219,1.19},
    {17279,1.29},
    {17280,1.23},
    {17480,1.16},
    {17495,1.32},
    {17496,1.3},
    {17759,0.9},
    {17760,1.04},
    {17999,1.47},
    {18000,1.45},
    {18143,1.51},
    {18144,1.46},
    {18431,1.26},
    {18432,1.27},
    {18620,0.21},
    {18749,1.6},
    {18750,1.57},
    {19199,1.52},
    {19200,1.44},
    {19439,1.41},
    {19440,1.44},
    {19999,1.6},
    {20000,1.54},
    {20249,1.61},
    {20250,1.61},
    {20479,1.52},
    {20480,1.44},
    {20735,1.48},
    {20736,1.51}
};

#endif
