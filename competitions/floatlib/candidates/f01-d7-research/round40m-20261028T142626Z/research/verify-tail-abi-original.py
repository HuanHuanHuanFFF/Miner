"""Classify only the original already-launched ABI object's two direct edges."""
from pathlib import Path
import hashlib,json,re,datetime
HERE=Path(__file__).resolve().parent
run=HERE.parent/'ci-runs/40711515352';index=json.loads((run/'original-artifact-hashes.json').read_bytes())
directory=run/index['directory'];d=directory/'diagnostics/f01-d7-public-suite/public-suite/diagnostics/f01-r23-research-tail-abi'
rows=json.loads((d/'native-assembly-index.json').read_bytes());selected=[]
for row in rows:
 if 'R22IndexedResident8TailABI_' not in row.get('symbol',''):continue
 p=d/row['file'];raw=p.read_bytes();assert hashlib.sha256(raw).hexdigest()==row['sha256']
 assert row['kernel_sha256']=='b0efef1ee1a532efcd2e0a49c99aa1dccef6b8c613ea03073016865dd17d821b'
 txt=raw.decode();m=re.search(r'(?m)^[0-9a-f]+ <'+re.escape(row['symbol'])+r'>:',txt);assert m
 body=txt[m.start():].split('\nDisassembly of section ',1)[0]
 instructions=[];edges=[]
 for line in body.splitlines():
  if 'R_X86_64_PLT32' in line:
   target=line.split('R_X86_64_PLT32',1)[1].strip().rsplit('-0x4',1)[0]
   if 'TailABI_' in target:
    assert instructions;edges.append(dict(target=target,instruction=instructions[-1],relocation=line.strip()))
  else:
   ins=re.match(r'^\s*([0-9a-f]+):\s+([a-z][a-z0-9]*)\s*(.*)$',line)
   if ins:instructions.append(dict(address=ins.group(1),mnemonic=ins.group(2),operands=ins.group(3)))
 selected.append(dict(**row,exact_body_sha256=hashlib.sha256(body.encode()).hexdigest(),cross_edges=edges,
  direct_reference_management_calls=[line.strip() for line in body.splitlines() if re.search(r'\blean_(?:inc|dec)(?:_ref)?(?:-0x4)?\b',line)]))
assert len(selected)==2 and {r['symbol'].rsplit('_',1)[1] for r in selected}=={'hotMul','coldMul'}
hot=next(r for r in selected if r['symbol'].endswith('_hotMul'));cold=next(r for r in selected if r['symbol'].endswith('_coldMul'))
assert len(hot['cross_edges'])==len(cold['cross_edges'])==1
assert hot['cross_edges'][0]['instruction']['mnemonic']=='jmp'
assert cold['cross_edges'][0]['instruction']['mnemonic']=='call'
receipt=dict(verified_at_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),run=40711515352,
 source_commit='a3d92aca7fa49ee4905f786838bc2fb08bec4500',kernel_sha256=hot['kernel_sha256'],
 object_sha256=hot['object_sha256'],observations=selected,
 decision='The two-sided-tail-jump premise FAILS for this exact toy: hot→cold jmp, cold→hot ordinary call plus caller cleanup/return. No direct array inc/dec relocation is present in either exact body. Do not assume borrowed same ABI guarantees both machine tail edges.',
 scope='Already-launched original diagnostic replay object; not a new experiment, not actual BMM, no cleaned timed object or performance conclusion. Toy constant-index reads can be hoisted; hot-loop register appearance is not a BMM register-residency proof.')
(HERE/'tail-abi-machine-original.json').write_text(json.dumps(receipt,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:receipt[k] for k in ['run','object_sha256','decision','scope']},ensure_ascii=False))
