# A16：按既有近距拒绝域保留旧head

缺口：A14的metadata提速失败，A15的固定历史距离替换在所有活动输入上负决策次数多于正决策。现在用一份真实parser直接测质量，不再只累计局部机会。当前head的近距来源可使primary返回无匹配，随后原chain不再消费更旧来源。

变化：保持原641的consumer、hash、数组、normal/lazy预算、记录位置与发射。在现有link调用处，若新位置p与该hash的旧head间距为2..8且n!=500000，就让这次head/prev更新为空操作；否则执行原`pc_f_link`。distance1和原500000例外保持原行为。8来自原consumer的固定拒绝规则，只有这个版本，不扫描距离、频率或容量。

消费者预审：`pc_f_link`生产者仅有6个原调用点，分布在`pc_f_record3`与`pc_run1c`。本轮source检查逐个替换并能精确反转回父源码。此head用于同一个chain内核的`pc_probe_m`、`pc_probe_lazy`和`pc_f_try`，三个helper都保留同一个2..8、n!=500000早退规则。其他PC单head及其他引擎不使用该producer，原样保留。

这**不是语义等价修改**。旧位置目前不可用，不代表新位置在未来不可用；保留旧head可能失去以后更近的来源、改变链和lazy轨迹，也可能让较老的可用来源重新成为primary。这里的论据只支持一次真实质量比较。它不同于A7放宽consumer，也不同于R25按固定位置减少记录。

环形prev边界：空操作同时不改head和prev，不让head指向一个未设置prev的新位置。其他已有head仍可能涉及环回覆盖，沿用原`pc_f_try`的递减源、窗口和字节检查；不把这条结构观察写成完整链顺序等价。父证明仅维护head位置上界，no-op保该上界，update复用原helper；新wrapper仍需要精确提取、Lean接口规格和完整gate。

最小动作：原28完整parser/encoder及独立decode，与641保留所有增减字节；现有原生有限decode入口包含短/边界生成输入。若输出变差、仅稀薄改善或实测触发域不可解释，则停止；若实际质量规模/成本假设值得继续，再独立记录触发数并跑原协议总时间。减少写次数不能当速度收益。

成本：只在临时Linux runner编译，建议15分钟外层cap；无新长期状态，无额外match probe。首次native只区分真实输出，排队和时间收益UNKNOWN。UTC09:18:52冻结保留及最后90分钟gate/确认仍保留。

冻结Rust `83ae95175233346aebacbadadb0440d78b19e97676104626ce1fa76422d4fe72`；父Lean复制未适配。生成器`scripts/r26-a-build-near-retain.py`，候选`candidates/r26-a-641-near-retain`。
