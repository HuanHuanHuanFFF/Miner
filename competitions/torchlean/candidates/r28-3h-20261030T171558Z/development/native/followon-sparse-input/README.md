# 下一轮稀疏输入接口，非本轮新增候选

本目录在CI6隔离后独立建立，只用冻结前的源36边界、旧模型及通用word算术。未读CI6计划种子、输入或中途结果。当前角色入口仍是父目录READY/HANDOFF；不派发CI。

动机是两个已收结果：额外逐值cache/post-correction可压过删MAC（CI3 centered负）；直接随机零分支也可慢（CI4 Mobile消费者负，因果未定）。当前29e原型保留原路径、只在有零调用分支，已冻结不改。这里探索下一轮让零项消费者尽量不用逐项数据分支，不把同一零恒等式当成功概率。

另行验证输入行自身有限且`rowSpan<=15`后，其对齐系数严格`|a|<2^(24+15)=2^39`；原inW<2^20。用一个Nat记录`((a+2^39)<<20)|index`，值<2^60，因此没有每值tuple或单独index数组的必要。不能只凭原联合dot-span门槛推出该输入行界：全零权重与bias可让联合span为0，而输入行仍很宽；原始word反例在模型回执。宽行须原路回退，不能悄悄加强全输入前提。

非零输入按索引顺序存储；每个output沿该row支撑遍历，从原prepared W按index读取。两个row可分别处理：约半零时，逻辑W读总量约等于旧双行共享W，但乘加可减半；失去双行ILP、索引gather、准备/析构、标量loop依赖都可能抵消收益。

它属于仓库既有support/CSR打包族，不声称新颖或独立成功机会。与ResNet packed-support的具体producer、位宽、cache/caller不同；这里只保留源36 39bit+20bit的接口，未移植旧性能/证明。

`PackedInput.lean`仅未编译算术草稿；Python模型检查packet反解、小值范围、保持次序的零项省略与原signed128状态相同，保留缺index/系数边界的明确反例。不是完整模型的Native输出、Lean验收或速度。

最低下一步先构造一个一次准备、无额外逐值packet对象的完整线性入口成本原型，与原norm26/29e按同一完整边界比较。只有正成本才证明实际producer长度/索引、getters、filter保持dot、原bias/zero-sentinel、caller和全12；NativeOnly字节数不证明恢复后≤256000B。新候选另用新确认组。
