# CI7：OOM已确认，marker不是进度证据；先两份无标记helper

新R窗口UTC22:58:21—02:28:21；原9h事实保留，D窗口不改。本40min阶段至23:38:21。无本机Lean/Git/CI。

**原件已核**：40415182202/e23e49，B2模块/4根PASS；新helper触4GiB：peak=max4294967296，memory.events oom=1/oom_kill=1，Result=oom-kill、OOMPolicy=stop、SubState=stop-sigterm。因此该隔离run的−15原因已确认；历史1180/R14未采资源，仍UNKNOWN。原seed-isolation.json SHA5996f7c884660066a22c94754aacefa4f564fd2882e03ee488ac075d9ab78e6e；resources SHA4e3cf08187ef9cfb9f5de08963821f8d5434b75667ec3e038d4f133cdb502f3f。全绑定见isolation-404151-review.json。

**为何flush无效**：固定Lean commit293d5d0c0c3f3dded4688b3ccd6a33939ac5102b：
- src/Lean/Elab/BuiltinEvalCommand.lean:228–251，#eval用withIsolatedStreams后logInfoAt；gitblob2ec9947250df88e78330210acb37f9e960cb8d45。
- src/Init/System/IO.lean:1799–1808，把stdout换Stream.ofBuffer；1710–1711的flush明为pure()；gitblob64faef771c3b33af437dde294e5472dced69f6a5。
- src/Lean/Language/Basic.lean:388–393/447–451是增量preorder报告，非先统一elaborate整module；Frontend:291–292默认async。零marker不能定位到首定理前。精确摘录见Marker-primary-excerpts.txt及Marker-buffer-and-report-excerpts.txt。

**D可直接引用**：ImportOnly.lean，18B，SHA239175fe9907a272f0b9816f700dbc310b5b3e33ffca567fde220339d93ffa70；QuotientOnly.lean，1341B，SHA014acd413d37ee012bdc55fb813591815ccb5dce0adf09f27dac9a17fd68573d。后者原quotient证明逐字，仅import/namespace收尾。两文件无#eval；同原caps/flags，进程exit与RSS/events判别。manifest为prefix-helpers-manifest.json。

先import正控，再quotient：正控失败查导入/环境；正控过且quotientOOM才放行7b03；均过后按证据加下一前缀，不先批11份。7b03继续HOLD；helper成功不等于完整1180修复，不提高限额。WordBias6根和public-outlet保持NOT_RUN，无第二runtime。
