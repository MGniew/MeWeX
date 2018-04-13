#!/bin/bash


time bin/Teacher \
-I tuples/nkjp_kgr10_non_repeat_5 \
-O mlp/result \
-f 'vam(wsc(),sfbmd(),me(),tscore(),g2(),jaccard(),sorgenfrei(),us(),sec(e=3.8),wsec(e=1.15),cval(),ct1(),ct2(),wo())' \
-m 'mlp(model=mlp/model.txt, epoch=1)' \
-m 'mlp(model=mlp/model.txt, epoch=5)' \
-m 'mlp(model=mlp/model.txt, epoch=10)' \
-m 'mlp(model=mlp/model.txt, epoch=15)' \
-m 'mlp(model=mlp/model.txt, epoch=50)' \
-m 'mlp(model=mlp/model.txt, epoch=100)' \
-q 'pc(length=5000)' \
-r mwe/new_mwe.txt \
-F 'every_word(^,file=mwe/morfeusz.txt)' \
-t 6
# -p 'normalization(-0.000113472,0.0172224,-63.3211,-6,1.76302e-14,0.00116278,-4857.71,387.906,-1.38093e-08,1.94893e+06,4.42166e-07,0.333333,1.33549e-28,0.25,-48.7993,13.3291,-83.7851,-15.3503,-0.000335203,0.0133202,1,6.83304e+33,1,1.65093e+38,-0.0497013,-3.98724e-08,0.170691,0.938039)' \
