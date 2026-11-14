from pathlib import Path
import datetime,hashlib,json

HERE=Path(__file__).resolve().parent
names=('WordBlockRuntime.lean','IndexedInvariant.lean.inc','FactorBridge.lean.inc',
       'BlockComposition.lean.inc','CertifiedGuard.lean.inc','ContractFinish.lean.inc',
       'ScaledBias.lean.inc','BiasDotBridge.lean.inc','ZeroSafeCaller.lean.inc')
out=HERE/'WordBlockComplete.lean'
out.write_text('\n'.join((HERE/n).read_text(encoding='utf-8-sig') for n in names),encoding='utf-8',newline='\n')
record={'at_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
        'status':'PROOF_AND_RUNTIME_SOURCE_NOT_COMPILED',
        'file':out.name,'sha256':hashlib.sha256(out.read_bytes()).hexdigest(),'bytes':out.stat().st_size,
        'parts':{n:hashlib.sha256((HERE/n).read_bytes()).hexdigest() for n in names},
        'target':'Submission.R26WordBlock.zeroSafeFinish_bias_dot',
        'scope':'Actual prepared UInt32 indexed block/each128 body; exact bias at common scale; one original finishWord; original finite dotOf including bias once; zero or false guard invokes shipped',
        'remaining':['All Lean declarations uncompiled','Actual preprocessing guard must discharge explicit domain premises','No all12 Kernel assembly or native cost evidence'],
        'not_claimed':'The filename Complete describes the assembled source chain, not completed verification'}
(HERE/'complete-receipt.json').write_text(json.dumps(record,indent=2)+'\n',encoding='utf-8')
print(json.dumps(record,indent=2))
