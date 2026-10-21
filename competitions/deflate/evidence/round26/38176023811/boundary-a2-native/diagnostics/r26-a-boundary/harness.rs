
#![allow(dead_code)]
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/token.rs"]mod token;
#[path="/home/runner/work/_temp/deflate-native-upstream/validator/measure/src/deflate.rs"]mod codec;
#[path="/home/runner/work/_temp/r26-a-boundary-build/prices.rs"]mod prices;
#[path="/home/runner/work/Miner/Miner/candidates/r22-595-chain-halfhead/parse.rs"]mod parser;
#[path="/home/runner/work/_temp/r26-a-boundary-build/observer.rs"]mod observer;
fn parse(s:&[u8],f:fn(&[u8],&mut[u32])->usize)->Vec<u32>{let mut o=vec![0;s.len()];let n=f(s,&mut o);assert!(n<=s.len());o.truncate(n);o}
fn decode(s:&[u8],ts:&[u32]){let mut o=Vec::new();for &t in ts{match token::decode(t){token::Token::Literal(x)=>o.push(x),token::Token::Match{dist,len}=>{assert!(dist>0&&dist as usize<=o.len()&&o.len()+len as usize<=s.len());for _ in 0..len{let x=o[o.len()-dist as usize];o.push(x);}},_=>panic!("bad token")}}assert_eq!(o,s);}
fn ml(t:u32)->Option<(usize,usize)>{match token::decode(t){token::Token::Match{dist,len}=>Some((len as usize,dist as usize)),_=>None}}
fn tk(l:usize,d:usize)->u32{assert!((3..=258).contains(&l)&&(1..=32768).contains(&d));16777216+(d as u32-1)*256+l as u32-3}
fn rewrite(s:&[u8],ts:&[u32],pr:&[Vec<u32>])->(Vec<u32>,[u64;13]){
 let mut out=ts.to_vec();let mut stat=[0u64;13];let mut p=0usize;
 for i in 0..ts.len(){
  let current=ml(ts[i]);
  if i>0 {if let (Some((l,d)),Some((w,old_d)))=(current,ml(out[i-1])) {
   stat[0]+=1;
   if i/16384==(i-1)/16384 {
    stat[1]+=1;
    let cap=(w-3).min(258-l).min(p.saturating_sub(d));
    if cap>0 {
     stat[2]+=1;let mut reach=0usize;
     while reach<cap {stat[3]+=1;if s[p-reach-1]!=s[p-reach-1-d]{break;}reach+=1;}
     if reach>0 {stat[4]+=1;}
     let price=&pr[i/16384];
     if price[w]==u32::MAX||price[l]==u32::MAX {stat[12]+=1;} else {
      let old_cost=price[w]+price[l];let mut best=old_cost;let mut shift=0usize;
      for k in 1..=reach {
       stat[5]+=1;
       if price[w-k]==u32::MAX||price[l+k]==u32::MAX {stat[7]+=1;continue;}
       stat[6]+=1;let cost=price[w-k]+price[l+k];
       if cost<best {best=cost;shift=k;}
      }
      if shift>0 {
       out[i-1]=tk(w-shift,old_d);out[i]=tk(l+shift,d);
       stat[8]+=1;stat[9]+=shift as u64;stat[10]+=(old_cost-best)as u64;stat[11]=stat[11].max(shift as u64);
      }
     }
    }
   }
  }}
  p+=current.map(|x|x.0).unwrap_or(1);
 }
 assert_eq!(p,s.len());(out,stat)
}
fn main(){
 let args:Vec<_>=std::env::args().collect();let spool=std::path::Path::new(&args[2]);
 let mut files:Vec<_>=std::fs::read_dir(&args[1]).unwrap().map(|x|x.unwrap().path()).filter(|p|p.is_file()).collect();files.sort();
 for (index,path) in files.iter().enumerate(){
  let data=std::fs::read(path).unwrap();let name=path.file_name().unwrap().to_str().unwrap();
  let original=parse(&data,parser::parse);let observed=parse(&data,observer::parse);assert_eq!(original,observed);decode(&data,&original);
  let hits=observer::r25_lp_take();assert!(hits.iter().sum::<u64>()<=1);let row=hits.iter().position(|&v|v>0).unwrap_or(32);
  let original_encoded=codec::encode(&original,data.len()).unwrap();assert_eq!(original_encoded,prices::encode(&original,data.len()).unwrap());
  let active=[0usize,1,3,5,6,7,8,9].contains(&row);
  let (changed,stat)=if active{rewrite(&data,&original,&prices::r26_length_prices(&original))}else{(original.clone(),[0;13])};
  assert_eq!(original.len(),changed.len());decode(&data,&changed);
  let encoded=codec::encode(&changed,data.len()).unwrap();
  for (label,ts,bytes) in [("original",&original,&original_encoded),("boundary",&changed,&encoded)] {
   let mut raw=Vec::new();for&t in ts {raw.extend(t.to_le_bytes());}
   std::fs::write(spool.join(format!("{}-{}.tokens",index,label)),raw).unwrap();std::fs::write(spool.join(format!("{}-{}.deflate",index,label)),bytes).unwrap();
   println!("R26_BOUNDARY_ROW {} {} {} {} {} {}",index,name,label,ts.len(),bytes.len(),row);
  }
  print!("R26_BOUNDARY_COUNT {} {}",index,name);for v in stat {print!(" {}",v);}println!();
 }
}
