# A23：V1 原始端点 CPU／时长及 cgroup 独立复核

复核时间：2026-10-12 UTC 10:07–10:15。只使用已经收齐的运行38233428813及已保存官方文档；没有 CI、网络查询、候选／配置修改。根线程的 `extension4h/v1-analysis.json` 总计数与本次独立重算一致。

**结论：V1 成功补齐了可见cgroup链的控制器状态，并取得可按调用身份关联的CPU端点／阶段时长。它没有识别A19历史根因，也没有证明迁移导致或不能导致当前时长差。** 两次较长阶段与端点变化共现，另一次端点变化没有相近幅度的耗时增加；相同CPU端点的跨进程样本仍有一组完全不交叠。所有这些是新runner、同一scratch引擎下的描述性观察，不修正候选成绩或正式概率。

## 身份与数据核验

没有调用根线程分析器或V1自己的 `verify_trace` 代替复核。本次从原JSONL的每文件／方法／rep构造预期键，与trace的 `(file, method, round, phase, order_index, stage)` 独立逐项连接，并另行按实际CPU端点分组重算。

- 下载清单的11份原文件，字节数和SHA-256全部一致；receipt内部10份artifact哈希也一致。
- 两进程各1344条stage事件，其中112条warmup、1232条measured。2688条全部连接到原JSONL，parser／encoder的原elapsed值逐项完全相同，无重复／缺失键；外部单调时间括号均覆盖记录的原elapsed。
- 两进程使用同一scratch engine `153c5185f08697c6dea13efd7aa8a797548cc3303595950ab122818640c01156`，与未改的原engine `ab202460691492f48d5c632375f5df2a74fc3769a81337e876607e9326a46fac` 分列。
- 两份DSO在两个进程与A20一致：incumbent `141f58ceb5d68fdd9fef84fc9da46540dfd34174de8533d923ef187ae09ec57b`；public658 `5445a65b8a70a125c25d25b2b560aa751dcadad5f4b7343b266044345fa70d29`。112个“进程×文件×方法”输入／token／output身份与A20原引擎回执相同。
- 原官方pins前后相同。云端保存的scratch diff仍只在原timer之外加采样，原stderr末尾输出trace；这证明记录位置与身份，不保证额外代码没有改变调度、缓存或机器码布局。

[原始目录](../38233428813/verify-callcpu-v1-diagnostic/diagnostics/r26-v-call-cpu/)；运行提交 `9c4cfc0941cbe2007bdcc8ec12eb32ef95ae8b39`，CI success。`receipt.json` SHA为 `76539b67b0c7028fae5f61ab7faae6a049e34648ef0578885f4788c65d0ce914`；所核根线程分析SHA为 `aa2c23e1abf4911969d1c5d3b71d5988df8c438dea3c919ef62c6ad53d3de799`。

## CPU端点与时长：有共现，没有因果闭合

两进程同为AMD EPYC 7763。精确已执行engine身份为PID6318／starttime38633、PID6326／starttime39970，各有52个外部匹配样本，全部绑定本次Popen子树、scratch exe及PID启动时间。实际affinity始终0–3；外部监控线程都固定CPU1。

| 过程 | measured stage事件 | 端点相同的分布 | 端点不同 | 外部last-executed CPU采样 |
|---|---:|---|---|---|
| 1 | 1232 | 3→3：520；2→2：108；0→0：602 | 3→2：1；2→0：1 | CPU3：24；CPU2：7；CPU0：21 |
| 2 | 1232 | 2→2：12；3→3：1219 | 2→3：1 | 52次均为CPU3 |

两进程没有负getcpu读数。**这些计数不是迁移率**：相同端点可能中途迁移又返回，调用之间也可能迁移；外部4Hz采样会漏掉短阶段。过程2开始时的CPU2及2→3事件没有出现在其52个外部样本中，直接说明稀疏外部观察不能覆盖逐调用状态。

三个异端点事件逐项保留。下表差额只将该事件与**同进程、同文件、同方法、同阶段**的其余同端点事件中位数比较；不是配对因果效应或显著性检验。

| 过程／具体调用 | 端点 | 原stage耗时 | 同组其他同端点中位数 | 描述性差额 |
|---|---|---:|---:|---:|
| 1，metrics.csv.txt，incumbent parser，rep10/order285 | 3→2 | 46.884551 ms | 38.9320325 ms | +20.4267% |
| 1，prose.txt，incumbent encoder，rep4/order345 | 2→0 | 21.127849 ms | 17.7645855 ms | +18.9324% |
| 2，binary.db.bin，incumbent parser，rep4/order9 | 2→3 | 8.834463 ms | 8.7634395 ms | +0.8105% |

前两项与较长耗时共现，不能忽略这个线索；第三项也必须保留，不能推导“异端点会增加约20%”。CPU变化可能发生于计时外采样间隙，阶段变慢与端点变化也可能同受调度／主机状态影响。没有调度trace、每调用CPU周期或频率，无法把增加的时间分配给迁移本身。

## 跨进程可比性与没有复现的部分

