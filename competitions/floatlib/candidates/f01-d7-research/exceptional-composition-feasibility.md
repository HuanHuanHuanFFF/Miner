# 冻结 cc06 与 939 的组合可行性源审查

2026-10-23 02:58:27–03:10:45 UTC。只读现有冻结源；仅交付本报告和同名 JSON。未编写原939的数学块/helper/builder，也未编写cc06、3d9或97f DirectSmall末段；此前做过939静态复核。本人另写的DDot scanner/native-singleton不在本次cc06中。

**存在可逐字定位的替换区，内存投影为252,623字节，低于256,000上限，余3,377字节；静态检查未发现新增同名冲突或依赖顺序阻塞。** 这只支持下一轮接线的容量与接口可行性，不是已构造、登记或验证的候选。冻结cc06保持不变；Lean、完整gate、C/asm和收益均NOT_RUN/UNKNOWN。

| 实际原件 | bytes | SHA256 |
|---|---:|---|
| [cc06冻结组合](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-singlepass/Kernel.lean) | 232363 | `cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc` |
| [939 exceptional](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-scalar-exceptional-word/Kernel.lean) | 175363 | `939dbf31705408ac5177e4ede746b7cd52c72e9b7ab7b75eb2a1fd2178635237` |
| [60f基座](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-nonnan/Kernel.lean) | 155103 | `60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15` |

三份及0e8/97f/3d9均重新读取原字节，匹配02:45冻结清单。六源、参考builder、旧review和机会数据的精确摘要见 [JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/exceptional-composition-feasibility.json)。没有执行builder或写入任何新Lean源码。

| 内存替换项 | 精确区间与身份 |
|---|---|
| 60f完整旧scalar区 | byte `[85647,115608)`，L2042–2654；29961B；SHA `590284a92073487dacdf1c6127c51693dabb1954a47d195d2bf87f7827fb9fdd` |
| cc06中的唯一相同旧区 | byte `[113716,143677)`，L2739–3351；在0e8、97f、3d9、cc06中均各完整出现一次 |
| 939完整对应区 | byte `[85647,135868)`，L2042–3133；50221B；SHA `2952d9e99cc05110fa6d4826703e2958f7980a73782a0f6ea44057a037f9e8e0` |
| 内存投影 | 232363−29961+50221=252623B；SHA `2b4dfc444ac4bd71abebc96ce647f470a35aab40acb3d4bf2e1c4d03cbe926d9` |

旧区从 `end WordFinite` 后开始，到 `end R7Native` 后结束。60f→939在该区以外的全部字节相等，因此此区涵盖939相对60f的全部新增、搬移和替换。目标匹配使用**完整29961B原字节及唯一出现断言**；内存正向替换后再逆回，恢复完整精确cc06。投影的SHA仅用于本报告复核，不对应磁盘文件、注册候选、manifest或CI plan。

粗差额20260B在这个精确替换下适用。直接把50221B新区追加到cc06会变成282584B，超限26584B，而且重复已有声明；不能把搬移的proof再次追加。原官方gate的 `_MAX_BYTES=256_000` 在第179行，intake第509行按实际文件字节数检查。本次计的是完整单文件UTF-8原字节，没有删注释腾容量；未对投影执行policy或Lean。

**宽锚点有明确反例。** 如果在cc06沿用“`end WordFinite`之后→`namespace NativeFinal`之前”作为整个目标，会取到 byte `[113716,184420)`，额外删除 `[143677,184420)` 的40743B，即L3352–5068，SHA `e16068bc6d879286bb7d4492579e2716570104ebff122177b3a9a77509c594d1`。该区属于上述精确cc06源，含R7W03/W05/W12、R7SumRepair及R7NaNReplay。错误内存投影反而仅211880B；小于上限不能发现依赖被删除。

| 宽锚点会删掉的真实声明实例 | cc06原位置 | 后续关系 |
|---|---:|---|
| `Submission.R7W03.chooseNaN2_none_not_snan`、`model_add_not_snan` | [3360](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-singlepass/Kernel.lean:3360)、3369 | 已有raw/spec数学链 |
| `Submission.R7W12.rawNotNaN` | [4894](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-singlepass/Kernel.lean:4894) | 后续R7SinglePassSum仍引用 |
| `Submission.R7SumRepair.suffixLoop` | [4963](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-singlepass/Kernel.lean:4963) | 单遍sum首NaN修复后仍调用 |
| `Submission.R7NaNReplay.replayEarly/replayEarly_eq` | [5043](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-direct-singlepass/Kernel.lean:5043)、5046 | NativeFinal/Packed BMM原冷路依赖 |

