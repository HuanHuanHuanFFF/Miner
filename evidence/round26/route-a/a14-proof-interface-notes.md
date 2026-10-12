# A14 证明接口预审（未写完整证明）

冻结Rust `f5350f86643ca65b955b4739165c6f04b27ef673a6e986c1614257687618e04c`。父Lean `7a30722b3a337918422e3af277bf33f48073594483b9df7a7ae3c43cbf81412e`，487015B；512KiB限制下剩37273B。原pc_run1c在fallback可达，不能删旧chain证明。新的完整证明/编译/公理审计均未运行。

可以避免证明标签的语义可靠性：原obligation要求合法解码，允许漏匹配。`at_probe`与`at_lazy`的miss分支返回(0,0)，用已有`FoundAt.none`；非miss分支才需要原位置与`word8`身份。标签拒绝不影响token的更强性质已经接受原生有限核验，但它不是完成原obligation必需的引理。也无需把prev加上标签语义；原`pc_f_try`对候选位置和输入字节再次检查。

最小新不变量：

- `PosHeadBound head B`：每个head的低24位位置不超过B。保留mono/init/set/get形状；link只需证明`(p | (tag << 24)) & 0xffffff = p`，前提p<2^24来自入口与当前位置边界。
- 缓存槽只需`a & 32767 < H`，不需要a本身小于H。`at_key`结果、旧tag组合都最多31bit，因此32/64位usize均可表示。
- `c & 0xffffff <= B`；`c < 2^24 -> w = word8 s c`。miss标记为第24位，原成功primary分支的c会显式mask后交给原deepen。
- `at_ahead_fix`复用时比较重构旧head与当前head；从head低位界恢复缓存位置界。word身份只取决于不可变input和原缓存，不必维护旧tag等于源字节hash的不变量。
- record/main/lazy沿父版的终止度量、Dec和MatchAt。record的首次slot条件改为低15位；新H前提在非fallback为32768<=H。原loop中的剩余bit、cast范围由独立小引理封装。

原PC中可复用的证明包括`be4_spec`、`be8_spec`、`probe_m_spec`、`probe_lazy_spec`、`f_try_spec`、`f_deepen_spec`、`fold_w_spec`、flush/emitter/tail的证明模式。只移植chain专用循环，不复制无链`pc_run1`证明。粗源码分段显示主/惰性链循环与record约12KB（其中try/deepen仍可共用）；新head/cache引理及不变量可在剩余37KB内争取，但尚未生成或编译，容量和编译时间保持UNKNOWN。

接入点在父Lean的`p135_row*_spec`之前加入新namespace和`at_run1c`规格，再为原13个调用所在的row启用新step规格；旧`PC.run1c_spec`仍用于fallback。精确提取后的`slot.at_*`实参、loop返回tuple和名字必须从该Rust的真实产物读取，不能按Rust外观猜测后直接宣称可验证。

投入条件：先看A14原协议整轴和同源码对照。一个明确回退不值得将完整证明当补救。若仅小正而当前5%规划缺口更大，保留可组合组件，但完整gate投入仍与其余路线和确认时间比较。
