# R11 结构组合构建器：默认仅干运行

工具：`compose-structural.py`。本轮只运行干运行与自检，没有新建候选目录或写出Kernel。Root在914/916完整成本回收并选模块后，才调用显式`--write`。本工具不估算组合收益，也不启动Git/CI或Lean工具链。

## 精确输入与组合顺序

|模块|固定SHA前缀|字节|
|---|---|---:|
|compact fused基座f2fa|f2fa8d10872e|236400|
|Cross P12 proof2|5c5e70719274|252699|
|Cross唯一short-shared替代|7cad7df494da|254550|
|Underflow proof2|6a69d6edd8af|244896|
|DirectContinuous|2aaa5d9e84c7|248566|

完整SHA、原路径、增量范围SHA和大小都进入每次干运行JSON。Cross与short互斥；batch-local28af不在允许recipe或输入中。原5b也固定读取，作为S/O精确删段的哈希核对原件，不作为新父本拼接。

所有recipe都从f2fa开始，按`review-integration-headroom.json`的精确整段删除S1–S5共5011 B、O1–O5共2837 B。偏移只用于从精确5b取待核对原块；SHA、完整起止锚点及实际组合中的整块唯一匹配都必须成立，不能按历史行号切当前源。f2fa已有P链净省9441 B，不重复裁剪。当前sum真正的SinglePass Nat回退、NativeFinal.dot、原字NaN回放和Cross消费的DirectRows.core/证明都保留。

增量只抽取完整namespace及原归属注释，不拼接多份共同父本。分派顺序是：

1. 下溢若选中，最终`bmm`命中返回zeros，miss调用`bmmBeforeUnderflowZero`。
2. Cross/short若选中，上述下一层是原Cross条件，命中R11CrossRows.core，miss调用`bmmBeforeR11Cross`。
3. 内层是当前DirectContinuous或旧DirectRows的`n≤4 ∧ 2<p`分支，miss仍到fused父本的bmmBeforeDirectRows，再按原空维数/n=0/机器边界/NaN规则执行。

别名从“当前组合的最终bmm/spec”逐层改名，而非复制组件自身原a066 fallback。静态调用链检查会拒绝错误的miss重接。所有新增组合Lean、公理、checksum、完整gate和性能都是NOT_RUN；组件通过不能替代新组合验收。

## 使用

从仓库根目录干运行：

```powershell
python competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/compose-structural.py --recipe cross+underflow+direct
python competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/compose-structural.py --recipe short+underflow+direct
python competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/compose-structural.py --self-test
```

可选模块只有cross或short，以及underflow、direct；`base`表示仅固定基座和精确S/O精简。未传recipe时默认对cross+underflow+direct干运行。`--self-test`检查12种合法模块选择，属于组合工具验证，不是性能或参数搜索。

仅Root选定recipe后调用，例如：

```powershell
python competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/compose-structural.py --write --recipe cross+underflow+direct --output-dir f01-d11-selected-r11
```

`--write`必须显式recipe和全新目录，目录必须直接位于candidates且名为f01-d11-*，任何已有目录均拒绝覆盖。可用`--report`指定本轮review-output-composition-*.json；其它报告路径拒绝。全部输入哈希、路径与静态检查在候选写出前核对，写出的Kernel还会逐字节核对；本轮未实际执行落盘分支。

## 已验证结果

|干运行recipe|组合字节|余量|普通空白行处理|
|---|---:|---:|---|
|cross+underflow+direct|254588|1412|无|
|short+underflow+direct|256000|0|从256439删439个注释外空白行|
|cross+underflow|251863|4137|无|
|short+underflow|253714|2286|无|

只有三项都选中且超上限，才允许补删普通源码空白行。词元、证明非空行、注释内空行、许可／归属文字不改。该步骤验证所有非空物理行逐字一致、所有注释的字节与顺序一致；不会删普通注释来取空间。short四模块现在恰好到256000 B，没有剩余字节，不隐含允许后续扩大。

每次JSON保存完整可逆edit ledger：阶段前后整文件SHA、准确byte位置、旧/新段SHA及原文。构造后按倒序逐步核对并逆变换，最终必须恢复精确f2fa全字节。许可／来源注释的受保护段hash按模块和共同基座盘点；最终计数必须完全一致。

静态策略直接加载固定4b7原gate的policy/options函数及常量，使用仅返回内存源码的接口，不运行gate或外部工具；固定gate SHA为1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194。另查namespace闭合、重复完整声明、四export/spec各一份、已删链残留名字、必须保留的回退及实际分派体。

`review-output-composition-selftest.json`记录12种recipe全部通过、每份逆变换、篡改逆变换拒绝、错误recipe拒绝、缺显式recipe／target和已有／越界target拒绝，以及原policy对内存中的禁止词负控制拒绝。所有测试都没有写Kernel。精确原件保持不变。

当前限制：静态名字盘点不等于Lean依赖闭包，语句和原完整gate仍需Root对选定新SHA运行；组合性能UNKNOWN，不把局部降耗比例相加。首次实际`--write`由Root执行，本轮只核对其路径拒绝与干运行行为。
