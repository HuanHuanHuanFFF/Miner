
#![allow(dead_code, unused_variables)]
#[path="frozen.rs"] mod base;
#[path="candidate.rs"] mod new;

fn table(mode: usize) -> Vec<u32> {
    let mut tabs = vec![0u32; base::D_TS];
    for i in 0..256 { tabs[i] = match mode { 0 => 1, 1 => 0, 2 => u32::MAX,
        3 => if i % 3 == 0 { 0 } else { 3 }, 4 => 1_000_000, _ => 3 }; }
    for i in 0..264 { tabs[256+i] = if mode>=5 {2} else {(i/4+2) as u32}; }
    if mode==6 { tabs[256+12]=3; }
    for i in 520..752 { tabs[i] = 17; }
    tabs
}
fn main() {
    let mut loader_cases = 0;
    for mode in 0..7 {
        let tabs = table(mode); let mut a = [0;256]; let mut b = [0;256];
        let mut la = [0;512]; let mut lb = [0;512]; let mut da = [0;32]; let mut db = [0;32];
        base::d_load(&tabs,0,&mut a,&mut la,&mut da);
        new::d_load_groups(&tabs,0,&mut b,&mut lb,&mut db);
        assert_eq!(a,b); assert_eq!(da,db); assert_eq!(la[..511],lb[..511]);
        let maximum=*b.iter().max().unwrap(); let mut mask=0u32;
        let starts=[11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227];
        let ends=[13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258];
        for g in 0..20 { if la[starts[g]..ends[g]].iter().all(|&x|x==la[starts[g]]) {mask|=1<<g;} }
        let expected=if b.iter().any(|&x|x==0) || maximum>4095 || mask==0 {0} else {(mask<<12)|maximum};
        assert_eq!(lb[511],expected); loader_cases += 1;
        let mut oldlc = [7;512]; let mut newlc = [7;512];
        base::d_load(&tabs,usize::MAX,&mut a,&mut oldlc,&mut da);
        new::d_load(&tabs,usize::MAX,&mut b,&mut newlc,&mut db);
        assert_eq!(a,b); assert_eq!(oldlc,newlc); assert_eq!(da,db); loader_cases += 1;
    }
    let mut dp_cases = 0;
    for n in [0usize,1,2,3,16,259,511,600,1025] {
        let src: Vec<u8> = (0..n).map(|i|(i%256)as u8).collect();
        for mode in 0..7 { for pmode in 0..4 { for len in [0u32,2,3,258,259,264,510,511] {
            let tabs = table(mode); let bs = vec![0]; let dt = [0;512];
            let rs = vec![len | (32767<<9) | (255<<24),0,1];
            let mut a=vec![0;n]; let mut b=vec![0;n];
            base::d_dp(&src,&rs,&tabs,&bs,&dt,&mut a,pmode);
            new::d_dp(&src,&rs,&tabs,&bs,&dt,&mut b,pmode);
            assert_eq!(a,b,"malformed len={} n={} mode={} pmode={}",len,n,mode,pmode);
            dp_cases += 1;
        } } }
    }
    // Multi-block reload, malformed records and differing dtab entries.
    for mode in 0..7 { for pmode in 0..4 {
        let src:Vec<u8>=(0..1200).map(|i|(i%256)as u8).collect();
        let mut tabs=table(mode); tabs.extend(table((mode+1)%7));
        let bs=vec![0,550]; let dt=[29;512];
        for rs in [vec![511,0,1,258 | (7<<9),600,1],vec![0,0,0],vec![3,0,999],vec![511,1100,1],vec![]] {
            let mut a=vec![0;1200]; let mut b=vec![0;1200];
            base::d_dp(&src,&rs,&tabs,&bs,&dt,&mut a,pmode);
            new::d_dp(&src,&rs,&tabs,&bs,&dt,&mut b,pmode);
            assert_eq!(a,b,"multi-block mode={} pmode={}",mode,pmode); dp_cases+=1;
        }
    } }
    // Witness that 510 is an actual generic gap price, while only 511 is reserved.
    let src=vec![0u8;600]; let lit=[1_000_000;256];
    let mut lc=[0u32;512]; for i in 264..512 {lc[i]=0x00ff_ffff;}
    let mut meta=lc; meta[511]=new::d_gap_word(&lit,&lc);
    let mut ra=[0u64;base::D_RING]; let mut rb=ra; let mut oa=vec![0;600]; let mut ob=oa.clone();
    let va=base::d_gap(&src,&lit,&lc,&mut ra,&mut oa,509,1,511,0,512,600,0,base::D_LIT);
    let vb=new::d_gap_groups(&src,&lit,&meta,&mut rb,&mut ob,509,1,511,0,512,600,0,new::D_LIT);
    assert_eq!(va,vb); assert_eq!(ra,rb); assert_eq!(oa,ob);
    let mut changed=lc; changed[510]=0;
    let mut rc=[0u64;base::D_RING]; let mut oc=vec![0;600];
    let vc=base::d_gap(&src,&lit,&changed,&mut rc,&mut oc,509,1,511,0,512,600,0,base::D_LIT);
    assert_ne!(va,vc,"510 witness failed to observe its price");
    // False stand-alone metadata is deliberately NOT an equivalence claim.
    let mut s=vec![0u8;9]; s[4]=1; let mut prices=[1u32;256]; prices[1]=3;
    let mut honest=[0u32;512]; honest[511]=(0xfffff<<12)|3; let mut fake=honest; fake[511]=(0xfffff<<12)|1;
    let mut ra=[0u64;base::D_RING]; ra[16]=(0xffff_fffeu64)<<32; let mut rb=ra; let mut rc=ra;
    let mut oa=vec![0;9]; let mut ob=oa.clone(); let mut oc=oa.clone();
    let nxt=0xffff_fffeu64<<32;
    let va=base::d_gap(&s,&prices,&honest,&mut ra,&mut oa,6,3,16,0,512,100,nxt,base::D_LIT);
    let vb=new::d_gap_groups(&s,&prices,&honest,&mut rb,&mut ob,6,3,16,0,512,100,nxt,new::D_LIT);
    assert_eq!(va,vb); assert_eq!(ra,rb); assert_eq!(oa,ob);
    let vc=new::d_gap_groups(&s,&prices,&fake,&mut rc,&mut oc,6,3,16,0,512,100,nxt,new::D_LIT);
    assert!(vc!=va || oc!=oa,"expected false-metadata counterexample absent");
    println!("R11_GAP_GROUPS_BOUNDARY {{\"loader_cases\":{},\"dp_cases\":{},\"slot510_witness\":true,\"honest_wrap_fallback\":true,\"false_metadata_counterexample_expected\":true}}",loader_cases,dp_cases);
}
