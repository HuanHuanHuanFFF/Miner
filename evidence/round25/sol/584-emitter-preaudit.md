# public584 odd emitter 的静态预审

2026-10-11 10:12–10:16 UTC。根据主线程明确提出的固定替代，仅审阅 public584 原源码、原 Lean 与旧 R4 实际回执；**不生成候选、不运行本地工具链、不启动 CI**。原 public584 / duplicate-hop 文件均未改。

**结论：在父版已有 `Dec` / 完整 `MatchAt` 前提下，odd 分支改调用 `pc_put_match` 是合理的原生 token 等价试验，证明前提不需加强；但本轮默认不启动。** 最初“删去重复全字节扫描”的解释不成立：`pc_VERIFY=0`，checked 分支不会再次调用 `pc_same`。能省的只是距离、长度、位置的 range guard 和 fallback；旧同类别 R4 原始配对没有显示足够大的稳定整体收益。**该 exact public584 改法未测，性能仍 UNKNOWN**，不能写成已测无效。

## 原文件和静态路径

public584 Rust SHA `82297feee16db3fe6af50fe07f034b81d73d7189a40a829b78b44db167410cf2`，Lean SHA `96239a6fcad5be34ad4ec3b8caaaa379592166ff99b9194803e432f6d0482f4d`。作者归属保持 `references/round18-public-584/PROVENANCE.md` / source-receipt，hotkey `5ETiZDkCgKUJAWEc2xgcsaUmpXRNYiNoCG5amz72ZseSqXMx`。

`parse.rs:2063` 的 wrapper：

```rust
if H % 2 == 1 { pc_put_match_checked(...) }
else if H % 4 == 2 { pc_put_match_wrapped(...) }
else { pc_put_match(...) }
```

拟审的操作只替换第一处 callee，保持所有 H、分支条件、路由、hash、搜索、记录、其他 emitter 与 encoder。row0 是 `pc_run1c::<32769>(skip5,lazy0,full4,dp1,min4)`；row3 是 `pc_run1::<32769>(skip6,lazy16,full4)`，显式 12,000 输入入口以及 fallback 的既有分配可到这些行。它不是新的输入长度或文件名路由。

`pc_slot_of_m` 对 H32769 走 shift49：64 位 wrapping product 右移49后小于 2^15=32768，故 `%32769` 不会提供第32769桶。**不能**通过改 H32769→32768 做此实验，因为那还改变 emitter 路径、数组尺寸与可能的代码生成。本审只审 wrapper callee 替换。

## 否定重复字节扫描的直接证据

`parse.rs:1411` 明确 `pub const pc_VERIFY: usize = 0`。`pc_put_match_checked` 在合法性条件中使用：

```rust
(pc_VERIFY == 0 || pc_same(s, p - d, p, l) == 1)
```

Rust `||` 短路，左侧恒真。因此这个 emitter 在原 584 源里不会执行右侧字节验证。搜索和 backward-fold 仍会实际比较字节，但这里不存在可删除的一次重复 match 扫描。此处不需要汇编猜测或 `pc_same` 调用计数就能排除原假设。

checked emitter 仍判断 `1<=d<=32768`、`d<=p`、`3<=l<=258`、`p<n`、`l<=n-p`；不满足时写一个 literal 并前进1。normal emitter 直接写 wrapping 形式的 canonical packed token，再返回 `(nt+1,p+l)`。这些 guard 可能增加/减少编译后检查、寄存器或布局影响；源码数量不能兑换为速度，更不能解释整个 584 与 combo 的时间差。

## 父 Lean 前提没有放宽到任意无效 match

`Parse.lean:2835` 的 `PC.MatchAt s p l d` 同时要求：

```text
3 ≤ l ≤ 258, p+l ≤ s.length,
1 ≤ d ≤ 32768, d ≤ p,
Matches s (p-d) p l.
```

`PC.put_match_spec`（2992）、`put_match_checked_spec`（3027）、`put_match_wrapped_spec`（3038）、`put_match_h_spec`（3073）**都显式取 `hdec : Dec ... nt p` 与 `hm : MatchAt ... p l d`**，都保证 token 数恰增1、终点 `p+l`、out 长度不变与 Dec。这不是只证明 totality/out.length 的 SF checked-emitter 接口。

调用路径已有这组强前提：main probe 的 `FoundAt.real` 给真实 match；chain 的 `f_try/f_deepen_spec` 保持 `MatchAt`；lazy 的有效 offer 保持它；`fold_w_spec` 保证折叠后的 `Dec` 与 `MatchAt`。`run1_spec`（3757）与 `run1c_spec`（3954）对任意 input 只要求 out 足够长、H正、skip<32，内部建立并传递这些不变量，不需要从固定公共输入假定字节匹配。

在这些调用态下 checked 的所有 range guard 都真，返回值与 normal 相同。两种 pack 形式也相等：`d-1`、`l-3` 没有下溢，最大 packed token 为 `2^24 + 32767*256 + 255 = 25165823 < 2^32`；`Dec` 与 `p+l<=length<=usize.max` 提供写入和两个返回加法的界。该 normal helper 的 wrapping-u32 canonical 化**原 Lean 已经证明**，不需新建 R4 那种 pack helper 引理。

