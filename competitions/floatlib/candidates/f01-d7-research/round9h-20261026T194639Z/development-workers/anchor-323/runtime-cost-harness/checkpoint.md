# 前15分钟可行性判别

UTC 2026-10-27 00:13；接手00:01:23，30分钟上限00:31:23。只写本目录，无Git/CI/本地Lean/新agent。

结论：有小接口可复用，值得落一个NOT_RUN草稿；并非零构建成本。官方BenchSuite.run直接接受typed四个callback。独立Lean模块可把MUL绑定到`@[inline] guardedMul Submission.mul`，ADD/SUM/BMM固定原B2；同一新binary另含control分支，variant选择放计时之外。不调用noinline diagnosticEntry。

- capture-mainfull/capture-codegen是原gate输出观察器，不能直接替换callback或生成新binary；不改写它们。
- R13 whole_multi已提供完整156行parser、checksum核对和原BenchSuite计时进程模式；可直接复用parser，不复制stage框架。
- 固定Lean293d的Lake CLI确有-f备用配置，lean_exe使用root的原native link信息。草稿将另建配置文件（原lakefile完整字节前缀＋新增自有exe stanza），原gate/contract/bench/pins/lakefile本体保持不动；调用原g.own build=write，不手写clang flags。
- 热缓存构建下限：一次新配置加载、一个新Main模块Lean→C、一个C对象及一次link；精确秒数UNKNOWN。现有748999的statement/模块/7root诊断replay总70.628s（非新增target成本）。若新target触发非自有dependency重建、flags漂移或改动原bench对象，停止，不再扩框架。
- 先冻结已见plan1927003/5，原BenchSuite timer、原CPU/memory约束，8个control/guarded交错进程保留全156行和checksum。输出为该composition的诊断whole；不是原25-round gate/adoption、新public MUL证明，未来caller/frame和transitive绑定不同仍需另验。

待交：最小Lean模块、只生成自有输入/复用g接口的草稿、源/plan/parser/trace/hash回执及不可区分点。实际CI由D决定。原4b7 gate/lakefile远端读取cache miss，不能把旧本地lakefile当成当前原件；草稿必须在runner读取当前原件并在前后绑定哈希。
