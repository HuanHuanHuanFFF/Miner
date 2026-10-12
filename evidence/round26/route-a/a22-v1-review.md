# A22：V1 逐调用 CPU 诊断的只读压力审查

审查时间：2026-10-12 UTC 09:46–09:57。状态：**静态审查无剩余派发阻断；Rust 编译、运行和数据完整性尚待本次 CI。** 本审查未修改实现、Git、工作流或 CI，只写本文件。它不重开 A21 算法路线，不授权重跑失败作业或扩大固定四小时截止。

审核对象：

- `scripts/r26-v-call-cpu.py` SHA-256：`17c03acfcb1410b834e8d5969caa34d6c4b350054d5cf8126829b7e5864a8770`。
- 修正后的 `evidence/round26/verification-v1-plan.json` SHA-256：`cca3cb4901c229e487b3ef579e60e4234e97f7cf70636bf755c32be8977b34e9`。
- 独立读取原 `validator/measure/src/method.rs`、`main.rs`、`Cargo.toml`、官方 `PINS.json` 与成功 A20 的 `pins_before`；在内存中调用补丁／反转及预检，没有本地 Rust 编译或性能执行。

## 已发现并修正的阻断

首版计划 `1cdff4a56de01362ce4e39e1192846354ad2443f58553c858c6c8532c62c291d` 的五个 `verification_original_measure_sources` 值来自本地 Windows CRLF 阅读副本。Linux 上游是官方 LF 原字节，运行期的 `source_before == spec[...]` 因此必然失败。例如 method.rs 错误期望为 `d2b683f7...f42`，实际官方值为 `64a45cf3...79b1`；main.rs 错误期望为 `fe9ff7fc...bec4`，官方值为 `ea4d6378...adaa`。Cargo.toml、Cargo.lock、record.rs 同样受影响。

实现线程只修正计划中的五个值，从已成功 A20 原始 `receipt.pins_before['measure/'+path]` 取得，并核对本地 CRLF→LF 的阅读副本内容与该官方值相同。审查独立复核五项全部一致。**运行期仍对官方原字节计算 SHA，不在运行期 normalize 或放宽断言；原官方树未改。** 此问题在派发前发现，不计为已经发生的 CI 失败。

## 关键实现核对

| 检查点 | 直接源码核验 | 结论边界 |
|---|---|---|
| 原 parser 计时 | 连续三句 `t0=Instant::now → p.parse → t0.elapsed` 与原文一致；before在t0前，after在elapsed后 | CPU／时间采样未被文本插入原计时区间；编译后代码布局仍可能改变 |
| 原 encoder 计时 | 连续三句 `t1=Instant::now → black_box(deflate::encode) → t1.elapsed` 与原文一致；before／after分列其外 | 原encode调用、black_box和elapsed表达式未改；不声称整个scratch机器码等于原引擎 |
| 记录与分配 | 初始化一次 `Vec::with_capacity`；28×12×2×2=1344个scalar事件；push前检查len<声明capacity且实际capacity≥声明值 | 已声明范围内push不会扩容；记录push、TLS/RefCell、getcpu及额外clock都仍可能扰动后续调用 |
| 输出位置 | file／method名称表在初始化建立，事件只持标量索引；`flush()`位于全部文件loop之后，写独立stderr JSON marker | 不在每次调用内格式化／写文件；官方stdout JSONL结构保持原版 |
| 原调用顺序 | 方法循环只改为带index的enumerate；toks.fill、run_once和order增量原序保持 | 仍为incumbent先、public658后；没有balanced-order干预 |
| 事件对应 | verify_trace将file、method、phase、order_index、stage精确join到原JSONL rep，并要求阶段elapsed浮点值完全一致、事件恰好1344条 | 可核对记录身份，不意味着获得额外独立性能样本 |
| 端点CPU失效 | `sched_getcpu < 0` 时 `cpu_endpoint_changed=None` | 缺值保留UNKNOWN，不把−1／−1算成CPU未变 |
| 两进程身份 | scratch只构建一次；两次顺序Popen复用同一command、scratch exe、workspace及两份DSO；每进程meta及运行后再次核对DSO哈希 | 同一runner、同binary两个诊断进程，不是独立确认 |
| 原／scratch身份分开 | receipt分别存original_engine、original_driver_provenance和scratch_engine SHA；传给A20.observe的是scratch路径；捕获exe SHA必须等于scratch值 | 不会用driver里原engine的SHA冒充scratch运行身份 |
| 官方文件不变 | 前后官方pins、五份原测量源码SHA、原engine SHA及上游git diff均设断言；补丁只写临时scratch | 云端实际断言通过之前仍是待验证条件，不提前声称官方树检查已执行 |
| 构建与协议 | 原Cargo配置／lock复制，offline+locked release；原候选模板构建；1预热、11测量、28文件、CPU0请求、300秒build/measure限制 | scratch加遥测是诊断引擎，所有计时排除候选评分；25分钟外层cap由派发器设定 |

