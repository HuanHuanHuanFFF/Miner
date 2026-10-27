# 表示路线：当前可证边界与投入排序

R续窗22:58:21Z—02:28:21Z；D原授权窗不变。本阶段先查机制，未生成任何新候选、未本机编译、未派CI。

| 路线 | 已核实的可去工作／收益上界 | 桥接及新增成本 | 决定 |
|---|---|---|---|
| 9c4e连续静态表 | 实际MainFull每命中scale读少一层boxed pointer依赖；不是少一次完整decoder。首完整D whole/B2=1.029671，p05−0.045627，ADD1.028807/MUL1.044535 | checked512常量桥已通过；两narrow、globalvalid判断、原codec/guards/fallback，以及常驻中间boxed Float64数组均保留 | **同源停放，无A/B、无换seed**。55原件复核见compact-cost-40417039536 |
| 把valid移至函数值初始化 | 最多针对每native scalar一次flag读/比较/分支；其耗时份额UNKNOWN，不能给有意义的整包加速上界 | 固定ToDecl对函数型声明前后eta-expand；数据record投影得到函数后，LambdaLifting只收缩直接const全参数转发，无法据此保证消除额外wrapper/apply。macro_inline不在官方属性白名单 | **不造包装候选**。最小合法无额外调用路径未建立；不是用noinline/inline试网格 |
| 保持Double做ADD/MUL再窄化 | 48bit乘积可精确容纳，不等于实际Float.toFloat32语义已证明；ADD双舍入还另需证明 | 固定4.34两跨宽cast仍opaque；旧FloatLib同宽桥和模型量化不能证明该native窄化。9c4e只check512静态常量，不能外推任意运算结果 | **旧硬障碍未解除，停止Double支**，不做RNE大证明或性能候选 |
| 换Float32模型字段投影以绕过toBits | 固定Float32.toModel/ofModel与toBits/ofBits对应相同runtime extern边界；未提供核心工作删除 | 只是改变拼写，允许接口未提供更廉价bit reinterpret路径 | 停放，不复测等价源码 |

冻结模型ADD36.56%/MUL38.72%只用于投入量级，不是valid/decoder阶段耗时；不能把它们相加当作可实现收益。没有真实阶段占比与可信降耗，数值“上界”只能标UNKNOWN。已观察9c4e负结果不能被静态工作量假设覆盖。

最短primary定位：`primary/ToDecl.lean:158–175`的eta展开；`primary/LambdaLifting.lean:125–139`只匹配直接const；`primary/Passes.lean`显示lambdaLifting早于extractClosed；`primary/gate-4b7.py:198–206`属性白名单；固定Float32源码548/555仍是opaque。12份原作者源共148020B已按Git blob逐字核验，`primary/source-index.json`绑定URL/commit/hash，都是证据副本，未修改编译器或gate。函数包装性能仍未测，此处是先决条件不足的停放，不是宣称所有可能表示都不可能。

重访只接受新的允许语义桥、或实际selected MainFull证明**无额外apply/boxing**的合法一次选择路径；不据可选属性重新开同源。下一阶段按根的新20min GRS ADD请求做最短运行机制/历史负例证伪；DirectBias与既有证明队列仍优先。
