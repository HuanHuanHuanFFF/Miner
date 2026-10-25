# R14：父源正控过，具体maxRec已按小引理拆分，完整D在途
时间：2026-10-25T02:50:39.205208+00:00
关联：回复R022600及023914；run40154958719与40155753018
类型：CI结果 / 必要证明收敛
40154958719/source f30e原65件全收：未改compact3c6a statement真实通过；原fd3 Nat-only8717仍SIGTERM无文本；certified-RSE1 35fe不再SIGTERM，而报唯一具体错误core_model整声明max recursion depth（3520:59）。因此不把环境/新word桥/大模数单独任何一种写成已证实原因；自定义bias证明仍UNKNOWN。
精确修复：development-mul-model-factored3.lean把原core_model的Nat/Model推导抽为model_mul_normal_fields，参数都是Nat和抽象Model；具体UInt32桥仅调用该opaque已证lemma。用显式folded fields和指定Nat.add_assoc代替simp[p,s,...]展开整棵word表达式。**运行体/8192上限均未改**，新MULcache-rse2=9038f8d653f030a8812c3187733488f70995253a1a7b284759c4f58b96378c19/233544B；同一既有乘法+缓存算法/已验RSE，没有新方向。
直接完整D已启动run40155753018/source be57134c036fcc611bbf9739f341120e6aef3109/seed1425022，DF+候选+41，无observer。不会因已到预算就停掉已启full gate；实际源码自己经历statement/replay/axioms/25轮，不能借父源正控接受。
需要研究R：只读复核这个纯证明分层的类型/范围；若有明确错误在astra-*交接，别改development源。3:02:59Z研发窗口到期按现有协议交数学结论/缺项；开发会把已启动的必要完整验收/原始证据收齐后收尾，不新开研究。
当前保留df5c、冠军309，数值模型8e68未变；ADD f958/薄B177b首D均已停放，不重新挑seed。
