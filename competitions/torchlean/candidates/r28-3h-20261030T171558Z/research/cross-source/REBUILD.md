# 重建与验收边界

当前权威入口是[HANDOFF.md](HANDOFF.md)。[交付核验](DELIVERY-ARTIFACT-AUDIT.json)
已把8个配方用本地固定输入重建并逐字比较；这不是新的Lean或原生测试。

所有源重建需要私有保存的完整公开36字节，SHA-256为
`595a90fa2b6bc5d3657434fae7d1292b27910ef653da2b7f409ed9c34c956e2b`。
这些配方不发布该完整源。使用每个脚本的CLI时，把输出和新重建回执写入忽略的
`private/`，不要覆盖历史创建回执。

| 目标 | 配方 | 当前验收 |
|---|---|---|
| norm26 `79615bd5` | `build_norm26_36.py` | CI3原all12通过；探索成本0.94444×36；标准确认另看Droot |
| centered64 `c5acf195` | `build_centered64_cost.py` | 原生全成本负；无correct，停止主投入 |
| singleton `578f374c` | `build_single_row36.py` | 仅源码/有限模型，未编译，低优先 |
| pairlinear+norm26 `3d59846e` | `build_pairlinear_norm26.py` | 未编译；paired组件已负，保留不排队 |
| wide singleton54 `8de73c86` | `build_wide_singleton54_cost.py` | 未编译NativeOnly；同offset家族的新producer域，未排队 |
| checked norm quotient `acd6bb86` | `build_checked_norm_division_cost.py` | 未编译NativeOnly；严格HOLD，未排队 |

`build_centered64_cost.py`、wide、checked-division、composition脚本有同目录模块依赖。
直接运行CLI会按Python规则加入脚本目录；若用`importlib`加载`transform`，须由
加载器把配方所在目录加入`sys.path`，或采用Droot CI3的固定适配器。不要为适配
入口改动冻结候选字节。各receipt列有精确依赖哈希。

composition还需要公开27的固定原件及native目录的冻结pairlinear v1/v2脚本。
wide的`transform`不需要完整54源；它的CLI创建来源回执时会核对本地保存的54原件。
较早的centered61/linear-only与零B重复原型只作历史，不能与实际C5或native7100
混为同一精确版本。

有限模型使用旧R26根26102901及已保存原生request/measurement；完整路径和哈希
写在各JSON。36 cells/90 samples重放同时匹配旧reference与candidate两列；该组
始终是旧已见材料，不是新确认。CI6标准组的输入、种子和中途结果未被本角色读取。

`CenteredArithmetic.lean`、`MetadataRange36.lean.inc`仍是未编译的自写证明草稿。
本目录8个配方中只有精确79615bd5拥有当前原始all12 PASS回执；不要把源码中的`correct`声明、
Python重建或有限字模型当作其他候选的门禁通过。
