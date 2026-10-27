# CI12逐shape清单

shape顺序：batch,m,n,p。完整pass原ns，两次均保留。

## 窄域 seed 1927003

| case | shape | 原ns0 | 原ns1 | 均值ns |
|---|---|---:|---:|---:|
| bmm:dense:4 | 59,46,16,4 | 535257 | 534826 | 535041.5 |
| bmm:ml:3 | 87,4,126,4 | 893895 | 905878 | 899886.5 |
| bmm:sparse:0 | 16,67,20,8 | 481357 | 481457 | 481407.0 |
| bmm:sparse:3 | 2521,5,2,7 | 3366820 | 3374535 | 3370677.5 |
| bmm:sparse:4 | 106,4,52,8 | 1238777 | 1251631 | 1245204.0 |
| bmm:specials:1 | 296,5,17,7 | 1123342 | 1124534 | 1123938.0 |

## 选路coverage seed 1927003

| 原route | case | shape | timed | 原ns0 | 原ns1 | 均值ns |
|---|---|---|---|---:|---:|---:|
| B2 | bmm:dense:4 | 59,46,16,4 | True | 535257 | 534826 | 535041.5 |
| B2 | bmm:ml:3 | 87,4,126,4 | True | 893895 | 905878 | 899886.5 |
| B2 | bmm:sparse:0 | 16,67,20,8 | True | 481357 | 481457 | 481407.0 |
| B2 | bmm:sparse:3 | 2521,5,2,7 | True | 3366820 | 3374535 | 3370677.5 |
| B2 | bmm:sparse:4 | 106,4,52,8 | True | 1238777 | 1251631 | 1245204.0 |
| B2 | bmm:specials:1 | 296,5,17,7 | True | 1123342 | 1124534 | 1123938.0 |
| B2 | bmm:check | 15,45,2,3 | False | 0 | 0 | 0.0 |
| DirectContinuous | bmm:ml:2 | 319,3,23,8 | True | 1027053 | 1026562 | 1026807.5 |
| DirectContinuous | bmm:ml:4 | 157,2,80,7 | True | 976308 | 975507 | 975907.5 |
| DirectContinuous | bmm:ml:5 | 94,3,208,3 | True | 953405 | 941935 | 947670.0 |
| DirectContinuous | bmm:sparse:1 | 474,2,62,3 | True | 1005352 | 997578 | 1001465.0 |
| DirectContinuous | bmm:sparse:5 | 4201,1,14,3 | True | 1129944 | 1139272 | 1134608.0 |
| Packed10 | bmm:dense:1 | 1,63,77,43 | True | 188361 | 188201 | 188281.0 |
| Packed10 | bmm:ml:0 | 1,35,112,23 | True | 85139 | 85168 | 85153.5 |
| UnderflowZero | bmm:subnormal:1 | 24,11,55,12 | True | 16311 | 16270 | 16290.5 |
| UnderflowZero | bmm:subnormal:2 | 298,1,197,3 | True | 76402 | 77845 | 77123.5 |

## 窄域 seed 1927005

| case | shape | 原ns0 | 原ns1 | 均值ns |
|---|---|---:|---:|---:|
| bmm:dense:3 | 213,4,69,3 | 1263684 | 1267617 | 1265650.5 |
| bmm:ml:2 | 83,4,177,3 | 1175729 | 1200523 | 1188126.0 |
| bmm:ml:6 | 1730,17,2,3 | 2694218 | 2722354 | 2708286.0 |
| bmm:extremes:2 | 1,11,56,4 | 146673 | 146804 | 146738.5 |

## 选路coverage seed 1927005

| 原route | case | shape | timed | 原ns0 | 原ns1 | 均值ns |
|---|---|---|---|---:|---:|---:|
| B2 | bmm:dense:3 | 213,4,69,3 | True | 1263684 | 1267617 | 1265650.5 |
| B2 | bmm:ml:2 | 83,4,177,3 | True | 1175729 | 1200523 | 1188126.0 |
| B2 | bmm:ml:6 | 1730,17,2,3 | True | 2694218 | 2722354 | 2708286.0 |
| B2 | bmm:extremes:2 | 1,11,56,4 | True | 146673 | 146804 | 146738.5 |
| DirectContinuous | bmm:dense:5 | 36,1,56,3 | True | 36878 | 36878 | 36878.0 |
| DirectContinuous | bmm:ml:0 | 151,2,83,7 | True | 960489 | 971647 | 966068.0 |
| DirectContinuous | bmm:ml:7 | 67,2,438,3 | True | 944719 | 945248 | 944983.5 |
| DirectContinuous | bmm:sparse:2 | 11029,2,2,4 | True | 2028108 | 2031057 | 2029582.5 |
| DirectContinuous | bmm:specials:0 | 1,3,372,3 | True | 22672 | 22662 | 22667.0 |
| Packed10 | bmm:sparse:5 | 1,49,107,60 | True | 235849 | 235037 | 235443.0 |
| Packed10 | bmm:specials:1 | 1,16,14,27 | True | 138758 | 138989 | 138873.5 |
| Packed10 | bmm:extremes:3 | 5,2,30,12 | True | 397561 | 400626 | 399093.5 |
| Packed10 | bmm:check | 1,14,25,16 | False | 0 | 0 | 0.0 |
| UnderflowZero | bmm:subnormal:0 | 96,5,91,4 | True | 29975 | 30147 | 30061.0 |
| UnderflowZero | bmm:subnormal:3 | 190,29,4,8 | True | 101259 | 98884 | 100071.5 |

