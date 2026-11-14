LEAN_EXPORT uint32_t lp_competition_main___lam__2(uint32_t v___y_1064_, uint32_t v___y_1065_){
_start:
{
uint8_t v___y_1072_; uint8_t v___y_1086_; uint8_t v___y_1100_; uint8_t v___y_1117_; float v___y_1124_; float v___y_1125_; float v___y_1139_; uint8_t v___y_1140_; float v___y_1155_; uint8_t v___y_1165_; uint32_t v___x_1179_; uint32_t v_a_1180_; uint32_t v___x_1181_; uint32_t v___x_1182_; uint32_t v___x_1183_; uint8_t v___x_1184_; 
v___x_1179_ = 2147483647;
v_a_1180_ = lean_uint32_land(v___y_1064_, v___x_1179_);
v___x_1181_ = 201326591;
v___x_1182_ = 1;
v___x_1183_ = lean_uint32_sub(v_a_1180_, v___x_1182_);
v___x_1184_ = lean_uint32_dec_le(v___x_1181_, v___x_1183_);
if (v___x_1184_ == 0)
{
v___y_1165_ = v___x_1184_;
goto v___jp_1164_;
}
else
{
uint32_t v___x_1185_; uint8_t v___x_1186_; 
v___x_1185_ = 2139095040;
v___x_1186_ = lean_uint32_dec_lt(v_a_1180_, v___x_1185_);
v___y_1165_ = v___x_1186_;
goto v___jp_1164_;
}
v___jp_1066_:
{
lean_object* v___x_1067_; lean_object* v___x_1068_; lean_object* v___x_1069_; uint32_t v___x_1070_; 
v___x_1067_ = lean_uint32_to_nat(v___y_1064_);
v___x_1068_ = lean_uint32_to_nat(v___y_1065_);
v___x_1069_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1067_, v___x_1068_);
v___x_1070_ = lean_uint32_of_nat(v___x_1069_);
lean_dec(v___x_1069_);
return v___x_1070_;
}
v___jp_1071_:
{
if (v___y_1072_ == 0)
{
goto v___jp_1066_;
}
else
{
uint32_t v___x_1073_; uint32_t v___x_1074_; 
v___x_1073_ = 4194304;
v___x_1074_ = lean_uint32_lor(v___y_1065_, v___x_1073_);
return v___x_1074_;
}
}
v___jp_1075_:
{
uint32_t v___x_1076_; uint32_t v___x_1077_; uint32_t v___x_1078_; uint32_t v___x_1079_; uint8_t v___x_1080_; 
v___x_1076_ = 23;
v___x_1077_ = lean_uint32_shift_right(v___y_1065_, v___x_1076_);
v___x_1078_ = 255;
v___x_1079_ = lean_uint32_land(v___x_1077_, v___x_1078_);
v___x_1080_ = lean_uint32_dec_eq(v___x_1079_, v___x_1078_);
if (v___x_1080_ == 0)
{
v___y_1072_ = v___x_1080_;
goto v___jp_1071_;
}
else
{
uint32_t v___x_1081_; uint32_t v___x_1082_; uint32_t v___x_1083_; uint8_t v___x_1084_; 
v___x_1081_ = 8388607;
v___x_1082_ = lean_uint32_land(v___y_1065_, v___x_1081_);
v___x_1083_ = 0;
v___x_1084_ = lean_uint32_dec_eq(v___x_1082_, v___x_1083_);
if (v___x_1084_ == 0)
{
v___y_1072_ = v___x_1080_;
goto v___jp_1071_;
}
else
{
goto v___jp_1066_;
}
}
}
v___jp_1085_:
{
if (v___y_1086_ == 0)
{
goto v___jp_1075_;
}
else
{
uint32_t v___x_1087_; uint32_t v___x_1088_; 
v___x_1087_ = 4194304;
v___x_1088_ = lean_uint32_lor(v___y_1064_, v___x_1087_);
return v___x_1088_;
}
}
v___jp_1089_:
{
uint32_t v___x_1090_; uint32_t v___x_1091_; uint32_t v___x_1092_; uint32_t v___x_1093_; uint8_t v___x_1094_; 
v___x_1090_ = 23;
v___x_1091_ = lean_uint32_shift_right(v___y_1064_, v___x_1090_);
v___x_1092_ = 255;
v___x_1093_ = lean_uint32_land(v___x_1091_, v___x_1092_);
v___x_1094_ = lean_uint32_dec_eq(v___x_1093_, v___x_1092_);
if (v___x_1094_ == 0)
{
v___y_1086_ = v___x_1094_;
goto v___jp_1085_;
}
else
{
uint32_t v___x_1095_; uint32_t v___x_1096_; uint32_t v___x_1097_; uint8_t v___x_1098_; 
v___x_1095_ = 8388607;
v___x_1096_ = lean_uint32_land(v___y_1064_, v___x_1095_);
v___x_1097_ = 0;
v___x_1098_ = lean_uint32_dec_eq(v___x_1096_, v___x_1097_);
if (v___x_1098_ == 0)
{
v___y_1086_ = v___x_1094_;
goto v___jp_1085_;
}
else
{
goto v___jp_1075_;
}
}
}
v___jp_1099_:
{
if (v___y_1100_ == 0)
{
goto v___jp_1089_;
}
else
{
uint32_t v___x_1101_; uint32_t v___x_1102_; uint32_t v___x_1103_; uint8_t v___x_1104_; 
v___x_1101_ = 4194304;
v___x_1102_ = lean_uint32_land(v___y_1065_, v___x_1101_);
v___x_1103_ = 0;
v___x_1104_ = lean_uint32_dec_eq(v___x_1102_, v___x_1103_);
if (v___x_1104_ == 0)
{
goto v___jp_1089_;
}
else
{
uint32_t v___x_1105_; 
v___x_1105_ = lean_uint32_lor(v___y_1065_, v___x_1101_);
return v___x_1105_;
}
}
}
v___jp_1106_:
{
uint32_t v___x_1107_; uint32_t v___x_1108_; uint32_t v___x_1109_; uint32_t v___x_1110_; uint8_t v___x_1111_; 
v___x_1107_ = 23;
v___x_1108_ = lean_uint32_shift_right(v___y_1065_, v___x_1107_);
v___x_1109_ = 255;
v___x_1110_ = lean_uint32_land(v___x_1108_, v___x_1109_);
v___x_1111_ = lean_uint32_dec_eq(v___x_1110_, v___x_1109_);
if (v___x_1111_ == 0)
{
v___y_1100_ = v___x_1111_;
goto v___jp_1099_;
}
else
{
uint32_t v___x_1112_; uint32_t v___x_1113_; uint32_t v___x_1114_; uint8_t v___x_1115_; 
v___x_1112_ = 8388607;
v___x_1113_ = lean_uint32_land(v___y_1065_, v___x_1112_);
v___x_1114_ = 0;
v___x_1115_ = lean_uint32_dec_eq(v___x_1113_, v___x_1114_);
if (v___x_1115_ == 0)
{
v___y_1100_ = v___x_1111_;
goto v___jp_1099_;
}
else
{
goto v___jp_1089_;
}
}
}
v___jp_1116_:
{
if (v___y_1117_ == 0)
{
goto v___jp_1106_;
}
else
{
uint32_t v___x_1118_; uint32_t v___x_1119_; uint32_t v___x_1120_; uint8_t v___x_1121_; 
v___x_1118_ = 4194304;
v___x_1119_ = lean_uint32_land(v___y_1064_, v___x_1118_);
v___x_1120_ = 0;
v___x_1121_ = lean_uint32_dec_eq(v___x_1119_, v___x_1120_);
if (v___x_1121_ == 0)
{
goto v___jp_1106_;
}
else
{
uint32_t v___x_1122_; 
v___x_1122_ = lean_uint32_lor(v___y_1064_, v___x_1118_);
return v___x_1122_;
}
}
}
v___jp_1123_:
{
float v_result_1126_; uint8_t v___x_1127_; 
v_result_1126_ = lean_float32_add(v___y_1124_, v___y_1125_);
v___x_1127_ = lean_float32_beq(v_result_1126_, v_result_1126_);
if (v___x_1127_ == 0)
{
uint32_t v___x_1128_; uint32_t v___x_1129_; uint32_t v___x_1130_; uint32_t v___x_1131_; uint8_t v___x_1132_; 
v___x_1128_ = 23;
v___x_1129_ = lean_uint32_shift_right(v___y_1064_, v___x_1128_);
v___x_1130_ = 255;
v___x_1131_ = lean_uint32_land(v___x_1129_, v___x_1130_);
v___x_1132_ = lean_uint32_dec_eq(v___x_1131_, v___x_1130_);
if (v___x_1132_ == 0)
{
v___y_1117_ = v___x_1132_;
goto v___jp_1116_;
}
else
{
uint32_t v___x_1133_; uint32_t v___x_1134_; uint32_t v___x_1135_; uint8_t v___x_1136_; 
v___x_1133_ = 8388607;
v___x_1134_ = lean_uint32_land(v___y_1064_, v___x_1133_);
v___x_1135_ = 0;
v___x_1136_ = lean_uint32_dec_eq(v___x_1134_, v___x_1135_);
if (v___x_1136_ == 0)
{
v___y_1117_ = v___x_1132_;
goto v___jp_1116_;
}
else
{
goto v___jp_1106_;
}
}
}
else
{
uint32_t v___x_1137_; 
v___x_1137_ = lean_float32_to_bits(v_result_1126_);
return v___x_1137_;
}
}
v___jp_1138_:
{
if (v___y_1140_ == 0)
{
float v___x_1141_; 
v___x_1141_ = lean_float32_of_bits(v___y_1065_);
v___y_1124_ = v___y_1139_;
v___y_1125_ = v___x_1141_;
goto v___jp_1123_;
}
else
{
uint32_t v___x_1142_; uint32_t v___x_1143_; uint32_t v___x_1144_; uint32_t v___x_1145_; float v___x_1146_; lean_object* v___x_1147_; uint32_t v___x_1148_; uint32_t v___x_1149_; lean_object* v___x_1150_; lean_object* v___x_1151_; float v___x_1152_; float v___x_1153_; 
v___x_1142_ = 8388607;
v___x_1143_ = lean_uint32_land(v___y_1065_, v___x_1142_);
v___x_1144_ = 8388608;
v___x_1145_ = lean_uint32_lor(v___x_1143_, v___x_1144_);
v___x_1146_ = lean_uint32_to_float32(v___x_1145_);
v___x_1147_ = lp_competition_R2W01b_scaleTable;
v___x_1148_ = 23;
v___x_1149_ = lean_uint32_shift_right(v___y_1065_, v___x_1148_);
v___x_1150_ = lean_uint32_to_nat(v___x_1149_);
v___x_1151_ = lean_array_fget_borrowed(v___x_1147_, v___x_1150_);
lean_dec(v___x_1150_);
v___x_1152_ = lean_unbox_float32(v___x_1151_);
v___x_1153_ = lean_float32_mul(v___x_1146_, v___x_1152_);
v___y_1124_ = v___y_1139_;
v___y_1125_ = v___x_1153_;
goto v___jp_1123_;
}
}
v___jp_1154_:
{
uint32_t v___x_1156_; uint32_t v_a_1157_; uint32_t v___x_1158_; uint32_t v___x_1159_; uint32_t v___x_1160_; uint8_t v___x_1161_; 
v___x_1156_ = 2147483647;
v_a_1157_ = lean_uint32_land(v___y_1065_, v___x_1156_);
v___x_1158_ = 201326591;
v___x_1159_ = 1;
v___x_1160_ = lean_uint32_sub(v_a_1157_, v___x_1159_);
v___x_1161_ = lean_uint32_dec_le(v___x_1158_, v___x_1160_);
if (v___x_1161_ == 0)
{
v___y_1139_ = v___y_1155_;
v___y_1140_ = v___x_1161_;
goto v___jp_1138_;
}
else
{
uint32_t v___x_1162_; uint8_t v___x_1163_; 
v___x_1162_ = 2139095040;
v___x_1163_ = lean_uint32_dec_lt(v_a_1157_, v___x_1162_);
v___y_1139_ = v___y_1155_;
v___y_1140_ = v___x_1163_;
goto v___jp_1138_;
}
}
v___jp_1164_:
{
if (v___y_1165_ == 0)
{
float v___x_1166_; 
v___x_1166_ = lean_float32_of_bits(v___y_1064_);
v___y_1155_ = v___x_1166_;
goto v___jp_1154_;
}
else
{
uint32_t v___x_1167_; uint32_t v___x_1168_; uint32_t v___x_1169_; uint32_t v___x_1170_; float v___x_1171_; lean_object* v___x_1172_; uint32_t v___x_1173_; uint32_t v___x_1174_; lean_object* v___x_1175_; lean_object* v___x_1176_; float v___x_1177_; float v___x_1178_; 
v___x_1167_ = 8388607;
v___x_1168_ = lean_uint32_land(v___y_1064_, v___x_1167_);
v___x_1169_ = 8388608;
v___x_1170_ = lean_uint32_lor(v___x_1168_, v___x_1169_);
v___x_1171_ = lean_uint32_to_float32(v___x_1170_);
v___x_1172_ = lp_competition_R2W01b_scaleTable;
v___x_1173_ = 23;
v___x_1174_ = lean_uint32_shift_right(v___y_1064_, v___x_1173_);
v___x_1175_ = lean_uint32_to_nat(v___x_1174_);
v___x_1176_ = lean_array_fget_borrowed(v___x_1172_, v___x_1175_);
lean_dec(v___x_1175_);
v___x_1177_ = lean_unbox_float32(v___x_1176_);
v___x_1178_ = lean_float32_mul(v___x_1171_, v___x_1177_);
v___y_1155_ = v___x_1178_;
goto v___jp_1154_;
}
}
}
}
