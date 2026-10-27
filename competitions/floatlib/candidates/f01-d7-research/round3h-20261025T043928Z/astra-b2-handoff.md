# R15：B2源码根独立审查完成，供下一最小编译选择

时间：2026-10-25T05:54:25.262100+00:00。回复D054920：b116/f529声明通过已知，现两者自己首次完整D在40166656717/708ff116/seed1526005；R不把其声明PASS写成完整gate。

B2主源astra-workers/matrix-structure/Kernel-b2.lean，226829B，SHA622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58；父b1160671。R已独立含换行逆patch逐字恢复父本，读完全部PackedB2函数/证明；新Nat.mul_add_div和mul_add_mod_of_lt又从固定Lean293d原源码确认真实签名（Lemmas.lean1563/1580），不是猜API。未发现具体纸面类型/前提缺项，但全部新Lean脚本尚未执行。回执astra-b2-independent-review.json。

表示为Vector(Vector F2 n)(batch*ceil(p/2))，外层一次算tile batch/group，内层每k一个两F32字段记录；热点每k取一个记录，保留两条原k链和raw finish。odd tail第二个未输出lane也保留原total getD地址，没有擅自置零。空batch/m/n/p及越界默认通过相同读不变式覆盖。完整proof尝试及90720结构轨迹只作为检查入口，不当全输入正确。

固定lean.h和旧生成C支持内嵌F32字段的表示机会，新622d C仍未取得。必须把嵌套vector/closure/container、奇尾多解码、strided gather准备、return-F2、读取RC、数组存活和销毁算全；不能称整体分配减半。请D若选择用自己唯一槽作最小声明检查，随后看实际packB回调/loop是否单记录无逐字段float box、tile div/mod是否外移k；只有精确新源完整D才看性能。旧whole诊断域3.36–6.94%不是当前计分份额或预计收益。

紧RSE已给完整候选bb512446/250492B，R读完通用引理和三分支、逆patch恢复df5c；但各21504样本只有9/31/23新增非零命中，reserve，不请求CI。源码/数学边界/反例保存，见astra-tight-rse-independent-review.json与worker tight-literal-rse-handoff.md。D f529是另一normal-MUL结构，不能混淆。

R第三Astra已专门核对f529的0/1等式、literal RSE与oldcore接口及实际statement选中C，报告已回收待root简报。原9038负D保留，C有flag分支/重复product的静态观察也不等于机器成本。源冻结06:19:28、截止07:39:28、单CI不变；190旧材料HOLD。
