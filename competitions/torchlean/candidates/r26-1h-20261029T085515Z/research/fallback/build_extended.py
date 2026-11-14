from pathlib import Path
import datetime,hashlib,json

HERE=Path(__file__).resolve().parent
names=('WordBlockRuntime.lean','IndexedInvariant.lean.inc','FactorBridge.lean.inc',
       'BlockComposition.lean.inc','CertifiedGuard.lean.inc','ContractFinish.lean.inc')
text='\n'.join((HERE/n).read_text(encoding='utf-8-sig') for n in names)
out=HERE/'WordBlockExtended.lean'
out.write_text(text,encoding='utf-8',newline='\n')
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'SOURCE_DRAFT_NOT_COMPILED',
        'file':out.name,'sha256':hashlib.sha256(out.read_bytes()).hexdigest(),'bytes':out.stat().st_size,
        'parts':{n:hashlib.sha256((HERE/n).read_bytes()).hexdigest() for n in names},
        'roots':['Submission.R26WordBlock.block_exact','Submission.R26WordBlock.merge_represents128',
                 'Submission.R26WordBlock.prepareFactor_getter','Submission.R26WordBlock.preparedBody_exact',
                 'Submission.R26WordBlock.preparedFinish_exact','Submission.R26WordBlock.dotOf_finite_finish',
                 'Submission.R26WordBlock.guardedFinish_correct'],
        'limits':['All roots uncompiled','guardedFinish_correct requires actual preparation-to-dsum-and-zero contract hvalue',
                  'n cap must be established by the outer guard','No performance evidence'],
        'preserved':{'WordBlockCarrier.lean':'33746c383576029185f062c011705191fbbe0f97a965a187f5729e095d151201'}}
for n,sha in record['preserved'].items():
    assert hashlib.sha256((HERE/n).read_bytes()).hexdigest()==sha
(HERE/'extended-receipt.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
