# ADD对照首10分钟检查点

已生成真实文件，尚无新Lean/计时。carrier逐字77377f8b/228707B；它以622d全文件为前缀，因此control四个原public入口保持B2。新Main明确inline `R19GRS32Add.guardedAdd Submission.add`，guarded分支只替换第一个Bench.Suite.run callback，MUL/SUM/BMM未换；不用diagnosticEntry。

已核CI12/40430974047所有原件及source input/7roots/replay，历史绑定全部改为CI12；MUL/CI13只作为已实际跑通模板。另核CI13/40432634558全部121原件，实际caller字节与模板相同，prepare实际`lake -f work/R19RuntimeCostLake.lean build r19RuntimeCost`，actual compile/link/rsp三项只root/target路径映射后相同。新ADD包的normalize只接受MainFull↔R19AddCostMain、benchFull↔r19AddCost，拒绝旧MUL root别名。

新target为R19AddCostMain/r19AddCost，独立-f work/R19AddCostLake.lean；不写原lakefile。16组件逐项重算SHA/size。两份已见plan、8个ABBA进程、156行/152timed、checksum、原flags/BenchSuite/原source/object/binary前后身份保护照搬已跑通实现。600外/580内绝对remaining、180/300/32阶段ceiling、20秒reserve和4GiB原build scope不变；任何阶段失败保留partial。

23项本地Python合成接线检查PASS，包括schema错误trace、额外traceFlags、错误ADD fallback alias、旧target碰撞、flags/依赖/原object漂移、checksum/缺行及总体预算拒绝。合成计时只让ADD变化，MUL/SUM/BMM保持1；不作为真实速度。所有临时fixture已删除，不提交。当前准备完整新包并做最终manifest/static绑定复核，真实Lean/C/ASM/benchmark均NOT_RUN。
