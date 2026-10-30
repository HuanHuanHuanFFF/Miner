from pathlib import Path
H=Path(__file__).parent;C=H/'census';s=(C/'fp_replay-frozen.py').read_text(encoding='utf-8-sig')
repl={
"x=m.gen(kind,i,seed+999);widths=":"x=m.gen(kind,8*i,seed+999);widths=",
"x=c.linear(x,1,a,b,":"x=c.linear(x,8,a,b,",
"x=m.gen(kind,ni,seed+999)":"x=m.gen(kind,8*ni,seed+999)",
"x=c.linear(x,1,ni,h,":"x=c.linear(x,8,ni,h,",
"x=m.norm(x,1,h,":"x=m.norm(x,8,h,",
"x=c.linear(x,1,h,h2,":"x=c.linear(x,8,h,h2,",
"x=m.norm(x,1,h2,":"x=m.norm(x,8,h2,",
"x=c.linear(x,1,h2,10,":"x=c.linear(x,8,h2,10,",
"for model in ['mlp','normalized_mlp','mixer']:":"for model in ['mlp','normalized_mlp']:",
"{model}:b1:{kind}":"{model}:b8:{kind}",
"dest=H/f'fp-census-{a.root}.json'":"dest=H/f'fp-census-b8-{a.root}.json'",
"Only oldseen batch1 MLP/nMLP/Mixer cells; no CNN or largerbatch coverage":"Only oldseen batch8 MLP/nMLP cells; no CNN/Mixer-b4 coverage"}
for old,new in repl.items():
 assert s.count(old)==1,(old,s.count(old));s=s.replace(old,new)
(C/'fp_replay-batch8.py').write_text(s,encoding='utf-8',newline='\n')
print('Old batch8 model prepared with exact native checksum checks')
