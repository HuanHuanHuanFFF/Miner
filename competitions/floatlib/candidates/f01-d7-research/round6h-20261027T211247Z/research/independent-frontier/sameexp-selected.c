LEAN_EXPORT uint32_t lp_competition_main___lam__0(uint32_t v___y_1784_, uint32_t v___y_1785_){
_start:
{
uint8_t v___y_1792_; uint8_t v___y_1806_; uint8_t v___y_1820_; uint8_t v___y_1837_; float v___y_1844_; float v___y_1845_; float v___y_1859_; uint8_t v___y_1860_; float v___y_1875_; uint8_t v___y_1885_; uint8_t v___y_1909_; uint32_t v___x_1933_; uint32_t v___x_1934_; uint8_t v___x_1935_; 
v___x_1933_ = lean_uint32_xor(v___y_1784_, v___y_1785_);
v___x_1934_ = 8388608;
v___x_1935_ = lean_uint32_dec_lt(v___x_1933_, v___x_1934_);
if (v___x_1935_ == 0)
{
v___y_1909_ = v___x_1935_;
goto v___jp_1908_;
}
else
{
uint32_t v___x_1936_; uint32_t v___x_1937_; uint8_t v___x_1938_; 
v___x_1936_ = 2139095040;
v___x_1937_ = lean_uint32_land(v___y_1784_, v___x_1936_);
v___x_1938_ = lean_uint32_dec_eq(v___x_1937_, v___x_1936_);
if (v___x_1938_ == 0)
{
v___y_1909_ = v___x_1935_;
goto v___jp_1908_;
}
else
{
goto v___jp_1899_;
}
}
v___jp_1786_:
{
lean_object* v___x_1787_; lean_object* v___x_1788_; lean_object* v___x_1789_; uint32_t v___x_1790_; 
v___x_1787_ = lean_uint32_to_nat(v___y_1784_);
v___x_1788_ = lean_uint32_to_nat(v___y_1785_);
v___x_1789_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_1787_, v___x_1788_);
v___x_1790_ = lean_uint32_of_nat(v___x_1789_);
lean_dec(v___x_1789_);
return v___x_1790_;
}
v___jp_1791_:
{
if (v___y_1792_ == 0)
{
goto v___jp_1786_;
}
else
{
uint32_t v___x_1793_; uint32_t v___x_1794_; 
v___x_1793_ = 4194304;
v___x_1794_ = lean_uint32_lor(v___y_1785_, v___x_1793_);
return v___x_1794_;
}
}
v___jp_1795_:
{
uint32_t v___x_1796_; uint32_t v___x_1797_; uint32_t v___x_1798_; uint32_t v___x_1799_; uint8_t v___x_1800_; 
v___x_1796_ = 23;
v___x_1797_ = lean_uint32_shift_right(v___y_1785_, v___x_1796_);
v___x_1798_ = 255;
v___x_1799_ = lean_uint32_land(v___x_1797_, v___x_1798_);
v___x_1800_ = lean_uint32_dec_eq(v___x_1799_, v___x_1798_);
if (v___x_1800_ == 0)
{
v___y_1792_ = v___x_1800_;
goto v___jp_1791_;
}
else
{
uint32_t v___x_1801_; uint32_t v___x_1802_; uint32_t v___x_1803_; uint8_t v___x_1804_; 
v___x_1801_ = 8388607;
v___x_1802_ = lean_uint32_land(v___y_1785_, v___x_1801_);
v___x_1803_ = 0;
v___x_1804_ = lean_uint32_dec_eq(v___x_1802_, v___x_1803_);
if (v___x_1804_ == 0)
{
v___y_1792_ = v___x_1800_;
goto v___jp_1791_;
}
else
{
goto v___jp_1786_;
}
}
}
v___jp_1805_:
{
if (v___y_1806_ == 0)
{
goto v___jp_1795_;
}
else
{
uint32_t v___x_1807_; uint32_t v___x_1808_; 
v___x_1807_ = 4194304;
v___x_1808_ = lean_uint32_lor(v___y_1784_, v___x_1807_);
return v___x_1808_;
}
}
v___jp_1809_:
{
uint32_t v___x_1810_; uint32_t v___x_1811_; uint32_t v___x_1812_; uint32_t v___x_1813_; uint8_t v___x_1814_; 
v___x_1810_ = 23;
v___x_1811_ = lean_uint32_shift_right(v___y_1784_, v___x_1810_);
v___x_1812_ = 255;
v___x_1813_ = lean_uint32_land(v___x_1811_, v___x_1812_);
v___x_1814_ = lean_uint32_dec_eq(v___x_1813_, v___x_1812_);
if (v___x_1814_ == 0)
{
v___y_1806_ = v___x_1814_;
goto v___jp_1805_;
}
else
{
uint32_t v___x_1815_; uint32_t v___x_1816_; uint32_t v___x_1817_; uint8_t v___x_1818_; 
v___x_1815_ = 8388607;
v___x_1816_ = lean_uint32_land(v___y_1784_, v___x_1815_);
v___x_1817_ = 0;
v___x_1818_ = lean_uint32_dec_eq(v___x_1816_, v___x_1817_);
if (v___x_1818_ == 0)
{
v___y_1806_ = v___x_1814_;
goto v___jp_1805_;
}
else
{
goto v___jp_1795_;
}
}
}
v___jp_1819_:
{
if (v___y_1820_ == 0)
{
goto v___jp_1809_;
}
else
{
uint32_t v___x_1821_; uint32_t v___x_1822_; uint32_t v___x_1823_; uint8_t v___x_1824_; 
v___x_1821_ = 4194304;
v___x_1822_ = lean_uint32_land(v___y_1785_, v___x_1821_);
v___x_1823_ = 0;
v___x_1824_ = lean_uint32_dec_eq(v___x_1822_, v___x_1823_);
if (v___x_1824_ == 0)
{
goto v___jp_1809_;
}
else
{
uint32_t v___x_1825_; 
v___x_1825_ = lean_uint32_lor(v___y_1785_, v___x_1821_);
return v___x_1825_;
}
}
}
v___jp_1826_:
{
uint32_t v___x_1827_; uint32_t v___x_1828_; uint32_t v___x_1829_; uint32_t v___x_1830_; uint8_t v___x_1831_; 
v___x_1827_ = 23;
v___x_1828_ = lean_uint32_shift_right(v___y_1785_, v___x_1827_);
v___x_1829_ = 255;
v___x_1830_ = lean_uint32_land(v___x_1828_, v___x_1829_);
v___x_1831_ = lean_uint32_dec_eq(v___x_1830_, v___x_1829_);
if (v___x_1831_ == 0)
{
v___y_1820_ = v___x_1831_;
goto v___jp_1819_;
}
else
{
uint32_t v___x_1832_; uint32_t v___x_1833_; uint32_t v___x_1834_; uint8_t v___x_1835_; 
v___x_1832_ = 8388607;
v___x_1833_ = lean_uint32_land(v___y_1785_, v___x_1832_);
v___x_1834_ = 0;
v___x_1835_ = lean_uint32_dec_eq(v___x_1833_, v___x_1834_);
if (v___x_1835_ == 0)
{
v___y_1820_ = v___x_1831_;
goto v___jp_1819_;
}
else
{
goto v___jp_1809_;
}
}
}
v___jp_1836_:
{
if (v___y_1837_ == 0)
{
goto v___jp_1826_;
}
else
{
uint32_t v___x_1838_; uint32_t v___x_1839_; uint32_t v___x_1840_; uint8_t v___x_1841_; 
v___x_1838_ = 4194304;
v___x_1839_ = lean_uint32_land(v___y_1784_, v___x_1838_);
v___x_1840_ = 0;
v___x_1841_ = lean_uint32_dec_eq(v___x_1839_, v___x_1840_);
if (v___x_1841_ == 0)
{
goto v___jp_1826_;
}
else
{
uint32_t v___x_1842_; 
v___x_1842_ = lean_uint32_lor(v___y_1784_, v___x_1838_);
return v___x_1842_;
}
}
}
v___jp_1843_:
{
float v_result_1846_; uint8_t v___x_1847_; 
v_result_1846_ = lean_float32_add(v___y_1844_, v___y_1845_);
v___x_1847_ = lean_float32_beq(v_result_1846_, v_result_1846_);
if (v___x_1847_ == 0)
{
uint32_t v___x_1848_; uint32_t v___x_1849_; uint32_t v___x_1850_; uint32_t v___x_1851_; uint8_t v___x_1852_; 
v___x_1848_ = 23;
v___x_1849_ = lean_uint32_shift_right(v___y_1784_, v___x_1848_);
v___x_1850_ = 255;
v___x_1851_ = lean_uint32_land(v___x_1849_, v___x_1850_);
v___x_1852_ = lean_uint32_dec_eq(v___x_1851_, v___x_1850_);
if (v___x_1852_ == 0)
{
v___y_1837_ = v___x_1852_;
goto v___jp_1836_;
}
else
{
uint32_t v___x_1853_; uint32_t v___x_1854_; uint32_t v___x_1855_; uint8_t v___x_1856_; 
v___x_1853_ = 8388607;
v___x_1854_ = lean_uint32_land(v___y_1784_, v___x_1853_);
v___x_1855_ = 0;
v___x_1856_ = lean_uint32_dec_eq(v___x_1854_, v___x_1855_);
if (v___x_1856_ == 0)
{
v___y_1837_ = v___x_1852_;
goto v___jp_1836_;
}
else
{
goto v___jp_1826_;
}
}
}
else
{
uint32_t v___x_1857_; 
v___x_1857_ = lean_float32_to_bits(v_result_1846_);
return v___x_1857_;
}
}
v___jp_1858_:
{
if (v___y_1860_ == 0)
{
float v___x_1861_; 
v___x_1861_ = lean_float32_of_bits(v___y_1785_);
v___y_1844_ = v___y_1859_;
v___y_1845_ = v___x_1861_;
goto v___jp_1843_;
}
else
{
uint32_t v___x_1862_; uint32_t v___x_1863_; uint32_t v___x_1864_; uint32_t v___x_1865_; float v___x_1866_; lean_object* v___x_1867_; uint32_t v___x_1868_; uint32_t v___x_1869_; lean_object* v___x_1870_; lean_object* v___x_1871_; float v___x_1872_; float v___x_1873_; 
v___x_1862_ = 8388607;
v___x_1863_ = lean_uint32_land(v___y_1785_, v___x_1862_);
v___x_1864_ = 8388608;
v___x_1865_ = lean_uint32_lor(v___x_1863_, v___x_1864_);
v___x_1866_ = lean_uint32_to_float32(v___x_1865_);
v___x_1867_ = lp_competition_R2W01b_scaleTable;
v___x_1868_ = 23;
v___x_1869_ = lean_uint32_shift_right(v___y_1785_, v___x_1868_);
v___x_1870_ = lean_uint32_to_nat(v___x_1869_);
v___x_1871_ = lean_array_fget_borrowed(v___x_1867_, v___x_1870_);
lean_dec(v___x_1870_);
v___x_1872_ = lean_unbox_float32(v___x_1871_);
v___x_1873_ = lean_float32_mul(v___x_1866_, v___x_1872_);
v___y_1844_ = v___y_1859_;
v___y_1845_ = v___x_1873_;
goto v___jp_1843_;
}
}
v___jp_1874_:
{
uint32_t v___x_1876_; uint32_t v_a_1877_; uint32_t v___x_1878_; uint32_t v___x_1879_; uint32_t v___x_1880_; uint8_t v___x_1881_; 
v___x_1876_ = 2147483647;
v_a_1877_ = lean_uint32_land(v___y_1785_, v___x_1876_);
v___x_1878_ = 201326591;
v___x_1879_ = 1;
v___x_1880_ = lean_uint32_sub(v_a_1877_, v___x_1879_);
v___x_1881_ = lean_uint32_dec_le(v___x_1878_, v___x_1880_);
if (v___x_1881_ == 0)
{
v___y_1859_ = v___y_1875_;
v___y_1860_ = v___x_1881_;
goto v___jp_1858_;
}
else
{
uint32_t v___x_1882_; uint8_t v___x_1883_; 
v___x_1882_ = 2139095040;
v___x_1883_ = lean_uint32_dec_lt(v_a_1877_, v___x_1882_);
v___y_1859_ = v___y_1875_;
v___y_1860_ = v___x_1883_;
goto v___jp_1858_;
}
}
v___jp_1884_:
{
if (v___y_1885_ == 0)
{
float v___x_1886_; 
v___x_1886_ = lean_float32_of_bits(v___y_1784_);
v___y_1875_ = v___x_1886_;
goto v___jp_1874_;
}
else
{
uint32_t v___x_1887_; uint32_t v___x_1888_; uint32_t v___x_1889_; uint32_t v___x_1890_; float v___x_1891_; lean_object* v___x_1892_; uint32_t v___x_1893_; uint32_t v___x_1894_; lean_object* v___x_1895_; lean_object* v___x_1896_; float v___x_1897_; float v___x_1898_; 
v___x_1887_ = 8388607;
v___x_1888_ = lean_uint32_land(v___y_1784_, v___x_1887_);
v___x_1889_ = 8388608;
v___x_1890_ = lean_uint32_lor(v___x_1888_, v___x_1889_);
v___x_1891_ = lean_uint32_to_float32(v___x_1890_);
v___x_1892_ = lp_competition_R2W01b_scaleTable;
v___x_1893_ = 23;
v___x_1894_ = lean_uint32_shift_right(v___y_1784_, v___x_1893_);
v___x_1895_ = lean_uint32_to_nat(v___x_1894_);
v___x_1896_ = lean_array_fget_borrowed(v___x_1892_, v___x_1895_);
lean_dec(v___x_1895_);
v___x_1897_ = lean_unbox_float32(v___x_1896_);
v___x_1898_ = lean_float32_mul(v___x_1891_, v___x_1897_);
v___y_1875_ = v___x_1898_;
goto v___jp_1874_;
}
}
v___jp_1899_:
{
uint32_t v___x_1900_; uint32_t v_a_1901_; uint32_t v___x_1902_; uint32_t v___x_1903_; uint32_t v___x_1904_; uint8_t v___x_1905_; 
v___x_1900_ = 2147483647;
v_a_1901_ = lean_uint32_land(v___y_1784_, v___x_1900_);
v___x_1902_ = 201326591;
v___x_1903_ = 1;
v___x_1904_ = lean_uint32_sub(v_a_1901_, v___x_1903_);
v___x_1905_ = lean_uint32_dec_le(v___x_1902_, v___x_1904_);
if (v___x_1905_ == 0)
{
v___y_1885_ = v___x_1905_;
goto v___jp_1884_;
}
else
{
uint32_t v___x_1906_; uint8_t v___x_1907_; 
v___x_1906_ = 2139095040;
v___x_1907_ = lean_uint32_dec_lt(v_a_1901_, v___x_1906_);
v___y_1885_ = v___x_1907_;
goto v___jp_1884_;
}
}
v___jp_1908_:
{
if (v___y_1909_ == 0)
{
goto v___jp_1899_;
}
else
{
uint32_t v___x_1910_; uint32_t v___x_1911_; uint32_t v___x_1912_; uint32_t v_t_1913_; uint32_t v___x_1914_; uint32_t v_e_1915_; uint32_t v___x_1916_; uint32_t v_s_1917_; uint32_t v___x_1918_; uint8_t v___x_1919_; 
v___x_1910_ = 8388607;
v___x_1911_ = lean_uint32_land(v___y_1784_, v___x_1910_);
v___x_1912_ = lean_uint32_land(v___y_1785_, v___x_1910_);
v_t_1913_ = lean_uint32_add(v___x_1911_, v___x_1912_);
v___x_1914_ = 2139095040;
v_e_1915_ = lean_uint32_land(v___y_1784_, v___x_1914_);
v___x_1916_ = 2147483648;
v_s_1917_ = lean_uint32_land(v___y_1784_, v___x_1916_);
v___x_1918_ = 0;
v___x_1919_ = lean_uint32_dec_eq(v_e_1915_, v___x_1918_);
if (v___x_1919_ == 0)
{
uint32_t v___x_1920_; uint8_t v___x_1921_; 
v___x_1920_ = 2130706432;
v___x_1921_ = lean_uint32_dec_eq(v_e_1915_, v___x_1920_);
if (v___x_1921_ == 0)
{
uint32_t v___x_1922_; uint32_t v___x_1923_; uint32_t v___x_1924_; uint32_t v___x_1925_; uint32_t v___x_1926_; uint32_t v___x_1927_; uint32_t v___x_1928_; uint32_t v___x_1929_; uint32_t v___x_1930_; 
v___x_1922_ = 8388608;
v___x_1923_ = lean_uint32_add(v_e_1915_, v___x_1922_);
v___x_1924_ = 1;
v___x_1925_ = lean_uint32_shift_right(v_t_1913_, v___x_1924_);
v___x_1926_ = lean_uint32_land(v___x_1925_, v___x_1924_);
v___x_1927_ = lean_uint32_add(v_t_1913_, v___x_1926_);
v___x_1928_ = lean_uint32_shift_right(v___x_1927_, v___x_1924_);
v___x_1929_ = lean_uint32_add(v___x_1923_, v___x_1928_);
v___x_1930_ = lean_uint32_lor(v_s_1917_, v___x_1929_);
return v___x_1930_;
}
else
{
uint32_t v___x_1931_; 
v___x_1931_ = lean_uint32_lor(v_s_1917_, v___x_1914_);
return v___x_1931_;
}
}
else
{
uint32_t v___x_1932_; 
v___x_1932_ = lean_uint32_lor(v_s_1917_, v_t_1913_);
return v___x_1932_;
}
}
}
}
}
