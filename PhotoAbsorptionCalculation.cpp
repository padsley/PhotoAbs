#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>

TGraphErrors *ge, *ge_neg2;

double CrossSectionFunction(double *x, double *pars)
{
    return ge_neg2->Eval(x[0]);
}

void PhotoAbsorptionCalculation(TString inputFile = "")//inputFile is the strong for the input file so something like PhotoAbsorptionCalculation("Zr90_gx.dat")
{
    //this is input stream declaration - then it prints out the name as a check and opens the file
    ifstream DataInput;
    std::cout << "Opening " << inputFile.Data() << std::endl;
    DataInput.open(inputFile.Data());
    
    //make a TGraphErrors to store the results
    ge = new TGraphErrors();
    ge->SetName("PhotoAbsorptionGraph");
    
    //make another TGraphErrors to store sigma/E^2 values
    ge_neg2 = new TGraphErrors();
    ge_neg2->SetName("PhotoAbsorptionGraph_neg2");
    
    //read in the input file while it's open - read three columns which are energy, cross section and uncertainty on that cross section - store the read values in the TGraphErrors
    if(DataInput.is_open())
    {
        double Egamma = 0, sigma = 0, sigmasigma = 0;
        while(DataInput >> Egamma >> sigma >> sigmasigma)
        {
            std::cout << Egamma << "\t" << sigma << "\t" << sigmasigma << std::endl;;
            ge->SetPoint(ge->GetN(),Egamma,sigma);
            ge->SetPointError(ge->GetN()-1,0,sigmasigma);
            
            ge_neg2->SetPoint(ge->GetN(),Egamma,sigma/pow(Egamma,2.));
            ge_neg2->SetPointError(ge->GetN()-1,0,sigmasigma/pow(Egamma,2.));
        }
    }
    
    //draw the cross section plot and label the axes
    ge->Draw("AP");
    ge->GetYaxis()->SetTitle("#sigma [mb]");
    ge->GetYaxis()->CenterTitle();
    ge->GetXaxis()->SetTitle("E_{#gamma} [MeV]");
    ge->GetXaxis()->CenterTitle();
    
    
    //draw the sigma-2 plot and label the axes
    ge_neg2->Draw("AP");
    ge_neg2->GetYaxis()->SetTitle("#sigma/E_{#gamma}^{2} [mb/MeV^{2}]");
    ge_neg2->GetYaxis()->CenterTitle();
    ge_neg2->GetXaxis()->SetTitle("E_{#gamma} [MeV]");
    ge_neg2->GetXaxis()->CenterTitle();
    
    //Simple numerical calculation of the polarisability value
    double sigma_neg2 = 0;
    for(int i=0;i<ge->GetN();i++)
    {
        sigma_neg2 += ge->GetPointY(i)/pow(ge->GetPointX(i),2.);
    }
    //print out that value
    std::cout << "sigma(-2): " << sigma_neg2 << std::endl;
    
    //integral of the total cross section
    std::cout << "sigma integral: " << ge->Integral() << std::endl;
    
    //integral of the sigma/E^2 function
    std::cout << "sigma_neg2 integral: " << ge_neg2->Integral() << std::endl;
    
    //trying it with a function but this doesn't seem to like the scatter in the results so it may not be trustworthy - commented out for now
//     TF1 *func_sigma = new TF1("func_sigma",CrossSectionFunction,ge->GetPointX(0),ge->GetPointX(ge->GetN()-1));
//     func_sigma->SetNpx(1e6);
    
//     func_sigma->Draw("same");
//     std::cout << "func_sigma integral: " << func_sigma->Integral(ge->GetPointX(0),ge->GetPointX(ge->GetN()-1)) << std::endl;
}
