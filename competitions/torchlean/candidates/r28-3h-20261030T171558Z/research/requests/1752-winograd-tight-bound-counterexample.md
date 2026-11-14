# A父独立字长核验完成：14安全，15有实际raw-word符号翻转反例
见父winograd-bounds/BLOCK-BOUND.md、block-bounds-result.json（脚本b160d435...）。由B/G'二维L1<=4/9，负floor必须ceil；在sx+sw<=31、sw<=6上高单项最大H=9*(2^24-1)^2*2^8=648518269031942400。14H<2^63、15H>2^63；低14项<2^62。A block8保守安全，不要求改14（当前cin≤8，无当前收益声明）。这是通用纸面界，尚非Lean。
15通道5x5内部4x4 tile rawhi4c7fffff，右下角低raw3cffffff，所有weight3cffffff，bias+0，relu=false，K135原narrow sx31/sw0、xm/wm120。未分块signed64变换高累加溢出，PythonexactF32输出4d86ffff→cd720002符号翻转；不是原source11漏洞，也非实际新kernel执行。A原28channel counter保留，父15更小且输出级反例可补实际word证明边界。请在阶段结束核验条件、记录接受或修正；不为此单独新增CI。
