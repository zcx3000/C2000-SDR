#include "DSP28x_Project.h"
#include "libs/complex/complex.h"

const short_complex_t sampleTable[] = { { 0,    1024 },
                                        { 391,   946 },
                                        { 724,   724 },
                                        { 946,   391 },
                                        { 1024,    0 },
                                        { 946,  -392 },
                                        { 724,  -725 },
                                        { 391,  -947 },
                                        { 0,   -1024 },
                                        { -392, -947 },
                                        { -725, -725 },
                                        { -947, -392 },
                                        { -1024,  -1 },
                                        { -947,  391 },
                                        { -725,  724 },
                                        { -392,  946 }};

const Uint16 scrambleTable[] = {
                             97,125,253,153,201,27,207,78,
                             197,205,208,148,135,45,5,27,
                             51,238,145,223,113,191,183,
                             121,161,6,25,63,73,193,179
};

const int16 filterTable[] = {

-0x286,-0x1f6,-0x127,-0x54,0x44,0x74,0x30,-0x6E,0x126,0x1A3,
-0x194,-0xBE,0xE7,0x328,0x598,0x7A6,0x8B5,0x849,0x622,0x25C,
-0x290,-0x7D8,-0xC84,-0xF9F,-0x1066,-0xE7D,-0xA00,-0x38E,0x3D5,
0xAED,0x107E,0x138D,0x138D,0x107E,0xAED,0x3D5,-0x38E,-0xA00,
-0xE7D,-0x1066,-0xF9F,-0xC84,-0x7D8,-0x290,0x25C,0x622,0x849,
0x8B5,0x7A6,0x598,0x328,0xE7,-0xBE,-0x194,0x1A3,0x126,-0x6E,
0x30,0x74,0x44,-0x54,-0x127,-0x1f6,-0x286
                             /*
                             0x2,-0x2F,-0x65,-0x9E,-0xDC,-0x11D,-0x161,-0x1A8,-0x1F2,-0x23E,-0x28B,
                             -0x2DA,-0x32,-0x379,-0x3C9,-0x418,-0x466,-0x4B2,-0x4FB,-0x542,-0x586,
                             -0x5C6,-0x601,-0x638,-0x66A,-0x696,-0x6BD,-0x6DE,-0x6F9,-0x70D,-0x71A,
                             0x78DF,0x78DF,-0x71A,-0x70D,-0x6F9,-0x6DE,-0x6BD,-0x696,-0x66A,-0x638,
                             -0x601,-0x5C6,-0x586,-0x542,-0x4FB,-0x4B2,-0x466,-0x418,-0x3C9,
                             -0x379,-0x32,-0x2DA,-0x28B,-0x23E,-0x1F2,-0x1A8,-0x161,-0x11D,-0xDC,
                             -0x9E,-0x65,-0x2F,0x2
                             */};

