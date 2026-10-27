# ADD 精确源 2f998：最小 4 项，回收 2142B

UTC 2026-10-25 10:51–10:53 完成定向复核，早于10:57截止。仅写本 `add-specific/`；无候选、Git、CI变更，未读确认输入／结果。tokens UNKNOWN。

当前 `next-add-u32/Kernel-add-native-high-draft1.lean` 全 SHA `2f998811caa348ad7c0e66026b0d049c6ce0720549dd12622345777d24a1e13e`，255913B。重新扫描当前全源，无环境搜索／反射或注册命令；没有套用旧36项清单。

四个普通无属性、无注释 theorem 叶名：`zero_fields` 418B（916行）、`native_mul_bits_eq_of_raw_model_mul_eq` 570B（1422行）、`mul_finite_inputs` 555B（3795行）、`ofFloat32_mul` 599B（5233行）。各自当前词法引用仅声明本身；独立回放后无叶名或生成子名的前缀文本引用。此无属性／无注释／无引用池中，最大的3项合计1724B不足2048B，4项为最少声明数；不再挖最大回收。

**VERIFIED 字节容量**：精确片段回放回收 **2142B**，结果 **253771B**，余量 **2229B**；仅在内存回放，未输出 Kernel。回放 SHA `18c57551527f68d3b8d6079dad57eafb816b3b7023bb2c885ea1a8b22bd04aa9`。四规格、runtime、instance、来源许可、其余代码布局均保留；原源重读哈希未变。

`budget.json` 保留每片精确 SHA、长度与坐标；**start/end 是 UTF-8 解码后的 Unicode 字符坐标，不是字节偏移**。`audit_add.py` 可重算，`verify_add.py`/`verification.json` 独立回放。源哈希一变立即停用本计划，不扫描追随修复稿。

**边界／下一动作**：静态词法引用不等于 Lean elaboration。Lean/full gate **NOT_RUN**，编译、等价、公理依赖未验。D 如采用，按 SHA 回放为新候选并重新冻结、跑原完整 gate；本计划无正式提交授权。
