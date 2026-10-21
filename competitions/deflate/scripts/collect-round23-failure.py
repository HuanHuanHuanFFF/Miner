"""Keep the mistakenly routed initial run as an orchestration failure, not a gate."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,importlib,json
ROOT=Path(__file__).resolve().parents[1]

def main():
    h=importlib.import_module('collect-round2');env=h.gh_env();ident='38072840653'
    body=h.run(['run','view',ident,'--repo','HuanHuanHuanFFF/Miner','--json','databaseId,headSha,headBranch,event,status,conclusion,createdAt,updatedAt,url,jobs'],env)
    data=json.loads(body);assert data['status']=='completed' and data['headSha']=='20950bc28d77e05f63d3d60ecaf167ffda96dec0'
    log=h.run(['run','view',ident,'--repo','HuanHuanHuanFFF/Miner','--log'],env).encode()
    e=ROOT/'evidence/round23';p=e/(ident+'-route-failure-ci.json');assert not p.exists()
    p.write_bytes((json.dumps(data,indent=2)+'\n').encode());(e/(ident+'-route-failure.log')).write_bytes(log)
    receipt={'status':'VERIFIED_ORCHESTRATION_FAILURE_BEFORE_GATE','run_id':ident,'checked_at_utc':datetime.now(timezone.utc).isoformat(),'actual_experiment_round':22,'intended_experiment_round':23,'candidate_gate_executed':False,'performance_measured':False,'log_sha256':hashlib.sha256(log).hexdigest(),'ci_conclusion':data['conclusion'],'evidence_files':[p.name,ident+'-route-failure.log']}
    (e/(ident+'-route-failure-receipt.json')).write_bytes((json.dumps(receipt,indent=2)+'\n').encode())
    print('PRESERVED_ROUTE_FAILURE',data['conclusion'])

if __name__=='__main__':main()
