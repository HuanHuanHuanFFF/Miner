# R10 三组验收适配

`verify-three-groups.py` 只产生独立验收收据。它先核验事前冻结，再分别调用原版 `verify_adoption(D,A)` 与 `verify_adoption(D,B)`，补齐三组全局检查。没有调用 adopter，没有写候选选择、状态、模型或看板。D 在两次调用中复用，但只计一次，共三组。

当前本地验收是 **18项测试通过**。原始 artifact I/O 用合成数据替代，统计部分实际调用未改动的 `adoption-guard.validate_packets`，使用原阈值、2000次 bootstrap、Random90423。测试进程禁止执行 guard 中的 Git 子进程。实际 R10 三组结论为 **NOT_RUN**；本子任务未读取或生成预留842/843输入。

## 冻结接口

根协调者在额外组输入／结果可见前创建 `cohort-freeze.json`，并另外记录整个冻结文件的 SHA-256。运行脚本必须提供该外部 digest；仅修改冻结文件并重算内部 hash 无法通过外部锚检查。冻结文件本身不由本脚本创建或重写。

必填字段：

- `schema_version: 1`、`required_groups: 3`、`frozen_at_utc`（带 UTC 时区的 ISO 时间）、`holdouts_unseen_before_freeze: true`。
- `candidate: {name, sha256}`；`baseline: {name, sha256}` 精确绑定 `f01-r8-combined-result-guard` 和41bce485全 hash。
- `groups: {D, A, B}`，每组预声明正整数 `seed`，三者不同。D 还必须冻结已知 `run`；A/B未来 run 未知时省略。任何组可以同时冻结已知 `run`／`job`，最终严格核对。
- `selection_policy` 与原 guard 字典和值类型完全一致；`suite_sha256`、`generator_sha256` 与原 guard 常量一致。
- `reference: {incumbent_sha256, champion_sha256}`，取精确 D 原始回执，三组全部核对。
- `files` 是仓库相对路径至 `{sha256}` 的映射，至少覆盖本轮 `round-plan.json`、`prepare-plan.py`、原 `adoption-guard.py`、`public-suite.py` 和新增 `verify-three-groups.py`。可增加 tests、审查或其他冻结文件；映射中每份文件都会重哈希。

完整字段说明与最终源码／测试 SHA 在 `three-group-design.json`。脚本还核对真实候选和41源码、round-plan三组目标及原 policy。冻结与所有 helper／源码在 guard 前、guard 后各核一次。原 helper、原 guard 和原 prepare-plan 均不修改。

运行形式：

```text
python -B competitions/floatlib/candidates/f01-d7-research/round2h-20261023T170031Z/verify-three-groups.py --freeze <cohort-freeze.json> --freeze-sha256 <外部记录的SHA256> --discovery <D-run> --confirmation-a <A-run> --confirmation-b <B-run> --output <新的收据路径.json>
```

成功退出0，拒绝退出2；所有结果均为本地验收收据，不表示正式准入。输出使用独占创建，已存在的成功或失败文件都不能被覆盖。应为每次尝试指定新的收据文件名。

## 验收与保留

两次原 guard 继续负责精确原 HEAD／request／helper／Kernel、完整 artifact 索引及原字节、官方 suite／generator、完整 gate 与25轮、observer关闭、参照与同 job control、既定独立 cross-gate bootstrap。包装层不降低门槛；每组都必须 normalized whole≤0.97 且 gain p05>0。

额外全局检查要求三个不同 run、三个不同实际 job、三个不同 seed；恰好对应冻结的 D/A/B；三个非空且不同的 drawn-plan SHA；候选、41、suite、generator和两种 reference hash一致；A/B均指向同一 D 与同一候选 SHA。两份 guard receipt 的 D 身份与统计必须相同，不能将 A 重复作 B，也不能用 best2-of3 或平均值替代第三组。

实际 drawn-plan从每个原 artifact 索引定位并再次核对大小／hash，保存完整 `(name,kernel,timed,length,batch,m,n,p,work)` 向量及其指纹，同时保存其余实际生成字段向量与指纹。D/A、D/B、A/B各自报告变化的 case 名称、数量、BMM数量和生成字段变化数量。shape／work碰巧全同、生成字段有变时明确写 `VALUE_GENERATION_ONLY`；仅 JSON hash不同而实际case全同会拒绝。

两次 guard 均运行并分别保留结果或异常。即使一份 guard 因第三组偏慢拒绝，仍尝试核验并保留三组原身份、raw evidence、实际 normalized ratio、shape／生成字段与已知 p05。原 guard 在拒绝前未计算的 p05写 `UNKNOWN_IF_GUARD_REJECTED`，不填零、不伪造。基础设施或原始证据失败保留具体 stage／异常，并保持未三组确认。

原 guard 每次调用重置Random90423，先消耗D再消耗对应确认组；所以D两次统计相同，A/B各使用各自调用中的确认段流。这是两次局部 cross-gate比较跨三个数据组，不能宣称三组联合置信或正式候选对冠军的配对 admission。

## 已验证范围与交接

测试覆盖三组成功、A=B、不同源、缺第三组、慢第三组不遗漏、不同run复用同job、drawn-plan缺失或复用、reference／generator变化、冻结文件字节篡改、helper变更、policy放宽、shape巧合相同、仅 JSON hash变化、实际shape变化计数、CLI拒绝收据及禁止覆盖，以及guard期间冻结变化导致最终拒绝。精确输出保存在 `three-group-design.json`；原 guard、adopter、prepare-plan、adapter与真实状态／view前后hash相同。

根协调者接管源码后将最终代码hash写入事前 cohort冻结，再运行实际三组验收。当前工具只核验提供的冻结角色 run；额外失败、基础设施attempt或经单独授权的同payload／seed重跑仍须由协调者完整保留，不能从收据中推断“没有其他attempt”。实际 R10 输入多样性、三组性能结论、采纳与正式准入均未由本子任务执行或宣称。

已执行821／822原始drawn-plan的只读重放也通过：每组156case、152timed，结构／work变化81项，其中BMM35项；此检查只验证历史提取器，不预测额外组。
