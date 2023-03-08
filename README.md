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

To add things:
git add -u (will add all changed files to the repo)
git add <file> (will add a specific file to the repo)

git commit -m "message" (make a commit, like a little package of changes to do all at once, with a message explaining it)

git push (push the changes to the remote repository)

git pull (pull any changes from the remote repository)