补丁函数的精确反转检查已执行；原parser及encoder三个连续计时语句内均没有 `callcpu`。本地预检也核对了源哈希与public658身份。未执行本地或云端新Rust编译，不将Python预检写成Rust通过。

## 进程／cgroup 读取边界

外部observer沿本次Popen的 `task/<pid>/children` 递归，不扫描全 `/proc`。只有exe路径匹配scratch并绑定exe SHA、PID和starttime的engine才读取扩展信息。监控线程沿用A20的独立线程亲和设置，尝试固定CPU1，实际成功或失败会进入回执；不修改engine亲和。

cgroup祖先读取从该精确engine的 `/proc/PID/cgroup` 得到路径，resolve后先断言落在 `/sys/fs/cgroup` 内，只沿父路径到该根；只读预列出的controllers、subtree_control、cpuset、cpu.max／cpu.stat，不枚举兄弟cgroup，不读其他进程环境。缺文件保留异常类型。**祖先cpu.stat可能聚合其他同runner任务，不能将其用量或差值归属于单个engine或某次调用。**

每进程的外部observer使用Unix时间，而调用trace使用该进程自己的相对单调时钟；当前未保存精确跨时钟同步锚。因此外部4Hz样本用于该进程的环境上下文，不能声称与某个call端点纳秒精确对齐。逐调用CPU端点与阶段时长本身已在同一trace事件中相连，不依赖这种跨时钟拼接。

## 这次判别够用的范围

本次可检验新runner上同file／method／stage的时长分布，是否随记录到的CPU端点类别、相对调用顺序及进程身份一起变化；还可验证scope缺失的控制文件是否在祖先可见。它不能单独识别迁移、频率、缓存、ASLR或主机负载的因果贡献。

必须同时保留两个方向的限制：

1. **端点CPU相同不排除中途迁移。** 即使这些事件仍有两种时长，也只能写“端点CPU身份不能单独分开时长带”；不能写“迁移不能解释波动”。这收紧了早期 A20 未执行计划中的过强判别句，历史计划原文不改写。
2. **端点CPU不同也不能定位变化发生在计时区内。** CPU查询在原timer之外，变化也可能落在采样与timer之间的未计时间隙。字段应称 `cpu_endpoint_changed`，不称“该调用已迁移／未迁移”。

分析应先固定file、method、stage，再分别看两个进程；不要把本来不同工作量的文件混成CPU速度分布。若某CPU只出现在第一进程、另一CPU只在第二进程，CPU与进程因素混杂，不能分开归因。若没有时长带、没有CPU变化或有效分层样本不足，结论是“本次未复现／不可判别”，不能宣称测量已修复，也不自动补第三进程或另一CPU条件。

保留全部原始rep、warmup和阴性现象，不选择最有利分层重新算候选时间轴或份额。两份同scratch进程足以作本次有限关联检查；不足以建立跨runner误差界、稳定收益或正式成功概率。

## 派发意见

在上述精确script／修正计划、主线程入口哈希及预算预检一致时，**没有剩余静态阻断**，可按既定一次、两进程、25分钟cap派发。计划字段声明的10:05最晚派发时间不等于脚本内部实时闸门，主线程仍需在实际派发时核对时钟；四小时总截止10:48:52不变。失败、身份缺失、trace不完整或两进程完成都停止，不为补样本自动重跑。

本结论仅允许按既有授权执行这份有限测量验证，不是候选晋升、原计时协议修正、gate或正式提交意见。
