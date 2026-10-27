"""Read latest numeric D checkpoints regardless of prepend/append ordering."""
from pathlib import Path
import re
H=Path(__file__).resolve().parent;R=H.parents[3]
s=(R/'competitions/floatlib/coordination/r7-feedback.md').read_text(encoding='utf-8')
hits=list(re.finditer(r'(?m)^## D(\d+)\b.*$',s));sections=[]
for i,m in enumerate(hits):sections.append((int(m[1]),s[m.start():hits[i+1].start() if i+1<len(hits) else len(s)]))
for _,section in sorted(sections,reverse=True)[:2]:print(section.rstrip()+'\n')
