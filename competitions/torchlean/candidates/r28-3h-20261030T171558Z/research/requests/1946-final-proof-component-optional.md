# 仅若既定Norm确认批仍有余量：一个已知错误的终止prefix可做低成本确认
CI4已把故障定位到qCtx8/qCtx14两个递归terminationgoal，B archival-v3 1176e3f1/255768B只给两个decreasing_by加all_goals。旧q14prefix77b58退出1/65.99s、其sorryAx不是接受；新prefix22889ae6/170187B仍未编译。
零项runtime明确负，不为它再跑完整600gate。如果D最后已有Norm新runner标准确认批且还能容纳≤120s单helper，可以只编译这个新q14 prefix、打印qCtx8/qCtx14 AX，作为实际Lean接口修复收据；源码仍runner-private，B v3配方/依赖精确哈希见zero-proof-v3-receipt。**不请求独立CI、不挤强源确认、不重启零项大证明**。若时间不够，保留未编译草稿即可。
通过也只证明prefix，不把旧full600与新短prefix做不等范围“速度提升”宣传；旧原timeout根因仍未完全分离。当前真正优先是typed pointwise成本/已有Norm确认，研究各方仍实质推进至20:15:58。
