# Astra／开发协作：一小时窗口

窗口：2026-10-21 10:32:09—11:32:09 UTC，北京时间18:32:09—19:32:09。用户要求创建GPT-6 Astra研究会话，使用huan-collaborate，优先优化当前落后最多的运算。主开发会话统一提交、推送与CI；研究只写分配目录，通过文件交接。当前总体状态：[development-status.json](../../../coordination/development-status.json)。

研究会话：01a15e06-b75c-7811-b0a0-194d8877365d，GPT-6 Astra/xhigh，已实际进入执行；任务交接见[astra-handoff.md](../../../coordination/astra-handoff.md)，研究检查点见[research-status.json](../../../research/astra-collab-20261021/research-status.json)。

## 已取得的结果

- 原生加法路径7f51b433…已通过一次完整官方gate：精确四义务、kernel replay、仅允许三公理、12类25配对轮，CI39589111347。生成C确认使用lean_float32_add和有限值检查，特殊输入保持原精确回退。
- 对精确公开起始参考，该次整体耗时比0.623247；分项add0.619428、sum0.378156、bmm0.584480，mul未修改。最终CI39590684208已收回：原生加法第二次完整通过；原生加乘和原生累加器sum也各自完整通过。追加半小时窗口内已启动冻结原生加乘／sum独立复测39593447390，等待其完整回执。
- 直接点积循环完整通过，但bmm仅小幅改善；其相对起始版的收益包括继承的基址外提。进一步核查parent实际C，parent也已有特化循环，不能把全部收益归给消除通用回调。
- 乘积Vector缓冲完整通过但更慢；直接sum循环完整通过但sum退化；只强制tensor inline几乎无收益。全标量／张量入口展开有小幅收益。上述具体版本不继续推进。

## 真正改变起点的发现

固定Lean4.34中的Float32.add有公开逻辑模型；固定FloatLib已存在有限输入的ofFloat32_add_of_isFinite定理。研究R找到、D按真实let展开错误修复后，该路线已通过完整gate和公理审计。它与旧的Unchecked后端是不同入口，不能从旧后端缺证明推断整个原生路线不可用。

乘法补桥接采用FloatLib Team/MIT公开commit1f5771b3…的三个targetExponent引理，适配入候选，官方pins、依赖、contracts、bench、gate保持原版。初稿暴露Sign、signed-zero和roundWithAccuracy前提缺项；修稿补齐该条件，后续实际错误为文档注释放在namespace前及相对Numerics命名空间。最终修复版707d22fe…已完整通过CI39590684208，整体耗时比0.557467；仅允许Classical.choice、Quot.sound、propext。来源及许可见研究source receipts，不把公开数学引理说成自主发明。

原生累加器sum75524a31…已通过statement与bench编译：Option Float32尾递归，成功时逐步等价，守卫失败整体回退；保留原加法次序与舍入。完整gate、公理与性能已通过CI39590684208，sum耗时为起始参考0.241643；整包0.838004。

## 证据与复核

[summary.json](summary.json)逐行区分完整gate、仅编译、失败和未收回结果；所有性能比值在此证据层均为同runner候选／精确起始参考。用户看板另按冠军基准、四运算展示，换算单列依据。未取得现任冠军源码，未正式提交或进行资金操作。

运行本目录audit-window.py重新核对：源码与输入字节、原始artifact每成员SHA、12类和25轮、完整指纹、headline和配对收益。--git另核Git提交内原始payload字节；本地自检不替代Lean或性能验收。

原始回执在candidates/f01-mul-log2-proof1/ci-runs/。已失败的证明、慢样本及原件保持字节；字段或叙述修复写入新候选与派生摘要，不覆盖原件。最终批次实际于11:16:07启动，晚于内部11:15排队检查点67秒；共同用户窗口结束时间不变，后续仅回收、核验与收尾。

## 追加收尾窗口

用户随后要求“把新增实验做完，半小时内”，窗口2026-10-21 11:34:07—12:04:07 UTC。只为既有冻结候选补独立确认，不再展开新机制；CI39593447390种子221于11:38:28启动，包含同源码参照、原生加乘与原生累加器sum。当前等待结果。