这是源依赖反例，没有生成该错误源码，也没有把它伪装成Lean失败回执。

三个闭proof块 `Submission.NativeBridge`、`Submission.NotNaNProbe`、`Submission.R7Native` 分别10136/2494/11022B，在六源中逐字相等；939只把它们搬到新helper之前。前置 `R2W01b/R2W01c/FastMul/TunedAdd/LowScale/GuardBridge/WordFinite` 七个完整namespace在60f、939、cc06也逐字相等。DWordNaN的selected_add及exceptional add桥需要的 `R7Native.toModelExecAdd`、mul桥需要的 `NativeBridge.toModelExecMul`，以及 `FastMul.ofBits` 均排在使用之前；DWordNaN又排在DExceptionalWord之前。新块不需要被宽锚点误删区中的R7W03/W05/W12来完成自身前置依赖。

轻量扫描屏蔽comment/string后，named namespace/section的end配对完整；相对cc06只新加 `Submission.DWordNaN` 和 `Submission.DExceptionalWord` 两个namespace、44个命名声明。未发现新增完全限定名重复或同名不同体并存。原scalar add/nativeMul及相应proof被替换，不是增加第二份同名定义。此扫描不是Lean parser；实际名字解析、definitional equality与搬移后的证明接受仍NOT_RUN。

| 实际运行/证明替换 | cc06旧位置 | 939复用位置 |
|---|---:|---:|
| add的false finite分支 → `DExceptionalWord.addCold x y` | 2745 | 2996 |
| nativeMul的false finite分支 → `DExceptionalWord.mulCold x y` | 2958 | 3019 |
| 两个cold证明叶传各自 `rename_i hf` | 2759 / 2970 | 3010 / 3031 |

939两条helper规格都要求否定“两个raw指数均非255”。当前两个if的false分支精确提供这个前提；ordinary finite路径不应调用addWord/mulWord。例如有限1+1并不属于word helper的正确域。外层mul低指数守卫及 `add_eq/mul_eq` 定理块在三源中逐字相同，投影的区外仍完整保留所有地址、tensor顺序、quiet-stop、direct dispatch和单遍sum。源级保留不证明机器布局或普通cell时间不变。

NaN数学存在可解释的重复，未出现接口冲突。cc06的 `R7W02.rawSNaN`（436，模型等式491）及 `quietRaw`（439）已经证明signaling分类和置quiet位；939的新DWordNaN用另一套字段公式证明相同模型分类，放在独立namespace中。本次原样保留两套数学，不进行去重或产生新证明。

两种运行范围也不同：`R7W02.step`（646）及 `step_eq_add`（656）要求左acc已是quiet NaN，suffix只在右输入sNaN时替换；完整exceptional addWord/mulWord则按“左sNaN、右sNaN、左NaN、右NaN”的顺序选词，再处理Inf/zero/invalid。3d9首rawNaN修复调用 `Submission.add (ofFloat32 acc) q`，此时acc可能已由先前Inf相反加变成canonical NaN；不能只看右q就接收它。旧有限模型保留的两条判别见证为：

- `[+Inf,−Inf,0xffc01234]` → `0x7fc00000`，左canonical quiet NaN保留优先级。
- `[+Inf,−Inf,0xff800011]` → `0xffc00011`，右sNaN覆盖左canonical quiet NaN。

这些是已有有限模型记录，非本轮新枚举或形式证明。原suffix已经直接调用R7W02.step，exceptional组合不会再次消除其scalar add。已有807前沿统计SHA `d30447c8…` 按97f quiet-stop及3d9单遍sum重数：

| 非NaN特殊cold调用 | 计分模型次数 |
|---|---:|
| standalone add | 3277 |
| standalone mul | 2042 |
| BMM add+mul | 2545+602=3147 |
| 单遍sum | 0 |
| 合计 | 8466 |

raw检查另有BMM876次，未混入8466。单遍sum另剩320次首rawNaN修复，不是非NaN特殊调用。上述均为已有源模型的一次checksum遍历次数，不是精确cc06 binary测量、时间份额或增益；本次未重跑浮点枚举，也不沿用旧60f整回放曝光估算收益。

归属信息原样保留：原scalar区14段comment共1693B在新区仍能逐字定位；三个闭proof中的原通知不变，cc06区外全部字节不变，939新区整体复用且未删其来源说明。此次没有新增作者或许可证主张，也没有压缩注释以挤入容量。

下一轮条件：**只有cc06和939各自通过精确完整gate，且939在scalar/BMM特殊cell显示可重复净收益而普通cell无回归，才值得解除冻结后考虑组合；组合仍须独立完整验收和配对计时，否则PARK。**

