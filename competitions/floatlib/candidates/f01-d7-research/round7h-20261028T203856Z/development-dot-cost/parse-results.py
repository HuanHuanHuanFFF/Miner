"""Strict completeness/checksum parser; all three raw samples remain available."""
import statistics

MASK=(1<<32)-1
def require(ok,message):
    if not ok:raise ValueError(message)

def verify(text,fixtures):
    expected={x['name']:x for x in fixtures['cases']};rounds={x['id']:x for x in fixtures['round_cases']}
    seen={};seen_rounds={};done=[]
    for line in text.splitlines():
        if not line.strip():continue
        f=line.split('\t')
        if f[0]=='DOT_VERIFY':
            require(len(f)==14,'Bad numerical row width')
            name=f[1];require(name in expected and name not in seen,'Unknown/duplicate numerical row')
            e=expected[name];v=list(map(int,f[2:13]));require(v[0]==e['expected'],'Expected word differs')
            require(v[1]==v[2],'Cold/prepared FP attempts differ')
            if e['fast_result'] is not None:require(v[1]==e['fast_result'],'Expected FP accept/miss differs')
            else:require(v[1] in (0,e['expected']),'Unknown-proposal wrong acceptance')
            require(all(x==e['expected'] for x in v[3:]),'Complete adapter/reference mismatch')
            require(f[13]=='true','Numerical checker rejected row');seen[name]=v
        elif f[0]=='DOT_ROUND':
            require(len(f)==5 and f[1] in rounds and f[1] not in seen_rounds,'Bad/duplicate round row')
            require(int(f[2])==int(f[3])==rounds[f[1]]['expected'] and f[4]=='true','Native word RNE mismatch')
            seen_rounds[f[1]]=int(f[3])
        elif f[0]=='DOT_VERIFY_DONE':
            require(len(f)==5,'Bad numerical footer');done.append(list(map(int,f[1:])))
        else:raise ValueError('Unexpected numerical output: '+line[:200])
    require(set(seen)==set(expected) and set(seen_rounds)==set(rounds),'Numerical rows incomplete')
    require(len(done)==1 and done[0][0]==len(expected) and done[0][1]==len(rounds),'Numerical footer incomplete')
    actual_accept=sum(v[1]!=0 for v in seen.values());unknown=sum(x['fast_result'] is None for x in expected.values())
    require(done[0][2:]==[actual_accept,unknown],'Numerical footer observer differs')
    known=[n for n,e in expected.items() if e['fast_result'] is not None]
    return {'dots':len(seen),'word_rounds':len(seen_rounds),'actual_accept':actual_accept,'known_fast_cases':len(known),
        'known_actual_accept':sum(seen[n][1]!=0 for n in known),'unknown_fast_cases':unknown,
        'all_complete_words_match':True,'all_expected_accept_miss_match':True,
        'scope':'Finite native checks only, not an all-input proof.'}

