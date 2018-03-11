set size ratio 1
set key top right
set terminal pdf size 11.1,11.1 font ",28"
set title lens

#set yrange [-1:16]
#set y2range [-1e-12:16e-12]
set yrange [-1:101]
#set y2range [-1e-12:16e-12]
#set y2range [-1e-12:101e-12]
set autoscale y2
set ylabel "number of iterations"
set y2label "squared error"
set y2tics
set ytics nomirror
set output 'convergence-profile.pdf'
plot 'lt_convergence_profile.dat' u 1:3 w l title 'squared outer error' axes x1y2,\
     'lt_convergence_profile.dat' u 1:4 w l title 'squared aperture error' axes x1y2,\
     'lt_convergence_profile.dat' u 1:2 w l title 'number of iterations' axes x1y1
set output 'convergence.pdf'
set ylabel "squared error"
unset y2label
#unset y2tics
#set yrange [:1]
set autoscale y
set logscale y
plot 'lt_convergence.dat' u 1:2 w l title 'squared error on aperture',\
     'lt_convergence.dat' u 1:3 w l title 'squared error on outer pupil',\
     'lt_convergence.dat' u 4:5:6:7 with vectors title 'sensor' axes x1y2,\
     'lt_convergence.dat' u 4:8:9:10 with vectors title 'outer pupil' axes x1y2
unset logscale y
unset output
