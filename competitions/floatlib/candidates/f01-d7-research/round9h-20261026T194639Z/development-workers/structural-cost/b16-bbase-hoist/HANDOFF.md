# 单一B-base let交接

Kernel-bbase-hoist.draft.lean：f49458b99475b1b7e4a368908c81590b7f357a06938f38d0df141ffa3df5dc5d/255745B；精确bb05父本255724B，+21B，剩255B。

只在R19Column4Temporal.group的runDot之后、emit之前绑定baseB:=bi.val*n*p+4*g.val，lambda改baseB+j.val。避免新增Nat跨dot延寿；原bi/n/p/g既有跨dot用途不宣称消除。baseA/loop/guard/fallback/finish/NaN顺序及所有proof逐字不变，无helper/noinline/额外网格。

完整正逆patch、逆恢复bb05、pure-let zeta、声明/20根索引与原件130hash核验PASS。source不超过256000。真实编译/20根/C/ASM/速度全NOT_RUN，不假定LCNF保留hoist，不把乘法次数换成速度。C判别还须核实际group/emit的新capture/RC/spill及完整生命周期。

未改父候选或manifest，未Git/CI/Lean，未读D22/确认数据。先收齐冻结批；若原源达标先原源确认。详README/receipt.json/roots.json。
