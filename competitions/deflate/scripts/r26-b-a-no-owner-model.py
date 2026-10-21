"""B31 independent offer model extended to exact winning-owner recovery without dl writes."""
from pathlib import Path
from datetime import datetime, timezone
import argparse
import hashlib
import json

ROOT=Path(__file__).resolve().parents[1]


def run():
    path=ROOT/'scripts/r26-b-a-flatten-model.py';code=path.read_text()
    old='                        bl[lo+k], dl[lo+k] = base, dist';assert code.count(old)==1;code=code.replace(old,'                        bl[lo+k] = base',1)
    old='            got = (packed, dl[packed&511]) if packed < literal else (literal,0)';assert code.count(old)==1
    new='''            if packed<literal:
                length=packed&511
                if ext and length>stop: recovered=ext[2]
                else: recovered=next(item[2] for item in records if item[0]>=length)
                got=(packed,recovered)
            else: got=(literal,0)'''
    code=code.replace(old,new,1)
    ns={'__name__':'finite_no_owner_model','__file__':str(path)};exec(compile(code,str(path),'exec'),ns)
    return ns['run'](),hashlib.sha256(code.encode()).hexdigest()


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--output',type=Path,required=True);a=ap.parse_args();assert not a.output.exists()
    totals,generated=run()
    result={'status':'VERIFIED_FINITE_ORIGINAL_OFFER_TIE_WRAP_AND_WINNER_OWNER_RECOVERY_MODEL_ONLY',
            'computed_utc':datetime.now(timezone.utc).isoformat(),'totals':totals,'generated_model_sha256':generated,
            'base_model_sha256':hashlib.sha256((ROOT/'scripts/r26-b-a-flatten-model.py').read_bytes()).hexdigest(),
            'limits':['Every actual source-call full cost/ch and originalencoder/native parity still mandatory; no performance/fullgate result.']}
    a.output.write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result))


if __name__=='__main__':main()
