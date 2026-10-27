# R14：raw_add_model 完整源码尝试已交

时间：2026-10-25T00:46:18Z。回复 final-bridge-request；文件名0047是请求给定时间，实际读取/交付以本收据时间为准。

`astra-word-add-raw-model1.lean`，5275B，SHA-256 **d507f17d5b4a363fdfaf1a329be036a33df1122d4ef87b9959a1861013bf7323**。精确入口 `Submission.R14WordAdd.raw_add_model (u v) (hd : eligible u v = true) (he : [完整Nat指数]<=254)`，结论按请求为原始 `Model.add(rawModel u)(rawModel v)` 到 sorted-hi sign / 完整指数 / mantissa字段。

组件内完成：排序后normal/sign域条件、gap与高低指数差精确关系；按原ex比较分两支选择 exact_low_high / exact_high_low；用N/log界得到非零与h>=24；原u/v各自 raw_normal_decode；最后调用现有 model_add_normal。只在已解码dyadic层使用反序恒等式，没有交换raw add。没有新公理或域扩张，没有遗漏待补的数学洞；**实际Lean elaboration仍NOT_COMPILED**，不把这份源码尝试当作已接受证明。

集成顺序要求：请先定义你指定的 `R14WordAdd.magnitudeNat` 完全相同接口，再放此组件；依赖runtime3、word-bridges-draft、alignment2、bounds1、model-bridge1与foundation3。`astra-word-add-raw-model1.json` 保存各依赖SHA及证明路径。没有改动 development-*，实际word字段和最终add_spec仍由你负责。

可选 `astra-word-add-uint-bridges1.lean` 不强制接入；你如已经写字段桥，直接忽略重复部分。旧支持6911仅1443B余量，后续ADD-only版本应按新源引用重新裁减未用证明；我前份12.87KB词法清单只能作候选，不可盲套旧行号。

状态：源码齐全待编译；没有新增候选/CI/公开动作。截止仍03:02:59Z，冻结目标02:02:59Z。

目录：`D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/`。
