"""Revisit DNA key collisions while retaining the original 65536-head capacity."""
from pathlib import Path
import importlib.util,itertools,json

ROOT=Path(__file__).resolve().parents[1]

def main():
    sp=importlib.util.spec_from_file_location('builder',ROOT/'scripts/build-round18-start.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m)
    p=ROOT/'candidates/r17-dna-nofold-proof1';original=(p/'parse.rs').read_text();proof=(p/'Parse.lean').read_text()
    old='''        let k = pc_be8(s, i) >> 16;
        (k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 48) as usize % H''';assert original.count(old)==1
    table=[255]*256
    for i,b in enumerate(b'ACGTN\n'):table[b]=i
    entries=[];checks=[]
    for name,alphabet in [('r18-dna-split4',b'ACGT'),('r18-dna-base6',b'ACGTN\n')]:
        radix=len(alphabet);count=radix**6;remaining=65536-count
        new='        let k = pc_be8(s, i) >> 16;\n'
        for i,shift in enumerate((40,32,24,16,8,0)):new+=f'        let d{i} = R18_DNA_DIGIT[((k >> {shift}) & 255) as usize] as usize;\n'
        expr='d0'
        for i in range(1,6):expr=f'({expr}).wrapping_mul({radix}).wrapping_add(d{i})'
        new+='        let key = '+expr+';\n'
        new+='        let slot = if '+' && '.join(f'd{i} < {radix}'for i in range(6))+' { key } else {\n'
        new+=f'            {count} + ((k.wrapping_mul(0x9E37_79B9_7F4A_7C15) >> 48) as usize % {remaining})\n        }};\n        slot % H'
        rust=original.replace(old,new)+'\n// Uppercase DNA symbols and line separators have distinct digits; other bytes keep a hashed region.\npub const R18_DNA_DIGIT:[u8;256]='+json.dumps(table)+';\n'
        keys=set()
        for seq in itertools.product(range(radix),repeat=6):
            value=0
            for d in seq:value=value*radix+d
            keys.add(value)
        assert keys==set(range(count)) and 0<count<65536
        e=m.write_candidate(name,p.name,rust,proof,
          f'Partition the original65536-head DNA table: collision-free radix{radix} keys for six-symbol prefixes in '+repr(alphabet)+f', and the original multiplied hash in the remaining{remaining}heads for all other prefixes. Keep table size, search effort, insertion and checked matching unchanged.',
          'Early dense4^6 trial also shrank the head table to4096 and aliased N/newline with canonical bases. Its16312B loss does not isolate that interaction. These two bounded representation variants explicitly separate noncanonical prefixes and retain65536heads; they are not random depth/pass retries. Native collision counts and actual bytes decide whether to revisit the unstable DNA target region.',
          {'parent':'candidates/r17-dna-nofold-proof1/manifest.json','negative_evidence':'evidence/round18/mechanisms-d-decision.json','ownership':'Original parser, proof authors and R17 contributions retained; new prefix-domain partition is this round.'})
        e.update(anchor='dna582',comparison_baseline='dna582',native_decode_reference='dna582');entries.append(e);checks.append({'candidate':name,'radix':radix,'enumerated_keys':len(keys),'allocated_special_heads':count,'fallback_heads':remaining})
    s=json.loads((ROOT/'evidence/round18/mechanisms-d-native.json').read_bytes());s['entries']=[e for e in s['entries']if e.get('control')and e['name']!='public583']+entries;s['native_encoder_references']=['dna582'];s['screen_orders']=[[e['name']for e in s['entries']],[e['name']for e in reversed(s['entries'])]];s['r18_dna_domain_counts']=True
    s['description']='AL bounded DNA representation revisit: isolate canonical-prefix interference from the earlier reduced-table failure. Two fixed radix domains, original65536heads and all original search/insertion effort; original encoder28files plus actual public genome prefix/collision counts. Cap25job-minutes. If quality meaningfully improves, replay target geometry and measure total time with same-source control before claiming anything. Historical DNA narrow-window and formal0 evidence remain in force; new exact proofs/gates still missing.'
    (ROOT/'evidence/round18/dna-al-native.json').write_bytes((json.dumps(s,indent=2)+'\n').encode());(ROOT/'evidence/round18/dna-al-key-preflight.json').write_bytes((json.dumps({'status':'VERIFIED_FINITE_RADIX_KEY_BIJECTION','variants':checks,'scope':'Python arithmetic key model only; does not establish Rust behavior, speed or fullgate.'},indent=2)+'\n').encode());print(json.dumps(entries))

if __name__=='__main__':main()
