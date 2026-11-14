# 实际 cold-outline 成本前提成立；继续最小公共证明，尚不采用

run40607316341／source fd4e5b5144d00f3413b0b367a748e9be8f55d51017b4a8aaa5be53d404b1d6c1。200原件21437486B全部SHA重核；精确输入、两份已见plan、32进程、每进程156行／152timed、同seed16进程checksum及原flags/link/rsp独立重核。CPU AMD EPYC7763、CPU0。JSON保留全部样本、168个MUL case pair及原件绑定。

| discovery seed／block | MUL outline/control | whole outline/control |
|---|---:|---:|
| 2220001／0 | 0.9392334384 | 0.9802605235 |
| 2220001／1 | 0.9621905048 | 0.9867711212 |
| 2220003／0 | 0.9409869561 | 0.9675669828 |
| 2220003／1 | 0.9674150573 | 1.0021123157 |

这是同binary完整Suite pass诊断，保留原timer/pass/checksum／输出清理边界；不是原25轮gate、score、跨runner确认或新public源的速度。所有块保留，包含whole略慢者。四块MUL均改善支持买最小public证明判别，未达完整采用或冠军目标。

五个零参数IO runner各调用一次原Bench.Suite.run。逐四个Suite实参追链后，控制／旧inline／新outline的ADD、SUM、BMM共享完全相同闭包；MUL各为自己的static closed→lam1 boxed→lam1(uint32,uint32)。9个static closure全部fixed0、无allocated closure；三个MUL boxed wrapper在符号映射后逐指令相同，仍保留共同unbox/RC/typed-call/box成本，不能称整个标量调用无栈保存。

真正被Suite选中的runOutline lam1全函数45条指令，一次imul、bt/adc偏置、一次可变shr，无push/pop/frame/call/FP/表／显式数据spill。原三个guard miss在0x14／0x2e／0x43，其R_X86_64_PLT32重定位都直达retainedMul，是保留原x/y的条件尾跳；objdump未链接时显示下一地址不能当fallthrough。导出ASM保留重定位。guard仍两指数1..254、和128..380，normalCore后无检查。旧inline实际接受路58条、五保存＋16Bframe；控制完整typed body326条亦有五保存＋16Bframe。

冷retainedMul源定义仍为原B2；原Submission对象7dbe4419与该binary计时前original_build_before一致，有真实native ASM。冷体326条，但C／ASM与Main control克隆并非逐体同形，有布局／条件方向差异；不能将全部速度差唯一归因为frame删除。原ELF未导出，只重hash原C／ASM及远端对象身份回执，未冒充本地ELF重hash。

已见plan的保守区间分类与成本交叉后，20个全域接受case四块比值约0.884／0.906／0.889／0.948；全域miss的3–4个case约1.163／1.148／1.139／1.120。冷回退开销抵消部分热收益。分类为生成器source域界，不是CPU占比或隐藏输入保证；不得只挑接受域报告。

公共草稿public/Kernel.lean：88cdf318d952d74df95ecabed5e2bbadeab76d4827af1c4e5fd88e43d9d8f054／255520B／余480B。从未全验fa652仅增209B，旧core／guard／算术证明不动，新增noinline原B2 fallback并把guardedMul_spec传参换到它；原48根加retainedMul定义共49根。intake/policy预检通过，statement／49根axiom+replay／原MainFull／完整D全NOT_RUN；旧fa652 signal−15／UNKNOWN保留。下一步由D跑原验证与实际public路径，新source不继承诊断或#336成绩。
