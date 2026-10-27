# CI13真实成本复核

结论：**停放精确748999运行体，当前成本证据不支持继续购买昂贵public MUL证明。** 这不证明其算术机制必然慢；只说明当前实现、当前诊断形态未给出充分正收益证据。本任务未Git/CI/Lean，未改候选、Harness或范围外文件。

`review.py`独立解析原log，不调用原driver/原parser；重算8次全部156唯一行、152正ns timed行及4零ns非timed行，对照派生rows、同seed四次checksum、metadata环境和四项/whole守恒均通过。CI13的121原件逐字节SHA全部核过，绑定见`all-originals.json`；head为93fe24bf105ed11fd5e56f262adef82be9129b44。

| 已见seed / block | MUL guarded/control | whole guarded/control | SUM guarded/control |
|---|---:|---:|---:|
| 1927003 / 0 | 1.017893301 | 1.000853380 | 0.998743376 |
| 1927003 / 1 | 1.136068921 | 1.085395764 | 1.221797973 |
| 1927005 / 0 | 1.024996980 | 1.010710488 | 1.010619246 |
| 1927005 / 1 | 0.980539722 | 0.990035177 | 1.014730631 |

所有8次样本和全部608个timed case pair均保留在`raw-recomputed.json`，未过滤seed3 block1。其MUL增加8,466,070ns、SUM增加3,358,008ns；共享同一SUM函数却出现明显波动，说明“全是新MUL算法差异”的解释不成立，但具体成因UNKNOWN，不能删除该block。四block描述性总和：MUL255,138,525 / 245,298,729 = 1.040113522，whole680,428,850 / 665,771,113 = 1.022016181；不是原gate分数、跨runner稳定性或成功概率。

真实选择链已核：C中的BENCH_VARIANT=control进入`main___lam__3___boxed`，guarded进入`main___lam__1___boxed`；ADD/SUM/BMM引用完全相同的闭包常量。guarded lambda1直接含guardedMul及normalCore整数逻辑；caller C无diagnosticEntry引用，也不通过独立r19CostGuardedMul符号再加一层hot call。eu、ev在1..254且和在128..380时，ASM路径0→76→122→33d→c06（十六进制）无call/FP/table/临时栈访存。**整个函数并非无call/spill**：原B2 fallback仍含FP/table/call和临时spill；两侧均有5个保存寄存器push及16B栈框架，boxed wrapper也有一层相同typed call。

重要局限：新Main两侧MUL均是arity3、固定捕获一个variant比较得到的true Bool，typed签名`(uint8,x,y)`；原statement MainFull MUL为arity2静态闭包`(x,y)`。两侧新wrapper逐指令相同，但原statement MUL326条静态指令与Harness control345条并不相同。一次variant读取/closure分配在Suite计时外，共同captured参数的unbox/ABI和寄存器分配仍影响scalar调用。故不能把诊断control称为原MainFull绝对成本。58条正常快速路径也不能换算速度。

实际compile22参数、link4参数、rsp4156参数独立比对，只有MainFull→R19RuntimeCostMain及benchFull→r19RuntimeCost路径映射，其他flags、顺序和输入相同；-O3、ffp-contract=off、原export配置保留。新目标构建9.6365s，仅观察3个自有Built目标；8230是Lake总job计数，不是8230个重新构建。原lakefile3864字节前缀SHA吻合。source748999、caller78123、C24770、ASM0d85及对象/binary身份完整在JSON。

可本地独立重核的是保留下来的source/C/trace/rsp原字节；原object/binary before-after不变为远端成功断言，ELF未导出，不能在本地再逐字节复核。测量的是新binary0be26877内两分支；单独statement的benchFull b8f8b3a6未在这8次内计时，原MainFull对象7ab23795与新对象9a8e527a分列。保持原4GiB build/512MiB bench、CPU0；实际entry remaining记录为864→834秒，不能声称实际外层entry预算等于默认600，独立580秒deadline另有记录。

这是一个runner、两份已见计划的完整Suite pass ns，含原timer/pass/checksum/cleanup边界；不是原D、确认、原25轮gate或新public MUL证明。当前停放证明投入；重开需不同runtime机制、可验证热域改进，或低成本验证无共同Bool捕获的新caller条件。不得仅换已见seed、删慢样本或从指令数量推收益。
