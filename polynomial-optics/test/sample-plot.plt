set size ratio 1
set key bottom right
set terminal pdf size 11.1,11.1 font ",28"
set output 'sample-plot.pdf'
set title lens
plot 'sample-plot.dat' u 1:2:3:4 w vectors title 'ray traced',\
     'sample-plot.dat' u 5:6:7:8 w vectors title 'polynomial'
unset output
#!pdfcrop 'fresnel.pdf' 'fresnel.pdf'
