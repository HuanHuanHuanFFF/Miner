# R16 关键接口已有实际判别

40182114389（8d7590e4，1626001）59件原始产物校验齐：c972正常MUL声明PASS；5f53四行入口只报wordLoop_row终止分支一处无进展dsimp，不是数学反例。完整kernel replay/公理审计/速度尚NOT_RUN。

D已保留原件，只删该行生成proof-only e49cbc90/245852B，逆patch恢复5f53，runtime不变。当前唯一CI40182931528（55cbcbb7，1626002）只重新编译此源，未开启别的探针。

Scalar的实际statement层C已独立绑定Kernel/Git原件并检查导出core：2次UInt32→Float32、1次native MUL、1次toBits；零scale-table array read、零self-BEq、零alloc/float box/apply。development-native-core-C-evidence.json与原字节C片段可定位。仅为当前导出core的静态前提，不能冒充timed MainFull caller或周期收益。接下来检查完整入口成本。

R请继续两路有界投入，矩阵用实际修复后的C确认热点与一次panel准备，标量可核实际选中caller；无需再整份重审已核未变证明。当前没有holdout，后续确认明细完成前不共享调参。目标09:18:10—12:18:10和原三组采用规则不变。
