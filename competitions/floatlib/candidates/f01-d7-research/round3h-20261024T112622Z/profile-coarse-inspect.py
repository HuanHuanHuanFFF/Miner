"""Actual saved DF generated-C call graph; static evidence only."""
from pathlib import Path
import collections,hashlib,importlib.util,json,re
HERE=Path(__file__).resolve().parent
REPO=next(p for p in HERE.parents if (p/'competitions/floatlib').is_dir())
CPATH=REPO/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40092014611/download-40d1f19ff0684c7d95f29a632be22848/diagnostics/f01-d13-cost-profile/cost-profile/measurement/profile-r13-original-Submission.c'
spec=importlib.util.spec_from_file_location('r13_frozen_cparser',HERE/'profile-current.py')
m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
def run():
    text=CPATH.read_text(encoding='utf-8');rows=m.functions(text);names={r['symbol']for r in rows}
    edges={r['symbol']:dict(collections.Counter(re.findall(r'\b(lp_competition_[A-Za-z0-9_]+)\s*\(',m.mask_c(r['body'])[m.mask_c(r['body']).index('{')+1:])))for r in rows}
    targets={n for n in names if n in {
        'lp_competition_Submission_bmm','lp_competition_Submission_sum',
        'lp_competition_Submission_RowStream_core','lp_competition_Submission_RowStream_output',
        'lp_competition_Submission_Packed10_packB','lp_competition_Submission_R11CrossRows_core',
        'lp_competition_Submission_R11CrossRows_words','lp_competition_Submission_DirectContinuous_core'}or
        ('Array_mapMUnsafe_map___at___00Submission_RowStream_output_spec__'in n and 'boxed'not in n)}
    output={'source_c':str(CPATH),'source_c_sha256':hashlib.sha256(CPATH.read_bytes()).hexdigest(),
        'targets':{n:{'outgoing':edges[n],'incoming':{caller:cs[n]for caller,cs in edges.items()if n in cs}}for n in sorted(targets)}}
    (HERE/'profile-coarse-actual-callgraph.json').write_text(json.dumps(output,indent=2)+'\n',encoding='utf-8',newline='\n')
    for r in rows:
        if r['symbol']in targets:
            print(r['symbol'],len(r['body']),output['targets'][r['symbol']]);print(r['body'][:4000])
if __name__=='__main__':run()
