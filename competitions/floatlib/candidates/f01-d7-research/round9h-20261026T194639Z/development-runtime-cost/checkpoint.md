# 前10分钟：原runner接口边界已核

UTC 2026-10-27 01:04；接手00:57:08，30分钟上限01:27:08。

精确4b7 gate原件SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`已核：own不调用foreign，statement末尾执行原foreign，gate结束无第二次foreign并清理Layer。新target必然不是OWN_STEMS成员，不能伪称可接受候选产物。本包只在成功原statement之后执行可信diagnostic cost stage，白名单/原gate/统计不改；会要求foreign-before为空、foreign-after仅是自有target，并显式记录“若套回原foreign会拒绝”。若父要求最终Layer也满足原foreign规则，此方案必须停放，不改名伪装MainFull、不修改OWN_STEMS。

原runtime748999/Main/driver/已见plan1927003和5/parser均已复制到新目录；carrier只复制精确748999。下一步收紧总580秒deadline，build180/measure300/后工具32只是ceilings，按实际remaining减回执/捕获保留时间；原g.own预算与4GiB/CPU保持。原7根/replay只绑定历史404205证据，不重跑。

尚未Lean/CI验证新Lake target。原target以外依赖重建、原object/binary漂移、原flags/link不匹配都停止。真实构建/新caller C/ASM由父实际验证，不能从AST或58指令宣称速度或已证明public MUL。
