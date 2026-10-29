# R24 scalar：目标变化后的可复用机会与停止线

UTC2026-10-28T21:00Z；只读新赛道分析。D尚未给迁移实现指令，本文件不启动新赛道实现、证明编译、CI或参赛。旧成本包e31d/254738B保持冻结NOT_RUN。

21:18Z补充：`native-add-adapter-audit.json`对精确F7 statement侧C复核后发现其Model/word adapter本已消除。下述native ADD只可能是新Model.add caller的不同算术路线，不能声称给旧F7删adapter。六根数学草稿停止在API运输，不据此补新candidate/CI；精确命题和NaN/Inf/±0边界见`RAW-NATIVE-ADD-INTERFACE.md`。

## 1. 已读的精确对象

- D固定TorchLean官方源`accb82b6e2adeda1b41a57a260d68fb3879c427e`；新`ContractExact`是raw UInt32接口，精确dot/sum最后一次舍入，linear/conv的bias同次舍入，scaleShift是FMA。旧left-fold SUM/BMM及rounded scalar MUL不能替换新dot/FMA的内部精确项。
- 本目录`source-cache/retrieval.json`保存19个公开一手源码，**154624B、19/19 Git blob逐字匹配**；固定FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`、Lean4.34。未复制前冠军实现；其D侧254884B/cea442…源仅作只读结构参考，复用许可由D核对。
- 旧R2 `numeric-decode-hypothesis.md`已经提出全finite的subnormal-scale表重建。该思路没有新增机制，**不据此重复旧实验或大证明**。实际吞吐、低指数范围成本仍UNKNOWN。

## 2. 最高价值的下一项判别：finite native ADD直达新addRelu

新`addReluSpec`逐元素执行`toWord (Model.add (ofW a) (ofW b))`再ReLU。旧raw→native→ADD→raw的有限输入桥仍有机会：**这是一次binary32加法，可以复用同宽语义；不用旧SUM/BMM的逐步舍入**。

关键已有接口不是新大证明：固定FloatLib `Native/AddSub.lean`的`ExecFloat.Binary.toModel_ofFloat32_add_of_isFinite`（150–164）、`ofFloat32_add_of_isFinite`（241–247）已连接有限native ADD与Model.add。`ExactToolkit.Decode.isFinite_ofUInt32`把raw指数≠255接到Model有限性。`Native/Model.lean`有`ofFloat32Model_toFloat32Model`、`canonicalizeModel_eq_self`；旧B2的`NotNaNProbe.modelCanonicalOfNotNaN`也是小型可复用证明。

待闭合点：raw有限字与`Float32.ofBits`的canonical roundtrip；native sum→toWord的逐位身份；原ReLU的−0/NaN处理；数组输出与原`a.size`、`b[i]!`行为一致。只在finite pair上走native，其余精确Model fallback，不能默认NaN payload等同。先用逐元素guard，是否做整数组预检必须计完整扫描/准备/释放成本。

`NativeWordAddBridge.lean.inc`提供6根**NOT_COMPILED**的FloatLib-only数学草稿，不定义新赛道kernel。它先证明所有raw word经过native ofBits后的unpack保持，再直接复用`Model.add_eq_ofModel_add_of_isFinite`，所以无需让NaN payload roundtrip假设进入finite ADD证明。仍需最小remote typing/重放/AX核验；这里只做接口储备。

D侧前冠军源的完整文本没有显式`Float32`或`toFloat32` token；其scalar ADD/FMA入口为word整数快路＋fallback。这只说明**显式源码路线不同**，不证明其最终二进制没有native操作，也不支持收益。新模型中addRelu的真实成本份额UNKNOWN；不得把旧ADD约36–39%整包份额迁移过去。最小实验应先取新模型profile和精确调用链，再比较完整elem/kernel与整模型，含raw转换、NaN miss、ReLU、输出和释放。

**旧负面约束不能跳过**：合入的`research/deepseek-20261025/R19-SUMMARY.md`记录40405652739，旧79022b4a源的convert→ofBits（ADD＋MUL）归一化whole1.1215、ADD1.1558、MUL1.1375，明显差于B2的数值表解码。该精确候选SHA现已重新核到`79022b4a59457e5254e35440c85989c45dff5d38dddbfa614a36a8fe3eaeeca3`；本次没有重算其25轮原数据。故新目标中direct-ofBits native ADD只能作为**对整数基线的新调用关系**实验，不能宣称bitcast免费，不能复活旧B2替换体；需要另列既有数值table decoder对照或在实际ASM确定转换边界。表解码证明/源码能否在前冠军仅1116B余量内集成UNKNOWN，未授权复用前冠军前不组包。

一手源：[FloatLib有限native ADD桥](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/AddSub.lean)、[native表示桥](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model.lean)、[新raw contract](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ContractExact.lean)。

## 3. 已排除的便宜但重复的FMA提案

不能把Model.fma当纯大整数规格，然后声称换`softwareFma32`能删掉大整数计算。固定FloatLib `Arithmetic/Runtime.lean`定义Model.fma→FmaBackend.dispatch；对binary32，dispatch直接到`FmaBackend.word`，再到`NativeBinary32.fmaFiniteImpl?`。`softwareFma32`复用同一word算术，仅将carrier adapter固定；是否改善codec/调用边界需要实际C/ASM/成本证据。

Lean4.34的已读`Float32.lean`/`Float.lean`没有导出fma/mulAdd；跨宽`Float32.toFloat`和`Float.toFloat32`仍opaque，不能拿host双精度或“两步mul+add”冒充已证明的single-round FMA。完整工具链其他模块是否有可用精确FMA原语未作全局断言。

即使补齐跨宽语义，**binary64 mul+add再转binary32也不是全输入FMA**。`fma-double-counterexample.py/json`保留5个精确整数反例：`x=0x3f800001`、`scale=0x3fc00000`、`shift=−2^-54`（也可−2^-60/80/120/149）。精确single-RN32是`0x3fc00001`，binary64中间步骤丢失负微量后给`0x3fc00002`；乘积恰为RN32中点，负微量必须把它拉到下邻。这是有限具体反例，足以否定不加guard的全输入替换；不是所有受限跨宽域都不可用。

一手源：[FMA dispatch](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Dispatch/Fma/Runtime.lean)、[word FMA](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Dispatch/FmaWord/Runtime.lean)、[direct carrier软件FMA](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Runtime.lean)。

## 4. 旧目标的不同算术储备：全normal输入整数MUL

`NormalAll.lean.inc`仅研究草稿；`normal-all-model.py/json`对全部64516指数对×8分数/符号组合＋100000固定随机＋8边界，共**616136**例，通用exact-integer RNE及精确binary64产品→binary32两对照无差异，trace`2066a197…`。不是Lean证明/计时。

令正常输入精确乘积为`p·2^(s−300)`，`2^46≤p<(2^48)`。新分支不是扩大旧normalCore守卫：s≤102直接有符号0；103≤s≤127按次正规格点`RNE(p/2^(151−s))`编码，允许接入最小正规；128≤s≤380复用旧核心；s=381显式按舍入后指数clamp∞；s≥382有符号∞。正常输入覆盖由48259增至64516指数对，新增16257，**不是输入概率或CPU份额**。

旧381/382反例现在走显式∞分支；zero/subnormal/NaN/Inf输入仍fallback。未知：新guard、分支与乘法位置是否更便宜，尤其原LowScale已很便宜；新域性能与Lean证明均UNKNOWN。新TorchLean没有公共rounded MUL entry，此储备不值得因迁移而立即补大证明；可复用的是未舍入24×24产品语义，不是它的最终RN32输出。
