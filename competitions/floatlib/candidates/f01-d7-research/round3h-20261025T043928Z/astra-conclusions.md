# R15 数学、Lean 与运行成本结论

研究窗口 UTC 2026-10-25 04:39:28—07:39:28。开发在06:19:09冻结运行源；后续仅验收既有源码。唯一当前研究索引为 `astra-status.json`，全局采用/Git/CI由开发协调者负责。

## 已形成并绑定实际源码的数学资产

| 资产 | 原义务与本轮变化 | 验证边界 |
|---|---|---|
| 两条相邻列的原序链 | `R15ThinPairs.loop_s0/loop_s1`把每条累积链投影回同一`NativeFinal.dotLoop`；`finish_select`和Prefix运输保留raw NaN重放、初始+0及奇数尾列 | b116完整原版gate通过；首次D失败。原b962三处脚本错误及修复源都保留，不是数学反例 |
| B2准备值到原数组地址的桥 | `tileIndex/packB_get`对完整batch、k、pair索引建立字段等式；泛型read invariant连接两条链，再以group/row/output等式回原完整规格。未输出的奇尾第二lane也保持原total-getD值 | 622d完整gate在D/A/B三组通过。不是仅有限轨迹或仅声明接受；逐组原件见cohort审核 |
| 原字指数守卫到signed zero | 复用已验`UnderflowZero.roundP_zero`，新增raw指数和不回卷、special排除、finiteScale上界与LowScale调用桥；保留XOR负零 | 在cb7完整组合上下文中通过原版gate；不能把它写成独立8373文件已验。cb7首次D失败，不证明单组件提速 |
| UInt64 flag恒等式 | 三个定义上为0/1的flag组合等于原rse条件树，保持模2^64语义；再由已验shiftWord_values限制到23/24，与原core和完整guard/fallback接线 | f529完整gate通过；裸round等式对任意shift仅表示等于旧rse，不表示任意shift都等于数学RNE。首次D中MUL回退，已停放 |
| 参数化低尺度紧界 | 非零product<2^width且width+scale≤172给出leading+scale≤171；保留scale<149和原roundLow零/进位分支。具体124/125/126分别需48/47/46bit严格乘积界 | bb512完整证明草稿未编译。根912项、worker3120项有限检查及真实mantissa域外反例不能替代Lean。命中稀少，不排性能CI |

这些是既有FloatLib/本项目证明的复用与新增接线，不声称发现新的IEEE舍入理论。完整源码、原作者许可和固定版本分别保留在各worker交接/manifest/source-index；新运行代码没有复制外部BLAS或更改编译参数。

## 运行证据与当前决定

| 精确源 | 原版完整gate | 首次D whole/DF | 首次D p05 | 决定 |
|---|---|---:|---:|---|
| ec82 matrix-only | PASS | 0.97608656 | -0.00604681 | 停放 |
| cb7 shortn/cache/decoder/cutoff组合 | PASS | 0.98041964 | -0.00402005 | 停放；不加总或归因单件收益 |
| b116 双列 | PASS | 1.03124725 | -0.05009149 | 停放；不豁免scalar慢样本 |
| f529 flags/literal正常MUL | PASS | 1.24480321 | -0.26090980 | 停放；MUL/DF=1.702578 |
| 622d packed-B2 | D/A/B均PASS | 0.95999301 | +0.02015310 | 三组均达原采用门槛，交开发按原流程采用 |

B2的A组 whole/DF=0.93761533，完整gate+25轮通过。原每组独立汇总p05=+0.03329485；根按冻结整cohort连续随机流独立复算A为+0.03420069，方法/流水位置不同，均不改原始回执。D/A输入顺序、精确Kernel、模型与46个冻结控制文件已核对。B为事前声明的1526102，顺序B2/41/DF；任何一组不达都不采用，不替换输入或重置首次D。

`astra-independent-cohort-check.py`仅重算原始逐项/25轮和冻结绑定，未跑新benchmark。最终回执`astra-cohort-independent-D-A-B.json`已独立重算三组，均通过；B组whole/DF=0.91108689、p05=+0.07617015，BMM/DF=0.66038416。新鲜GitHub任务响应记录D/A/B为三个不同runner ID（1000001518/1519/1520），物理宿主身份仍UNKNOWN。线上冠军仍为已核对的309；本地DF比较、冠军耗时估算、正式准入/排名/奖励分别判断，当前没有正式提交或资金动作。

## Lean代码生成与成本边界

B2的实际statement C确认一条记录的标量区8B、字段offset0/4、无逐字段Float32 box；准备只在入口一次，tile div/mod在k外。相较父loop，C对象参数7→5、数组读取3→2、热点Nat stride乘法移出；F2只在循环终态构造。诊断汇编观察到两lane mulps/addps，同时仍有调用和栈存取。这些不是原完整计时对象，也不证明总分配、spill成本或时间减半。嵌套容器、奇尾额外解码/MAC、strided准备、RC及销毁都保留在完整测量中。

另一个可复核事实：b116/f529的ADD前置118185B源码相同；实际selected MainFull ADD诊断C体8286B逐字相同。13个函数中11个原字节相同，其余仅局部SSA名变化。仍不能断言timed ELF相同。原始时间分解显示参照ADD只差约0.24%，而b116提交自身约慢6.8%；该差距的原因保持UNKNOWN，不归为CPU噪声、不修改失败结论。根审核分别见 `astra-b2-C-independent-review.json`、`astra-add-codegen-independent-review.json`、`astra-run5-normalization-diagnostic.json`。

公开源码调查没有获得309代码；公开incumbent仍为旧参考。所查最新FloatLib窄乘法在改名后运行体相同，不升级固定依赖。固定Lean的Float32位转换是bit_cast加NaN规范化，索引可为tagged Nat；不能仅凭函数/boxed名字就宣称分配或重型软件解码。

## 留存与权限

三条Astra分别负责矩阵结构、标量输入域、公开源码/真实运行时；根独立复算、审阅并以分题文件交开发。原失败、有限模型、源码和来源均留在本目录与CI原件目录。Pro实际额度禁用，本轮无新网页咨询/上传/下载；不把旧输出后端写成已证6 Pro。

部分研究screen读取本地R14的Python生成器转录，仅用于有界机会判断。旧190批次仍HOLD，不能为补公开依赖而改名复制/代理推送；这些screen不是正式gate依赖。已发布候选与原版CI使用自己的固定官方生成器和原始输入，无此私有研究helper依赖。完整研究资料保留本地，公开提交范围由开发按既有授权核对。
