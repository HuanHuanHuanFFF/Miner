"""One A4-temporal layout, literal source-event counts on completed exposed plans."""
from pathlib import Path
from datetime import datetime,timezone
import hashlib,json,time
H=Path(__file__).resolve().parent
R=next(p for p in H.parents if (p/'competitions/floatlib/pins.json').is_file())
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest();start=time.monotonic()
oldpath=R/'competitions/floatlib/candidates/f01-d7-research/round3h-20261025T091810Z/astra-workers/matrix-architecture/analysis.json'
old=json.loads(oldpath.read_bytes());specs=[]
for g in old['groups']:
 files={k:R/v['path'] for k,v in g['evidence'].items()}
 for k,f in files.items():assert sha(f)==g['evidence'][k]['sha256']
 specs.append((g['run'],g['seed'],files))
new=R/'competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/40398675395/download-42cfe8ce05b24bf6bd145777f10a1729/diagnostics/f01-d7-public-suite/public-suite'
specs.append((40398675395,1927003,{'plan':new/'public-drawn-plan.json','work':new/'public-cell-work.json','verdict':new/'f01-r15-dev-packed-b2-1-verdict.json'}))
groups=[]
for run,seed,files in specs:
 plan,work,v=(json.loads(files[k].read_bytes()) for k in ('plan','work','verdict'))
 cost={c:work[c]*v['classes'][c]['submission_ns'] for c in work};whole=sum(cost.values());rows=[]
 for c in plan['cases']:
  if c['kernel']!='bmm' or not c['timed']:continue
  b,m,n,p=(c[k] for k in ('batch','m','n','p'))
  if not(3<=p<=8 and n>1 and m>=4):continue
  G=(p+1)//2;T=(n+3)//4;N=b*m*n;H4=m//4;tail=m%4;apackets=b*m*T
  rows.append({'name':c['name'],'shape':[b,m,n,p],'G_A_reuse':G,'T_k_packets':T,
    'old_c70_A_ofbits':G*N,'new_valid_A_ofbits':N,'removed_A_ofbits':(G-1)*N,
    'new_A_packet_records':apackets,'new_A_pointer_slots':apackets,'new_A_padding_fields':b*m*(4*T-n),
    'new_A_global_major_request_bytes':32*apackets+24,
    'new_A_live_cache_major_bytes':32*apackets+24,
    'new_A_packet_hot_reads':b*m*G*T,'old_c70_A_raw_hot_reads':b*m*G*n,
    'unchanged_B_packet_records':b*G*T,'unchanged_B_valid_native_fields':2*b*G*n,
    'unchanged_terminal_F2':b*m*G,'unchanged_finish_calls':b*m*p,
    'R16_comparison_A_only':{'A4_records':b*H4*n,'A_native_decodes_including_unprepared_tail':b*(4*H4+tail*G)*n,'A_panel_arrays':b*H4,'result_tile_arrays':b*H4,'F8_result_tiles':b*H4*G,'old_extra_request_vs_B2':b*H4*(32*n+160-16*G),'scope':'R16 had old B2, cross-row eight accumulators and own tails; not a direct whole-cost comparison to c70'}})
 cells={':'.join(x['name'].split(':')[:2]) for x in rows}
 keys=['old_c70_A_ofbits','new_valid_A_ofbits','removed_A_ofbits','new_A_packet_records','new_A_pointer_slots','new_A_padding_fields','new_A_global_major_request_bytes','new_A_packet_hot_reads','old_c70_A_raw_hot_reads','unchanged_B_packet_records','unchanged_B_valid_native_fields','unchanged_terminal_F2','unchanged_finish_calls']
 groups.append({'run':run,'seed':seed,'shapes':len(rows),'source_counts':{k:sum(x[k] for x in rows) for k in keys},'max_new_A_live_major_bytes':max([x['new_A_live_cache_major_bytes'] for x in rows] or [0]),'whole_BMM_share':sum(x for k,x in cost.items() if k.startswith('bmm:'))/whole,'selected_cell_whole_upper':sum(cost[x] for x in cells)/whole,'target_time':'UNKNOWN','actual_underflow_miss':'UNKNOWN','cases':rows,'evidence':{k:{'path':str(p.relative_to(R)),'sha256':sha(p)} for k,p in files.items()}})
report={'at_utc':datetime.now(timezone.utc).isoformat(),'layout':'Flat global Array A4 with one packet per row per4 consecutive k, synchronized with existing temporal B8; no cross-row result tile cache','initial_domain':'3<=p<=8,n>1,m>=4; p2 intentionally stays c70 because G=1 provides zero conversion-count amortization; not a width grid','groups':groups,'cost_scope':'Source counts for one plan evaluation conditional on every selected shape missing UnderflowZero. A bytes are8B header+16B payload+8B pointer slot per packet plus24B array header; physical allocator/closure/RC/caches/timing UNKNOWN. New preparation has exactly valid A decodes and padding stores. One flat global A buffer lives through the full output, unlike streamed R16 panels.','new_C':'NOT_RUN','new_Lean':'NOT_RUN','new_gate':'NOT_RUN','elapsed_seconds':time.monotonic()-start}
(H/'cost-screen.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps([{k:g[k] for k in ('run','seed','shapes','source_counts','max_new_A_live_major_bytes','whole_BMM_share','selected_cell_whole_upper')} for g in groups]))
