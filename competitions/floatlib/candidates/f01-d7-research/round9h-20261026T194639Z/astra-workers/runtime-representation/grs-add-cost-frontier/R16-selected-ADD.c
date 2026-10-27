LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t v___y_1238_, uint32_t v___y_1239_){
_start:
{
uint32_t v___y_1241_; uint32_t v___y_1242_; uint32_t v___y_1243_; uint32_t v___y_1244_; uint32_t v___y_1245_; uint32_t v___y_1246_; uint32_t v___y_1253_; uint32_t v___y_1254_; uint32_t v___y_1255_; uint32_t v___y_1256_; uint32_t v___y_1257_; uint32_t v___y_1258_; uint8_t v___y_1269_; uint8_t v___y_1283_; uint8_t v___y_1297_; uint8_t v___y_1314_; float v___y_1321_; float v___y_1322_; float v___y_1336_; uint8_t v___y_1337_; float v___y_1352_; uint8_t v___y_1362_; uint8_t v___y_1382_; uint8_t v___y_1396_; uint8_t v___y_1410_; uint8_t v___y_1427_; float v___y_1434_; float v___y_1435_; float v___y_1449_; uint8_t v___y_1450_; float v___y_1465_; uint8_t v___y_1475_; uint8_t v___y_1495_; uint8_t v___y_1509_; uint8_t v___y_1523_; uint8_t v___y_1540_; float v___y_1547_; float v___y_1548_; float v___y_1562_; uint8_t v___y_1563_; float v___y_1578_; uint32_t v___y_1588_; uint8_t v___y_1589_; uint8_t v___y_1608_; uint8_t v___y_1622_; uint8_t v___y_1636_; uint8_t v___y_1653_; float v___y_1660_; float v___y_1661_; float v___y_1675_; uint8_t v___y_1676_; float v___y_1691_; uint32_t v___y_1701_; uint32_t v___y_1702_; uint8_t v___y_1703_; uint32_t v___y_1716_; uint32_t v___y_1717_; uint32_t v___y_1718_; uint32_t v___y_1719_; uint32_t v___y_1720_; uint32_t v___y_1721_; uint32_t v___y_1745_; uint32_t v___y_1768_; uint32_t v___y_1769_; uint8_t v___y_1770_; uint32_t v___y_1774_; uint32_t v___y_1775_; uint32_t v___y_1776_; uint32_t v___y_1777_; uint32_t v___y_1785_; uint32_t v___y_1786_; uint32_t v___y_1787_; uint32_t v___y_1788_; uint32_t v___y_1789_; uint32_t v___y_1790_; uint32_t v___y_1791_; uint32_t v___y_1802_; uint32_t v___y_1803_; uint32_t v___y_1804_; uint32_t v___y_1805_; uint32_t v___y_1816_; uint8_t v___y_1837_; uint32_t v___y_1847_; uint32_t v___y_1848_; uint32_t v___y_1849_; uint32_t v___y_1850_; uint32_t v___y_1851_; uint32_t v___y_1857_; uint32_t v___y_1858_; uint8_t v___y_1869_; uint32_t v___y_1879_; uint32_t v___y_1880_; uint32_t v___y_1881_; uint32_t v___y_1882_; uint32_t v___y_1892_; uint8_t v___y_1903_; uint32_t v___x_1919_; uint32_t v___x_1920_; uint32_t v___x_1921_; uint32_t v___x_1922_; uint32_t v___x_1923_; uint32_t v___x_1924_; uint32_t v___x_1925_; uint8_t v___x_1926_; 
v___x_1919_ = 23;
v___x_1920_ = lean_uint32_shift_right(v___y_1238_, v___x_1919_);
v___x_1921_ = 255;
v___x_1922_ = lean_uint32_land(v___x_1920_, v___x_1921_);
v___x_1923_ = 1;
v___x_1924_ = lean_uint32_sub(v___x_1922_, v___x_1923_);
v___x_1925_ = 253;
v___x_1926_ = lean_uint32_dec_le(v___x_1924_, v___x_1925_);
if (v___x_1926_ == 0)
{
v___y_1903_ = v___x_1926_;
goto v___jp_1902_;
}
else
{
uint32_t v___x_1927_; uint32_t v___x_1928_; uint32_t v___x_1929_; uint8_t v___x_1930_; 
v___x_1927_ = lean_uint32_shift_right(v___y_1239_, v___x_1919_);
v___x_1928_ = lean_uint32_land(v___x_1927_, v___x_1921_);
v___x_1929_ = lean_uint32_sub(v___x_1928_, v___x_1923_);
v___x_1930_ = lean_uint32_dec_le(v___x_1929_, v___x_1925_);
v___y_1903_ = v___x_1930_;
goto v___jp_1902_;
}
v___jp_1240_:
{
uint32_t v___x_1247_; uint32_t v___x_1248_; uint32_t v___x_1249_; uint32_t v___x_1250_; uint32_t v___x_1251_; 
v___x_1247_ = lean_uint32_land(v___y_1242_, v___y_1245_);
v___x_1248_ = lean_uint32_shift_left(v___x_1247_, v___y_1244_);
v___x_1249_ = lean_uint32_lor(v___y_1246_, v___x_1248_);
v___x_1250_ = lean_uint32_land(v___y_1243_, v___y_1241_);
v___x_1251_ = lean_uint32_lor(v___x_1249_, v___x_1250_);
return v___x_1251_;
}
v___jp_1252_:
{
uint8_t v___x_1259_; uint32_t v___x_1260_; uint32_t v___x_1261_; 
v___x_1259_ = lean_uint32_dec_le(v___y_1254_, v___y_1258_);
v___x_1260_ = 8388607;
v___x_1261_ = lean_uint32_land(v___y_1256_, v___x_1260_);
if (v___x_1259_ == 0)
{
uint32_t v___x_1262_; 
v___x_1262_ = 0;
v___y_1241_ = v___x_1260_;
v___y_1242_ = v___y_1253_;
v___y_1243_ = v___x_1261_;
v___y_1244_ = v___y_1255_;
v___y_1245_ = v___y_1257_;
v___y_1246_ = v___x_1262_;
goto v___jp_1240_;
}
else
{
v___y_1241_ = v___x_1260_;
v___y_1242_ = v___y_1253_;
v___y_1243_ = v___x_1261_;
v___y_1244_ = v___y_1255_;
v___y_1245_ = v___y_1257_;
v___y_1246_ = v___y_1254_;
goto v___jp_1240_;
}
}
v___jp_1263_:
{
lean_object* v___x_1264_; lean_object* v___x_1265_; lean_object* v___x_1266_; uint32_t v___x_1267_; 
v___x_1264_ = lean_uint32_to_nat(v___y_1238_);
v___x_1265_ = lean_uint32_to_nat(v___y_1239_);
v___x_1266_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1264_, v___x_1265_);
v___x_1267_ = lean_uint32_of_nat(v___x_1266_);
lean_dec(v___x_1266_);
return v___x_1267_;
}
v___jp_1268_:
{
if (v___y_1269_ == 0)
{
goto v___jp_1263_;
}
else
{
uint32_t v___x_1270_; uint32_t v___x_1271_; 
v___x_1270_ = 4194304;
v___x_1271_ = lean_uint32_lor(v___y_1239_, v___x_1270_);
return v___x_1271_;
}
}
v___jp_1272_:
{
uint32_t v___x_1273_; uint32_t v___x_1274_; uint32_t v___x_1275_; uint32_t v___x_1276_; uint8_t v___x_1277_; 
v___x_1273_ = 23;
v___x_1274_ = lean_uint32_shift_right(v___y_1239_, v___x_1273_);
v___x_1275_ = 255;
v___x_1276_ = lean_uint32_land(v___x_1274_, v___x_1275_);
v___x_1277_ = lean_uint32_dec_eq(v___x_1276_, v___x_1275_);
if (v___x_1277_ == 0)
{
v___y_1269_ = v___x_1277_;
goto v___jp_1268_;
}
else
{
uint32_t v___x_1278_; uint32_t v___x_1279_; uint32_t v___x_1280_; uint8_t v___x_1281_; 
v___x_1278_ = 8388607;
v___x_1279_ = lean_uint32_land(v___y_1239_, v___x_1278_);
v___x_1280_ = 0;
v___x_1281_ = lean_uint32_dec_eq(v___x_1279_, v___x_1280_);
if (v___x_1281_ == 0)
{
v___y_1269_ = v___x_1277_;
goto v___jp_1268_;
}
else
{
goto v___jp_1263_;
}
}
}
v___jp_1282_:
{
if (v___y_1283_ == 0)
{
goto v___jp_1272_;
}
else
{
uint32_t v___x_1284_; uint32_t v___x_1285_; 
v___x_1284_ = 4194304;
v___x_1285_ = lean_uint32_lor(v___y_1238_, v___x_1284_);
return v___x_1285_;
}
}
v___jp_1286_:
{
uint32_t v___x_1287_; uint32_t v___x_1288_; uint32_t v___x_1289_; uint32_t v___x_1290_; uint8_t v___x_1291_; 
v___x_1287_ = 23;
v___x_1288_ = lean_uint32_shift_right(v___y_1238_, v___x_1287_);
v___x_1289_ = 255;
v___x_1290_ = lean_uint32_land(v___x_1288_, v___x_1289_);
v___x_1291_ = lean_uint32_dec_eq(v___x_1290_, v___x_1289_);
if (v___x_1291_ == 0)
{
v___y_1283_ = v___x_1291_;
goto v___jp_1282_;
}
else
{
uint32_t v___x_1292_; uint32_t v___x_1293_; uint32_t v___x_1294_; uint8_t v___x_1295_; 
v___x_1292_ = 8388607;
v___x_1293_ = lean_uint32_land(v___y_1238_, v___x_1292_);
v___x_1294_ = 0;
v___x_1295_ = lean_uint32_dec_eq(v___x_1293_, v___x_1294_);
if (v___x_1295_ == 0)
{
v___y_1283_ = v___x_1291_;
goto v___jp_1282_;
}
else
{
goto v___jp_1272_;
}
}
}
v___jp_1296_:
{
if (v___y_1297_ == 0)
{
goto v___jp_1286_;
}
else
{
uint32_t v___x_1298_; uint32_t v___x_1299_; uint32_t v___x_1300_; uint8_t v___x_1301_; 
v___x_1298_ = 4194304;
v___x_1299_ = lean_uint32_land(v___y_1239_, v___x_1298_);
v___x_1300_ = 0;
v___x_1301_ = lean_uint32_dec_eq(v___x_1299_, v___x_1300_);
if (v___x_1301_ == 0)
{
goto v___jp_1286_;
}
else
{
uint32_t v___x_1302_; 
v___x_1302_ = lean_uint32_lor(v___y_1239_, v___x_1298_);
return v___x_1302_;
}
}
}
v___jp_1303_:
{
uint32_t v___x_1304_; uint32_t v___x_1305_; uint32_t v___x_1306_; uint32_t v___x_1307_; uint8_t v___x_1308_; 
v___x_1304_ = 23;
v___x_1305_ = lean_uint32_shift_right(v___y_1239_, v___x_1304_);
v___x_1306_ = 255;
v___x_1307_ = lean_uint32_land(v___x_1305_, v___x_1306_);
v___x_1308_ = lean_uint32_dec_eq(v___x_1307_, v___x_1306_);
if (v___x_1308_ == 0)
{
v___y_1297_ = v___x_1308_;
goto v___jp_1296_;
}
else
{
uint32_t v___x_1309_; uint32_t v___x_1310_; uint32_t v___x_1311_; uint8_t v___x_1312_; 
v___x_1309_ = 8388607;
v___x_1310_ = lean_uint32_land(v___y_1239_, v___x_1309_);
v___x_1311_ = 0;
v___x_1312_ = lean_uint32_dec_eq(v___x_1310_, v___x_1311_);
if (v___x_1312_ == 0)
{
v___y_1297_ = v___x_1308_;
goto v___jp_1296_;
}
else
{
goto v___jp_1286_;
}
}
}
v___jp_1313_:
{
if (v___y_1314_ == 0)
{
goto v___jp_1303_;
}
else
{
uint32_t v___x_1315_; uint32_t v___x_1316_; uint32_t v___x_1317_; uint8_t v___x_1318_; 
v___x_1315_ = 4194304;
v___x_1316_ = lean_uint32_land(v___y_1238_, v___x_1315_);
v___x_1317_ = 0;
v___x_1318_ = lean_uint32_dec_eq(v___x_1316_, v___x_1317_);
if (v___x_1318_ == 0)
{
goto v___jp_1303_;
}
else
{
uint32_t v___x_1319_; 
v___x_1319_ = lean_uint32_lor(v___y_1238_, v___x_1315_);
return v___x_1319_;
}
}
}
v___jp_1320_:
{
float v_result_1323_; uint8_t v___x_1324_; 
v_result_1323_ = lean_float32_add(v___y_1321_, v___y_1322_);
v___x_1324_ = lean_float32_beq(v_result_1323_, v_result_1323_);
if (v___x_1324_ == 0)
{
uint32_t v___x_1325_; uint32_t v___x_1326_; uint32_t v___x_1327_; uint32_t v___x_1328_; uint8_t v___x_1329_; 
v___x_1325_ = 23;
v___x_1326_ = lean_uint32_shift_right(v___y_1238_, v___x_1325_);
v___x_1327_ = 255;
v___x_1328_ = lean_uint32_land(v___x_1326_, v___x_1327_);
v___x_1329_ = lean_uint32_dec_eq(v___x_1328_, v___x_1327_);
if (v___x_1329_ == 0)
{
v___y_1314_ = v___x_1329_;
goto v___jp_1313_;
}
else
{
uint32_t v___x_1330_; uint32_t v___x_1331_; uint32_t v___x_1332_; uint8_t v___x_1333_; 
v___x_1330_ = 8388607;
v___x_1331_ = lean_uint32_land(v___y_1238_, v___x_1330_);
v___x_1332_ = 0;
v___x_1333_ = lean_uint32_dec_eq(v___x_1331_, v___x_1332_);
if (v___x_1333_ == 0)
{
v___y_1314_ = v___x_1329_;
goto v___jp_1313_;
}
else
{
goto v___jp_1303_;
}
}
}
else
{
uint32_t v___x_1334_; 
v___x_1334_ = lean_float32_to_bits(v_result_1323_);
return v___x_1334_;
}
}
v___jp_1335_:
{
if (v___y_1337_ == 0)
{
float v___x_1338_; 
v___x_1338_ = lean_float32_of_bits(v___y_1239_);
v___y_1321_ = v___y_1336_;
v___y_1322_ = v___x_1338_;
goto v___jp_1320_;
}
else
{
uint32_t v___x_1339_; uint32_t v___x_1340_; uint32_t v___x_1341_; uint32_t v___x_1342_; float v___x_1343_; lean_object* v___x_1344_; uint32_t v___x_1345_; uint32_t v___x_1346_; lean_object* v___x_1347_; lean_object* v___x_1348_; float v___x_1349_; float v___x_1350_; 
v___x_1339_ = 8388607;
v___x_1340_ = lean_uint32_land(v___y_1239_, v___x_1339_);
v___x_1341_ = 8388608;
v___x_1342_ = lean_uint32_lor(v___x_1340_, v___x_1341_);
v___x_1343_ = lean_uint32_to_float32(v___x_1342_);
v___x_1344_ = lp_competition_R2W01b_scaleTable;
v___x_1345_ = 23;
v___x_1346_ = lean_uint32_shift_right(v___y_1239_, v___x_1345_);
v___x_1347_ = lean_uint32_to_nat(v___x_1346_);
v___x_1348_ = lean_array_fget_borrowed(v___x_1344_, v___x_1347_);
lean_dec(v___x_1347_);
v___x_1349_ = lean_unbox_float32(v___x_1348_);
v___x_1350_ = lean_float32_mul(v___x_1343_, v___x_1349_);
v___y_1321_ = v___y_1336_;
v___y_1322_ = v___x_1350_;
goto v___jp_1320_;
}
}
v___jp_1351_:
{
uint32_t v___x_1353_; uint32_t v_a_1354_; uint32_t v___x_1355_; uint32_t v___x_1356_; uint32_t v___x_1357_; uint8_t v___x_1358_; 
v___x_1353_ = 2147483647;
v_a_1354_ = lean_uint32_land(v___y_1239_, v___x_1353_);
v___x_1355_ = 201326591;
v___x_1356_ = 1;
v___x_1357_ = lean_uint32_sub(v_a_1354_, v___x_1356_);
v___x_1358_ = lean_uint32_dec_le(v___x_1355_, v___x_1357_);
if (v___x_1358_ == 0)
{
v___y_1336_ = v___y_1352_;
v___y_1337_ = v___x_1358_;
goto v___jp_1335_;
}
else
{
uint32_t v___x_1359_; uint8_t v___x_1360_; 
v___x_1359_ = 2139095040;
v___x_1360_ = lean_uint32_dec_lt(v_a_1354_, v___x_1359_);
v___y_1336_ = v___y_1352_;
v___y_1337_ = v___x_1360_;
goto v___jp_1335_;
}
}
v___jp_1361_:
{
if (v___y_1362_ == 0)
{
float v___x_1363_; 
v___x_1363_ = lean_float32_of_bits(v___y_1238_);
v___y_1352_ = v___x_1363_;
goto v___jp_1351_;
}
else
{
uint32_t v___x_1364_; uint32_t v___x_1365_; uint32_t v___x_1366_; uint32_t v___x_1367_; float v___x_1368_; lean_object* v___x_1369_; uint32_t v___x_1370_; uint32_t v___x_1371_; lean_object* v___x_1372_; lean_object* v___x_1373_; float v___x_1374_; float v___x_1375_; 
v___x_1364_ = 8388607;
v___x_1365_ = lean_uint32_land(v___y_1238_, v___x_1364_);
v___x_1366_ = 8388608;
v___x_1367_ = lean_uint32_lor(v___x_1365_, v___x_1366_);
v___x_1368_ = lean_uint32_to_float32(v___x_1367_);
v___x_1369_ = lp_competition_R2W01b_scaleTable;
v___x_1370_ = 23;
v___x_1371_ = lean_uint32_shift_right(v___y_1238_, v___x_1370_);
v___x_1372_ = lean_uint32_to_nat(v___x_1371_);
v___x_1373_ = lean_array_fget_borrowed(v___x_1369_, v___x_1372_);
lean_dec(v___x_1372_);
v___x_1374_ = lean_unbox_float32(v___x_1373_);
v___x_1375_ = lean_float32_mul(v___x_1368_, v___x_1374_);
v___y_1352_ = v___x_1375_;
goto v___jp_1351_;
}
}
v___jp_1376_:
{
lean_object* v___x_1377_; lean_object* v___x_1378_; lean_object* v___x_1379_; uint32_t v___x_1380_; 
v___x_1377_ = lean_uint32_to_nat(v___y_1238_);
v___x_1378_ = lean_uint32_to_nat(v___y_1239_);
v___x_1379_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1377_, v___x_1378_);
v___x_1380_ = lean_uint32_of_nat(v___x_1379_);
lean_dec(v___x_1379_);
return v___x_1380_;
}
v___jp_1381_:
{
if (v___y_1382_ == 0)
{
goto v___jp_1376_;
}
else
{
uint32_t v___x_1383_; uint32_t v___x_1384_; 
v___x_1383_ = 4194304;
v___x_1384_ = lean_uint32_lor(v___y_1239_, v___x_1383_);
return v___x_1384_;
}
}
v___jp_1385_:
{
uint32_t v___x_1386_; uint32_t v___x_1387_; uint32_t v___x_1388_; uint32_t v___x_1389_; uint8_t v___x_1390_; 
v___x_1386_ = 23;
v___x_1387_ = lean_uint32_shift_right(v___y_1239_, v___x_1386_);
v___x_1388_ = 255;
v___x_1389_ = lean_uint32_land(v___x_1387_, v___x_1388_);
v___x_1390_ = lean_uint32_dec_eq(v___x_1389_, v___x_1388_);
if (v___x_1390_ == 0)
{
v___y_1382_ = v___x_1390_;
goto v___jp_1381_;
}
else
{
uint32_t v___x_1391_; uint32_t v___x_1392_; uint32_t v___x_1393_; uint8_t v___x_1394_; 
v___x_1391_ = 8388607;
v___x_1392_ = lean_uint32_land(v___y_1239_, v___x_1391_);
v___x_1393_ = 0;
v___x_1394_ = lean_uint32_dec_eq(v___x_1392_, v___x_1393_);
if (v___x_1394_ == 0)
{
v___y_1382_ = v___x_1390_;
goto v___jp_1381_;
}
else
{
goto v___jp_1376_;
}
}
}
v___jp_1395_:
{
if (v___y_1396_ == 0)
{
goto v___jp_1385_;
}
else
{
uint32_t v___x_1397_; uint32_t v___x_1398_; 
v___x_1397_ = 4194304;
v___x_1398_ = lean_uint32_lor(v___y_1238_, v___x_1397_);
return v___x_1398_;
}
}
v___jp_1399_:
{
uint32_t v___x_1400_; uint32_t v___x_1401_; uint32_t v___x_1402_; uint32_t v___x_1403_; uint8_t v___x_1404_; 
v___x_1400_ = 23;
v___x_1401_ = lean_uint32_shift_right(v___y_1238_, v___x_1400_);
v___x_1402_ = 255;
v___x_1403_ = lean_uint32_land(v___x_1401_, v___x_1402_);
v___x_1404_ = lean_uint32_dec_eq(v___x_1403_, v___x_1402_);
if (v___x_1404_ == 0)
{
v___y_1396_ = v___x_1404_;
goto v___jp_1395_;
}
else
{
uint32_t v___x_1405_; uint32_t v___x_1406_; uint32_t v___x_1407_; uint8_t v___x_1408_; 
v___x_1405_ = 8388607;
v___x_1406_ = lean_uint32_land(v___y_1238_, v___x_1405_);
v___x_1407_ = 0;
v___x_1408_ = lean_uint32_dec_eq(v___x_1406_, v___x_1407_);
if (v___x_1408_ == 0)
{
v___y_1396_ = v___x_1404_;
goto v___jp_1395_;
}
else
{
goto v___jp_1385_;
}
}
}
v___jp_1409_:
{
if (v___y_1410_ == 0)
{
goto v___jp_1399_;
}
else
{
uint32_t v___x_1411_; uint32_t v___x_1412_; uint32_t v___x_1413_; uint8_t v___x_1414_; 
v___x_1411_ = 4194304;
v___x_1412_ = lean_uint32_land(v___y_1239_, v___x_1411_);
v___x_1413_ = 0;
v___x_1414_ = lean_uint32_dec_eq(v___x_1412_, v___x_1413_);
if (v___x_1414_ == 0)
{
goto v___jp_1399_;
}
else
{
uint32_t v___x_1415_; 
v___x_1415_ = lean_uint32_lor(v___y_1239_, v___x_1411_);
return v___x_1415_;
}
}
}
v___jp_1416_:
{
uint32_t v___x_1417_; uint32_t v___x_1418_; uint32_t v___x_1419_; uint32_t v___x_1420_; uint8_t v___x_1421_; 
v___x_1417_ = 23;
v___x_1418_ = lean_uint32_shift_right(v___y_1239_, v___x_1417_);
v___x_1419_ = 255;
v___x_1420_ = lean_uint32_land(v___x_1418_, v___x_1419_);
v___x_1421_ = lean_uint32_dec_eq(v___x_1420_, v___x_1419_);
if (v___x_1421_ == 0)
{
v___y_1410_ = v___x_1421_;
goto v___jp_1409_;
}
else
{
uint32_t v___x_1422_; uint32_t v___x_1423_; uint32_t v___x_1424_; uint8_t v___x_1425_; 
v___x_1422_ = 8388607;
v___x_1423_ = lean_uint32_land(v___y_1239_, v___x_1422_);
v___x_1424_ = 0;
v___x_1425_ = lean_uint32_dec_eq(v___x_1423_, v___x_1424_);
if (v___x_1425_ == 0)
{
v___y_1410_ = v___x_1421_;
goto v___jp_1409_;
}
else
{
goto v___jp_1399_;
}
}
}
v___jp_1426_:
{
if (v___y_1427_ == 0)
{
goto v___jp_1416_;
}
else
{
uint32_t v___x_1428_; uint32_t v___x_1429_; uint32_t v___x_1430_; uint8_t v___x_1431_; 
v___x_1428_ = 4194304;
v___x_1429_ = lean_uint32_land(v___y_1238_, v___x_1428_);
v___x_1430_ = 0;
v___x_1431_ = lean_uint32_dec_eq(v___x_1429_, v___x_1430_);
if (v___x_1431_ == 0)
{
goto v___jp_1416_;
}
else
{
uint32_t v___x_1432_; 
v___x_1432_ = lean_uint32_lor(v___y_1238_, v___x_1428_);
return v___x_1432_;
}
}
}
v___jp_1433_:
{
float v_result_1436_; uint8_t v___x_1437_; 
v_result_1436_ = lean_float32_add(v___y_1434_, v___y_1435_);
v___x_1437_ = lean_float32_beq(v_result_1436_, v_result_1436_);
if (v___x_1437_ == 0)
{
uint32_t v___x_1438_; uint32_t v___x_1439_; uint32_t v___x_1440_; uint32_t v___x_1441_; uint8_t v___x_1442_; 
v___x_1438_ = 23;
v___x_1439_ = lean_uint32_shift_right(v___y_1238_, v___x_1438_);
v___x_1440_ = 255;
v___x_1441_ = lean_uint32_land(v___x_1439_, v___x_1440_);
v___x_1442_ = lean_uint32_dec_eq(v___x_1441_, v___x_1440_);
if (v___x_1442_ == 0)
{
v___y_1427_ = v___x_1442_;
goto v___jp_1426_;
}
else
{
uint32_t v___x_1443_; uint32_t v___x_1444_; uint32_t v___x_1445_; uint8_t v___x_1446_; 
v___x_1443_ = 8388607;
v___x_1444_ = lean_uint32_land(v___y_1238_, v___x_1443_);
v___x_1445_ = 0;
v___x_1446_ = lean_uint32_dec_eq(v___x_1444_, v___x_1445_);
if (v___x_1446_ == 0)
{
v___y_1427_ = v___x_1442_;
goto v___jp_1426_;
}
else
{
goto v___jp_1416_;
}
}
}
else
{
uint32_t v___x_1447_; 
v___x_1447_ = lean_float32_to_bits(v_result_1436_);
return v___x_1447_;
}
}
v___jp_1448_:
{
if (v___y_1450_ == 0)
{
float v___x_1451_; 
v___x_1451_ = lean_float32_of_bits(v___y_1239_);
v___y_1434_ = v___y_1449_;
v___y_1435_ = v___x_1451_;
goto v___jp_1433_;
}
else
{
uint32_t v___x_1452_; uint32_t v___x_1453_; uint32_t v___x_1454_; uint32_t v___x_1455_; float v___x_1456_; lean_object* v___x_1457_; uint32_t v___x_1458_; uint32_t v___x_1459_; lean_object* v___x_1460_; lean_object* v___x_1461_; float v___x_1462_; float v___x_1463_; 
v___x_1452_ = 8388607;
v___x_1453_ = lean_uint32_land(v___y_1239_, v___x_1452_);
v___x_1454_ = 8388608;
v___x_1455_ = lean_uint32_lor(v___x_1453_, v___x_1454_);
v___x_1456_ = lean_uint32_to_float32(v___x_1455_);
v___x_1457_ = lp_competition_R2W01b_scaleTable;
v___x_1458_ = 23;
v___x_1459_ = lean_uint32_shift_right(v___y_1239_, v___x_1458_);
v___x_1460_ = lean_uint32_to_nat(v___x_1459_);
v___x_1461_ = lean_array_fget_borrowed(v___x_1457_, v___x_1460_);
lean_dec(v___x_1460_);
v___x_1462_ = lean_unbox_float32(v___x_1461_);
v___x_1463_ = lean_float32_mul(v___x_1456_, v___x_1462_);
v___y_1434_ = v___y_1449_;
v___y_1435_ = v___x_1463_;
goto v___jp_1433_;
}
}
v___jp_1464_:
{
uint32_t v___x_1466_; uint32_t v_a_1467_; uint32_t v___x_1468_; uint32_t v___x_1469_; uint32_t v___x_1470_; uint8_t v___x_1471_; 
v___x_1466_ = 2147483647;
v_a_1467_ = lean_uint32_land(v___y_1239_, v___x_1466_);
v___x_1468_ = 201326591;
v___x_1469_ = 1;
v___x_1470_ = lean_uint32_sub(v_a_1467_, v___x_1469_);
v___x_1471_ = lean_uint32_dec_le(v___x_1468_, v___x_1470_);
if (v___x_1471_ == 0)
{
v___y_1449_ = v___y_1465_;
v___y_1450_ = v___x_1471_;
goto v___jp_1448_;
}
else
{
uint32_t v___x_1472_; uint8_t v___x_1473_; 
v___x_1472_ = 2139095040;
v___x_1473_ = lean_uint32_dec_lt(v_a_1467_, v___x_1472_);
v___y_1449_ = v___y_1465_;
v___y_1450_ = v___x_1473_;
goto v___jp_1448_;
}
}
v___jp_1474_:
{
if (v___y_1475_ == 0)
{
float v___x_1476_; 
v___x_1476_ = lean_float32_of_bits(v___y_1238_);
v___y_1465_ = v___x_1476_;
goto v___jp_1464_;
}
else
{
uint32_t v___x_1477_; uint32_t v___x_1478_; uint32_t v___x_1479_; uint32_t v___x_1480_; float v___x_1481_; lean_object* v___x_1482_; uint32_t v___x_1483_; uint32_t v___x_1484_; lean_object* v___x_1485_; lean_object* v___x_1486_; float v___x_1487_; float v___x_1488_; 
v___x_1477_ = 8388607;
v___x_1478_ = lean_uint32_land(v___y_1238_, v___x_1477_);
v___x_1479_ = 8388608;
v___x_1480_ = lean_uint32_lor(v___x_1478_, v___x_1479_);
v___x_1481_ = lean_uint32_to_float32(v___x_1480_);
v___x_1482_ = lp_competition_R2W01b_scaleTable;
v___x_1483_ = 23;
v___x_1484_ = lean_uint32_shift_right(v___y_1238_, v___x_1483_);
v___x_1485_ = lean_uint32_to_nat(v___x_1484_);
v___x_1486_ = lean_array_fget_borrowed(v___x_1482_, v___x_1485_);
lean_dec(v___x_1485_);
v___x_1487_ = lean_unbox_float32(v___x_1486_);
v___x_1488_ = lean_float32_mul(v___x_1481_, v___x_1487_);
v___y_1465_ = v___x_1488_;
goto v___jp_1464_;
}
}
v___jp_1489_:
{
lean_object* v___x_1490_; lean_object* v___x_1491_; lean_object* v___x_1492_; uint32_t v___x_1493_; 
v___x_1490_ = lean_uint32_to_nat(v___y_1238_);
v___x_1491_ = lean_uint32_to_nat(v___y_1239_);
v___x_1492_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1490_, v___x_1491_);
v___x_1493_ = lean_uint32_of_nat(v___x_1492_);
lean_dec(v___x_1492_);
return v___x_1493_;
}
v___jp_1494_:
{
if (v___y_1495_ == 0)
{
goto v___jp_1489_;
}
else
{
uint32_t v___x_1496_; uint32_t v___x_1497_; 
v___x_1496_ = 4194304;
v___x_1497_ = lean_uint32_lor(v___y_1239_, v___x_1496_);
return v___x_1497_;
}
}
v___jp_1498_:
{
uint32_t v___x_1499_; uint32_t v___x_1500_; uint32_t v___x_1501_; uint32_t v___x_1502_; uint8_t v___x_1503_; 
v___x_1499_ = 23;
v___x_1500_ = lean_uint32_shift_right(v___y_1239_, v___x_1499_);
v___x_1501_ = 255;
v___x_1502_ = lean_uint32_land(v___x_1500_, v___x_1501_);
v___x_1503_ = lean_uint32_dec_eq(v___x_1502_, v___x_1501_);
if (v___x_1503_ == 0)
{
v___y_1495_ = v___x_1503_;
goto v___jp_1494_;
}
else
{
uint32_t v___x_1504_; uint32_t v___x_1505_; uint32_t v___x_1506_; uint8_t v___x_1507_; 
v___x_1504_ = 8388607;
v___x_1505_ = lean_uint32_land(v___y_1239_, v___x_1504_);
v___x_1506_ = 0;
v___x_1507_ = lean_uint32_dec_eq(v___x_1505_, v___x_1506_);
if (v___x_1507_ == 0)
{
v___y_1495_ = v___x_1503_;
goto v___jp_1494_;
}
else
{
goto v___jp_1489_;
}
}
}
v___jp_1508_:
{
if (v___y_1509_ == 0)
{
goto v___jp_1498_;
}
else
{
uint32_t v___x_1510_; uint32_t v___x_1511_; 
v___x_1510_ = 4194304;
v___x_1511_ = lean_uint32_lor(v___y_1238_, v___x_1510_);
return v___x_1511_;
}
}
v___jp_1512_:
{
uint32_t v___x_1513_; uint32_t v___x_1514_; uint32_t v___x_1515_; uint32_t v___x_1516_; uint8_t v___x_1517_; 
v___x_1513_ = 23;
v___x_1514_ = lean_uint32_shift_right(v___y_1238_, v___x_1513_);
v___x_1515_ = 255;
v___x_1516_ = lean_uint32_land(v___x_1514_, v___x_1515_);
v___x_1517_ = lean_uint32_dec_eq(v___x_1516_, v___x_1515_);
if (v___x_1517_ == 0)
{
v___y_1509_ = v___x_1517_;
goto v___jp_1508_;
}
else
{
uint32_t v___x_1518_; uint32_t v___x_1519_; uint32_t v___x_1520_; uint8_t v___x_1521_; 
v___x_1518_ = 8388607;
v___x_1519_ = lean_uint32_land(v___y_1238_, v___x_1518_);
v___x_1520_ = 0;
v___x_1521_ = lean_uint32_dec_eq(v___x_1519_, v___x_1520_);
if (v___x_1521_ == 0)
{
v___y_1509_ = v___x_1517_;
goto v___jp_1508_;
}
else
{
goto v___jp_1498_;
}
}
}
v___jp_1522_:
{
if (v___y_1523_ == 0)
{
goto v___jp_1512_;
}
else
{
uint32_t v___x_1524_; uint32_t v___x_1525_; uint32_t v___x_1526_; uint8_t v___x_1527_; 
v___x_1524_ = 4194304;
v___x_1525_ = lean_uint32_land(v___y_1239_, v___x_1524_);
v___x_1526_ = 0;
v___x_1527_ = lean_uint32_dec_eq(v___x_1525_, v___x_1526_);
if (v___x_1527_ == 0)
{
goto v___jp_1512_;
}
else
{
uint32_t v___x_1528_; 
v___x_1528_ = lean_uint32_lor(v___y_1239_, v___x_1524_);
return v___x_1528_;
}
}
}
v___jp_1529_:
{
uint32_t v___x_1530_; uint32_t v___x_1531_; uint32_t v___x_1532_; uint32_t v___x_1533_; uint8_t v___x_1534_; 
v___x_1530_ = 23;
v___x_1531_ = lean_uint32_shift_right(v___y_1239_, v___x_1530_);
v___x_1532_ = 255;
v___x_1533_ = lean_uint32_land(v___x_1531_, v___x_1532_);
v___x_1534_ = lean_uint32_dec_eq(v___x_1533_, v___x_1532_);
if (v___x_1534_ == 0)
{
v___y_1523_ = v___x_1534_;
goto v___jp_1522_;
}
else
{
uint32_t v___x_1535_; uint32_t v___x_1536_; uint32_t v___x_1537_; uint8_t v___x_1538_; 
v___x_1535_ = 8388607;
v___x_1536_ = lean_uint32_land(v___y_1239_, v___x_1535_);
v___x_1537_ = 0;
v___x_1538_ = lean_uint32_dec_eq(v___x_1536_, v___x_1537_);
if (v___x_1538_ == 0)
{
v___y_1523_ = v___x_1534_;
goto v___jp_1522_;
}
else
{
goto v___jp_1512_;
}
}
}
v___jp_1539_:
{
if (v___y_1540_ == 0)
{
goto v___jp_1529_;
}
else
{
uint32_t v___x_1541_; uint32_t v___x_1542_; uint32_t v___x_1543_; uint8_t v___x_1544_; 
v___x_1541_ = 4194304;
v___x_1542_ = lean_uint32_land(v___y_1238_, v___x_1541_);
v___x_1543_ = 0;
v___x_1544_ = lean_uint32_dec_eq(v___x_1542_, v___x_1543_);
if (v___x_1544_ == 0)
{
goto v___jp_1529_;
}
else
{
uint32_t v___x_1545_; 
v___x_1545_ = lean_uint32_lor(v___y_1238_, v___x_1541_);
return v___x_1545_;
}
}
}
v___jp_1546_:
{
float v_result_1549_; uint8_t v___x_1550_; 
v_result_1549_ = lean_float32_add(v___y_1547_, v___y_1548_);
v___x_1550_ = lean_float32_beq(v_result_1549_, v_result_1549_);
if (v___x_1550_ == 0)
{
uint32_t v___x_1551_; uint32_t v___x_1552_; uint32_t v___x_1553_; uint32_t v___x_1554_; uint8_t v___x_1555_; 
v___x_1551_ = 23;
v___x_1552_ = lean_uint32_shift_right(v___y_1238_, v___x_1551_);
v___x_1553_ = 255;
v___x_1554_ = lean_uint32_land(v___x_1552_, v___x_1553_);
v___x_1555_ = lean_uint32_dec_eq(v___x_1554_, v___x_1553_);
if (v___x_1555_ == 0)
{
v___y_1540_ = v___x_1555_;
goto v___jp_1539_;
}
else
{
uint32_t v___x_1556_; uint32_t v___x_1557_; uint32_t v___x_1558_; uint8_t v___x_1559_; 
v___x_1556_ = 8388607;
v___x_1557_ = lean_uint32_land(v___y_1238_, v___x_1556_);
v___x_1558_ = 0;
v___x_1559_ = lean_uint32_dec_eq(v___x_1557_, v___x_1558_);
if (v___x_1559_ == 0)
{
v___y_1540_ = v___x_1555_;
goto v___jp_1539_;
}
else
{
goto v___jp_1529_;
}
}
}
else
{
uint32_t v___x_1560_; 
v___x_1560_ = lean_float32_to_bits(v_result_1549_);
return v___x_1560_;
}
}
v___jp_1561_:
{
if (v___y_1563_ == 0)
{
float v___x_1564_; 
v___x_1564_ = lean_float32_of_bits(v___y_1239_);
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___x_1564_;
goto v___jp_1546_;
}
else
{
uint32_t v___x_1565_; uint32_t v___x_1566_; uint32_t v___x_1567_; uint32_t v___x_1568_; float v___x_1569_; lean_object* v___x_1570_; uint32_t v___x_1571_; uint32_t v___x_1572_; lean_object* v___x_1573_; lean_object* v___x_1574_; float v___x_1575_; float v___x_1576_; 
v___x_1565_ = 8388607;
v___x_1566_ = lean_uint32_land(v___y_1239_, v___x_1565_);
v___x_1567_ = 8388608;
v___x_1568_ = lean_uint32_lor(v___x_1566_, v___x_1567_);
v___x_1569_ = lean_uint32_to_float32(v___x_1568_);
v___x_1570_ = lp_competition_R2W01b_scaleTable;
v___x_1571_ = 23;
v___x_1572_ = lean_uint32_shift_right(v___y_1239_, v___x_1571_);
v___x_1573_ = lean_uint32_to_nat(v___x_1572_);
v___x_1574_ = lean_array_fget_borrowed(v___x_1570_, v___x_1573_);
lean_dec(v___x_1573_);
v___x_1575_ = lean_unbox_float32(v___x_1574_);
v___x_1576_ = lean_float32_mul(v___x_1569_, v___x_1575_);
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___x_1576_;
goto v___jp_1546_;
}
}
v___jp_1577_:
{
uint32_t v___x_1579_; uint32_t v_a_1580_; uint32_t v___x_1581_; uint32_t v___x_1582_; uint32_t v___x_1583_; uint8_t v___x_1584_; 
v___x_1579_ = 2147483647;
v_a_1580_ = lean_uint32_land(v___y_1239_, v___x_1579_);
v___x_1581_ = 201326591;
v___x_1582_ = 1;
v___x_1583_ = lean_uint32_sub(v_a_1580_, v___x_1582_);
v___x_1584_ = lean_uint32_dec_le(v___x_1581_, v___x_1583_);
if (v___x_1584_ == 0)
{
v___y_1562_ = v___y_1578_;
v___y_1563_ = v___x_1584_;
goto v___jp_1561_;
}
else
{
uint32_t v___x_1585_; uint8_t v___x_1586_; 
v___x_1585_ = 2139095040;
v___x_1586_ = lean_uint32_dec_lt(v_a_1580_, v___x_1585_);
v___y_1562_ = v___y_1578_;
v___y_1563_ = v___x_1586_;
goto v___jp_1561_;
}
}
v___jp_1587_:
{
if (v___y_1589_ == 0)
{
float v___x_1590_; 
v___x_1590_ = lean_float32_of_bits(v___y_1238_);
v___y_1578_ = v___x_1590_;
goto v___jp_1577_;
}
else
{
uint32_t v___x_1591_; uint32_t v___x_1592_; uint32_t v___x_1593_; float v___x_1594_; lean_object* v___x_1595_; uint32_t v___x_1596_; uint32_t v___x_1597_; lean_object* v___x_1598_; lean_object* v___x_1599_; float v___x_1600_; float v___x_1601_; 
v___x_1591_ = 8388607;
v___x_1592_ = lean_uint32_land(v___y_1238_, v___x_1591_);
v___x_1593_ = lean_uint32_lor(v___x_1592_, v___y_1588_);
v___x_1594_ = lean_uint32_to_float32(v___x_1593_);
v___x_1595_ = lp_competition_R2W01b_scaleTable;
v___x_1596_ = 23;
v___x_1597_ = lean_uint32_shift_right(v___y_1238_, v___x_1596_);
v___x_1598_ = lean_uint32_to_nat(v___x_1597_);
v___x_1599_ = lean_array_fget_borrowed(v___x_1595_, v___x_1598_);
lean_dec(v___x_1598_);
v___x_1600_ = lean_unbox_float32(v___x_1599_);
v___x_1601_ = lean_float32_mul(v___x_1594_, v___x_1600_);
v___y_1578_ = v___x_1601_;
goto v___jp_1577_;
}
}
v___jp_1602_:
{
lean_object* v___x_1603_; lean_object* v___x_1604_; lean_object* v___x_1605_; uint32_t v___x_1606_; 
v___x_1603_ = lean_uint32_to_nat(v___y_1238_);
v___x_1604_ = lean_uint32_to_nat(v___y_1239_);
v___x_1605_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1603_, v___x_1604_);
v___x_1606_ = lean_uint32_of_nat(v___x_1605_);
lean_dec(v___x_1605_);
return v___x_1606_;
}
v___jp_1607_:
{
if (v___y_1608_ == 0)
{
goto v___jp_1602_;
}
else
{
uint32_t v___x_1609_; uint32_t v___x_1610_; 
v___x_1609_ = 4194304;
v___x_1610_ = lean_uint32_lor(v___y_1239_, v___x_1609_);
return v___x_1610_;
}
}
v___jp_1611_:
{
uint32_t v___x_1612_; uint32_t v___x_1613_; uint32_t v___x_1614_; uint32_t v___x_1615_; uint8_t v___x_1616_; 
v___x_1612_ = 23;
v___x_1613_ = lean_uint32_shift_right(v___y_1239_, v___x_1612_);
v___x_1614_ = 255;
v___x_1615_ = lean_uint32_land(v___x_1613_, v___x_1614_);
v___x_1616_ = lean_uint32_dec_eq(v___x_1615_, v___x_1614_);
if (v___x_1616_ == 0)
{
v___y_1608_ = v___x_1616_;
goto v___jp_1607_;
}
else
{
uint32_t v___x_1617_; uint32_t v___x_1618_; uint32_t v___x_1619_; uint8_t v___x_1620_; 
v___x_1617_ = 8388607;
v___x_1618_ = lean_uint32_land(v___y_1239_, v___x_1617_);
v___x_1619_ = 0;
v___x_1620_ = lean_uint32_dec_eq(v___x_1618_, v___x_1619_);
if (v___x_1620_ == 0)
{
v___y_1608_ = v___x_1616_;
goto v___jp_1607_;
}
else
{
goto v___jp_1602_;
}
}
}
v___jp_1621_:
{
if (v___y_1622_ == 0)
{
goto v___jp_1611_;
}
else
{
uint32_t v___x_1623_; uint32_t v___x_1624_; 
v___x_1623_ = 4194304;
v___x_1624_ = lean_uint32_lor(v___y_1238_, v___x_1623_);
return v___x_1624_;
}
}
v___jp_1625_:
{
uint32_t v___x_1626_; uint32_t v___x_1627_; uint32_t v___x_1628_; uint32_t v___x_1629_; uint8_t v___x_1630_; 
v___x_1626_ = 23;
v___x_1627_ = lean_uint32_shift_right(v___y_1238_, v___x_1626_);
v___x_1628_ = 255;
v___x_1629_ = lean_uint32_land(v___x_1627_, v___x_1628_);
v___x_1630_ = lean_uint32_dec_eq(v___x_1629_, v___x_1628_);
if (v___x_1630_ == 0)
{
v___y_1622_ = v___x_1630_;
goto v___jp_1621_;
}
else
{
uint32_t v___x_1631_; uint32_t v___x_1632_; uint32_t v___x_1633_; uint8_t v___x_1634_; 
v___x_1631_ = 8388607;
v___x_1632_ = lean_uint32_land(v___y_1238_, v___x_1631_);
v___x_1633_ = 0;
v___x_1634_ = lean_uint32_dec_eq(v___x_1632_, v___x_1633_);
if (v___x_1634_ == 0)
{
v___y_1622_ = v___x_1630_;
goto v___jp_1621_;
}
else
{
goto v___jp_1611_;
}
}
}
v___jp_1635_:
{
if (v___y_1636_ == 0)
{
goto v___jp_1625_;
}
else
{
uint32_t v___x_1637_; uint32_t v___x_1638_; uint32_t v___x_1639_; uint8_t v___x_1640_; 
v___x_1637_ = 4194304;
v___x_1638_ = lean_uint32_land(v___y_1239_, v___x_1637_);
v___x_1639_ = 0;
v___x_1640_ = lean_uint32_dec_eq(v___x_1638_, v___x_1639_);
if (v___x_1640_ == 0)
{
goto v___jp_1625_;
}
else
{
uint32_t v___x_1641_; 
v___x_1641_ = lean_uint32_lor(v___y_1239_, v___x_1637_);
return v___x_1641_;
}
}
}
v___jp_1642_:
{
uint32_t v___x_1643_; uint32_t v___x_1644_; uint32_t v___x_1645_; uint32_t v___x_1646_; uint8_t v___x_1647_; 
v___x_1643_ = 23;
v___x_1644_ = lean_uint32_shift_right(v___y_1239_, v___x_1643_);
v___x_1645_ = 255;
v___x_1646_ = lean_uint32_land(v___x_1644_, v___x_1645_);
v___x_1647_ = lean_uint32_dec_eq(v___x_1646_, v___x_1645_);
if (v___x_1647_ == 0)
{
v___y_1636_ = v___x_1647_;
goto v___jp_1635_;
}
else
{
uint32_t v___x_1648_; uint32_t v___x_1649_; uint32_t v___x_1650_; uint8_t v___x_1651_; 
v___x_1648_ = 8388607;
v___x_1649_ = lean_uint32_land(v___y_1239_, v___x_1648_);
v___x_1650_ = 0;
v___x_1651_ = lean_uint32_dec_eq(v___x_1649_, v___x_1650_);
if (v___x_1651_ == 0)
{
v___y_1636_ = v___x_1647_;
goto v___jp_1635_;
}
else
{
goto v___jp_1625_;
}
}
}
v___jp_1652_:
{
if (v___y_1653_ == 0)
{
goto v___jp_1642_;
}
else
{
uint32_t v___x_1654_; uint32_t v___x_1655_; uint32_t v___x_1656_; uint8_t v___x_1657_; 
v___x_1654_ = 4194304;
v___x_1655_ = lean_uint32_land(v___y_1238_, v___x_1654_);
v___x_1656_ = 0;
v___x_1657_ = lean_uint32_dec_eq(v___x_1655_, v___x_1656_);
if (v___x_1657_ == 0)
{
goto v___jp_1642_;
}
else
{
uint32_t v___x_1658_; 
v___x_1658_ = lean_uint32_lor(v___y_1238_, v___x_1654_);
return v___x_1658_;
}
}
}
v___jp_1659_:
{
float v_result_1662_; uint8_t v___x_1663_; 
v_result_1662_ = lean_float32_add(v___y_1660_, v___y_1661_);
v___x_1663_ = lean_float32_beq(v_result_1662_, v_result_1662_);
if (v___x_1663_ == 0)
{
uint32_t v___x_1664_; uint32_t v___x_1665_; uint32_t v___x_1666_; uint32_t v___x_1667_; uint8_t v___x_1668_; 
v___x_1664_ = 23;
v___x_1665_ = lean_uint32_shift_right(v___y_1238_, v___x_1664_);
v___x_1666_ = 255;
v___x_1667_ = lean_uint32_land(v___x_1665_, v___x_1666_);
v___x_1668_ = lean_uint32_dec_eq(v___x_1667_, v___x_1666_);
if (v___x_1668_ == 0)
{
v___y_1653_ = v___x_1668_;
goto v___jp_1652_;
}
else
{
uint32_t v___x_1669_; uint32_t v___x_1670_; uint32_t v___x_1671_; uint8_t v___x_1672_; 
v___x_1669_ = 8388607;
v___x_1670_ = lean_uint32_land(v___y_1238_, v___x_1669_);
v___x_1671_ = 0;
v___x_1672_ = lean_uint32_dec_eq(v___x_1670_, v___x_1671_);
if (v___x_1672_ == 0)
{
v___y_1653_ = v___x_1668_;
goto v___jp_1652_;
}
else
{
goto v___jp_1642_;
}
}
}
else
{
uint32_t v___x_1673_; 
v___x_1673_ = lean_float32_to_bits(v_result_1662_);
return v___x_1673_;
}
}
v___jp_1674_:
{
if (v___y_1676_ == 0)
{
float v___x_1677_; 
v___x_1677_ = lean_float32_of_bits(v___y_1239_);
v___y_1660_ = v___y_1675_;
v___y_1661_ = v___x_1677_;
goto v___jp_1659_;
}
else
{
uint32_t v___x_1678_; uint32_t v___x_1679_; uint32_t v___x_1680_; uint32_t v___x_1681_; float v___x_1682_; lean_object* v___x_1683_; uint32_t v___x_1684_; uint32_t v___x_1685_; lean_object* v___x_1686_; lean_object* v___x_1687_; float v___x_1688_; float v___x_1689_; 
v___x_1678_ = 8388607;
v___x_1679_ = lean_uint32_land(v___y_1239_, v___x_1678_);
v___x_1680_ = 8388608;
v___x_1681_ = lean_uint32_lor(v___x_1679_, v___x_1680_);
v___x_1682_ = lean_uint32_to_float32(v___x_1681_);
v___x_1683_ = lp_competition_R2W01b_scaleTable;
v___x_1684_ = 23;
v___x_1685_ = lean_uint32_shift_right(v___y_1239_, v___x_1684_);
v___x_1686_ = lean_uint32_to_nat(v___x_1685_);
v___x_1687_ = lean_array_fget_borrowed(v___x_1683_, v___x_1686_);
lean_dec(v___x_1686_);
v___x_1688_ = lean_unbox_float32(v___x_1687_);
v___x_1689_ = lean_float32_mul(v___x_1682_, v___x_1688_);
v___y_1660_ = v___y_1675_;
v___y_1661_ = v___x_1689_;
goto v___jp_1659_;
}
}
v___jp_1690_:
{
uint32_t v___x_1692_; uint32_t v_a_1693_; uint32_t v___x_1694_; uint32_t v___x_1695_; uint32_t v___x_1696_; uint8_t v___x_1697_; 
v___x_1692_ = 2147483647;
v_a_1693_ = lean_uint32_land(v___y_1239_, v___x_1692_);
v___x_1694_ = 201326591;
v___x_1695_ = 1;
v___x_1696_ = lean_uint32_sub(v_a_1693_, v___x_1695_);
v___x_1697_ = lean_uint32_dec_le(v___x_1694_, v___x_1696_);
if (v___x_1697_ == 0)
{
v___y_1675_ = v___y_1691_;
v___y_1676_ = v___x_1697_;
goto v___jp_1674_;
}
else
{
uint32_t v___x_1698_; uint8_t v___x_1699_; 
v___x_1698_ = 2139095040;
v___x_1699_ = lean_uint32_dec_lt(v_a_1693_, v___x_1698_);
v___y_1675_ = v___y_1691_;
v___y_1676_ = v___x_1699_;
goto v___jp_1674_;
}
}
v___jp_1700_:
{
if (v___y_1703_ == 0)
{
float v___x_1704_; 
v___x_1704_ = lean_float32_of_bits(v___y_1238_);
v___y_1691_ = v___x_1704_;
goto v___jp_1690_;
}
else
{
uint32_t v___x_1705_; uint32_t v___x_1706_; uint32_t v___x_1707_; float v___x_1708_; lean_object* v___x_1709_; uint32_t v___x_1710_; lean_object* v___x_1711_; lean_object* v___x_1712_; float v___x_1713_; float v___x_1714_; 
v___x_1705_ = 8388607;
v___x_1706_ = lean_uint32_land(v___y_1238_, v___x_1705_);
v___x_1707_ = lean_uint32_lor(v___x_1706_, v___y_1702_);
v___x_1708_ = lean_uint32_to_float32(v___x_1707_);
v___x_1709_ = lp_competition_R2W01b_scaleTable;
v___x_1710_ = lean_uint32_shift_right(v___y_1238_, v___y_1701_);
v___x_1711_ = lean_uint32_to_nat(v___x_1710_);
v___x_1712_ = lean_array_fget_borrowed(v___x_1709_, v___x_1711_);
lean_dec(v___x_1711_);
v___x_1713_ = lean_unbox_float32(v___x_1712_);
v___x_1714_ = lean_float32_mul(v___x_1708_, v___x_1713_);
v___y_1691_ = v___x_1714_;
goto v___jp_1690_;
}
}
v___jp_1715_:
{
uint32_t v___x_1722_; uint32_t v___x_1723_; uint32_t v___x_1724_; uint32_t v___x_1725_; uint32_t v_e_1726_; uint32_t v___x_1727_; uint32_t v___x_1728_; uint32_t v___x_1729_; uint8_t v___x_1730_; 
v___x_1722_ = lean_uint32_shift_right(v___y_1721_, v___y_1718_);
v___x_1723_ = lean_uint32_land(v___x_1722_, v___y_1720_);
v___x_1724_ = lean_uint32_add(v___y_1716_, v___x_1723_);
v___x_1725_ = 150;
v_e_1726_ = lean_uint32_sub(v___x_1724_, v___x_1725_);
v___x_1727_ = 1;
v___x_1728_ = lean_uint32_sub(v_e_1726_, v___x_1727_);
v___x_1729_ = 253;
v___x_1730_ = lean_uint32_dec_le(v___x_1728_, v___x_1729_);
if (v___x_1730_ == 0)
{
uint32_t v___x_1731_; uint32_t v_a_1732_; uint32_t v___x_1733_; uint32_t v___x_1734_; uint8_t v___x_1735_; 
v___x_1731_ = 2147483647;
v_a_1732_ = lean_uint32_land(v___y_1238_, v___x_1731_);
v___x_1733_ = 201326591;
v___x_1734_ = lean_uint32_sub(v_a_1732_, v___x_1727_);
v___x_1735_ = lean_uint32_dec_le(v___x_1733_, v___x_1734_);
if (v___x_1735_ == 0)
{
v___y_1701_ = v___y_1718_;
v___y_1702_ = v___y_1719_;
v___y_1703_ = v___x_1735_;
goto v___jp_1700_;
}
else
{
uint32_t v___x_1736_; uint8_t v___x_1737_; 
v___x_1736_ = 2139095040;
v___x_1737_ = lean_uint32_dec_lt(v_a_1732_, v___x_1736_);
v___y_1701_ = v___y_1718_;
v___y_1702_ = v___y_1719_;
v___y_1703_ = v___x_1737_;
goto v___jp_1700_;
}
}
else
{
uint32_t v___x_1738_; uint32_t v___x_1739_; uint32_t v___x_1740_; uint32_t v___x_1741_; uint32_t v___x_1742_; uint8_t v___x_1743_; 
v___x_1738_ = 2147483648;
v___x_1739_ = lean_uint32_shift_right(v___y_1238_, v___y_1718_);
v___x_1740_ = lean_uint32_land(v___x_1739_, v___y_1720_);
v___x_1741_ = lean_uint32_shift_right(v___y_1239_, v___y_1718_);
v___x_1742_ = lean_uint32_land(v___x_1741_, v___y_1720_);
v___x_1743_ = lean_uint32_dec_lt(v___x_1740_, v___x_1742_);
if (v___x_1743_ == 0)
{
v___y_1253_ = v_e_1726_;
v___y_1254_ = v___x_1738_;
v___y_1255_ = v___y_1718_;
v___y_1256_ = v___y_1717_;
v___y_1257_ = v___y_1720_;
v___y_1258_ = v___y_1238_;
goto v___jp_1252_;
}
else
{
v___y_1253_ = v_e_1726_;
v___y_1254_ = v___x_1738_;
v___y_1255_ = v___y_1718_;
v___y_1256_ = v___y_1717_;
v___y_1257_ = v___y_1720_;
v___y_1258_ = v___y_1239_;
goto v___jp_1252_;
}
}
}
v___jp_1744_:
{
uint32_t v___x_1746_; uint8_t v___x_1747_; 
v___x_1746_ = 8388608;
v___x_1747_ = lean_uint32_dec_le(v___x_1746_, v___y_1745_);
if (v___x_1747_ == 0)
{
uint32_t v___x_1748_; uint32_t v_a_1749_; uint32_t v___x_1750_; uint32_t v___x_1751_; uint32_t v___x_1752_; uint8_t v___x_1753_; 
v___x_1748_ = 2147483647;
v_a_1749_ = lean_uint32_land(v___y_1238_, v___x_1748_);
v___x_1750_ = 201326591;
v___x_1751_ = 1;
v___x_1752_ = lean_uint32_sub(v_a_1749_, v___x_1751_);
v___x_1753_ = lean_uint32_dec_le(v___x_1750_, v___x_1752_);
if (v___x_1753_ == 0)
{
v___y_1588_ = v___x_1746_;
v___y_1589_ = v___x_1753_;
goto v___jp_1587_;
}
else
{
uint32_t v___x_1754_; uint8_t v___x_1755_; 
v___x_1754_ = 2139095040;
v___x_1755_ = lean_uint32_dec_lt(v_a_1749_, v___x_1754_);
v___y_1588_ = v___x_1746_;
v___y_1589_ = v___x_1755_;
goto v___jp_1587_;
}
}
else
{
float v___x_1756_; uint32_t v_mid_1757_; uint32_t v___x_1758_; uint32_t v___x_1759_; uint32_t v___x_1760_; uint32_t v___x_1761_; uint32_t v___x_1762_; uint32_t v___x_1763_; uint32_t v___x_1764_; uint32_t v___x_1765_; uint8_t v___x_1766_; 
v___x_1756_ = lean_uint32_to_float32(v___y_1745_);
v_mid_1757_ = lean_float32_to_bits(v___x_1756_);
v___x_1758_ = 23;
v___x_1759_ = lean_uint32_shift_right(v_mid_1757_, v___x_1758_);
v___x_1760_ = 255;
v___x_1761_ = lean_uint32_land(v___x_1759_, v___x_1760_);
v___x_1762_ = lean_uint32_shift_right(v___y_1238_, v___x_1758_);
v___x_1763_ = lean_uint32_land(v___x_1762_, v___x_1760_);
v___x_1764_ = lean_uint32_shift_right(v___y_1239_, v___x_1758_);
v___x_1765_ = lean_uint32_land(v___x_1764_, v___x_1760_);
v___x_1766_ = lean_uint32_dec_lt(v___x_1763_, v___x_1765_);
if (v___x_1766_ == 0)
{
v___y_1716_ = v___x_1761_;
v___y_1717_ = v_mid_1757_;
v___y_1718_ = v___x_1758_;
v___y_1719_ = v___x_1746_;
v___y_1720_ = v___x_1760_;
v___y_1721_ = v___y_1239_;
goto v___jp_1715_;
}
else
{
v___y_1716_ = v___x_1761_;
v___y_1717_ = v_mid_1757_;
v___y_1718_ = v___x_1758_;
v___y_1719_ = v___x_1746_;
v___y_1720_ = v___x_1760_;
v___y_1721_ = v___y_1238_;
goto v___jp_1715_;
}
}
}
v___jp_1767_:
{
if (v___y_1770_ == 0)
{
uint32_t v___x_1771_; 
v___x_1771_ = lean_uint32_sub(v___y_1769_, v___y_1768_);
v___y_1745_ = v___x_1771_;
goto v___jp_1744_;
}
else
{
uint32_t v___x_1772_; 
v___x_1772_ = lean_uint32_add(v___y_1769_, v___y_1768_);
v___y_1745_ = v___x_1772_;
goto v___jp_1744_;
}
}
v___jp_1773_:
{
uint32_t v___x_1778_; uint32_t v_right_1779_; uint32_t v___x_1780_; uint8_t v___x_1781_; uint8_t v___x_1782_; 
v___x_1778_ = lean_uint32_land(v___y_1777_, v___y_1776_);
v_right_1779_ = lean_uint32_lor(v___x_1778_, v___y_1774_);
v___x_1780_ = 2147483648;
v___x_1781_ = lean_uint32_dec_le(v___x_1780_, v___y_1238_);
v___x_1782_ = lean_uint32_dec_le(v___x_1780_, v___y_1239_);
if (v___x_1781_ == 0)
{
if (v___x_1782_ == 0)
{
uint32_t v___x_1783_; 
v___x_1783_ = lean_uint32_add(v___y_1775_, v_right_1779_);
v___y_1745_ = v___x_1783_;
goto v___jp_1744_;
}
else
{
v___y_1768_ = v_right_1779_;
v___y_1769_ = v___y_1775_;
v___y_1770_ = v___x_1781_;
goto v___jp_1767_;
}
}
else
{
v___y_1768_ = v_right_1779_;
v___y_1769_ = v___y_1775_;
v___y_1770_ = v___x_1782_;
goto v___jp_1767_;
}
}
v___jp_1784_:
{
uint32_t v___x_1792_; uint32_t v___x_1793_; uint32_t v___x_1794_; uint32_t v_left_1795_; uint32_t v___x_1796_; uint32_t v___x_1797_; uint32_t v___x_1798_; uint32_t v___x_1799_; uint8_t v___x_1800_; 
v___x_1792_ = lean_uint32_shift_right(v___y_1791_, v___y_1787_);
v___x_1793_ = lean_uint32_land(v___x_1792_, v___y_1789_);
v___x_1794_ = lean_uint32_sub(v___y_1790_, v___x_1793_);
v_left_1795_ = lean_uint32_shift_left(v___y_1786_, v___x_1794_);
v___x_1796_ = lean_uint32_shift_right(v___y_1238_, v___y_1787_);
v___x_1797_ = lean_uint32_land(v___x_1796_, v___y_1789_);
v___x_1798_ = lean_uint32_shift_right(v___y_1239_, v___y_1787_);
v___x_1799_ = lean_uint32_land(v___x_1798_, v___y_1789_);
v___x_1800_ = lean_uint32_dec_lt(v___x_1797_, v___x_1799_);
if (v___x_1800_ == 0)
{
v___y_1774_ = v___y_1785_;
v___y_1775_ = v_left_1795_;
v___y_1776_ = v___y_1788_;
v___y_1777_ = v___y_1239_;
goto v___jp_1773_;
}
else
{
v___y_1774_ = v___y_1785_;
v___y_1775_ = v_left_1795_;
v___y_1776_ = v___y_1788_;
v___y_1777_ = v___y_1238_;
goto v___jp_1773_;
}
}
v___jp_1801_:
{
uint32_t v___x_1806_; uint32_t v___x_1807_; uint32_t v___x_1808_; uint32_t v___x_1809_; uint32_t v___x_1810_; uint32_t v___x_1811_; uint32_t v___x_1812_; uint32_t v___x_1813_; uint8_t v___x_1814_; 
v___x_1806_ = 23;
v___x_1807_ = lean_uint32_shift_right(v___y_1805_, v___x_1806_);
v___x_1808_ = 255;
v___x_1809_ = lean_uint32_land(v___x_1807_, v___x_1808_);
v___x_1810_ = lean_uint32_shift_right(v___y_1238_, v___x_1806_);
v___x_1811_ = lean_uint32_land(v___x_1810_, v___x_1808_);
v___x_1812_ = lean_uint32_shift_right(v___y_1239_, v___x_1806_);
v___x_1813_ = lean_uint32_land(v___x_1812_, v___x_1808_);
v___x_1814_ = lean_uint32_dec_lt(v___x_1811_, v___x_1813_);
if (v___x_1814_ == 0)
{
v___y_1785_ = v___y_1802_;
v___y_1786_ = v___y_1803_;
v___y_1787_ = v___x_1806_;
v___y_1788_ = v___y_1804_;
v___y_1789_ = v___x_1808_;
v___y_1790_ = v___x_1809_;
v___y_1791_ = v___y_1239_;
goto v___jp_1784_;
}
else
{
v___y_1785_ = v___y_1802_;
v___y_1786_ = v___y_1803_;
v___y_1787_ = v___x_1806_;
v___y_1788_ = v___y_1804_;
v___y_1789_ = v___x_1808_;
v___y_1790_ = v___x_1809_;
v___y_1791_ = v___y_1238_;
goto v___jp_1784_;
}
}
v___jp_1815_:
{
uint32_t v___x_1817_; uint32_t v___x_1818_; uint32_t v___x_1819_; uint32_t v___x_1820_; uint32_t v___x_1821_; uint32_t v___x_1822_; uint32_t v___x_1823_; uint32_t v___x_1824_; uint32_t v___x_1825_; uint32_t v___x_1826_; uint8_t v___x_1827_; 
v___x_1817_ = 8388607;
v___x_1818_ = lean_uint32_land(v___y_1816_, v___x_1817_);
v___x_1819_ = 8388608;
v___x_1820_ = lean_uint32_lor(v___x_1818_, v___x_1819_);
v___x_1821_ = 23;
v___x_1822_ = lean_uint32_shift_right(v___y_1238_, v___x_1821_);
v___x_1823_ = 255;
v___x_1824_ = lean_uint32_land(v___x_1822_, v___x_1823_);
v___x_1825_ = lean_uint32_shift_right(v___y_1239_, v___x_1821_);
v___x_1826_ = lean_uint32_land(v___x_1825_, v___x_1823_);
v___x_1827_ = lean_uint32_dec_lt(v___x_1824_, v___x_1826_);
if (v___x_1827_ == 0)
{
v___y_1802_ = v___x_1819_;
v___y_1803_ = v___x_1820_;
v___y_1804_ = v___x_1817_;
v___y_1805_ = v___y_1238_;
goto v___jp_1801_;
}
else
{
v___y_1802_ = v___x_1819_;
v___y_1803_ = v___x_1820_;
v___y_1804_ = v___x_1817_;
v___y_1805_ = v___y_1239_;
goto v___jp_1801_;
}
}
v___jp_1828_:
{
uint32_t v___x_1829_; uint32_t v___x_1830_; uint32_t v___x_1831_; uint32_t v___x_1832_; uint32_t v___x_1833_; uint32_t v___x_1834_; uint8_t v___x_1835_; 
v___x_1829_ = 23;
v___x_1830_ = lean_uint32_shift_right(v___y_1238_, v___x_1829_);
v___x_1831_ = 255;
v___x_1832_ = lean_uint32_land(v___x_1830_, v___x_1831_);
v___x_1833_ = lean_uint32_shift_right(v___y_1239_, v___x_1829_);
v___x_1834_ = lean_uint32_land(v___x_1833_, v___x_1831_);
v___x_1835_ = lean_uint32_dec_lt(v___x_1832_, v___x_1834_);
if (v___x_1835_ == 0)
{
v___y_1816_ = v___y_1238_;
goto v___jp_1815_;
}
else
{
v___y_1816_ = v___y_1239_;
goto v___jp_1815_;
}
}
v___jp_1836_:
{
if (v___y_1837_ == 0)
{
uint32_t v___x_1838_; uint32_t v_a_1839_; uint32_t v___x_1840_; uint32_t v___x_1841_; uint32_t v___x_1842_; uint8_t v___x_1843_; 
v___x_1838_ = 2147483647;
v_a_1839_ = lean_uint32_land(v___y_1238_, v___x_1838_);
v___x_1840_ = 201326591;
v___x_1841_ = 1;
v___x_1842_ = lean_uint32_sub(v_a_1839_, v___x_1841_);
v___x_1843_ = lean_uint32_dec_le(v___x_1840_, v___x_1842_);
if (v___x_1843_ == 0)
{
v___y_1475_ = v___x_1843_;
goto v___jp_1474_;
}
else
{
uint32_t v___x_1844_; uint8_t v___x_1845_; 
v___x_1844_ = 2139095040;
v___x_1845_ = lean_uint32_dec_lt(v_a_1839_, v___x_1844_);
v___y_1475_ = v___x_1845_;
goto v___jp_1474_;
}
}
else
{
goto v___jp_1828_;
}
}
v___jp_1846_:
{
uint32_t v___x_1852_; uint32_t v___x_1853_; uint32_t v___x_1854_; uint8_t v___x_1855_; 
v___x_1852_ = lean_uint32_shift_right(v___y_1851_, v___y_1850_);
v___x_1853_ = lean_uint32_land(v___x_1852_, v___y_1849_);
v___x_1854_ = lean_uint32_sub(v___y_1848_, v___x_1853_);
v___x_1855_ = lean_uint32_dec_le(v___y_1847_, v___x_1854_);
v___y_1837_ = v___x_1855_;
goto v___jp_1836_;
}
v___jp_1856_:
{
uint32_t v___x_1859_; uint32_t v___x_1860_; uint32_t v___x_1861_; uint32_t v___x_1862_; uint32_t v___x_1863_; uint32_t v___x_1864_; uint32_t v___x_1865_; uint32_t v___x_1866_; uint8_t v___x_1867_; 
v___x_1859_ = 23;
v___x_1860_ = lean_uint32_shift_right(v___y_1858_, v___x_1859_);
v___x_1861_ = 255;
v___x_1862_ = lean_uint32_land(v___x_1860_, v___x_1861_);
v___x_1863_ = lean_uint32_shift_right(v___y_1238_, v___x_1859_);
v___x_1864_ = lean_uint32_land(v___x_1863_, v___x_1861_);
v___x_1865_ = lean_uint32_shift_right(v___y_1239_, v___x_1859_);
v___x_1866_ = lean_uint32_land(v___x_1865_, v___x_1861_);
v___x_1867_ = lean_uint32_dec_lt(v___x_1864_, v___x_1866_);
if (v___x_1867_ == 0)
{
v___y_1847_ = v___y_1857_;
v___y_1848_ = v___x_1862_;
v___y_1849_ = v___x_1861_;
v___y_1850_ = v___x_1859_;
v___y_1851_ = v___y_1239_;
goto v___jp_1846_;
}
else
{
v___y_1847_ = v___y_1857_;
v___y_1848_ = v___x_1862_;
v___y_1849_ = v___x_1861_;
v___y_1850_ = v___x_1859_;
v___y_1851_ = v___y_1238_;
goto v___jp_1846_;
}
}
v___jp_1868_:
{
if (v___y_1869_ == 0)
{
uint32_t v___x_1870_; uint32_t v___x_1871_; uint32_t v___x_1872_; uint32_t v___x_1873_; uint32_t v___x_1874_; uint32_t v___x_1875_; uint32_t v___x_1876_; uint8_t v___x_1877_; 
v___x_1870_ = 1;
v___x_1871_ = 23;
v___x_1872_ = lean_uint32_shift_right(v___y_1238_, v___x_1871_);
v___x_1873_ = 255;
v___x_1874_ = lean_uint32_land(v___x_1872_, v___x_1873_);
v___x_1875_ = lean_uint32_shift_right(v___y_1239_, v___x_1871_);
v___x_1876_ = lean_uint32_land(v___x_1875_, v___x_1873_);
v___x_1877_ = lean_uint32_dec_lt(v___x_1874_, v___x_1876_);
if (v___x_1877_ == 0)
{
v___y_1857_ = v___x_1870_;
v___y_1858_ = v___y_1238_;
goto v___jp_1856_;
}
else
{
v___y_1857_ = v___x_1870_;
v___y_1858_ = v___y_1239_;
goto v___jp_1856_;
}
}
else
{
goto v___jp_1828_;
}
}
v___jp_1878_:
{
uint32_t v___x_1883_; uint32_t v___x_1884_; uint32_t v___x_1885_; uint32_t v___x_1886_; uint8_t v___x_1887_; 
v___x_1883_ = lean_uint32_shift_right(v___y_1882_, v___y_1879_);
v___x_1884_ = lean_uint32_land(v___x_1883_, v___y_1880_);
v___x_1885_ = lean_uint32_sub(v___y_1881_, v___x_1884_);
v___x_1886_ = 7;
v___x_1887_ = lean_uint32_dec_le(v___x_1885_, v___x_1886_);
if (v___x_1887_ == 0)
{
v___y_1837_ = v___x_1887_;
goto v___jp_1836_;
}
else
{
uint32_t v___x_1888_; uint8_t v___x_1889_; uint8_t v___x_1890_; 
v___x_1888_ = 2147483648;
v___x_1889_ = lean_uint32_dec_le(v___x_1888_, v___y_1238_);
v___x_1890_ = lean_uint32_dec_le(v___x_1888_, v___y_1239_);
if (v___x_1889_ == 0)
{
if (v___x_1890_ == 0)
{
v___y_1837_ = v___x_1887_;
goto v___jp_1836_;
}
else
{
v___y_1869_ = v___x_1889_;
goto v___jp_1868_;
}
}
else
{
v___y_1869_ = v___x_1890_;
goto v___jp_1868_;
}
}
}
v___jp_1891_:
{
uint32_t v___x_1893_; uint32_t v___x_1894_; uint32_t v___x_1895_; uint32_t v___x_1896_; uint32_t v___x_1897_; uint32_t v___x_1898_; uint32_t v___x_1899_; uint32_t v___x_1900_; uint8_t v___x_1901_; 
v___x_1893_ = 23;
v___x_1894_ = lean_uint32_shift_right(v___y_1892_, v___x_1893_);
v___x_1895_ = 255;
v___x_1896_ = lean_uint32_land(v___x_1894_, v___x_1895_);
v___x_1897_ = lean_uint32_shift_right(v___y_1238_, v___x_1893_);
v___x_1898_ = lean_uint32_land(v___x_1897_, v___x_1895_);
v___x_1899_ = lean_uint32_shift_right(v___y_1239_, v___x_1893_);
v___x_1900_ = lean_uint32_land(v___x_1899_, v___x_1895_);
v___x_1901_ = lean_uint32_dec_lt(v___x_1898_, v___x_1900_);
if (v___x_1901_ == 0)
{
v___y_1879_ = v___x_1893_;
v___y_1880_ = v___x_1895_;
v___y_1881_ = v___x_1896_;
v___y_1882_ = v___y_1239_;
goto v___jp_1878_;
}
else
{
v___y_1879_ = v___x_1893_;
v___y_1880_ = v___x_1895_;
v___y_1881_ = v___x_1896_;
v___y_1882_ = v___y_1238_;
goto v___jp_1878_;
}
}
v___jp_1902_:
{
if (v___y_1903_ == 0)
{
uint32_t v___x_1904_; uint32_t v_a_1905_; uint32_t v___x_1906_; uint32_t v___x_1907_; uint32_t v___x_1908_; uint8_t v___x_1909_; 
v___x_1904_ = 2147483647;
v_a_1905_ = lean_uint32_land(v___y_1238_, v___x_1904_);
v___x_1906_ = 201326591;
v___x_1907_ = 1;
v___x_1908_ = lean_uint32_sub(v_a_1905_, v___x_1907_);
v___x_1909_ = lean_uint32_dec_le(v___x_1906_, v___x_1908_);
if (v___x_1909_ == 0)
{
v___y_1362_ = v___x_1909_;
goto v___jp_1361_;
}
else
{
uint32_t v___x_1910_; uint8_t v___x_1911_; 
v___x_1910_ = 2139095040;
v___x_1911_ = lean_uint32_dec_lt(v_a_1905_, v___x_1910_);
v___y_1362_ = v___x_1911_;
goto v___jp_1361_;
}
}
else
{
uint32_t v___x_1912_; uint32_t v___x_1913_; uint32_t v___x_1914_; uint32_t v___x_1915_; uint32_t v___x_1916_; uint32_t v___x_1917_; uint8_t v___x_1918_; 
v___x_1912_ = 23;
v___x_1913_ = lean_uint32_shift_right(v___y_1238_, v___x_1912_);
v___x_1914_ = 255;
v___x_1915_ = lean_uint32_land(v___x_1913_, v___x_1914_);
v___x_1916_ = lean_uint32_shift_right(v___y_1239_, v___x_1912_);
v___x_1917_ = lean_uint32_land(v___x_1916_, v___x_1914_);
v___x_1918_ = lean_uint32_dec_lt(v___x_1915_, v___x_1917_);
if (v___x_1918_ == 0)
{
v___y_1892_ = v___y_1238_;
goto v___jp_1891_;
}
else
{
v___y_1892_ = v___y_1239_;
goto v___jp_1891_;
}
}
}
}
}
