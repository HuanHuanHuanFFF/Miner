# 十分钟内判别：compactScales成本前提

UTC 2026-10-26 22:41（接手22:35:02，20分钟上限22:55:02）。仅本目录写；无CI/Lean/Git，未读未来compact完整D/holdout。

- 实际MainFull ADD lambda0/MUL lambda3均选中compact分支：ASM每个fastOK hit是`movsd [table+index*8+0x18]` + `cvtsd2ss`，不是boxed entry pointer再取Float32。C闭包绑定lambda0为ADD、suite lambda3为MUL。
- ADD每次1个global valid检查；MUL native路径1次，LowScale(ex+ey<128)在ASM先分支，0次。不是每个operand重复检查。原boxed-table false arm和NaN/LowScale fallback都还在。
- MainFull生成C没有FloatArray.data；Submission.c有4个proof splitter materialization函数，不能宣称全文件不存在，但未见选中链引用。
- packed与valid在Submission模块init赋值，MainFull的C main先初始化再运行bench。C明确有512-entry map和all-check循环、once cell与模块guard；只能说每process一次，不能说整个25轮gate只有一次。初始化ASM未被这批捕获，不能从true/512宣称native恰好执行512次检查。

倾向：成本前提成立到足以支持一次首完整D；新增flag/转换与移除boxed dependent load之间的收益仍UNKNOWN，不预排A/B。正在完成88原件重哈希、控制版本及JSON/短MD回执。
