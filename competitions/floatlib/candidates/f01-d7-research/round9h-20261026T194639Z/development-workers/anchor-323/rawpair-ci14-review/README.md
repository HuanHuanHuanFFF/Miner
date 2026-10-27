# CI14：保留证明源，暂不晋级完整D

**75原件SHA、精确6a0c18c5/235456B、statement、Submission+VerifyFull完整重放及14根审计均通过核验；未取得新计时。** 完整D/采用仍NOT_RUN。

真实C链从MainFull的public bmm闭包，经B2/B1 miss及原DC guard进入RawPair，最终为output→专化row(spec3)→pair(spec2)→loop。每完整pair一次loop，共享一次A读取/转换、三次原of_bits，两条有序mul/add；同一个终态F2供两列读取，emit后释放。selected路径无新动态apply/closure/Float32 box，无正常pair旧dot重算；原UInt32输出box、getD/Nat后备、NaN finish/replay保留。基址和row/m在每行计算一次；odd尾只跑一次旧dot。导出的groupFrom虽含闭包，却不是selected C路径，不能据此误判。

**机器成本前提仍未闭合。** native-loop6只有导出RawPair.loop，无实际pair caller或旧NativeFinal.dotLoop ASM，且未带relocation。新导出loop有6个push、0xa8栈帧及A/B0/双acc三组16B保存重载；无法判断相对旧loop的spill增减，也不能排除clang在caller内inline/clone。原codec目标只能由C及调用顺序推断，不把helper ASM冒充实际caller。

下一已有空余statement槽只需同6a0c的原`Submission.c.o.export`，按原编译flags直接`objdump -dr`采：

```text
lp_competition_Submission_NativeFinal_dotLoop
lp_competition_Submission_R19DCRawPair_loop
lp_competition_Fin_foldl_loop___at___00Submission_R19DCRawPair_output_spec__2
```

旧NativeFinal namespace与622d原字节相同，旧/new函数已同在此源，勿加hot wrapper或另编C。当前selector的Submission前缀loop白名单含RawPair/Packed等而不含NativeFinal；Fin专化caller又不满足Submission前缀，且工具用`-d`而非`-dr`，故丢失上述关键证据。可选row/spec3、emit/spec0、odd/spec1完整符号见review.json。

原已见计划影响域约5.98%whole，达到3%whole需约50.18%完整局部节省；少一次codec调用不是速度估计。建议依原停止条件暂缓完整D，先补上述已有对象采证；与高上限路线争CI槽时停放。原object哈希d9f3358e、C e43e059e、MainFull C94f69ed1；完整原件、flags、根名单、链路及精确hash见review.json/all-originals.json和receipt.json。无Git/CI/本机Lean、候选或全局修改。
