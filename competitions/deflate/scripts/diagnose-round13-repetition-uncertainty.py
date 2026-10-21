"""Replay pinned repetition statistics as a public-only measurement diagnostic."""
from pathlib import Path
from types import SimpleNamespace,ModuleType
from typing import cast
import ast,hashlib,json,math,random,re,statistics,subprocess,sys

ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round13'
UP=ROOT/'sources/conjectures-optimisation-deflate/validator'
sys.path.insert(0,str(UP))
sys.dont_write_bytecode=True
# The package initializer imports the runner's logging/deployment dependencies.
# Load its unchanged pure parsing modules through an explicit lightweight shell.
assert 'bench' not in sys.modules
package=ModuleType('bench');package.__path__=[str(UP/'bench')];sys.modules['bench']=package
from bench.corpora import Corpus
from bench.hashing import sha256
from bench.results import INCUMBENT,SCHEMA_VERSION,Run,parse

def load_functions(path,names,ns):
    tree=ast.parse(path.read_text());nodes=[n for n in tree.body if isinstance(n,ast.FunctionDef) and n.name in names]
    assert {n.name for n in nodes}==set(names)
    future=ast.ImportFrom(module='__future__',names=[ast.alias(name='annotations')],level=0)
    code=ast.fix_missing_locations(ast.Module(body=[future,*nodes],type_ignores=[]))
    exec(compile(code,str(path),'exec'),ns)

def main():
    pin='a356bbff18b60c4527fbcc85d5a28ef9c20214e0';source_root=UP.parent
    assert subprocess.check_output(['git','-C',str(source_root),'rev-parse','--show-toplevel'],text=True).strip()==source_root.as_posix()
    assert subprocess.check_output(['git','-C',str(source_root),'rev-parse','HEAD'],text=True).strip()==pin
    source_hashes={}
    for path in ('db/admission_statistics.py','db/aggregation.py','bench/results.py','bench/hashing.py','bench/corpora.py','bench/errors.py'):
        local=(UP/path).read_bytes();blob=subprocess.check_output(['git','-C',str(source_root),'show',pin+':validator/'+path])
        assert local.replace(b'\r\n',b'\n')==blob.replace(b'\r\n',b'\n')
        source_hashes[path]={'local_sha256':hashlib.sha256(local).hexdigest(),'git_blob_sha256':hashlib.sha256(blob).hexdigest(),'normalized_source_equal':True}
    stats=UP/'db/admission_statistics.py';agg=UP/'db/aggregation.py'
    ns={**globals(),'METHOD_VERSION':'mixed-files-independent-runs-percentile-v2','DEFAULT_DRAWS':2000,'MIN_REPETITIONS':3}
    tree=ast.parse(stats.read_text())
    for key in ('METHOD_VERSION','DEFAULT_DRAWS','MIN_REPETITIONS'):
        node=next(n for n in tree.body if isinstance(n,ast.Assign) and any(isinstance(t,ast.Name) and t.id==key for t in n.targets))
        assert ast.literal_eval(node.value)==ns[key]
    load_functions(agg,['validate_evidence'],ns)
    def single_public_envelope(rows):
        # The official SQL aggregation is not imported or simulated. Diagnostics
        # contain exactly one stage1 process per side; validate its real raw envelope.
        assert len(rows)==1 and rows[0].corpus=='corpus-stage1'
        run=ns['validate_evidence'](rows[0]);assert len(run.files)==28
        assert sum(f.raw_bytes for f in run.files)==15930000
        for method in (rows[0].candidate_method,INCUMBENT):
            totals=run.totals(method);assert totals.total_s and totals.total_s>0
    ns['reduce_runs']=single_public_envelope
    load_functions(stats,['quantile','evidence_files','coordinate','compare'],ns)
    folder=E/'37869790385/confirm-aa/gate';state=json.loads((folder/'state.json').read_bytes())
    ci=json.loads((folder/'ci-run.json').read_bytes());assert ci['status']=='completed' and ci['conclusion']=='success'
    entries={e['name']:e for e in state['spec']['entries']};input_rows={};manifest=None
    for block in range(1,5):
        for name in ('r13-514-abs15','public514','public514-shadow'):
            path=folder/f'round{block}-{name}.jsonl';raw=[json.loads(s) for s in path.read_text().splitlines()]
            files=[r for r in raw if r['kind']=='file'];content=sorted((f['file'],f['sha256'],f['raw_bytes']) for f in files)
            if manifest is None:manifest=content
            assert manifest==content and raw[0]['methods'][name]['source_sha256']==entries[name]['hashes']['parse.rs']
            digest=sha256(raw);row=SimpleNamespace(id=int(digest[:14],16),source_sha256=entries[name]['hashes']['parse.rs'],candidate_method=name,
                corpus='corpus-stage1',corpus_sha256=sha256(content),status='complete',invalidated_at=None,raw_data=raw)
            input_rows[name,block]=(row,{'path':path.relative_to(ROOT).as_posix(),'raw_file_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
                'canonical_evidence_sha256':digest,'synthetic_observation_id':row.id})
    assert len({r.id for r,_ in input_rows.values()})==12
    results=[]
    for block in range(1,5):
        for candidate,reference in (('r13-514-abs15','public514'),('r13-514-abs15','public514-shadow'),('public514-shadow','public514')):
            result=ns['compare']([input_rows[candidate,block][0]],[input_rows[reference,block][0]],draws=2000)
            assert result['file_sets_equal'] and result['per_file_sizes_equal']
            results.append({'block':block,'candidate':candidate,'reference':reference,'result':result})
            print(json.dumps({'block':block,'candidate':candidate,'reference':reference,**{k:result[k] for k in ('gain_pct','lower_pct','upper_pct','outcome')}}),flush=True)
    output={'status':'PUBLIC_ONLY_PINNED_STATISTIC_DIAGNOSTIC','run_id':state['run_id'],'git_sha':state['git_sha'],
        'upstream_commit':pin,'source_file_hashes':source_hashes,'script_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'source_functions':{'admission_statistics_sha256':hashlib.sha256(stats.read_bytes()).hexdigest(),'aggregation_sha256':hashlib.sha256(agg.read_bytes()).hexdigest(),
            'unchanged_functions':['quantile','evidence_files','coordinate','compare','validate_evidence']},
        'adapter':'Pure bench modules loaded without the runner package initializer; AST loads unchanged pure functions; one-public-process envelope replaces the SQL aggregate call. Synthetic immutable observation IDs derive from canonical raw evidence; they are not official database IDs or admission seeds.',
        'inputs':[v for _,v in input_rows.values()],'comparisons':results,
        'limits':'Stage1 only; fixed files, repetition bootstrap, no file resampling and no pooling across four blocks. Host/corpus drift and cross-file dependence are excluded by this statistic. Public514 is not the current539 admission reference. Neither diagnostic passed/inconclusive labels nor intervals are official admission, deployed-validator identity, held-out performance or reward. These do not change the frozen composition stop decision.'}
    (E/'repetition-uncertainty-diagnostic.json').write_bytes((json.dumps(output,indent=2)+'\n').encode())

if __name__=='__main__':main()
