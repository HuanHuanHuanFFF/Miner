# 相对冻结B2更新：语义闭合，纯函数验证通过；尚未接入D工具

UTC 2026-10-26 20:28:47接手，预算20分钟，20:38完成本地分析/验证。只新增本目录文件；先前anchor/build/README/MANIFEST及全局模型、D工具、Git、CI、Lean均未修改。没有把在途诊断40395429076算成完整D或确认结果。

结论：可用**原六份control41成本 × 冻结B2/41 cell delta × 新三组C/B2 cell delta中位数**估计新源；它在数学和数据流上不需要新runner再测41。冠军323的六份分母逐字段沿ab3b，B2本身严格返回ab3b原模型。该方法是明确的新估算政策，不是原C/41方法的等价改写；仅替换DEFAULT_ANCHOR无法实现它。建议D在首次完整D之前决定并冻结政策，随后保持整轮一致，不根据有利D结果选择方法。

产物：[纯函数](retained-relative-draft.py)、[复验脚本](verify-retained-relative.py)、[派生成本表](derived-b2-cells.json)、[历史导出模型](retained-relative-historical-model.json)、[验证回执](retained-relative-verification.json)。派生成本表不是原始B2测量；本次实际认证36个去重原件，路径和哈希全部在回执。

## 计算及恒等性

设六份旧冻结样本为s，cell为k；旧control41的实测成本为a(s,k)，冻结工作量为w(s,k)，ab3b保留的B2/41 cell delta为dB(k)。ab3b现有分子就是：

`B(s,op) = Σ[k∈op] a(s,k) * w(s,k) * dB(k)`。

导出B2单位成本`b(s,k)=a(s,k)*dB(k)`，明确标为DERIVED。为了逐浮点位重建ab3b，权威贡献项仍按原乘法次序`a*w*dB`保存；`b*w`数学相等，机器浮点最后一位不保证相等。

新源C的每组实际同runner配对给出：

`q(j,k) = (C_submission_ns/C_incumbent_ns) / (B2_submission_ns/B2_incumbent_ns)`，`dRel(k)=median[j∈D,A,B] q(j,k)`。

新分子为`C(s,op)=Σ[k∈op] (a*w*dB) * dRel(k)`。每份冠军分母H(s,op)直接复制ab3b的`champion_projected_total_ns`，不再次计算、不引入新runner绝对ns。四项为各样本`C/H`的中位数；whole先各自求和再相除，最后跨六样本取中位数。

若C的精确source SHA等于B2，函数直接deepcopy返回ab3b，连时间戳、method、samples和配对列表都不改。后续任意数量、任意噪声的控制数据被忽略，不构成重新拟合。实际测试还验证了返回对象重新序列化后与ab3b原字节完全一致。对不同SHA但三组cell比值全为1的变形，所有数值也精确回到B2；这是代数测试，不是可提交的同源测量证据。

## 与旧C/41方法的精确关系

同一组三方回执中，令`x(j,k)=C/41`、`y(j,k)=C/B2`、`z(j,k)=B2/41`，均按原normalized ratio定义。逐组有`x=y*z`。旧方法使用`median(y*z)`；本方法使用`dB_frozen * median(y)`。一般二者不同，即使新三组`median(z)=dB_frozen`也不保证相同，因为中位数不对乘法分配。例如`y=[1,2,3]`、`z=[3,2,1]`、`dB_frozen=2`：旧值3，新值4。

若每一组的z都恰好等于冻结dB，则两种方法逐cell相等；也可能偶然相等。新runner的z发生漂移时，旧方法会把它重新带入新源估算，本方法以冻结B2为局部坐标。新方法因此维持保留版本的数值连续性，但不证明哪一个更接近真实冠军时间；两者的cross-suite/hardware转移误差仍UNKNOWN。

历史真实验证使用`f01-d12-scalar-combined`/`df5c61a0...`，同run的C、B2、41三方均有完整25轮原gate：`40168687803 / 40169957447 / 40171180249`。原`checked_record`逐项认证source/verdict/summary/provenance/plan/suite/work/seed/verifier，requested-plan均无profile/codegen。下表仅比较估算算法；这些历史样本不是该候选的新未见D/A/B，也不构成采用建议。