const int16 atan2Table[] = { 5, 11, 16, 22, 27, 33, 39, 44, 50, 55, 61, 67, 72,
                             78, 83, 89, 95, 100, 106, 111, 117, 123, 128, 134,
                             139, 145, 151, 156, 162, 167, 173, 179, 184, 190,
                             195, 201, 207, 212, 218, 223, 229, 234, 240, 246,
                             251, 257, 262, 268, 274, 279, 285, 290, 296, 301,
                             307, 313, 318, 324, 329, 335, 341, 346, 352, 357,
                             363, 368, 374, 380, 385, 391, 396, 402, 407, 413,
                             419, 424, 430, 435, 441, 446, 452, 458, 463, 469,
                             474, 480, 485, 491, 496, 502, 508, 513, 519, 524,
                             530, 535, 541, 546, 552, 557, 563, 569, 574, 580,
                             585, 591, 596, 602, 607, 613, 618, 624, 629, 635,
                             641, 646, 652, 657, 663, 668, 674, 679, 685, 690,
                             696, 701, 707, 712, 718, 723, 729, 734, 740, 745,
                             751, 756, 762, 767, 773, 778, 784, 789, 795, 800,
                             806, 811, 817, 822, 828, 833, 839, 844, 850, 855,
                             861, 866, 872, 877, 882, 888, 893, 899, 904, 910,
                             915, 921, 926, 932, 937, 943, 948, 953, 959, 964,
                             970, 975, 981, 986, 991, 997, 1002, 1008, 1013,
                             1019, 1024, 1029, 1035, 1040, 1046, 1051, 1057,
                             1062, 1067, 1073, 1078, 1084, 1089, 1094, 1100,
                             1105, 1111, 1116, 1121, 1127, 1132, 1137, 1143,
                             1148, 1154, 1159, 1164, 1170, 1175, 1180, 1186,
                             1191, 1196, 1202, 1207, 1213, 1218, 1223, 1229,
                             1234, 1239, 1245, 1250, 1255, 1261, 1266, 1271,
                             1277, 1282, 1287, 1293, 1298, 1303, 1309, 1314,
                             1319, 1324, 1330, 1335, 1340, 1346, 1351, 1356,
                             1361, 1367, 1372, 1377, 1383, 1388, 1393, 1398,
                             1404, 1409, 1414, 1420, 1425, 1430, 1435, 1441,
                             1446, 1451, 1456, 1462, 1467, 1472, 1477, 1482,
                             1488, 1493, 1498, 1503, 1509, 1514, 1519, 1524,
                             1529, 1535, 1540, 1545, 1550, 1555, 1561, 1566,
                             1571, 1576, 1581, 1587, 1592, 1597, 1602, 1607,
                             1612, 1618, 1623, 1628, 1633, 1638, 1643, 1649,
                             1654, 1659, 1664, 1669, 1674, 1679, 1684, 1690,
                             1695, 1700, 1705, 1710, 1715, 1720, 1725, 1731,
                             1736, 1741, 1746, 1751, 1756, 1761, 1766, 1771,
                             1776, 1781, 1786, 1792, 1797, 1802, 1807, 1812,
                             1817, 1822, 1827, 1832, 1837, 1842, 1847, 1852,
                             1857, 1862, 1867, 1872, 1877, 1882, 1887, 1892,
                             1897, 1902, 1907, 1912, 1917, 1922, 1927, 1932,
                             1937, 1942, 1947, 1952, 1957, 1962, 1967, 1972,
                             1977, 1982, 1987, 1992, 1997, 2002, 2007, 2012,
                             2017, 2022, 2026, 2031, 2036, 2041, 2046, 2051,
                             2056, 2061, 2066, 2071, 2076, 2080, 2085, 2090,
                             2095, 2100, 2105, 2110, 2115, 2120, 2124, 2129,
                             2134, 2139, 2144, 2149, 2153, 2158, 2163, 2168,
                             2173, 2178, 2182, 2187, 2192, 2197, 2202, 2207,
                             2211, 2216, 2221, 2226, 2231, 2235, 2240, 2245,
                             2250, 2254, 2259, 2264, 2269, 2274, 2278, 2283,
                             2288, 2293, 2297, 2302, 2307, 2312, 2316, 2321,
                             2326, 2330, 2335, 2340, 2345, 2349, 2354, 2359,
                             2363, 2368, 2373, 2378, 2382, 2387, 2392, 2396,
                             2401, 2406, 2410, 2415, 2420, 2424, 2429, 2434,
                             2438, 2443, 2447, 2452, 2457, 2461, 2466, 2471,
                             2475, 2480, 2484, 2489, 2494, 2498, 2503, 2507,
                             2512, 2517, 2521, 2526, 2530, 2535, 2540, 2544,
                             2549, 2553, 2558, 2562, 2567, 2571, 2576, 2580,
                             2585, 2590, 2594, 2599, 2603, 2608, 2612, 2617,
                             2621, 2626, 2630, 2635, 2639, 2644, 2648, 2653,
                             2657, 2662, 2666, 2671, 2675, 2679, 2684, 2688,
                             2693, 2697, 2702, 2706, 2711, 2715, 2719, 2724,
                             2728, 2733, 2737, 2742, 2746, 2750, 2755, 2759,
                             2764, 2768, 2772, 2777, 2781, 2786, 2790, 2794,
                             2799, 2803, 2807, 2812, 2816, 2820, 2825, 2829,
                             2833, 2838, 2842, 2846, 2851, 2855, 2859, 2864,
                             2868, 2872, 2877, 2881, 2885, 2890, 2894, 2898,
                             2902, 2907, 2911, 2915, 2919, 2924, 2928, 2932,
                             2937, 2941, 2945, 2949, 2953, 2958, 2962, 2966,
                             2970, 2975, 2979, 2983, 2987, 2991, 2996, 3000,
                             3004, 3008, 3012, 3017, 3021, 3025, 3029, 3033,
                             3038, 3042, 3046, 3050, 3054, 3058, 3062, 3067,
                             3071, 3075, 3079, 3083, 3087, 3091, 3096, 3100,
                             3104, 3108, 3112, 3116, 3120, 3124, 3128, 3132,
                             3137, 3141, 3145, 3149, 3153, 3157, 3161, 3165,
                             3169, 3173, 3177, 3181, 3185, 3189, 3193, 3197,
                             3201, 3205, 3209, 3213, 3217, 3221, 3225, 3229,
                             3233, 3237, 3241, 3245, 3249, 3253, 3257, 3261,
                             3265, 3269, 3273, 3277, 3281, 3285, 3289, 3293,
                             3297, 3301, 3305, 3309, 3313, 3317, 3321, 3324,
                             3328, 3332, 3336, 3340, 3344, 3348, 3352, 3356,
                             3360, 3363, 3367, 3371, 3375, 3379, 3383, 3387,
                             3391, 3394, 3398, 3402, 3406, 3410, 3414, 3417,
                             3421, 3425, 3429, 3433, 3437, 3440, 3444, 3448,
                             3452, 3456, 3459, 3463, 3467, 3471, 3475, 3478,
                             3482, 3486, 3490, 3493, 3497, 3501, 3505, 3508,
                             3512, 3516, 3520, 3523, 3527, 3531, 3535, 3538,
                             3542, 3546, 3549, 3553, 3557, 3561, 3564, 3568,
                             3572, 3575, 3579, 3583, 3586, 3590, 3594, 3597,
                             3601, 3605, 3608, 3612, 3616, 3619, 3623, 3627,
                             3630, 3634, 3638, 3641, 3645, 3648, 3652, 3656,
                             3659, 3663, 3666, 3670, 3674, 3677, 3681, 3684,
                             3688, 3692, 3695, 3699, 3702, 3706, 3709, 3713,
                             3717, 3720, 3724, 3727, 3731, 3734, 3738, 3741,
                             3745, 3748, 3752, 3756, 3759, 3763, 3766, 3770,
                             3773, 3777, 3780, 3784, 3787, 3791, 3794, 3798,
                             3801, 3804, 3808, 3811, 3815, 3818, 3822, 3825,
                             3829, 3832, 3836, 3839, 3842, 3846, 3849, 3853,
                             3856, 3860, 3863, 3866, 3870, 3873, 3877, 3880,
                             3883, 3887, 3890, 3894, 3897, 3900, 3904, 3907,
                             3911, 3914, 3917, 3921, 3924, 3927, 3931, 3934,
                             3937, 3941, 3944, 3947, 3951, 3954, 3957, 3961,
                             3964, 3967, 3971, 3974, 3977, 3981, 3984, 3987,
                             3991, 3994, 3997, 4000, 4004, 4007, 4010, 4014,
                             4017, 4020, 4023, 4027, 4030, 4033, 4036, 4040,
                             4043, 4046, 4049, 4053, 4056, 4059, 4062, 4065,
                             4069, 4072, 4075, 4078, 4082, 4085, 4088, 4091,
                             4094, 4098, 4101, 4104, 4107, 4110, 4113, 4117,
                             4120, 4123, 4126, 4129, 4132, 4136, 4139, 4142,
                             4145, 4148, 4151, 4155, 4158, 4161, 4164, 4167,
                             4170, 4173, 4176, 4180, 4183, 4186, 4189, 4192,
                             4195, 4198, 4201, 4204, 4207, 4210, 4214, 4217,
                             4220, 4223, 4226, 4229, 4232, 4235, 4238, 4241,
                             4244, 4247, 4250, 4253, 4256, 4259, 4262, 4265,
                             4269, 4272, 4275, 4278, 4281, 4284, 4287, 4290,
                             4293, 4296, 4299, 4302, 4305, 4308, 4311, 4314,
                             4317, 4320, 4323, 4325, 4328, 4331, 4334, 4337,
                             4340, 4343, 4346, 4349, 4352, 4355, 4358, 4361,
                             4364, 4367, 4370, 4373, 4376, 4378, 4381, 4384,
                             4387, 4390, 4393, 4396, 4399, 4402, 4405, 4408,
                             4410, 4413, 4416, 4419, 4422, 4425, 4428, 4431,
                             4433, 4436, 4439, 4442, 4445, 4448, 4451, 4453,
                             4456, 4459, 4462, 4465, 4468, 4470, 4473, 4476,
                             4479, 4482, 4485, 4487, 4490, 4493, 4496, 4499,
                             4501 };

#pragma CODE_SECTION(atan2_table_16,"ramfuncs");
int16 atan2_table_16(int16 x, int16 y)
{
    int16 result;
    Uint32 z;
    int16 abs_x = (x < 0) ? (0 - x) : (x);
    int16 abs_y = (y < 0) ? (0 - y) : (y);

    if ((x == 0) && (y == 0))
    {
        return 0;
    }

    if (abs_y < abs_x)
    {
        z = (abs_y) * 65536u / (abs_x);
        z = z >> 6;
        result = atan2Table[z];
    }
    else
    {
        z = (abs_x) * 65536u / (abs_y);
        z = z >> 6;
        result = 9000 - atan2Table[z];
    }

    if ((x >= 0) && (y < 0))
    {
        return -result;
    }
    else if ((x < 0) && (y >= 0))
    {
        return 18000 - result;
    }
    else if ((x < 0) && (y < 0))
    {
        return result - 18000;
    }
    else
    {
        return result;
    }
}
