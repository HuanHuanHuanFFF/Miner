# C2：U118 backward fold 的末字节必要条件

2026-10-12 UTC 11:56。这里只准备一个实际候选，未编译、未计时、未 gate。候选是 `candidates/r26-c-658-fold-tail`，父版是公开 658 的精确文件；公开作者及原注释保留。

## 问题与变化

U118 吸收上一输出 match 时，在原有 `l+w<=258`、位置与距离 guard 后，从前向逐字比较整段旧 match。若其最后一个字节就不同，整段比较不可能成功。新版本只在这里增加末字节必要条件；失败走原来的失败/partial merge 路径，成功仍执行原始 `u118_same`。其余搜索、记录、lazy、fold 预算、输入路由及 encoder 不变。没有增加表或长期状态，也没有按文件身份选择行为。

这不是大结构优化。机会是跳过真实的一次旧 token 扫描，同时付每次合格 fold 的两次 byte load 和分支。公开 corpus 的覆盖尚 UNKNOWN；不能把最长旧 token 长度当作省下的比较量。

## 旧结果及排除

- A18 对前向链 common 加末端窗口，取消 9.66% 调用但增加读取，未进入计时。本次消费点是输出 token 的 backward fold，无窗口缓存维护；该负例仍限制期待。
- R20 全部取消 PC fold 导致明显质量回退。本版本没有取消任何能成功的 fold。
- `pc_fold` 本体也从 token 前端比较，但其调用 wrapper `pc_fold_w` 已有末尾 `min(w,8)` 字节必要过滤。本次不在 PC 第一轮重复已有工作；多次回卷后的剩余范围未测。
- 起初 C1 拟用同距离旧 token 直接跳过扫描；源码最大前缀和长度 258 上界使这类相邻合并大概率不可达。直接先例：`evidence/round26/route-a/forward-fold-domain-closure.md`。因此 C1 不生成候选，仅在 C2 oracle 中顺便核对实际次数。

## 最小操作与判据

一份 native 批次：原 658、校准 public514 和 C2 使用原 encoder；已有 444 finite equality、28 逐 token/编码/hash/round trip 检查。额外 observer 只在原 658 轨迹上执行，逐文件数：

- 所有合格原 `same` 调用、待比较长度；
- 尾字失败次数及其原比较实际执行的 8-byte word pair/单 byte pair；
- 尾字通过的新增判断次数、原比较成功/失败；
- C1 同距离可达次数，若出现则断言其旧 token 字节确实匹配。

原比较次数由精确源码等价的诊断模型核对；不是汇编指令、周期或计时。observer 输出逐 token 必须等于原版，并与本批原 encoder receipt 的输入与 token SHA 绑定。候选必须同 token/同输出，否则停止定位。

如果省下的比较薄、原多数失败只扫描一个 word，或增加判断工作接近省下工作，则暂停，不扫 guard 宽度。只有真实取消覆盖值得测试时才进入一份原协议配对计时，随后冻结、新 runner 独立确认、完整 gate 均另算。任何频率或 byte count 都不直接换算份额。

## 证明与资源

从有效 parse 状态有 `p<=input.len()`，原 loop 有 `d<p`；旧 match 长度 `w>=3`，原 guard 有 `w<=p`、`d<=p-w`，所以 `p-1` 与 `p-1-d` 的读取有界，包括允许重叠匹配。任何旧 `same=1` 都蕴含末字节相等；额外 false 分支与原 false 分支相同。

完整正确性不需证明质量最优。可复用 `U118_MAIN.BackInv.match`、`part_merge_spec`、已有 loop 不变量；实际提取后多出的条件和局部名字需要重新核验。当前 `Parse.lean` 仅复制父证明作为草稿骨架；没有声称已适配/编译。余量 19,145 bytes。全 gate 的提取、原始 obligation、公理白名单、round trip 均 NOT_RUN。

建议 native job 上限 15 分钟（实际重用现有 workflow 参数，由主线程冻结）；observer 编译/运行各有 240 秒 subprocess 上限，原 encoder 自有上限。输出限于本 route-c、r26-c scripts 与候选目录。无 Git/CI 派发/正式上传/资金操作由本子任务执行。
