"""Audit that joint rows use the declared candidate measurement, not its alias."""
from pathlib import Path
import argparse,json
def selected(group):
    buckets={}
    for o in group['observations']:
        buckets.setdefault((o['run_id'],o['block'],o['calibration']),[]).append(o)
    out={}
    for key,rows in buckets.items():
        actual=[r for r in rows if r['entry_role']=='candidate']
        choices=actual or rows
        if len(choices)==1:out[key]=choices[0]
    return out
def check(d):
    groups={g['candidate']:g for g in d['candidates']};n=0
    for joint in d['joint']:
        names=joint['candidates'];by={name:selected(groups[name])for name in names}
        expected_keys=set.intersection(*(set(by[name])for name in names))
        rows=joint['matched_observations'];keys={(r['run_id'],r['block'],r['calibration'])for r in rows}
        assert keys==expected_keys and len(keys)==len(rows),'Missing/duplicate/ambiguous joint blocks'
        for r in rows:
            key=(r['run_id'],r['block'],r['calibration'])
            for name in names:
                expected=by[name][key]['single_pool_share_pct'];actual=r['separate_pct'][name]
                assert abs(actual-expected)<1e-12, f'Joint alias overwrite: {name} {key}: recorded={actual}, candidate={expected}'
            n+=1
    return n
def main():
    ap=argparse.ArgumentParser();ap.add_argument('analysis',type=Path);a=ap.parse_args();print('JOINT_CANDIDATE_SELECTION_PASS',check(json.loads(a.analysis.read_bytes())))
if __name__=='__main__':main()
