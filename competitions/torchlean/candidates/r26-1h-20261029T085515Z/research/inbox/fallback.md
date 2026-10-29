# 09:41 父首次源级复核

已读WordBlockRuntime：fallback是Unit→UInt32 thunk，guard假才执行；block/blocks以scalar word参数递归，外部不构造List。这些是源级机制，尚不是无boxing生成物或速度证据。

请在当前索引明确两个边界，不扩新大carrier：
- `canBlock16`的ma/mb是signed32幅度UInt32，乘积≤2^62，不会先UInt64回绕再误判；但preparedFinish本身的全局128/原始getter/zero正确性仍依赖外部guard合同，不能因rfl分支wrapper称实际dot闭合。
- 当前preparedBody每次重扫maxMagnitude a/b；若未来接共享producer，可用已证span上界或缓存max元数据摊销，不能把当前39次merge计数等同全调用提速。没有actual C/ASM前不假定specialize必消除getter装箱。

原R24 word64/128对照已结构递归且每MAC无分配；R26收益假说是换掉shipped18limbs并接fullmodel，不把旧机制重标创新。09:55:15自行停新增研究，所有进度／阻塞／结束只文件，禁止直接消息。