def rows(text,fixtures,group):
    selected={x['name']:x for x in fixtures['cases'] if x['timed'] and x['group'] in (group,'directed')}
    samples={n:[] for n in selected};setup={};variant=set();boundary=set();footers=[]
    for line in text.splitlines():
        if not line.strip():continue
        f=line.split('\t')
        if f[0]=='DOT_SAMPLE':
            require(len(f)==13,'Bad timing row width');name=f[1]
            require(name in selected,'Unknown timed case');e=selected[name]
            require(f[2]==e['group'],'Case group changed');variant.add(f[3]);boundary.add(f[4])
            trial,n,iters,macs,ns,sink,printed,keep=map(int,f[5:])
            require(trial in (0,1,2) and all(x['trial']!=trial for x in samples[name]),'Bad/duplicate trial')
            require(n==len(e['x'])==len(e['y']) and n>0,'Input length differs')
            want_iters=max(1,(131072+n-1)//n)
            require(iters==want_iters and macs==n*iters,'Timed work differs')
            seed=(1664525*trial+2654435769)&MASK;wanted=(seed+iters*e['expected'])&MASK
            require(sink==printed==wanted and keep==e['expected'],'Timed checksum/witness mismatch')
            require(ns>0,'Nonpositive measured cost')
            samples[name].append({'trial':trial,'n':n,'iterations':iters,'actual_macs':macs,'ns':ns,
                'sink':sink,'expected_sink':wanted,'witness_word':keep})
        elif f[0]=='DOT_SETUP':
            require(len(f)==9 and f[1] in selected and f[1] not in setup,'Bad/duplicate setup row')
            name=f[1];e=selected[name];require(f[2]==e['group'],'Setup group differs')
            variant.add(f[3]);boundary.add(f[4]);prep,life,trials,witness=map(int,f[5:])
            require(prep>=0 and life>0 and trials==3 and witness==e['expected'],'Invalid lifecycle/witness')
            if f[4]=='full':require(prep==0,'Full call must include its own prep')
            setup[name]={'prep_ns':prep,'lifecycle_wall_ns':life,'trials':trials,'witness':witness}
        elif f[0]=='DOT_MEASURE_DONE':
            require(len(f)==6 and f[1]==group,'Invalid measurement footer')
            require(int(f[4])==len(selected) and int(f[5])==3,'Measurement footer count differs')
            footers.append({'variant':f[2],'boundary':f[3]})
        else:raise ValueError('Unexpected timing output: '+line[:200])
    require(len(variant)==len(boundary)==1,'Mixed/missing runner modes')
    require(set(setup)==set(selected) and all(len(x)==3 for x in samples.values()),'Timed records incomplete')
    require(len(footers)==1 and footers[0]=={'variant':next(iter(variant)),'boundary':next(iter(boundary))},'Missing/duplicate/mixed measurement footer')
    result={}
    for name,e in selected.items():
        data=sorted(samples[name],key=lambda x:x['trial']);ns=[x['ns'] for x in data]
        result[name]={'kind':e['kind'],'group':e['group'],'n':len(e['x']),'variant':next(iter(variant)),
            'boundary':next(iter(boundary)),'median_ns':statistics.median(ns),'samples':data,'setup':setup[name],
            'model_fast_result':e['fast_result']}
    return result

def paired(runs):
    result=[]
    for group in ('24282403','24282405'):
        for boundary in ('full','prepared'):
            block=sorted([r for r in runs if r['group']==group and r['boundary']==boundary],key=lambda x:x['order'])
            require([r['order'] for r in block]==list(range(8)),'Incomplete ABBA block')
            require([r['variant'] for r in block]==['exact','eager','eager','exact','exact','lazy','lazy','exact'],'Order changed')
            for variant,start in [('eager',0),('lazy',4)]:
                for offset,ci,vi in [(0,start,start+1),(1,start+3,start+2)]:
                    c=block[ci]['rows'];v=block[vi]['rows'];require(set(c)==set(v),'Paired cases differ')
                    cat={}
                    for kind in sorted({x['kind'] for x in c.values()}):
                        names=[n for n,x in c.items() if x['kind']==kind]
                        base=sum(c[n]['median_ns'] for n in names);new=sum(v[n]['median_ns'] for n in names)
                        cat[kind]={'cases':len(names),'control_ns_sum':base,'variant_ns_sum':new,'ratio':new/base}
                    base=sum(x['median_ns'] for x in c.values());new=sum(x['median_ns'] for x in v.values())
                    result.append({'group':group,'boundary':boundary,'variant':variant,'abba_pair':offset,
                        'control_order':ci,'variant_order':vi,'all_cases':len(c),'control_ns_sum':base,'variant_ns_sum':new,
                        'ratio':new/base,'categories':cat,'per_case_ratios':{n:v[n]['median_ns']/c[n]['median_ns'] for n in c},
                        'process_wall_ratio':block[vi]['wall_seconds']/block[ci]['wall_seconds'],
                        'scope':'All retained synthetic timed cases; not a competition/model score or success probability.'})
    return result
