# source-budget独立审查与修复闭环

开始2026-10-23 01:39:58 UTC，最多25分钟。只写本报告及同名JSON。未修改脚本、测试、候选或R文件，未运行Git/CI/Lean。两条旧版CLI反例在独占ignored临时目录中用冻结脚本副本重放，原输入不变，临时文件逐文件删除后移除空目录；初次系统TEMP权限失败未写入文件，该临时路径后续检查已不存在。

**发现三类真实通知保留漏项，均已先报告给协调者。当前修复版e1ee对这三条已有反例的独立复核通过；已保存的8组CLI回归receipt与raw输出一致。未发现额外确定的代码缩进/路径覆盖问题，但这不是Lean词法或语义等价证明，所有新Lean/fullgate/性能仍NOT_RUN。**

## 确定问题与原负面证据

原版脚本SHA `be0a57f8c62989506e194fa454a1fffdb74f65dd4382b0b51d3f64d0d95c8109`，4815字节。`LICENCE_WORDS`第7行只覆盖少量法律词；第29行prepare按每个comment span独立判定；第56行licence_hashes又使用同一不完整选择器。因此“被选中的notice哈希相同”没有证明所有notice保留。

1. **attribution整条丢失。** 最小输入：

   ```lean
   -- Attribution: Alice; adapted from Project X
   def x : Nat := 1
   ```

   旧版删除第一行，仍给出`code_lines_byte_equal=true`和空notice哈希列表。独立真实CLI返回0，并生成错误prepared和正常report。此问题确实影响已有47d产物：旧`c27229a9…` prepared删除c44c开头整段`Sources: supplied W10…`、FloatLib MIT/Lean Apache-2.0归属说明；不是仅有合成样例。

2. **连续行注释许可证被截断。** 下列前两行被保留，grant/disclaimer两行被删；CLI仍返回0、report仍通过：

   ```lean
   -- MIT License
   -- Copyright 2026 Alice
   -- Permission is hereby granted, free of charge, to any person obtaining a copy.
   -- THE SOFTWARE IS PROVIDED AS IS.
   def x : Nat := 1
   ```

   原报告只哈希带关键词的前两条span，漏掉同段正文。应保护整个相邻notice段，不能逐条`--`筛选。

3. **仅使用©的版权通知丢失。** 中间53aa版已修前两类，但`-- © 2026 Alice`仍被删除，report继续通过。该版本SHA `53aa85af4353599666ba7a51a6c7a465cef6568a484c431f95e1d4531281eea0`；此反例也已先报告，再由协调者加红修复。

旧原件已冻结，可直接定位：

- [be0脚本、原5组测试、旧summary及两条真实CLI反例](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/negative-sources/source-budget-licence0/receipt.json)。旧summary SHA `8ab6c7f6f47b7e582ca60a8cce6721acb382b1fb6ae7fb2b284972091386a17e`。
- [53aa脚本及©反例CLI](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/negative-sources/source-budget-copyright1/receipt.json)。

本审查JSON另保留原脚本全文和最小输入/错误输出，未用修复后结果覆盖原失败。

## 当前修复及复核范围

当前[source-budget.py](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/source-budget.py) SHA：`e1ee62f4d61219a80fffe20b54b869baf666b25d136a08a4087f3380a5d6ee51`。

修复识别author/attribution、Sources:、MIT/Apache等明确cue及©/(c)，并保护由空白连接的整个注释段，直到下一代码边界。notice哈希覆盖段内全部comment spans，含grant/disclaimer。它可能保守保留更多普通注释，影响压缩量；不保证识别任意自然语言归属。

本审查对上述**恰三条**已有反例重新执行prepare/report：三个输入的通知与完整源字节均保留。此前对53aa的窄复核也已确认实际47d归属块恢复；不将这个单源检查写成所有重新准备文件已审计。本轮没有扩自然语言词网格或重扫七源。

协调者保存的[8组CLI回归receipt](/D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/source-budget-test-evidence/receipt.json)绑定同一e1ee、测试SHA `a0fad18716e57206ed4f1e9d36c4bf96016a464803518798653dee66119fde9e`，退出0。raw stderr为`Ran 8 tests … OK`，111字节/SHA `7827e0ed5b940751bb337fa33ba02dbfd2c679685d6227b0e3eaadcb2b0c1f4e`；stdout为空。本审查核对原件与哈希，没有把自己的三个内存反例说成另一次完整8组运行。

两份既有nested/layout fixture增加了namespace代码边界，使无关普通注释仍被实际移除；不再要求工具截断相邻法律段。这与保守保留目标一致。

## 词法、布局、文件与报告边界

源审查确认：嵌套block按depth扫描；只有起止物理行前后均无代码时才删整行comment；替换保留一个EOL。存在真实代码的物理行，包括缩进和行内comment，都由原始字节进入code-lines比较。live双引号、backtick和UTF8 quoted-id定界符在comment外被拒绝，main完成prepare/report前不写产物。未发现本轮另一个确定普通注释/布局反例。

**同一个comment scanner同时定义“code lines”和验证输出，不能据其自洽推出真实Lean解析等价。** 文档元数据/行号会改变；新源仍须自身Lean及完整gate。此工具不是Lean parser。

路径审查覆盖resolve后三路径互异、既有artifact与symlink拒绝、父目录存在及`xb`/`x`独占创建；没有发现确定覆盖原输入/既有产物的漏洞。两个输出顺序写入而非事务写入：若后续report I/O失败，prepared可能留存，但进程失败；不能把文件存在单独当作成功。现有成功判定还需读取report、核完整SHA并检查size-fit字段。

原be0七份预检在审查开始时已逐项核对：输入SHA均与原候选一致，prepared完整SHA、report内容均匹配旧summary。3d9的230650→209038是真实旧版字节计数，**不是有效notice保留、Lean或性能结论**。旧47d归属损失使旧packaging认证不完整，原prepared按负面证据保留；修复后的七源重算由协调者另行完成，本报告不把旧summary归给e1ee。

此前W13c/353d等报告保持原字节。除三类notice缺口已修外，本轮不声称工具已对全部Lean词法、任意许可证措辞或实际gate给出完整保证。
