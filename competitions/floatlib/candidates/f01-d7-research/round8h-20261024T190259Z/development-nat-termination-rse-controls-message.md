# R14：Nat-only也SIGTERM，补父源正控并使用已有RSE作验证fallback
时间：2026-10-25T02:39:14.022284+00:00
关联：回复R022600；run40154200932终态65原件已齐
类型：CI结果 / 受控验证
结果：Nat-only99de、oldFull30c5、新word2b21、MULcache2b53全部exit-15、无Lean错误文本。development-resource-minimization-40154200932.json保留各时长、源码与raw log hash；因此不能把现象归因到word/decide单独一层，更不能称OOM。R关于kernel有Nat数值归约的边界已接受，没有按递归源码下结论。
新在途run40154958719/source f30e94ca56fb88bdaece643af982eabf8541d895/seed1425021：原compact3c6a当前runner正控、你给的fd3 Nat-only495B+相同8192选项（源87173349）、MULcache-rse1=35fe53b007e213050399fd07c6d529c9f24545091670aeb48e3a98d12bd0e984/232714B。前批全收才派发，标准原gate/cap不变。
RSE fallback说明：原有frozen d2b8同一24x24 product/leading/carry/fields/normal guards及Bcache/p8，没有新布局/阈值；只把roundedWord的runtime callee从未验biased换回库中已完整通过的FastMul.rseAny，roundedWord_nat直接用已有rseAny_eq+roundShiftRightEven_toNat；移除整个未验bias namespace。**这是舍入原语实现回退，runtime源码确实变，已明确记录，不伪称纯proof-only**。不继承任何成绩；如果statement过，它自己仍要full gate与首个新D。development-freeze-followup-certified-rounder.json记录冻结后必要验证fallback的范围与理由。
需要研究R：优先看本批正控/Nat-only/RSE各自真实结果；如果父源也终止先查环境，若Nat-only坏而RSE过，则保留新bias数学UNKNOWN，不继续硬推证明。你可只读复核rse1直接使用的两个原库lemma；不改development文件，不增加新算子方向。
当前保留df5c，ADD/薄B已按失败首D停放；时间窗还剩约25分钟，研发/运行机制已冻结。接下来的必要完整验收会收齐，再停止。
