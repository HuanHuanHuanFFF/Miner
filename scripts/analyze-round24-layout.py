"""Audit the process-layout diagnostic without turning it into official scores."""
from pathlib import Path
import json,hashlib,statistics as st,subprocess
ROOT=Path(__file__).resolve().parents[1];E=ROOT/'evidence/round24'
def main():
    root=E/'38101377725/layout-av-diagnostic/diagnostics/r24-layout';source=root/'layout.json';d=json.loads(source.read_bytes());assert d['status']=='COMPLETE_CONTROLLED_PAIRED_LAYOUT_DIAGNOSTIC';meta=json.loads((E/'am-once-decomposition.json').read_bytes());hs={k.replace('\\','/'):v for k,v in meta['local_official_source_read'].items()};assert len(d['blocks'])==16;gaps=[]
    upstream=ROOT.parents[1]/'sources/conjectures-optimisation-deflate';local=(upstream/'validator/incumbent/parse.rs').read_bytes();assert hashlib.sha256(local).hexdigest()==hs['incumbent/parse.rs']
    blob=subprocess.check_output(['git','-C',str(upstream),'show','a356bbff18b60c4527fbcc85d5a28ef9c20214e0:validator/incumbent/parse.rs']);assert blob==local.replace(b'\r\n',b'\n') and hashlib.sha256(blob).hexdigest()==d['incumbent_source_sha256']
    binding={'local_raw_sha256':hs['incumbent/parse.rs'],'pinned_git_blob_sha256':hashlib.sha256(blob).hexdigest(),'runner_source_sha256':d['incumbent_source_sha256'],'local_text_matches_pin_after_CRLF_to_LF':True,'scope':'Localreadingcopy usedCRLF; runnerexactbytes matchthe originalpinnedGitblob. Localrawbytes were notrewritten.'}
    for row in d['blocks']:
        p=root/row['raw_file'];assert hashlib.sha256(p.read_bytes()).hexdigest()==row['raw_sha256'];ctx=row['actual_context'];assert ctx['files']['/proc/sys/kernel/randomize_va_space'].strip()=='2';flag=int(ctx['files']['/proc/self/personality'].strip(),16);assert bool(flag&0x40000)==(row['mode']=='process_no_randomize')
    modes=['original_randomization','process_no_randomize'];names=['once','r24-609-root-word-price-proof1']
    for mode in modes:
        for block in [1,2]:
            by={r['method']:r for r in d['blocks']if r['mode']==mode and r['block']==block}
            for name in names:
                a,b=by[name],by[name+'-shadow'];assert a['metadata']['methods'][name]['lib_sha256']==b['metadata']['methods'][name+'-shadow']['lib_sha256'];gaps.append({'mode':mode,'block':block,'family':name,'alias_gap_pct':100*(b['diagnostic_time_axis']/a['diagnostic_time_axis']-1)})
    summaries=[{'family':name,**{mode:{'absolute_gap_median_pct':st.median(abs(r['alias_gap_pct'])for r in gaps if r['mode']==mode and r['family']==name),'signed_gaps_pct':[r['alias_gap_pct']for r in gaps if r['mode']==mode and r['family']==name]}for mode in modes}}for name in names]
    result={'status':'VERIFIED_CONTROLLED_LAYOUT_DIAGNOSTIC_NOT_OFFICIAL_PERFORMANCE','source':source.relative_to(ROOT).as_posix(),'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'incumbent_source_binding':binding,'process_personality_verified':True,'global_randomize_setting_unchanged':2,'paired_processes':16,'gaps':gaps,'summary':summaries,'decision':'No uniform reduction: once worsens whilefaststack improves. Thisintervention doesnot establish a reliableprotocolcorrection or closeunderlyingcause. Do notreplaceofficialscores ormechanicallyrepeat layouttrials.','limits':'One diagnosticrunner,2blockspermode. Probe verifiedchildpersonality, notactualphysicalcache placement. No causalexclusion ofalladdresslayout interactions; no scoreprojection fromthese data.'}
    p=E/'layout-av-analysis.json';assert not p.exists();p.write_bytes((json.dumps(result,indent=2)+'\n').encode());print(json.dumps(summaries))
if __name__=='__main__':main()
