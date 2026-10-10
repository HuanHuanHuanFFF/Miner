pub fn Z353(d: usize) -> usize {
    let small = if d >= 1 { d.wrapping_sub(1) } else { 0 };
    let x = (d.wrapping_sub(1) % 65536) as u32;
    let msb = 31u32.wrapping_sub(x.leading_zeros());
    let sh = if msb >= 1 && msb <= 31 { msb.wrapping_sub(1) } else { 0 };
    let s = (2u32.wrapping_mul(msb % 32).wrapping_add((x >> (sh % 32)) & 1)) as usize;
    let big = if s > 29 { 29 } else { s };
    if d <= 4 {
        small
    } else {
        big
    }
}

pub fn SFlen(t:u32)->usize { if t<256 {1} else {(t.wrapping_sub(16777216)%256).wrapping_add(3) as usize} }

pub fn SFdist(t:u32)->usize {(t.wrapping_sub(16777216)/256).wrapping_add(1) as usize}

pub fn SFroom(best:&[u32;4],codes:&[usize;4],t:u32,ct:&[u32;1024])->usize {4}
// Extraction-only diagnostic fixture. Not a submitted parser or proof.
pub fn parse(input:&[u8],out:&mut[u32])->usize {
 let t=16777216u32.wrapping_add(if input.len()>0{input[0]as u32}else{0});
 let mut best=[t,t,t,t];let mut codes=[0usize,1,2,3];let ct=[16u32;1024];
 let count=SFroom(&best,&codes,t,&ct);
 let mut n=0usize;while n<input.len() && n<out.len() && n<count{out[n]=input[n]as u32;n+=1;}n
}
