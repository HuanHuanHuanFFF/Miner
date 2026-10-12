"""Limited static comparison of 662 with the four relevant existing fast bases."""
from pathlib import Path
import sys, importlib, re, json, difflib, hashlib
ROOT = Path(__file__).resolve().parents[4]
OUT = Path(__file__).parent
sys.path.insert(0, str(ROOT / 'scripts'))
F = importlib.import_module('make-round3-size385').function_bodies
def clean(s):
    return re.sub(r'//[^\n]*', '', re.sub(r'/\*.*?\*/', '', s, flags=re.S))
def norm(s): return re.sub(r'\s+', '', clean(s))
sources, funcs, constants, graph = {}, {}, {}, {}
for n in ['613','631','641','658','662']:
    p = ROOT / ('references/round26-public-'+n+'/parse.rs')
    sources[n] = p.read_text(encoding='utf-8')
    funcs[n] = F(sources[n])
    constants[n] = dict(re.findall(r'pub const\s+(\w+)\s*:[^=]+?=\s*([^;]+);', clean(sources[n])))
    graph[n] = {k: set(re.findall(r'\b([A-Za-z_]\w*)\s*(?:::<[^{};]*?>)?\s*\(', clean(v))) & set(funcs[n]) for k,v in funcs[n].items()}
def closure(n):
    seen, q = set(), ['parse']
    while q:
        k=q.pop()
        if k in seen: continue
        seen.add(k); q.extend(graph[n][k]-seen)
    return seen
target = funcs['662']; target_reach = closure('662')
comparisons=[]
for n in ['613','631','641','658']:
    common=set(target)&set(funcs[n])
    equal=sorted(k for k in common if norm(target[k])==norm(funcs[n][k]))
    changed=sorted(common-set(equal)); added=sorted(set(target)-set(funcs[n]))
    record={'base':n,'common_count':len(common),'identical_body_count':len(equal),'changed':changed,
            'added':added,'removed':sorted(set(funcs[n])-set(target)),
            'active_changed':[k for k in changed if k in target_reach],
            'active_added':[k for k in added if k in target_reach],
            'common_constant_changes':{k:[constants[n][k],constants['662'][k]] for k in sorted(set(constants[n])&set(constants['662'])) if norm(constants[n][k])!=norm(constants['662'][k])}}
    comparisons.append(record)
    diff=[]
    for k in record['active_changed']:
        if re.fullmatch(r'p135_row\d+',k) or k in ['parse','bulk_parse','bulk_parse_fallback']:
            diff.extend(difflib.unified_diff(clean(funcs[n][k]).splitlines(),clean(target[k]).splitlines(),fromfile=n+':'+k,tofile='662:'+k,lineterm=''))
    (OUT / ('662-vs-'+n+'-active.diff')).write_text('\n'.join(diff)+'\n', encoding='utf-8')
new_vs641 = set(comparisons[2]['active_added']) | set(comparisons[2]['active_changed'])
matches={k:[n for n in ['613','631','641','658'] if k in funcs[n] and norm(target[k])==norm(funcs[n][k])]
         for k in sorted(new_vs641)}
result={'status':'VERIFIED_LIMITED_STATIC_BODY_AND_CONSTANT_COMPARISON_NOT_RUNTIME',
        'identities':{n:hashlib.sha256((ROOT/('references/round26-public-'+n+'/parse.rs')).read_bytes()).hexdigest() for n in funcs},
        'function_counts':{n:len(fs) for n,fs in funcs.items()},'comparisons':comparisons,
        '662_possible_parse_closure':sorted(target_reach),'changed_or_added_vs641_exact_known_bodies':matches,
        'limitations':['Only 613/631/641/658 were compared. No exhaustive novelty claim.',
                       'Function bodies omit comments/whitespace; constants and call parameters separate.',
                       'Syntactic closure includes inactive generic/constant branches. No runtime route/quality claim.']}
(OUT/'662-static-comparison.json').write_text(json.dumps(result,indent=2)+'\n',encoding='utf-8')
print(json.dumps({'counts':result['function_counts'], 'comparisons':[{'base':c['base'],'identical':c['identical_body_count'],'active_changed':c['active_changed'],'active_added':c['active_added'],'constants':c['common_constant_changes']} for c in comparisons],'known_added':matches}))
