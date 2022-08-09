#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>

TGraphErrors *ge, *ge_neg2;

double CrossSectionFunction(double *x, double *pars)
{
    return ge_neg2->Eval(x[0]);
}

void PhotoAbsorptionCalculation(TString inputFile = "")
{
    
    ifstream DataInput;
    std::cout << "Opening " << inputFile.Data() << std::endl;
    DataInput.open(inputFile.Data());
    
    ge = new TGraphErrors();
    ge->SetName("PhotoAbsorptionGraph");
    
    ge_neg2 = new TGraphErrors();
    ge_neg2->SetName("PhotoAbsorptionGraph_neg2");
    
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
    
    ge->Draw("AP");
    ge->GetYaxis()->SetTitle("#sigma [mb]");
    ge->GetYaxis()->CenterTitle();
    ge->GetXaxis()->SetTitle("E_{#gamma} [MeV]");
    ge->GetXaxis()->CenterTitle();
    
    ge_neg2->Draw("AP");
    ge_neg2->GetYaxis()->SetTitle("#sigma/E_{#gamma}^{2} [mb/MeV^{2}]");
    ge_neg2->GetYaxis()->CenterTitle();
    ge_neg2->GetXaxis()->SetTitle("E_{#gamma} [MeV]");
    ge_neg2->GetXaxis()->CenterTitle();
    
    double sigma_neg2 = 0;
    for(int i=0;i<ge->GetN();i++)
    {
        sigma_neg2 += ge->GetPointY(i)/pow(ge->GetPointX(i),2.);
    }
    
    std::cout << "sigma(-2): " << sigma_neg2 << std::endl;
    
    std::cout << "sigma integral: " << ge->Integral() << std::endl;
    
    std::cout << "sigma_neg2 integral: " << ge_neg2->Integral() << std::endl;
    
    TF1 *func_sigma = new TF1("func_sigma",CrossSectionFunction,ge->GetPointX(0),ge->GetPointX(ge->GetN()-1));
    func_sigma->SetNpx(1e6);
    
    func_sigma->Draw("same");
    std::cout << "func_sigma integral: " << func_sigma->Integral(ge->GetPointX(0),ge->GetPointX(ge->GetN()-1)) << std::endl;
}
