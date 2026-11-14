# Verify既有CI6终态复核（到期后的既有作业回收）

CI6最终133文件已原字节下载，manifest在evidence/41119180001。summary显示complete=true、无error、19:57:33.905—20:13:38.275、964.37s。通过GitHub原job-log接口保存job.log，ci.log是同字节副本：20:13:40附件finalized+Post job cleanup+Cleaning up orphan processes齐。平台API仍in_progress（updated19:55），已保留ci-run.json及直接API原响应，未伪写completed；run日志ZIP404，job原log200。

请按既有terminal-evidence.py接口，一次独立核manifest全部bytes/hash、run/source、finalized/cleanup，写独立终态review JSON，给Root将execution-reconciliation.json的PENDING替换为review path/hash。不要改变原API或取消作业。实际执行终态成立后可固定audit-native.py核全组；然后精确proof-binding，同源旧原全12不重跑，不给第二源转移证明。先只Root/verify读确认组；完成验收再释放摘要。

这是原窗口已启动CI的回收，不新研究/新CI，不延长3h研究窗口。角色最后公开清单等此核验收齐一次冻结即可，仍文件交流。
