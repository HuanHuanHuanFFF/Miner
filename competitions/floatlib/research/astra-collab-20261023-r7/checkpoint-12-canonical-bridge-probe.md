# R7检查点12：全输入canonical桥与首次事件quiet证明

2026-10-22 20:41 UTC。W05已实际完成并回收，现有组合/守卫/prefix的验证优先级不变。新增一份**仅statement的数学桥探针**，不增加未测运行变体。

## 真正更强的数学结论

W05实际证明全部原始Binary32输入的加法、乘法满足`toFloat32 (ExecFloat.op x y) = nativeOp (toFloat32 x) (toFloat32 y)`。这里是canonical Float32等式，NaN原始sign/payload从来不能经这一转换直接取回。具体NaN选择、quiet、codec和native非NaN桥均闭合，且原始Model/ExecFloat输出isNaN与native输出isNaN是完整Bool等式，不只一个方向。

因此，从任意native累加器转换回carrier再执行一个真实原始步骤，只要下一native结果为NaN，修复结果就实际为quiet NaN。`repairSumStep_isQNaN`/`repairDotStep_isQNaN`本身只需事件条件；若还要说明它等于此前原始参考前缀对应的步骤，仍必须有前缀匹配且事件前acc非NaN。普通sum后缀依然保留later sNaN替换。网页完整文件另接了原sumSpec/bmmSpec的canonical投影和有序前缀，但尚未实现完整事件调度Kernel。

## 原件与本地接入探针

E盘ZIP `R7-W05.zip`，511201字节，SHA `4acea8340e30e3e846f80552fd475ec73e05bea8c515e8cdae3c51c481e27489`；报告SHA `97c3e7f4c773954abd6ff15e893d1fe85585e94db9e8d178fe7d8e433bccce3e`。CRC/135条manifest通过。完整主源7ebaf282，Append SHA `1834ecafc62a464f54805befdc9b60e2a3e54b1f8102fb0bf47f854c94f6ad6e`，106166字节；网页实际编译和206声明/180定理公理审计通过，含唯一历史Lean失败。无运行计时，性能UNKNOWN。

为避免重复106KB缓存证明，本地只提取新的具体桥至两个repair-isQNaN定理，复用已有精确已验c760 native桥、9a2全局NaN helper和W03最小add-not-signaling证明。生成`f01-r7-canonical-bridge-probe-policy1/Kernel.lean`：

- SHA256 **a4f26514082e3d35738d253207db9f3127ca16de20e55fc6ac54d075710297a9**，193261字节。
- **NOT_RUN_POLICY_SPELLING_REPAIR，statement-only**。原四个运行kernel完全保留c760定义，不依赖失败b169或新prefix源码。
- 只需在方便的验证槽检查新增声明及原四项义务；不将probe的statement或网页compile称作新性能结果。

首个未交接e7bdae87稿被本地原版policy正则拒绝：网页位向量宽度推断写法`#_`被视为禁止命令标记。保留该源码和`canonical-prepolicy-failure.json`，新policy1仅将binary32 exponent/mantissa字面量显式写成`-1#8`/`0#23`；数学位宽不变。`canonical-probe-policycheck.json`静态PASS。历史e7仍会使默认全目录precheck报错，因此后续对准备交接的精确候选使用`--candidate <name>`，不要删除或隐藏这个负结果。

新增声明在`Submission.R7W03`和`Submission.R7W05`，可复用片段`add-nonsignaling-block.lean`、`canonical-native-block.lean`；后者已采用显式位宽，推断宽度原派生片段另留`.prepolicy.lean`。映射和具体原SHA均在manifest。

在此probe真正编译通过以及prefix候选闭合前，不生成删除guard/coldfallback的下一运行稿。W06仍于第二网页独立检查循环上下文代码生成；主网页已保留为完成交付页。
