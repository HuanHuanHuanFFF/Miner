
/- Diagnostic static scale layout. Original public algorithms remain B2. -/
namespace Submission.R22FlatScale
open Competition
open R2W01b

structure Block where
  x0 : Float32
  x1 : Float32
  x2 : Float32
  x3 : Float32
  x4 : Float32
  x5 : Float32
  x6 : Float32
  x7 : Float32
  x8 : Float32
  x9 : Float32
  x10 : Float32
  x11 : Float32
  x12 : Float32
  x13 : Float32
  x14 : Float32
  x15 : Float32
  x16 : Float32
  x17 : Float32
  x18 : Float32
  x19 : Float32
  x20 : Float32
  x21 : Float32
  x22 : Float32
  x23 : Float32
  x24 : Float32
  x25 : Float32
  x26 : Float32
  x27 : Float32
  x28 : Float32
  x29 : Float32
  x30 : Float32
  x31 : Float32
  x32 : Float32
  x33 : Float32
  x34 : Float32
  x35 : Float32
  x36 : Float32
  x37 : Float32
  x38 : Float32
  x39 : Float32
  x40 : Float32
  x41 : Float32
  x42 : Float32
  x43 : Float32
  x44 : Float32
  x45 : Float32
  x46 : Float32
  x47 : Float32
  x48 : Float32
  x49 : Float32
  x50 : Float32
  x51 : Float32
  x52 : Float32
  x53 : Float32
  x54 : Float32
  x55 : Float32
  x56 : Float32
  x57 : Float32
  x58 : Float32
  x59 : Float32
  x60 : Float32
  x61 : Float32
  x62 : Float32
  x63 : Float32
  x64 : Float32
  x65 : Float32
  x66 : Float32
  x67 : Float32
  x68 : Float32
  x69 : Float32
  x70 : Float32
  x71 : Float32
  x72 : Float32
  x73 : Float32
  x74 : Float32
  x75 : Float32
  x76 : Float32
  x77 : Float32
  x78 : Float32
  x79 : Float32
  x80 : Float32
  x81 : Float32
  x82 : Float32
  x83 : Float32
  x84 : Float32
  x85 : Float32
  x86 : Float32
  x87 : Float32
  x88 : Float32
  x89 : Float32
  x90 : Float32
  x91 : Float32
  x92 : Float32
  x93 : Float32
  x94 : Float32
  x95 : Float32
  x96 : Float32
  x97 : Float32
  x98 : Float32
  x99 : Float32
  x100 : Float32
  x101 : Float32
  x102 : Float32
  x103 : Float32
  x104 : Float32
  x105 : Float32
  x106 : Float32
  x107 : Float32
  x108 : Float32
  x109 : Float32
  x110 : Float32
  x111 : Float32
  x112 : Float32
  x113 : Float32
  x114 : Float32
  x115 : Float32
  x116 : Float32
  x117 : Float32
  x118 : Float32
  x119 : Float32
  x120 : Float32
  x121 : Float32
  x122 : Float32
  x123 : Float32
  x124 : Float32
  x125 : Float32
  x126 : Float32
  x127 : Float32

@[inline] def seed (j : UInt32) : Float32 := Float32.ofBits (scaleBits j)

def block0 : Block :=
  ⟨seed 0, seed 1, seed 2, seed 3, seed 4, seed 5, seed 6, seed 7, seed 8, seed 9, seed 10, seed 11, seed 12, seed 13, seed 14, seed 15, seed 16, seed 17, seed 18, seed 19, seed 20, seed 21, seed 22, seed 23, seed 24, seed 25, seed 26, seed 27, seed 28, seed 29, seed 30, seed 31, seed 32, seed 33, seed 34, seed 35, seed 36, seed 37, seed 38, seed 39, seed 40, seed 41, seed 42, seed 43, seed 44, seed 45, seed 46, seed 47, seed 48, seed 49, seed 50, seed 51, seed 52, seed 53, seed 54, seed 55, seed 56, seed 57, seed 58, seed 59, seed 60, seed 61, seed 62, seed 63, seed 64, seed 65, seed 66, seed 67, seed 68, seed 69, seed 70, seed 71, seed 72, seed 73, seed 74, seed 75, seed 76, seed 77, seed 78, seed 79, seed 80, seed 81, seed 82, seed 83, seed 84, seed 85, seed 86, seed 87, seed 88, seed 89, seed 90, seed 91, seed 92, seed 93, seed 94, seed 95, seed 96, seed 97, seed 98, seed 99, seed 100, seed 101, seed 102, seed 103, seed 104, seed 105, seed 106, seed 107, seed 108, seed 109, seed 110, seed 111, seed 112, seed 113, seed 114, seed 115, seed 116, seed 117, seed 118, seed 119, seed 120, seed 121, seed 122, seed 123, seed 124, seed 125, seed 126, seed 127⟩

