"""Independent local R26 B16 receipt audit and public601 executable-difference census."""
from pathlib import Path
from datetime import datetime, timezone
import difflib
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'evidence/round26/route-b'


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load(path):
    return json.loads(path.read_bytes())


def span(src, name):
    match = re.search(r'\bfn\s+' + re.escape(name) + r'\b', src)
    assert match, name
    begin = match.start()
    body = src.index('{', begin)
    depth = 0
    for end in range(body, len(src)):
        if src[end] == '{':
            depth += 1
        elif src[end] == '}':
            depth -= 1
            if depth == 0:
                return begin, end + 1
    raise AssertionError(name)


def function(src, name):
    start, end = span(src, name)
    return src[start:end]


def b16():
    rawdir = ROOT / 'evidence/round26/38190911140/dense-b16-native/diagnostics'
    inventory = load(rawdir / 'raw-artifact-files.json')
    input_hashes = {}
    for relative, expected in inventory['files'].items():
        path = rawdir / relative
        assert path.stat().st_size == expected['bytes']
        assert digest(path) == expected['sha256']
        input_hashes[path.relative_to(ROOT).as_posix()] = digest(path)
    assert len(input_hashes) == 8
    enc = load(rawdir / 'r13-encoder/encoder.json')
    prof = load(rawdir / 'r18-functions/functions.json')
    ci = load(rawdir / 'ci-run.json')
    assert str(ci['databaseId']) == enc['run_id'] == prof['run_id'] == '38190911140'
    assert ci['headSha'] == enc['git_sha'] == prof['git_sha']
    assert ci['status'] == 'completed' and ci['conclusion'] == 'success'
    cand = 'r26-b-552-dense-forward'
    par = {r['file']: r for r in enc['rows'] if r['candidate'] == 'public552'}
    new = {r['file']: r for r in enc['rows'] if r['candidate'] == cand}
    phases = {r['file']: r for r in prof['rows']}
    original = load(ROOT / 'evidence/round26/38181703981/dfront-b8-native/diagnostics/r18-functions/functions.json')
    prev = {r['file']: r for r in original['rows']}
    assert len(par) == len(new) == len(phases) == len(prev) == 28
    assert set(par) == set(new) == set(phases) == set(prev)
    for directory, key in [('candidates/'+cand, cand), ('references/round24-public-552', 'public552')]:
        assert {name: digest(ROOT / directory / name) for name in ['parse.rs','Parse.lean']} == enc['source_hashes'][key]
    assert prof['source_hashes'] == enc['source_hashes'][cand]
    rows = []
    for filename in sorted(par):
        old, candidate, phase, prior = par[filename], new[filename], phases[filename], prev[filename]
        assert len({r['input_sha256'] for r in [old,candidate,phase,prior]}) == 1
        assert old['raw_bytes'] == candidate['raw_bytes'] == phase['raw_bytes'] == prior['raw_bytes']
        active = phase['functions']['d_parse']['calls'] > 0
        assert active == (prior['functions']['d_parse']['calls'] > 0)
        same = all(old[key] == candidate[key] for key in ['tokens','tokens_sha256','output_bytes','output_sha256'])
        assert active or same
        rows.append({'file':filename,'D_active':active,'token_output_identity':same,
                     'byte_delta':candidate['output_bytes']-old['output_bytes'],
                     'token_delta':candidate['tokens']-old['tokens'],
                     'quality_delta_pp':100*(candidate['output_bytes']-old['output_bytes'])/old['raw_bytes']/28})
    totals = {name:{key:sum(r['functions'][name][key] for r in phases.values()) for key in ['calls','inclusive_ns']} for name in prof['functions']}
    assert totals == prof['totals']
    oldsrc = (ROOT/'references/round24-public-552/parse.rs').read_text()
    newsrc = (ROOT/'candidates'/cand/'parse.rs').read_text()
    a,b = span(oldsrc,'d_fill_nextl'); c,d = span(newsrc,'d_fill_nextl')
    # The source patch also removes the single separator newline following this helper.
    assert oldsrc[:a] == newsrc[:c]
    assert oldsrc[b:].lstrip('\n') == newsrc[d:].lstrip('\n')
    feedback_path = OUT/'b16-dense-forward-feedback.json'
    feedback = load(feedback_path)
    delta = sum(r['byte_delta'] for r in rows)
    pp = sum(r['quality_delta_pp'] for r in rows)
    assert delta == 80 == feedback['actual_output_bytes_delta']
    assert abs(pp - feedback['actual_mean_quality_delta_pp']) < 1e-15
    assert totals == feedback['candidate_complete_coarse_work']
    result = {'status':'VERIFIED_INDEPENDENT_RAW_RECEIPT_RECOMPUTATION',
              'computed_utc':datetime.now(timezone.utc).isoformat(),'run_id':enc['run_id'],'git_sha':ci['headSha'],
              'source_hashes':prof['source_hashes'],'raw_inventory_count':len(input_hashes),'raw_hashes':input_hashes,
              'original_feedback_sha256':digest(feedback_path),'original_analyzer_sha256':digest(ROOT/'scripts/r26-b-analyze-dense-forward.py'),
              'source_scope':'Only d_fill_nextl function plus following separator newline differs from public552.',
              'inputs':len(rows),'raw_bytes':sum(r['raw_bytes'] for r in par.values()),'D_active_inputs':sum(r['D_active'] for r in rows),
              'non_D_identity_inputs':sum(not r['D_active'] and r['token_output_identity'] for r in rows),
              'byte_delta':delta,'equal_file_quality_delta_pp':pp,
              'bytes_smaller':sum(r['byte_delta']<0 for r in rows),'bytes_larger':sum(r['byte_delta']>0 for r in rows),
              'bytes_equal':sum(r['byte_delta']==0 for r in rows),'identity_inputs':sum(r['token_output_identity'] for r in rows),
              'candidate_coarse_function_totals':totals,'rows':rows,
              'decision':'Preserve root stop decision for this quality-regressing B16; no paired/gate/flen sweep requested.',
              'limits':['Eight downloaded files hash-verified; GitHub ZIP digest not independently reconstructed.',
                        'Inclusive nested phase durations are diagnostic and cannot be added or compared across jobs as official speed.',
                        'Public encoder/decode receipt is finite; no original obligation/full gate, paired timing, independent runner or formal share claim.']}
    (OUT/'b16-independent-audit.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({k:result[k] for k in ['status','inputs','D_active_inputs','non_D_identity_inputs','byte_delta','equal_file_quality_delta_pp','bytes_smaller','bytes_larger','bytes_equal','identity_inputs']},indent=2))


def public601():
    refs = {'601':'references/round26-public-601','595':'references/round21-public-595','613':'references/round26-public-613','631':'references/round26-public-631','641':'references/round26-public-641'}
    srcs = {key:(ROOT/value/'parse.rs').read_text() for key,value in refs.items()}
    hashes = {key:{name:digest(ROOT/value/name) for name in ['parse.rs','Parse.lean']} for key,value in refs.items()}
    for key, relative in refs.items():
        receipt = load(ROOT/relative/'source-receipt.json')
        assert all(receipt['files'][name]['sha256'] == hashes[key][name] for name in hashes[key])
    def scrub(src):
        # Remove exactly the isolated changed wrappers and the two known header comments.
        src = re.sub(r'^// Derived from public #514; selected generic search rows from our #590 \(public #583/#542\)\.\n// Proven match/flush helpers from public #542 when recorded\. Classification and routing retained\.\n','',src)
        src = src.replace('#[inline(never)]\npub fn format_id', 'pub fn format_id')
        for name in ['bulk_parse'] + re.findall(r'\bfn (p125_row\d+)\b',src):
            a,b = span(src,name)
            src = src[:a]+'REMOVED_WRAPPER'+src[b:]
        # Wrapper count (17 vs 18) and whitespace outside wrappers are intentionally ignored.
        src = re.sub(r'#\[inline\(never\)\]\s*pub\s*REMOVED_WRAPPER', '', src)
        src = src.replace('pub REMOVED_WRAPPER','').replace('REMOVED_WRAPPER','')
        return re.sub(r'\s+','',src)
    assert scrub(srcs['601']) == scrub(srcs['595'])
    names = re.findall(r'\bfn\s+(\w+)\b',srcs['601'])
    assert len(names) == len(set(names))
    rows = []
    for key,src in srcs.items():
        common = set(names) & set(re.findall(r'\bfn\s+(\w+)\b',src))
        identity = [name for name in sorted(common) if function(srcs['601'],name) == function(src,name)]
        changed = [name for name in sorted(common) if name not in identity]
        rows.append({'reference':key,'common_functions':len(common),'exact_functions_equal':len(identity),'changed_functions':changed})
    difflines = list(difflib.unified_diff(srcs['595'].splitlines(),srcs['601'].splitlines(),fromfile='public595',tofile='public601',n=3))
    (OUT/'b17-public601-vs595.diff').write_text('\n'.join(difflines)+'\n')
    wrappers = {key:{name:function(src,name) for name in re.findall(r'\bfn (p125_row\d+)\b',src)} for key,src in srcs.items()}
    result = {'status':'VERIFIED_STATIC_EXECUTABLE_DIFFERENCE_CENSUS','computed_utc':datetime.now(timezone.utc).isoformat(),
              'source_hashes':hashes,'comparisons':rows,'public601_vs595_core_equal_after_isolated_changes':True,
              'changes_vs595':['two lineage header comments absent','format_id inline(never) attribute absent','bulk_parse class-to-row routing changed','17 row wrappers replaced by 18 wrappers with existing engine calls/parameter budgets'],
              'wrappers':wrappers,
              'decision':'NO_GO blind public601 mechanism-migration/whole-program rerun: existing595 kernels exact; no new match information or stage representation.',
              'limits':['Static source identity outside isolated wrappers is not runtime identity or performance evidence.',
                        'Existing published formal coordinates are whole-program historical observations, not module causal effects or this round results.',
                        'Changed wrapper budgets/routes can change output and work; no inherited gate or latest-share claim.']}
    (OUT/'b17-public601-static-audit.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'status':result['status'],'comparisons':rows,'core_equal_601_595':True,'decision':result['decision']},indent=2))


if __name__ == '__main__':
    b16()
    public601()
