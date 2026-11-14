# R24：全finite F64数值解码＋ADD完整成本诊断

UTC2026-10-28T21:33Z；限定准备窗21:25:08–21:45:08；仍沿共同03:38:56截止。D唯一Git/CI；本agent无本机Lean/native编译、独立CI、正式上传或资金操作。模型Sol/xhigh；token/cache/reasoning、runner实际占用UNKNOWN。

**READY**：`f01-r24-dev-scalar-f64array-cost1/Kernel.lean`，**08a0208ec09eeb583f9d8e451234a4f5e29cfa75eaa90d525073b7296b5584a2／229522B**。精确B2/622d前缀，四个public函数和spec不变；新helpers仅诊断。manifest绑定Main/driver/runtime/stage/static-audit，`helper_audit_module_path=f01-d7-research/round7h-20261028T203856Z/development-scalar/f64-cost/f64-cost-audit.py`。

**实质变化**：输入mantissa UInt32→Float64精确数值转换，乘global signed512尺度；E0用frac·2^-149，E1..254用(2^23+frac)·2^(E−150)，所有scale与非零输入都是binary64正常数。NaN/Inf原B2回退，±0同完整路线。R2旧提案是F32 subnormal-scale；R13仅审查F64 MUL narrowing信任障碍，没找到本F64 FloatArray ADD同体计时。旧F32 convert→ofBits强负保留。

**四静态Suite runner**（MUL/SUM/BMM恒B2）：

- control：B2 ADD。
- f64native：FloatArray连续未装箱尺度→F64 ADD→同宽Float.toBits→新UInt64 GRS/RNE word缩窄。
- f64boxed：同算术/GRS，Array Float尺度归因对照。
- f64cast：FloatArray→F64 ADD→opaque Float.toFloat32→toBits，仅工程对照，不能采用或替代legal路径成本；它也不是已证的机器时间下界。

**完整成本**：原156case/152计时，seed2240101/3、24个ABBA进程、inner3/pairs500000。driver先核原flags/link/.rsp与独立静态C闭包，后记录完整C/object/ASM。原case ns排除operand/global准备；另报进程墙钟含准备、输出、释放和进程开销。三个变体同一binary共享两表初始化，control也带诊断global；因此不能把进程墙钟说成精确独立B2包启动比较。

**已核范围**：`local-preflight.json`：Python AST/policy原regex、精确B2前缀/byte cap/组件hash、2文件prepare/cleanup/注册拒绝，及decoder103570、GRS128658、完整二元ADD360112有限例无差异。总592340例；**无Lean全输入证明、原生执行或性能结论**。首次保存回执遇str/bytes类型错误后已修，重跑完整预检通过；失败没有触发CI或源码变化。

**证明前提**：UInt32.toFloat与Float64 native ADD都有固定Lean模型和同宽FloatLib桥；Float.toBits同宽有模型。新GRS normal/subnormal/overflow/±0位处理、数值decoder全finite精确性、二元F32 ADD经F64再RNE32的充分条件、fallback组合均未验。`Float.toFloat32`仍opaque，f64cast无可用准入桥。FMA/任意fold不在此数学断言内。

**最小决策**：先原statement+该成本stage≤600s；D/R独立跟踪实际Suite callback及FloatArray存储/访问，确认没有捕获参数、每调用重建表、意外boxed表或额外narrowing。以legal路径完整whole/cases决定继续或杀路线，不以cast成绩代替它。全部legal路径失败就保留负例并停止本体；有实质收益才买最小数学接口与完整集成验证。新赛道实现仍待用户范围决定。
