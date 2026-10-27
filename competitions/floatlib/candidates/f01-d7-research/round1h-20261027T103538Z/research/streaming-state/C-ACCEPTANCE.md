# Actual caller成本判别清单（不是已观察结果）

精确冻结源以v2/4e36为准；v1/5bbf只有emit_size编译错误，没有新C或性能。不能用导出updateCell、通用storageLoop或旧B2 MainFull替代此新调用。

应从实际compiled `streamedPair → streamedRows → loop → advance`追踪到Array.mapIdx的实际专化循环，并同时追`controlPair → controlRows → NativeFinal.dot`。pair入口含Array.mkEmpty、replicate、全部k、两次row-major finish、输出Array和state生命周期。四公开算法仍B2；本诊断只完整两行，不能报告新publicBMM或继承正式#336。

| 要核的对象 | 当前源级前提 | 能改变决定的实际证据 |
|---|---|---|
| map运行边界 | safe mapIdx→mapIdxM→原mapFinIdxM，未改变库属性 | 实际走USize清洞后端而非proof参考push实现；只看源名字不够 |
| 旧state别名 | callback只用传入cell，捕获a0/a1、Braw、rowB，不get旧state | actual closure捕获/RC是否仍保留旧Array；每k是否复制整state |
| 第一遍 | replicate各槽共享同一个zero Cell，可能persistent | 不把它算成p个独占对象；记录首k实际Cell分配与数组行为 |
| steady Cell更新 | 清洞只在if possible时使Cell无共享 | 真正callback是否做CtorReuse、是否每slot新alloc、谁持有额外Cell引用 |
| slot与对象处理 | 原后端两次slot替换，数组/元素RC与COW检查 | 有多少实际store/check、哪些被消掉；不能从源码站点直接换周期 |
| closure及FP活跃值 | a0/a1需跨p次B转换使用 | 每k或每slot是否alloc closure/box Float32、是否dynamic apply、FPspill与读取布局 |
| 终端/异常 | 两遍原Packed10.finish，NaN时原raw replay | 真实selected writer、有无dot重算、完整state释放及output析构；不能把UInt32即时值当heapbox |

未打包DC的同batch两行源级raw-A/B codec数量：原独立dot=4np；streamed=n(p+2)。算术均为2np乘和2np加，每个输出k序不变。这里不包含zero闭合值初始化或finish codec，不是速度预测；也不适用于原B2/Packed10已经缓存B的路线。

本源码没有在n0时跳过replicate；p0直接返回out。奇行和多batch的完整公共运输不在冻结pair源中。隔离MatrixDriver只作为后继运行壳：batch内m/2对＋原odd行，controlOutput是全形状DC，不是保留B2完整路由成本。

停止条件：若actual caller每k整表COW或每slot持续Cell/closure分配且没有足够原工作删除，停止这份表示，不用阈值/seed追分。若实际复用且确实减少调用/生命周期工作，先测包含全部准备、首k、steady、finish和析构的完整调用，再讨论public路由、完整gate与新确认。当前所有这类机器结论UNKNOWN。
