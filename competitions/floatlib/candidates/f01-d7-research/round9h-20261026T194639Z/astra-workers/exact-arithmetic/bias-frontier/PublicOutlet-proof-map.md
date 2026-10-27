# DirectBias 公共出口证明依赖与失败定位

状态：纸面审核 + 精确源码映射，所有新数学声明 NOT_RUN。首选完整源 fa6529… / 模块接口 2177e7…；逐声明行号见 public-source-map.json。没有新有限抽样，已有50,004实际尾数对模型证据不替代证明。

1. **seed → PostBias**：旧 quotient_bias/nat_bias/nat_grouped_bias 给 literal23/24偏置商；PostBias 分 P<2^47/≥2^47恢复 posth/newq。唯一尚有实际资源疑点的最早依赖仍未定位，ImportOnly→QuotientOnly 先行；7b03未并入。
2. **WordBias 六根**：偏置和、high、最终shift、q 的无回卷 word→Nat。P<=281474943156225使B<=281474951544833<2^48，high<=1，最终shift23/24<64，q<2^24，UInt32转换无模截断。
3. **FastMulBoundary**：P>=2^46给L46/47；S128..380给position=L+S−2>=172。L47不进位（最大商<=16777214，RNE最多+1），故normalizedPosition<=425。消去原roundP的零/次正规/超界分支。
4. **TypedOutlet**：new high=L−46+carry；new q=旧normalizedMantissa；E=S−127+high=normalizedPosition−171；q−2^23=旧fracW。新E<=254且fraction<2^23，mkW掩码可删除。review1只将内层high的mod重写目标指定，避免外层先匹配。
5. **PublicOutlet**：实参product bounds由24bit尾数界乘得，有限尾数/scale由实际exp提取证明；guard的UInt32减法按模2^32证明接受范围，不能假设减法是Nat。正常条件排e0/255，S范围既排本路低值也排溢出；域外保留原B2。signBit单独经BitVec bit31同构，载体fromRaw/ofBits经toModel注入；最后复用FastMul.mul_spec。

全输入义务仍在guardedMul_spec(x,y)中实际消去guard；没有将范围/规格作为新公理、没有新的模型乘法假设。namespace改名只在完整候选，数学模块保留Submission以导入精确B2。四官方根及全部新显式定理根由清单生成；不能用模块接口通过代替完整候选重放或实际public计时。
