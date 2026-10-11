"""Conservative source reachability and proof-space inventory; no proof pruning."""
from pathlib import Path
import hashlib
import importlib
import json
import re

ROOT=Path(__file__).resolve().parents[1]
CANDIDATE=ROOT/'candidates/r26-b-628-shared-cache-fix1'
E=ROOT/'evidence/round26/route-b'


def sha(b):return hashlib.sha256(b).hexdigest()


def main():
    syntax=importlib.import_module('r26-b-fix-shared-cache')
    raw=(CANDIDATE/'parse.rs').read_bytes();source=raw.decode();code=syntax.masked(source);spans=syntax.spans(source)
    names=set(spans)
    calls={}
    for name,(lo,hi)in spans.items():
        body=code[code.index('{',lo):hi]
        refs=set(re.findall(r'\b([A-Za-z0-9_]+)\s*(?:::\s*<[^<>]*>)?\s*\(',body))&names
        calls[name]=sorted(refs)
    reached={'parse'};pending=['parse']
    while pending:
        name=pending.pop()
        for child in calls[name]:
            if child not in reached:reached.add(child);pending.append(child)
    unreachable=names-reached
    lean=(CANDIDATE/'Parse.lean').read_bytes();text=lean.decode()
    declarations=list(re.finditer(r'^theorem\s+([^\s(:]+)',text,re.M))
    proposals=[]
    for index,match in enumerate(declarations):
        stop=declarations[index+1].start()if index+1<len(declarations)else len(text)
        block=text[match.start():stop]
        targets=set(re.findall(r'\bslot\.([A-Za-z0-9_]+)',block))
        owners=set()
        for target in targets:
            owners.update(n for n in names if target==n or target.startswith(n+'_loop'))
        if owners and owners<=unreachable:
            # Only a space/investment proposal; declarations with explicit
            # proof dependencies or generic scopes must be checked before deletion.
            proposals.append({'theorem':match.group(1),'line':text.count('\n',0,match.start())+1,
                              'approx_block_bytes':len(block.encode()),'rust_owners':sorted(owners),
                              'status':'POSSIBLE_UNREACHABLE_TARGET_DECLARATION_NOT_APPROVED_FOR_REMOVAL'})
    result={'status':'VERIFIED_TEXTUAL_CALLGRAPH_AND_DECLARATION_SPACE_INVENTORY_ONLY',
            'candidate':CANDIDATE.name,'rust_sha256':sha(raw),'lean_sha256':sha(lean),
            'rust_functions':len(names),'syntactically_reachable_functions':len(reached),
            'unreachable_function_names':sorted(unreachable),'new_reachable_functions':sorted(n for n in reached if n.startswith('r26_b_')),
            'old_lean_bytes':len(lean),'official_cap_bytes':524288,'headroom_bytes':524288-len(lean),
            'possible_unreachable_target_declarations':proposals,
            'approx_proposal_bytes':sum(p['approx_block_bytes']for p in proposals),
            'acceptance_plan':[
                'Use native bytes/actual total-time first; no fullproof merely because source exists.',
                'Fresh extraction identifies cloned ownedcache argument/binder states, plannertransfer and SFconsumer loops. Inspect them before adapting arithmetic or borrowedarray specifications.',
                'Only after useful performance, prune declarations proven unnecessary by actualnew parse dependency/step resolution and exact concrete configuration, then compile with originallimits. Do not remove Rustfunctions or alter the originalLZ77 obligation to fit.',
                'New owner planner loops need totality and retained-buffer state; consumerloops need bounded progress/access and final validation linkage. Strongseed native equality is finite evidence only.',
                'Declare exactpair acceptance only after official re-extraction, originalobligation, axiomwhitelist and roundtrip/fullgate; freeze and independently confirm samepair.',
            ],
            'limits':[
                'Syntactic callgraph retains allbranches, does not evaluateconstants. Generic invocation regex and no function-pointer assumption require review before any pruning claim.',
                'Theorem block bytes end at the nexttheorem and can include intervening namespaces/notations. They are approximate inventory, not safe deletion spans.',
                'A theorem for an unreachableRusthelper may still be explicitly used in anotherproof or registeredstep; inspect actual proofdependencies. No Leandeclaration has been removed or compiled here.',
            ]}
    (E/'shared-cache-proof-preaudit.json').write_bytes((json.dumps(result,indent=2)+'\n').encode())
    print(json.dumps({k:result[k]for k in ('status','rust_functions','syntactically_reachable_functions','headroom_bytes','approx_proposal_bytes')},indent=2))


if __name__=='__main__':main()
