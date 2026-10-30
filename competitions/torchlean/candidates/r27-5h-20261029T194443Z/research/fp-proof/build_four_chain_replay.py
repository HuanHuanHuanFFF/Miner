from pathlib import Path
H=Path(__file__).parent;src=(H/'census/fp_replay-frozen.py').read_text(encoding='utf-8-sig')
src=src.replace("UTIL=H/'formula_snapshot.py'","UTIL=H.parent/'census/formula_snapshot.py'")
old='''        acc=0;exact=0
        for x,y in zip(ka,kb):
            prod=x*y;exact+=prod;acc=rnd53(acc+(prod<<5))'''
new='''        acc=0;exact=0
        if n>=5:
            lanes=[0,0,0,0]
            for i,(x,y) in enumerate(zip(ka,kb)):
                prod=x*y;exact+=prod;lanes[i%4]=rnd53(lanes[i%4]+(prod<<5))
            acc=rnd53(rnd53(lanes[0]+lanes[1])+rnd53(lanes[2]+lanes[3]))
        else:
            for x,y in zip(ka,kb):
                prod=x*y;exact+=prod;acc=rnd53(acc+(prod<<5))'''
assert src.count(old)==1;src=src.replace(old,new)
old='''            fs=0.0
            for u,v in zip(a,b):
                x=struct.unpack('<f',struct.pack('<I',u))[0];y=struct.unpack('<f',struct.pack('<I',v))[0]
                fs=fs+x*y'''
new='''            fs=0.0;fl=[0.0,0.0,0.0,0.0]
            for i,(u,v) in enumerate(zip(a,b)):
                x=struct.unpack('<f',struct.pack('<I',u))[0];y=struct.unpack('<f',struct.pack('<I',v))[0]
                if n>=5:fl[i%4]=fl[i%4]+x*y
                else:fs=fs+x*y
            if n>=5:fs=(fl[0]+fl[1])+(fl[2]+fl[3])'''
assert src.count(old)==1;src=src.replace(old,new)
src=src.replace("status='INTEGER_F64_CHECKER_REPLAY_OLD_SEEN_COHORT_ONLY'","status='FOLLOW_ON_FOURCHAIN_INTEGER_MODEL_NOT_NATIVE_OR_PROOF'")
src=src.replace("dest=H/f'fp-census-{a.root}.json'","dest=H/f'fourchain-fp-census-{a.root}.json'")
src=src.replace('RNE64 at every addition and both endpoints','RNE64 at eachlaneaddition,2pairmerges,1finalmerge and bothendpoints; n<=4 stayssequential')
(H/'follow-on/four_chain_replay.py').write_text(src,encoding='utf-8',newline='\n')
print('Four-chain old-cohort falsification model prepared')
