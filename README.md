# PhotoAbs
Repository on photoabsorption and polarisability calculations with new IAEA results

To calculate a polarisabilty, do:

root
.L PhotoAbsorptionCalculation.cpp
PhotoAbsorptionCalculation("data/Zr90_gx.dat") (for example... change the input file to calculate another nucleus apart from 90Zr.

To plot all of the dipole polarisabilities do:
root
.x PlotData.cpp

The data.txt file contains the polarisabilities from Dietrich and Bermann

The PlotData.cpp file gives another way of plotting new results