def block1 : Block :=
  ⟨seed 128, seed 129, seed 130, seed 131, seed 132, seed 133, seed 134, seed 135, seed 136, seed 137, seed 138, seed 139, seed 140, seed 141, seed 142, seed 143, seed 144, seed 145, seed 146, seed 147, seed 148, seed 149, seed 150, seed 151, seed 152, seed 153, seed 154, seed 155, seed 156, seed 157, seed 158, seed 159, seed 160, seed 161, seed 162, seed 163, seed 164, seed 165, seed 166, seed 167, seed 168, seed 169, seed 170, seed 171, seed 172, seed 173, seed 174, seed 175, seed 176, seed 177, seed 178, seed 179, seed 180, seed 181, seed 182, seed 183, seed 184, seed 185, seed 186, seed 187, seed 188, seed 189, seed 190, seed 191, seed 192, seed 193, seed 194, seed 195, seed 196, seed 197, seed 198, seed 199, seed 200, seed 201, seed 202, seed 203, seed 204, seed 205, seed 206, seed 207, seed 208, seed 209, seed 210, seed 211, seed 212, seed 213, seed 214, seed 215, seed 216, seed 217, seed 218, seed 219, seed 220, seed 221, seed 222, seed 223, seed 224, seed 225, seed 226, seed 227, seed 228, seed 229, seed 230, seed 231, seed 232, seed 233, seed 234, seed 235, seed 236, seed 237, seed 238, seed 239, seed 240, seed 241, seed 242, seed 243, seed 244, seed 245, seed 246, seed 247, seed 248, seed 249, seed 250, seed 251, seed 252, seed 253, seed 254, seed 255⟩

def block2 : Block :=
  ⟨seed 256, seed 257, seed 258, seed 259, seed 260, seed 261, seed 262, seed 263, seed 264, seed 265, seed 266, seed 267, seed 268, seed 269, seed 270, seed 271, seed 272, seed 273, seed 274, seed 275, seed 276, seed 277, seed 278, seed 279, seed 280, seed 281, seed 282, seed 283, seed 284, seed 285, seed 286, seed 287, seed 288, seed 289, seed 290, seed 291, seed 292, seed 293, seed 294, seed 295, seed 296, seed 297, seed 298, seed 299, seed 300, seed 301, seed 302, seed 303, seed 304, seed 305, seed 306, seed 307, seed 308, seed 309, seed 310, seed 311, seed 312, seed 313, seed 314, seed 315, seed 316, seed 317, seed 318, seed 319, seed 320, seed 321, seed 322, seed 323, seed 324, seed 325, seed 326, seed 327, seed 328, seed 329, seed 330, seed 331, seed 332, seed 333, seed 334, seed 335, seed 336, seed 337, seed 338, seed 339, seed 340, seed 341, seed 342, seed 343, seed 344, seed 345, seed 346, seed 347, seed 348, seed 349, seed 350, seed 351, seed 352, seed 353, seed 354, seed 355, seed 356, seed 357, seed 358, seed 359, seed 360, seed 361, seed 362, seed 363, seed 364, seed 365, seed 366, seed 367, seed 368, seed 369, seed 370, seed 371, seed 372, seed 373, seed 374, seed 375, seed 376, seed 377, seed 378, seed 379, seed 380, seed 381, seed 382, seed 383⟩

def block3 : Block :=
  ⟨seed 384, seed 385, seed 386, seed 387, seed 388, seed 389, seed 390, seed 391, seed 392, seed 393, seed 394, seed 395, seed 396, seed 397, seed 398, seed 399, seed 400, seed 401, seed 402, seed 403, seed 404, seed 405, seed 406, seed 407, seed 408, seed 409, seed 410, seed 411, seed 412, seed 413, seed 414, seed 415, seed 416, seed 417, seed 418, seed 419, seed 420, seed 421, seed 422, seed 423, seed 424, seed 425, seed 426, seed 427, seed 428, seed 429, seed 430, seed 431, seed 432, seed 433, seed 434, seed 435, seed 436, seed 437, seed 438, seed 439, seed 440, seed 441, seed 442, seed 443, seed 444, seed 445, seed 446, seed 447, seed 448, seed 449, seed 450, seed 451, seed 452, seed 453, seed 454, seed 455, seed 456, seed 457, seed 458, seed 459, seed 460, seed 461, seed 462, seed 463, seed 464, seed 465, seed 466, seed 467, seed 468, seed 469, seed 470, seed 471, seed 472, seed 473, seed 474, seed 475, seed 476, seed 477, seed 478, seed 479, seed 480, seed 481, seed 482, seed 483, seed 484, seed 485, seed 486, seed 487, seed 488, seed 489, seed 490, seed 491, seed 492, seed 493, seed 494, seed 495, seed 496, seed 497, seed 498, seed 499, seed 500, seed 501, seed 502, seed 503, seed 504, seed 505, seed 506, seed 507, seed 508, seed 509, seed 510, seed 511⟩

