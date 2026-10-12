"""Static body/constant/call-closure comparison of the three disclosed fast sources."""
from pathlib import Path
import difflib
import hashlib
import importlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'evidence/round26/route-a'
EXTRACT=importlib.import_module('make-round3-size385').function_bodies


def sha(raw):return hashlib.sha256(raw).hexdigest()
def strip(text):
    text=re.sub(r'/\*.*?\*/','',text,flags=re.S)
    return re.sub(r'//[^\n]*','',text)
def norm(text):return re.sub(r'\s+','',strip(text))


def main():
    sources={};functions={};constants={};identities={}
    for number in ['613','631','641']:
        folder=ROOT/f'references/round26-public-{number}';receipt=json.loads((folder/'source-receipt.json').read_bytes())
        for file in ['parse.rs','Parse.lean']:assert sha((folder/file).read_bytes())==receipt['files'][file]['sha256']
        sources[number]=(folder/'parse.rs').read_text();functions[number]=EXTRACT(sources[number])
        constants[number]=dict(re.findall(r'pub const\s+(\w+)\s*:[^=]+?=\s*([^;]+);',strip(sources[number])))
        identities[number]={'source_receipt_sha256':sha((folder/'source-receipt.json').read_bytes()),'rust_sha256':receipt['files']['parse.rs']['sha256'],'author_hotkey':receipt['author_hotkey'],'function_count':len(functions[number])}
    comparisons=[]
    prefixes=['pc_','pi1_','pim_','o_a_','r109_','n_','fx0_','q4_','p12_']
    for left,right in [('613','641'),('631','641')]:
        common=set(functions[left])&set(functions[right]);selected=[n for n in sorted(common)if any(n.startswith(p)for p in prefixes)]
        equal=[n for n in selected if norm(functions[left][n])==norm(functions[right][n])]
        changed=[n for n in selected if n not in equal]
        ccommon=set(constants[left])&set(constants[right]);cchanges={n:[constants[left][n],constants[right][n]]for n in sorted(ccommon)if any(n.startswith(p)for p in prefixes)and norm(constants[left][n])!=norm(constants[right][n])}
        comparisons.append({'left':left,'right':right,'same_named_functions':len(selected),'normalized_body_identical':equal,'changed_functions':changed,'changed_common_constants':cchanges})
        lines=[]
        for name in changed:
            if name.startswith(('pc_','pi1_','pim_','o_a_','r109_','n_','fx0_')):
                lines.extend(difflib.unified_diff(strip(functions[left][name]).splitlines(),strip(functions[right][name]).splitlines(),fromfile=left+':'+name,tofile=right+':'+name,lineterm=''))
        (OUT/f'fast-source-{left}-vs{right}.diff').write_text('\n'.join(lines)+'\n')
    for comparison in comparisons:
        left,right=comparison['left'],comparison['right']
        common=set(constants[left])&set(constants[right])
        comparison['all_common_constant_differences']={n:[constants[left][n],constants[right][n]]for n in sorted(common)if norm(constants[left][n])!=norm(constants[right][n])}
    pe_names=[n for n in functions['613']if n.startswith('pe_')and n.replace('pe_','pc_',1)in functions['613']]
    pe_changed=[n for n in pe_names if norm(functions['613'][n].replace('pe_','pc_'))!=norm(functions['613'][n.replace('pe_','pc_',1)])]
    closures={}
    for number,fs in functions.items():
        graph={name:set(re.findall(r'\b([A-Za-z_]\w*)\s*(?:::<[^{};]*?>)?\s*\(',strip(body)))&set(fs) for name,body in fs.items()}
        def reach(start):
            seen=set();queue=[start]
            while queue:
                n=queue.pop()
                if n in seen:continue
                seen.add(n);queue.extend(graph[n]-seen)
            return sorted(seen)
        wrappers=[n for n in fs if re.fullmatch(r'(?:x147|p135)_row\d+',n)]
        reachable=reach('parse')
        used_constants=set(re.findall(r'\b[A-Za-z_]\w*\b','\n'.join(fs[n]for n in reachable)))&set(constants[number])
        closures[number]={'parse_possible_closure':reachable,'reachable_referenced_constants':{n:constants[number][n]for n in sorted(used_constants)},'row_wrappers':{n:fs[n]for n in wrappers},
                          'parse_and_route_bodies':{n:fs[n]for n in ['parse','route','bulk_parse','bulk_parse_fallback','bulk_despec']if n in fs}}
    result={'status':'VERIFIED_STATIC_SOURCE_HASH_BODY_AND_POSSIBLE_CLOSURE_COMPARISON_NOT_RUNTIME_ROUTE',
            'identities':identities,'comparisons':comparisons,'613_PE_vs_PC':{'common_prefixed_count':len(pe_names),'changed_after_prefix_rename':pe_changed},
            'closures':closures,'limits':['Normalized function bodies omit whitespace/comments; this is not semantic equivalence. Referenced constants and call parameters are separate.','Call closure contains all syntactic branches, including unreachable constants and fallback domains; no actual public file route asserted.','No whole formal time is attributed to any module; no measured613/631native quality or current paired timing yet.']}
    (OUT/'fast-source-static-comparison.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({'comparisons':[{k:v for k,v in c.items()if k!='normalized_body_identical'}for c in comparisons],'PE':result['613_PE_vs_PC']},indent=2))


if __name__=='__main__':main()
