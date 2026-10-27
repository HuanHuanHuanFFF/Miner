# 40410895344：最小证明修复副本，待复编

当前副本 `Kernel-dual-temporal-a4-proof2.lean`：**d765bd41234a26640eaa6df6c7134e0d4d8dca760e50eaef3aa82eff1fac0847**，240398 B。只改 `Submission.R19DualTemporal.loop_eq` 与 `group_eq` 两个证明体；所有运行体、域谓词、原finish/replay、各定理声明和其他证明逐字相同。原9a5源码、原裁剪patch均保留。

已按D的原artifact索引逐字核对并复制5份原件到 `../ci-40410895344/`。原input精确9a5；verdict SHA `724dfa20ceae78ddaf80bce3dcdfbddeaa518d3e7711a4a87857329ba29fc435`，full-build-output SHA `46baed359ad365307302e2eacfbf6cecad0cc313b41565247a0919dc0afffe5a`。错误限定为loop_eq五次旧循环方程展开失败，以及group_eq展开后剩余等式；statement失败，**内核重放、18根审计、C/ASM和性能均未运行**。不能把同批其他候选的状态移给本源。

修复假设是长度别名 `blocks n` 与 `(n+3)/4` 的证明匹配问题，尚未经编译确认。loop_eq开始显式展开类型/前提中的blocks，再只在RHS展开旧R19Temporal.loop；group_eq在简化后用定义相等闭合。没有改循环、改变存储/索引、添加假设或减弱规格。

`repair-receipt.json`保存原件定位、两处证明范围、原policy检查与18根；`proof-only.patch`已在内存反向应用并精确恢复9a5。掩去这两个证明体后，新旧完整片段相同，前227238字节也不动。新副本的Lean、C、原gate和性能仍 **NOT_RUN/UNKNOWN**。

交D下一次真实检查仍是该精确副本的statement→原内核重放/18根审计，再抓真正R19DualTemporal active链/新loop ASM。若复编仍失败，保留新错误后再修；不凭静态检查宣布问题已解决。