@[inline] def pick (b : Block) (i : Nat) : Float32 :=
  match i with
  | 0 => b.x0
  | 1 => b.x1
  | 2 => b.x2
  | 3 => b.x3
  | 4 => b.x4
  | 5 => b.x5
  | 6 => b.x6
  | 7 => b.x7
  | 8 => b.x8
  | 9 => b.x9
  | 10 => b.x10
  | 11 => b.x11
  | 12 => b.x12
  | 13 => b.x13
  | 14 => b.x14
  | 15 => b.x15
  | 16 => b.x16
  | 17 => b.x17
  | 18 => b.x18
  | 19 => b.x19
  | 20 => b.x20
  | 21 => b.x21
  | 22 => b.x22
  | 23 => b.x23
  | 24 => b.x24
  | 25 => b.x25
  | 26 => b.x26
  | 27 => b.x27
  | 28 => b.x28
  | 29 => b.x29
  | 30 => b.x30
  | 31 => b.x31
  | 32 => b.x32
  | 33 => b.x33
  | 34 => b.x34
  | 35 => b.x35
  | 36 => b.x36
  | 37 => b.x37
  | 38 => b.x38
  | 39 => b.x39
  | 40 => b.x40
  | 41 => b.x41
  | 42 => b.x42
  | 43 => b.x43
  | 44 => b.x44
  | 45 => b.x45
  | 46 => b.x46
  | 47 => b.x47
  | 48 => b.x48
  | 49 => b.x49
  | 50 => b.x50
  | 51 => b.x51
  | 52 => b.x52
  | 53 => b.x53
  | 54 => b.x54
  | 55 => b.x55
  | 56 => b.x56
  | 57 => b.x57
  | 58 => b.x58
  | 59 => b.x59
  | 60 => b.x60
  | 61 => b.x61
  | 62 => b.x62
  | 63 => b.x63
  | 64 => b.x64
  | 65 => b.x65
  | 66 => b.x66
  | 67 => b.x67
  | 68 => b.x68
  | 69 => b.x69
  | 70 => b.x70
  | 71 => b.x71
  | 72 => b.x72
  | 73 => b.x73
  | 74 => b.x74
  | 75 => b.x75
  | 76 => b.x76
  | 77 => b.x77
  | 78 => b.x78
  | 79 => b.x79
  | 80 => b.x80
  | 81 => b.x81
  | 82 => b.x82
  | 83 => b.x83
  | 84 => b.x84
  | 85 => b.x85
  | 86 => b.x86
  | 87 => b.x87
  | 88 => b.x88
  | 89 => b.x89
  | 90 => b.x90
  | 91 => b.x91
  | 92 => b.x92
  | 93 => b.x93
  | 94 => b.x94
  | 95 => b.x95
  | 96 => b.x96
  | 97 => b.x97
  | 98 => b.x98
  | 99 => b.x99
  | 100 => b.x100
  | 101 => b.x101
  | 102 => b.x102
  | 103 => b.x103
  | 104 => b.x104
  | 105 => b.x105
  | 106 => b.x106
  | 107 => b.x107
  | 108 => b.x108
  | 109 => b.x109
  | 110 => b.x110
  | 111 => b.x111
  | 112 => b.x112
  | 113 => b.x113
  | 114 => b.x114
  | 115 => b.x115
  | 116 => b.x116
  | 117 => b.x117
  | 118 => b.x118
  | 119 => b.x119
  | 120 => b.x120
  | 121 => b.x121
  | 122 => b.x122
  | 123 => b.x123
  | 124 => b.x124
  | 125 => b.x125
  | 126 => b.x126
  | 127 => b.x127
  | _ => Packed10.zero32

@[inline] def lookup (u : UInt32) : Float32 :=
  let j := tableIndex u
  let group := j >>> (7 : UInt32)
  let slot := j &&& (127 : UInt32)
  let b := if group == (0 : UInt32) then block0
    else if group == (1 : UInt32) then block1
    else if group == (2 : UInt32) then block2 else block3
  pick b slot.toNat

@[inline] def convert (u : UInt32) : Float32 :=
  if fastOK u then (mantissa u).toFloat32 * lookup u else Float32.ofBits u

@[inline] def add (x y : Binary32) : Binary32 :=
  let result := convert x.raw.1 + convert y.raw.1
  if R7W04.nonNaN result then ExecFloat.Binary.ofFloat32 result
  else ScalarNaN.add x y

@[inline] def nativeMul (x y : Binary32) : Binary32 :=
  let result := convert x.raw.1 * convert y.raw.1
  if R7W04.nonNaN result then ExecFloat.Binary.ofFloat32 result
  else ScalarNaN.mul x y

@[inline] def mul (x y : Binary32) : Binary32 :=
  let ex := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField x.raw.1
  let ey := FloatLib.Floats.Formats.BinaryInterchange.Model.NativeBinary32.expField y.raw.1
  if ex + ey < (128 : UInt32) then LowScale.mul x y else nativeMul x y

end Submission.R22FlatScale