内部 helper 对任意参数不等价。例如输入/输出足够大但 d=0、p=5、l=3，checked 写 literal，normal 写 wrapping 编码；这个 tuple 不满足 `MatchAt`，父正确性接口不覆盖它。若有限 helper 测试把这种无效 tuple 当必须等价，应标注测试域错误，而不是削弱 helper spec。whole-parse 仍必须以实际原生等价和新 exact gate 验收，静态分析不是已编译定理。

## 证明迁移成本

`put_match_h_spec` 当前展开 wrapper、`step*`，再 `all_goals first` 尝试 checked/wrapped/normal 三份 spec；其中已有 `put_match_spec` 分支。**INFERRED**：只换 odd callee 后，当前 Lean 字节可能无需修改，因为相同 `hdec/hm` 直接供 normal spec。需要实际重新提取确认 helper/所有循环接口，以及原 obligation、公理白名单和 round trip；未跑 gate 前只能标 DRAFT。

即使需要修补，也应局限于 wrapper 分支证明，保持外部 theorem 的参数和后置条件，保留 root obligation，不增加 MatchAt 或缓存真值的新外层假设。没有新增循环、索引状态或新字节匹配 lemma。父原 Lean、官方旧 passed 状态及公共有限等价均不替代精确新 Rust / Lean gate。

## 同类别 R4：实际回执没有大幅稳定收益

精确 public584 odd-callee 替换未在 R20–R24 builder/报告/决策检索中找到；不能据此声称全历史不存在。但 R4 已直接尝试同类别机制：`scripts/make-round4-cpu.py` 的 `r4-cpu-directemit` 删除原 fast3 emitter 的 range/fallback，使用已有 `MatchAt`。其 Rust SHA `023d3866d4ea46eac0a5837646484d6388f3c40d1af5f57f626d67d47d73e863`，父 fast3 SHA `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef`。这次应称**不同父版的同类别重访**，不能称新发明。

已从每个原 JSONL 重算 `mean(file median(candidate total_s) / median(incumbent total_s))`，再与同块 fast3 轴比较；28文件 input/token/output SHA 全部同父。不是从 summary 标签直接采信：

|旧 run / block|directemit 对同块父版总时间轴变化|质量/有限检查|
|---|---:|---|
|37524045017 / 1|+0.547823705608%|28文件同 token/output，444有限 token/decode|
|37524045017 / 2|+0.626400411048%|同上|
|37529887857 / 1|+0.516904788037%|28文件同 token/output，444有限 token/decode|
|37529887857 / 2|−0.342995646940%|同上；正负反转未闭合因果|

原路径为 `evidence/round4/<run>/gate/round<block>-r4-cpu-directemit.jsonl` 与同目录 `round<block>-r3-432-fast3.jsonl`。四份 directemit 原 SHA 依序：

```text
55f47152fb85469ff6a1cd0a0669525fbbc0c1fd8b3e9e411feb0f25e90d3a9d
665e53c18c82ef62a8570e276bc9e0e1a5bc89285d5c3cbd7d6d1a32e13ad66f
6a4cedfdc6a44f6ad90aa17ec15f271b1687c8e55ff0bf19a4fd946bfc258edd
901fe68a850341ce5a8b5305c6ea3019c6e3b3bd8606818c4d9d537fd5c03172
```

两份 screen-summary SHA 分别 `9200ed7a0fe00642912b5a62c3d05618a6fb7a6448aebf61dfeae3dd5c50524a`、`7f4f2e2f73d4e08c4a71813cb7e69c2cb8bcb3533ab0aeb42737b2f662348c39`，与上述重算一致。R4 原证明曾在 canonical/wrapping 算术处失败；584 当前 normal helper 已有这种证明，证明机会更好，不意味着 CPU 收益更好。R4 wrapping-return 追加版也一慢一快；这次不扩大为 wrapping/layout 变体。

## 当前决定与重访条件

默认**不生成、不派发**此 exact584 变体。它具备清楚的合法调用态等价与低证明成本，但“重复全字节扫描”成本源被源码否定，旧同类别实际配对只显示约百分之零点几且不稳定的交换。现有证据没有达到主线程提出的“仅这些 guard 曾有足够大整体收益”的重访条件。

若未来出现新的同父实际工作量/原配对证据，重新投入也只允许固定一个 odd-callee 替换：实际 Rust 有界合法 helper 边界检查，加完整28原 encoder token/output parity 与独立 decode，再配对 parent / candidate-copy 原协议总时间。任何 parity 差异先查父 MatchAt/调用/overflow 边界，不调 H/路由或通过延时追回分数。是否进入完整 gate 仍由真实总成本/目标余量决定。

**VERIFIED**：VERIFY0短路、父 strong MatchAt specs、原 normal packing证明源码、H32769索引界、R4原始28文件身份和配对复算。

**INFERRED**：合法调用态下 exact584 wrapper 改法保持所有 token；原 Lean 文本可能足够、迁移成本局部。

**UNKNOWN**：该 exact584 新 Rust 的全输入等价证明、实际原生28 parity、机器码、总时间、独立复现、新精确 gate、正式准入/成绩。