| C/冠军323估计中位数 | 旧median(C/41) | 相对冻结B2 |
|---|---:|---:|
| add | 1.0327336681522907 | 1.0325226586293823 |
| mul | 1.1597263906474002 | 1.1601202014662413 |
| sum | 1.175909495347922 | 1.175728718628347 |
| bmm | 4.3017931486221475 | 3.8828079643986135 |
| whole | 1.3543932012061575 | 1.3202500263319141 |

BMM相差−9.7398%，whole相差−2.5209%；因此不能称为无语义变化的小修复。回执保留每cell两方法的差异和逐组乘法关系，不用整包统一缩放代替cell运算。

## 验证与不可替代的义务

已验证：同源ab3b逐字节identity、后续控制不重拟合、六份分母/工作量不变、输入对象不变、三组顺序不影响数值、每条C和B2回执的submission/incumbent同时独立乘不同2的幂后结果逐字段不变。后者证明绝对ns不进入旧校准成本。0.5/1/2倍相对变化的纯变形精确得到对应分子与whole方向。14项负测拒绝错run/seed/source/suite/plan/work/name、24轮、缺组、observer、伪造raw classes、修改冻结B2 delta及改变冠军digest。

纯函数不能通过一个内存dict自己证明raw字节、proof replay、独立runner、无observer或样本未见；`observer_free`、D/A/B role等是**调用方认证后的输入承诺**。本次历史核验只检查原计划无observer；正式选择仍须现有完整observer审计。变形样本均有显式SYNTHETIC说明，修改后的classes无法通过原`checked_record`重认证，不能冒充真实gate。

采用流程必须继续执行所有原始正确性/25轮full gate、固定精确源和工具链、第一组干净D及两组冻结未见确认、ratio≤.97、配对bootstrap正p05、无observer和最新官方状态认证；本函数不输出accepted、不改变门槛。调用方还须证明传入的是完整声明cohort，拒绝遗漏/替换/重置失败D，不能用估算中位数或范围替代实际选择guard。

成本转移假设仍存在：新三组C/B2的同名cell比值能代表旧六份不同长度/形状/值分布。模型不表示新同机绝对测试，直接对冠军比较和正式admission仍UNKNOWN。若源/官方suite/verifier/reference改变，本草案拒绝；若冠军改变，须另做明确复核，不能自动更新分母。

## D接入范围与边界

先前reviewed323 anchor保持原样，它仍是合法的41校准原件。不能把本次derived B2成本冒充六份原始B2 gate填进旧anchor schema。新函数已固定ab3b字典canonical SHA `7b74b04df19964a2b809e7a1c3623fa92dd50bfb2f1e104ea27570d683e82bb5`，对应原字节SHA ab3b；原41 anchor payload固定cc65。新模型专用`cell_relative_delta_to_retained_median`字段，移除旧名`cell_relative_delta_median`以免被误读为直接C/41；新估算时间和estimator代码hash由实际adapter补齐，不能继承旧时间或旧实现指纹。此草案只针对B2/ab3b，后续采用新保留源须另做明确复核，不自动递归更新基准。

当前R19代码的额外41要求分布在`prepare-plan.py`、`freeze-cohort.py`、`verify-three-groups.py`、`selection-policy.json`，adopt还调用原select_pairs/estimate_from_anchor/main。接入需同时：用B2认证三组C/B2；显式切换估算method；将新core/adapter/冻结ab3b/旧control41/冠军323分母与政策全纳入freeze；保持原事务save拦截/rollback；去掉的只能是额外候选41测量要求。旧官方reference仍按原full gate运行。只换DEFAULT_ANCHOR或对C/41结果乘一个整包常数均不正确。

本子任务没有实现全流程wrapper，也未改这些入口；给出的纯函数和数学闭合足够供D决定接入。若接入，需额外做“无41但C+B2完整三组可通过数据认证”和“任一原选择条件失败仍拒绝”的集成回归，之后再冻结首次完整D。本分析不能替代该集成验收。

复验：`python -B competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323/verify-retained-relative.py`。仅新增本次三份导出/验证文件；早前完成的anchor方案不被覆盖。新增文件哈希见`retained-relative-MANIFEST.json`。