独立重算得到239个 `(进程,文件,方法,阶段,CPU端点对)` 分层。跨进程有48组同文件／方法／阶段且相同CPU端点的比较，全部是3→3；每边至少7个样本，不存在少于3例的稀疏比较。它们只覆盖CPU3共同出现的部分，不能代表所有CPU、全部文件或其他runner。

这48组中只有一组原始min–max区间完全不交叠：catalog.xml.txt的public658 parser，两边均11例、均3→3。过程1范围1.854747–1.881225 ms；过程2范围1.835751–1.852091 ms；过程2中位数低1.36629%。正确结论是**端点CPU身份不能单独消除这组过程差异**，不是“排除了迁移”。其他47组区间交叠也不是相同分布证明。min–max是否相交依赖样本数，不提供显著性、误差界或稳定概率。

另将CPU端点暂不分组，完整比较全部112个同文件／方法／阶段的11对11原样本，仍只有上述catalog一组完全不交叠。因而本次没有重现A19那种多文件连续阶段整体不交叠的广泛偏移；不能只凭48组子集作这一判断。仍保留较大的单项中位变化：public658的weights-f16／bf16／q8 parser分别约+16.00%、+14.21%、−12.38%，但各自原区间交叠，且过程1端点0→0、过程2端点3→3，CPU、进程、调用时序混杂，正负也不一致。它们不能成为CPU3统一更快或更慢的结论。

当前设计没有随机分配CPU或固定单核控制；CPU0只在过程1出现，CPU2出现在两进程的不同时段／文件。不能把CPU与进程、文件先后、热状态的作用拆开。异端点仅三项，也不能解释A19或预测未来发生概率。A19是另一台Intel runner与原引擎；本次是AMD runner上的scratch引擎，不能跨运行对齐成因果对照。

## cgroup：已从缺文件推进到可见的传递断点

下表只列cpu／cpuset两种控制器，其他控制器省略。两个过程在全部52样本中的这些路径值均保持一致；各自的最后scope名字不同，但祖先链相同。

| 可见层级 | controllers中可用 | subtree_control向直接子层启用 | 相关文件观察 |
|---|---|---|---|
| `/sys/fs/cgroup` 根 | cpu、cpuset | cpu、cpuset | cpuset.cpus.effective=0–3 |
| `user.slice` | cpu、cpuset | cpu；**没有cpuset** | cpuset.cpus为空、effective=0–3；cpu.max=`max 100000` |
| `user-1001.slice` | cpu；无cpuset | cpu | cpuset文件缺失；cpu.max=`max 100000` |
| `user@1001.service` | cpu；无cpuset | cpu | cpuset文件缺失；cpu.max=`max 100000` |
| `app.slice` | cpu；无cpuset | **没有cpu，也没有cpuset** | cpuset文件缺失；cpu.max=`max 100000` |
| 本次 `run-….scope` | 无cpu、无cpuset（仅memory/pids） | 无二者 | cpuset／cpu.max缺失；cpu.stat存在并增长 |

这是比A20更强的直接状态证据：**cpuset在user.slice向user-1001.slice传递时没有启用；cpu在app.slice向本次scope传递时没有启用。** 所以“scope内cpu.stat增长”不能证明CPU或CPU集合限制工作。两个概念也不同：AllowedCPUs对应cpuset，cpu.max对应CPU带宽；不能用后者存在与否代替前者。

依据为主线程已经捕获、此次再次核对SHA的两份一手文档：[Linux cgroup v2保存原文](../extension4h/measurement-followup/kernel-cgroup-v2.html)说明父层subtree_control决定子层控制接口，cpu.stat在cpu控制器未启用时也存在；[systemd v255保存原文](../extension4h/measurement-followup/systemd-v255-resource-control.xml)说明AllowedCPUs作用于cpuset，实际值应另查EffectiveCPUs。文档解释接口，不证明本次runner安装了v255。

仍然缺少：实际systemd版本、对应scope／父user服务的AllowedCPUs、EffectiveCPUs、Delegate／DisableControllers等管理器属性及设置过程。当前可定位**内核可见状态在哪里没有向下启用**，但不能给出具体systemd配置责任、忽略请求的实现原因或一条已经验证的修复。该可见链上的cpu.max为max也不能推出宿主没有其他限制。所有CPU频率字段仍为FileNotFoundError；频率及虚拟化／宿主调度因素保持UNKNOWN。

祖先cpu.stat是聚合计数，不归因给本次engine；监控只沿当前engine所属路径的祖先读取，没有读取其他进程环境或修改配置。外部Unix时间与trace的进程相对单调时钟未作精确同步，不把ancestor计数与某个call按纳秒配对。

## 对后续工作的含义

此次关闭了“CPU0请求是否确实只限该engine”和“相关控制器在哪段可见链缺失”的观测缺口，没有关闭时长分歧根因。若未来获授权修复环境，应先将管理器请求、内核控制器状态和实际engine mask分别核验，再把“限制生效”与“副本差异是否改善”作两个验收；R24显式绑核未统一缩小差异的反例仍有效。本次不建议自动改配置或追加CI。

V1的原始时长全部保持diagnostic角色，不加入候选分数、冻结确认或正式成功率；不因少见异端点而删掉慢rep，不生成校正时间。A19的所有峰值、零值和未闭合因果原样保留。
