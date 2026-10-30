"""Compose three hash-pinned, disjoint ResNet changes; new fullgate required."""
from pathlib import Path
import hashlib,importlib.util,os
HERE=Path(__file__).resolve().parent
PINS={'build_resnet11_inplace_bn.py': '77b9d783d0fa5425683c87a81e8fc2b93d11e0d5957182035ad710e015f10b0a', 'build_zero_pair.py': '97fa0af45234ef9e19b266d45221dd207d291ac2f7dab1d06f8c1194fce61b22', 'mapidx_add_v2.py': '27ec14984df36fbdc2f94ff17b6c0db279ccdfab74d752b2b789183a399f5cfc'}
def module(name):
 p=HERE/name;assert hashlib.sha256(p.read_bytes()).hexdigest()==PINS[name]
 sp=importlib.util.spec_from_file_location('resnet_frozen_'+name.replace('.','_'),p);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);return m
def transform(raw,submission,variant,donor_raw=None):
 assert submission==11 and variant=='zero-bn-add'
 zero=module('build_zero_pair.py');bn=module('build_resnet11_inplace_bn.py');add=module('mapidx_add_v2.py')
 if donor_raw is None:donor_raw=(Path(os.environ['TORCHLEAN_ROOT'])/'r28-source-private/official-53.lean').read_bytes()
 base=raw.decode('utf-8');result=bn.build(raw,donor_raw)[0].decode('utf-8');result=zero.apply(result)
 mapped=add.transform(raw,11,'mapidx-add-v2').decode('utf-8')
 for start,end in [('def Ybf (','lemma ZdC:'),('lemma ZdC:', '@[inline] def YaJ (w:Word) (m:UInt64):UInt64 :=')]:
  a=base.index(start);b=base.index(end,a+len(start));before=base[a:b]
  a=mapped.index(start);b=mapped.index(end,a+len(start));after=mapped[a:b]
  assert result.count(before)==1;result=result.replace(before,after,1)
 out=result.encode('utf-8');assert len(out)<=256000;return out
