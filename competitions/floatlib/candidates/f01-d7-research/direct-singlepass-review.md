# cc06 direct + single-pass sum独立源审查

开始2026-10-23 02:32:31 UTC，约15分钟。审查者未编写3d9 single-pass sum、97f的DirectSmall/BMM末段或本次builder/组合；此前做过相关静态审查。本稿不含本人此前独立的seed-normalize/singleton/LowZero片段。只写本报告及同名JSON，未执行writing builder、Lean、Git、CI或上传，未改源/manifest/R目录。

**未发现确定的新接线或作用域bug。独立切片逆变换完整恢复3d9；DirectSmall正文与97f、已验60f逐字相同。精确cc06的Lean/公理/完整gate/C/性能仍NOT_RUN，gain UNKNOWN。**

## 精确来源与逆变换

| 原始候选 | bytes | SHA-256 |
|---|---:|---|
| [组合cc06](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-singlepass/Kernel.lean) | 232363 | `cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc` |
| 3d9 sum父本 | 230650 | `3d9b1ea94ec105073334b793adcb5a9fecc4eda37dd2a5809e715b5584a54576` |
| 97f direct父本 | 174925 | `97f77e2ce3f53dc3625349d5d2a7bc761570f9428c0b547070e37254c4960d26` |
| 0e8共同基座 | 173212 | `0e8bc05ce954e3e8213fbef05ac6041f8f882673c88c1071a3c9d4254a3064cd` |
| 60f DirectSmall来源 | 155103 | `60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15` |

本审查没有运行builder的replace/写盘逻辑。独立定位0e8末尾完整BMM块，从byte offset172397开始，815字节/SHA `49ecf286b9a84d9a653e18184952da36a9952313f9af6d5f077f0869a9ddbb9b`。该块在3d9中仅出现一次，offset221509。97f在原offset172397之前与0e8全部相同，之后2528字节为replacement，SHA `773200a8f9e323c2c99d2533be9f0a8a3c598da69851dcd5c499364dec3bc45d`。

cc06的replacement在offset221509仅出现一次。通过前段+旧块+后段的**切片重建**得到完整3d9及其SHA；替换区外每个字节相同。净增加1713字节，与manifest、`len(3d9)+len(97f)-len(0e8)`一致。builder SHA `9cc063c3925abca7b7159c01ca9198f49fcad422e854d2320ac7fb61ad9fb794`，其固定三源/唯一锚点/逆变换断言与实际产物一致；未执行它。

## 导出、作用域与规格接口

屏蔽comment后做轻量named namespace/section清点，结束配对完整；这不是Lean parser或elaboration。顶层Submission四个导出及四spec各仅一份：

| 导出/spec | cc06行 | 实际接线 |
|---|---:|---|
| add / add_spec | 2741 / 2747 | 原3d9 scalar字节保留 |
| mul / mul_spec | 2972 / 2977 | 原3d9 scalar字节保留 |
| bmm / bmm_spec | 6047 / 6052 | 完整97f末段，见下述两支 |
| sum / sum_spec | 6272 / 6274 | `R7SinglePassSum.run / run_spec`，原3d9后缀保留 |

旧sum仍命名`sumBeforeR7SinglePass`（5839），不冲突。旧BMM被明确改名`bmmPackedBase/bmmPackedBase_spec`（5992/5998）；DirectSmall在6015–6041单独开闭namespace；新BMM在6043重新打开Submission，6062关闭；原单遍sum随后6065重新打开Submission，末尾6276关闭。没有把R7SinglePassSum误放进DirectSmall或新增export遮蔽。

新BMM保持97f已准备路线：`n≤4 ∨ p≤2`时`DirectSmall.core`，否则`bmmPackedBase`。其完整all-Nat四维spec在直接支用`core_eq_reference`再接`referenceBmm_spec`，另一支用`bmmPackedBase_spec`。没有新增形状前提、seed/值分布派发或变化地址。n=0经direct空fold返回+0，空输出为empty Vector.ofFn；这些是继承证明应覆盖的全域情况，不是本轮新Lean验收。

sum的`run_spec`仍经原USize/Nat等式与`natLoop_eq`连接到全`sumSpec x.get`；新BMM声明不被sum调用。最后包括整个R7SinglePassSum namespace、run_spec及sum导出的8324字节后缀逐字同3d9，SHA `3cadbc0cf1ea21c21cabaec31b88f813564bda2aa89ee2ae6e0c76aee031618d`。既有singlepass新循环证明的未编译缺项未由组合消除。

## DirectSmall相同与依赖不同的边界

完整`namespace Submission.DirectSmall`块973字节/SHA `505b4d77333da4bbb0e31ff3b89330ac0e6f80171d1649d8a8b257323e1d17eb`，与97f、60f逐字相同。第6023行仍按reference的bmmDecodeC地址调用`NativeFinal.dot`；第6033行使用其完整fold等式，之后add_eq/mul_eq与index_address桥保持原正文。

但不能据此说整条运行路径等于已验60f：

- `NativeFinal.dotLoop`与0e8、97f、3d9、60f都相同，保留顺序native乘加。
- `NativeFinal.dot`（5149）及`dot_eq`（5154）与0e8、97f、3d9逐字相同，**与60f不同**。NaN冷支走继承的`R7NaNReplay.replayEarly`（5152）；这不是本次组合新增，但属于确切新候选仍需验收的依赖。

因此本次没有新的runtime算法/证明正文，但将direct dispatch置于3d9/0e8现有依赖上；已验60f仅支持复制块来源，不能代替精确97f、3d9或cc06的完整gate/计时。原两路线收益也不能相乘或直接相加。

## 大小、许可和实际未测项

232363≤256000，余量23637字节，**未使用source-budget或删除任何注释**。被替换的815字节块及新2528字节块均无comment spans；所有原3d9许可/copyright/attribution均在逐字保留的区外，未发生此前打包工具的通知删除问题。新尾完整复制97f，没有重新归属其作者。

唯一import仍为ContractTensor，无set_option。固定4b7原policy/options对精确cc06重新执行PASS_STATIC_ONLY；官方原源SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`。这仅证明静态规则，不证明四spec接受或任何运行行为。

下一判别仍是精确cc06 statement及原四义务/公理，尤其继承3d9循环与0e8 early-replay依赖；之后才是原完整public-v2配对边界和无observer的独立确认。此审查不创建新变体，不对未运行的C、性能、准入或排名作成功声明。
